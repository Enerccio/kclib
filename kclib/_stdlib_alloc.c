#include <stdlib.h>
#include <threads.h>
#include "intinc/stdlib.h"

#define HEADER_MAGIC (0b011001)

typedef struct aheader {
	uintptr_t prev_chunk;
	union {
		struct {
			uintptr_t magic : 6;
			uintptr_t free  : 1;
			uintptr_t chunk : 1;
		} flags;
		uintptr_t _;
	} flags;
	size_t    size;
	uintptr_t next_chunk;
} __attribute__((__packed__)) aheader_t;

#define __ALIGN(a, v) ((a) - ((a) % (v)))
#define __ALIGN_UP(a, v) (__ALIGN(a, v) + (v))
#define __ROUND_UP(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))
#define __MINIMUM_HEAP_EXTENDED_AMOUNT 0x2000
#define __MINIMUM_CHUNK_SIZE 64

static aheader_t* malloc_address;
static mtx_t allocation_mutex;
static bool mutex_ready = false;

void __initialize_malloc() {
	malloc_address = NULL;
	mutex_ready = mtx_init(&allocation_mutex, mtx_plain) == thrd_success;
}

static aheader_t* __extend_heap(size_t size) {
	if (size < __MINIMUM_HEAP_EXTENDED_AMOUNT) {
		size = __MINIMUM_HEAP_EXTENDED_AMOUNT;
	}

	void* new_chunk = __kclib_allocate(size);
	if (new_chunk == NULL)
		return NULL;

	aheader_t* header = (aheader_t*)new_chunk;
	header->flags._ = 0;
	header->flags.flags.free = 1;
	header->flags.flags.chunk = 1;
	header->flags.flags.magic = HEADER_MAGIC;
	header->size = size-sizeof(aheader_t);
	header->next_chunk = 0;
	header->prev_chunk = 0;

	return header;
}

static void __split_chunk(aheader_t* chunk, size_t size) {
	aheader_t* next_chunk = (aheader_t*)
			(((uintptr_t)chunk)+sizeof(aheader_t)+(chunk->size - size));
	next_chunk->size = size - sizeof(aheader_t);
	next_chunk->flags.flags.free = 1;
	next_chunk->flags.flags.chunk = 0;
	next_chunk->flags.flags.magic = HEADER_MAGIC;
	next_chunk->prev_chunk = (uintptr_t) chunk;
	next_chunk->next_chunk = chunk->next_chunk;
	if (chunk->next_chunk != 0)
		((aheader_t*)chunk->next_chunk)->prev_chunk = (uintptr_t)next_chunk;
	chunk->next_chunk = (uintptr_t)next_chunk;
	chunk->size -= size;
}

static void* __malloc(size_t size) {
	size_t total_size = size + sizeof(aheader_t) + 16;

	aheader_t** chunk = &malloc_address;
	aheader_t* free_chunk = NULL;
	aheader_t* pc = NULL;
	while ((*chunk) != NULL) {
		if ((*chunk)->flags.flags.magic != HEADER_MAGIC) {
			// TODO: Abort
			return 0;
		}

		if ((*chunk)->flags.flags.free && (*chunk)->size>=total_size) {
			free_chunk = *chunk;
			break;
		}
		pc = *chunk;
		chunk = (aheader_t**)&((*chunk)->next_chunk);
	}

	if (free_chunk == NULL) {
		*chunk = __extend_heap(total_size);

		if (*chunk == NULL)
			return NULL;

		free_chunk = *chunk;
		if (pc != NULL) {
			pc->next_chunk = (uintptr_t)free_chunk;
			free_chunk->prev_chunk = (uintptr_t)pc;
		}
	}

	free_chunk->flags.flags.free = 0;
	uintptr_t pos = ((uintptr_t)free_chunk);
	pos += size;
	pos = __ALIGN_UP(pos, 16);
	pos -= ((uintptr_t)free_chunk);

	size_t remaining_size = free_chunk->size - pos;
	if (remaining_size >= __MINIMUM_CHUNK_SIZE) {
		__split_chunk(free_chunk, remaining_size);
	}

	void* address = (void*) (((uintptr_t)free_chunk) + sizeof(aheader_t));
	memset(address, 0xDC, size);

	return address;
}

void* malloc(size_t s) {
	if (mutex_ready) {
		mtx_lock(&allocation_mutex);
	}
	void* mv = __malloc(s);
	if (mutex_ready) {
		mtx_unlock(&allocation_mutex);
	}
	return mv;
}

static void __free(void* ptr){
	aheader_t* chunk = &((aheader_t*)ptr)[-1];
	if (chunk->flags.flags.magic != HEADER_MAGIC) {
		return; // TODO: abort
	}
	chunk->flags.flags.free = 1;
	memset(ptr, 0xCD, chunk->size);

	aheader_t* nchunk = (aheader_t*)chunk->next_chunk;
	aheader_t* lvchunk = NULL;
	while (true) {
		if (nchunk == 0)
			break;
		lvchunk = nchunk;
		if (nchunk->flags.flags.chunk) {
			// next is allocator chunk, stop this
			break;
		}
		if (nchunk->flags.flags.free) {
			// chunk is free
			chunk->size += sizeof(aheader_t) + nchunk->size;
			nchunk->flags.flags.magic = 0;
			chunk->next_chunk = nchunk->next_chunk;
			if (nchunk->next_chunk != 0) {
				((aheader_t*)nchunk->next_chunk)->prev_chunk = (uintptr_t)chunk;
			}
			lvchunk = NULL;
			nchunk = chunk;
		} else {
			break;
		}

		nchunk = (aheader_t*)nchunk->next_chunk;
	}

	aheader_t* pchunk;
	while (true) {
		pchunk = (aheader_t*)chunk->prev_chunk;
		if (!chunk->flags.flags.free) {
			// filled chunk, we are done
			return;
		}
		if (pchunk == NULL || chunk->flags.flags.chunk) {
			// this is first chunk or NULL
			if (lvchunk == NULL || lvchunk->flags.flags.chunk) {
				if (pchunk == NULL) {
					malloc_address = lvchunk;
					if (lvchunk != NULL) {
						lvchunk->prev_chunk = 0;
					}
				} else {
					pchunk->next_chunk = (uintptr_t)lvchunk;
					if (lvchunk != NULL) {
						lvchunk->prev_chunk = (uintptr_t)pchunk;
					}
				}
				__kclib_deallocate((uintptr_t)chunk, chunk->size+sizeof(aheader_t));
			}
			return;
		}
		if (pchunk->flags.flags.free) {
			// chunk is free
			pchunk->size += sizeof(aheader_t) + chunk->size;
			pchunk->next_chunk = (uintptr_t)lvchunk;
			chunk->flags.flags.magic = 0;
			if (lvchunk != NULL) {
				lvchunk->prev_chunk = (uintptr_t)pchunk;
			}
		}
		chunk = (aheader_t*)chunk->prev_chunk;
	}
}

void free(void* ptr){
	if (mutex_ready) {
		mtx_lock(&allocation_mutex);
	}
	__free(ptr);
	if (mutex_ready) {
		mtx_unlock(&allocation_mutex);
	}
}

void* calloc(size_t nmemb, size_t size) {
	if (size == 0)
		return NULL;
	if (nmemb == 0)
		return NULL;

	void* data = malloc(nmemb * size);
	if (data == NULL)
		return NULL;

	memset(data, 0, nmemb * size);
	return data;
}

static void* __realloc(void* ptr, size_t size) {
	aheader_t* chunk = &((aheader_t*)ptr)[-1];

	uintptr_t pos = ((uintptr_t)chunk);
	pos += size;
	pos = __ALIGN_UP(pos, 16);
	pos -= ((uintptr_t)chunk);

	size_t remaining_size = chunk->size - pos;

	if (chunk->size > size && remaining_size >= __MINIMUM_CHUNK_SIZE) {
		__split_chunk(chunk, remaining_size);
		return ptr;
	} else if (chunk->size >= size){
		return ptr;
	} else {
		void* new_address = malloc(size);
		if (new_address == NULL)
			return NULL;
		memcpy(ptr, new_address, chunk->size);
		free(ptr);
		return new_address;
	}
}

void* realloc(void *ptr, size_t size) {
	if (size == 0){
		free(ptr);
		return NULL;
	}
	if (mutex_ready) {
		mtx_lock(&allocation_mutex);
	}
	void* rv = __realloc(ptr, size);
	if (mutex_ready) {
		mtx_unlock(&allocation_mutex);
	}
	return rv;
}
