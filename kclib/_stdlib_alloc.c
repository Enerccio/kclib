#include <stdlib.h>
#include "intinc/stdlib.h"

typedef struct aheader {
	uintptr_t prev_chunk;
	uintptr_t free;
	size_t    size;
	uintptr_t next_chunk;
} __attribute__((__packed__)) aheader_t;

#define __ALIGN(a, v) ((a) - ((a) % (v)))
#define __ALIGN_UP(a, v) (__ALIGN(a, v) + (v))
#define __ROUND_UP(a, b) (((a) / (b)) + (((a) % (b)) > 0 ? 1 : 0))
#define __MINIMUM_HEAP_EXTENDED_AMOUNT 0x2000
#define __MINIMUM_CHUNK_SIZE 64

aheader_t* malloc_address;

void __initialize_malloc() {
	malloc_address = NULL;
}

aheader_t* __extend_heap(size_t size) {
	if (size < __MINIMUM_HEAP_EXTENDED_AMOUNT) {
		size = __MINIMUM_HEAP_EXTENDED_AMOUNT;
	}

	void* new_chunk = __kclib_allocate(size);
	if (new_chunk == NULL)
		return NULL;

	aheader_t* header = (aheader_t*)new_chunk;
	header->free = 1<<1;
	header->size = size-sizeof(aheader_t);
	header->next_chunk = 0;

	return header;
}

void __split_chunk(aheader_t* chunk, size_t size) {
	aheader_t* next_chunk = (aheader_t*)
			(((uintptr_t)chunk)+sizeof(aheader_t)+size);
	next_chunk->size = chunk->size - size - sizeof(aheader_t);
	next_chunk->free = 1<<1;
	next_chunk->prev_chunk = (uintptr_t) chunk;
	next_chunk->next_chunk = chunk->next_chunk;
	if (chunk->next_chunk != 0)
		((aheader_t*)chunk->next_chunk)->prev_chunk = (uintptr_t)next_chunk;
	chunk->next_chunk = (uintptr_t)next_chunk;
}

void* __malloc(size_t size) {
	size_t total_size = __ALIGN_UP(size + sizeof(aheader_t), 16);

	aheader_t** chunk = &malloc_address;
	aheader_t* free_chunk = NULL;
	aheader_t* pc = NULL;
	while ((*chunk) != NULL) {
		if ((((*chunk)->free & ((1<<1))) != 0) && (*chunk)->size>=total_size) {
			free_chunk = *chunk;
			break;
		}
		pc = *chunk;
		if ((*chunk)->next_chunk == NULL)
			break;
		chunk = (aheader_t**)&((*chunk)->next_chunk);
	}

	if (free_chunk == NULL) {
		*chunk = __extend_heap(total_size);

		if (*chunk == NULL)
			return NULL;

		free_chunk = *chunk;
		free_chunk->free |= (1<<2);
		if (pc != NULL) {
			pc->next_chunk = (uintptr_t)free_chunk;
			free_chunk->prev_chunk = (uintptr_t)pc;
		}
	}

	free_chunk->free &= ~(1<<1);
	if (free_chunk->size - size >= __MINIMUM_CHUNK_SIZE) {
		__split_chunk(free_chunk, size);
	}

	void* address = (void*) (((uintptr_t)free_chunk) + sizeof(aheader_t));
	memset(address, 0xDC, size);

	return address;
}

void* malloc(size_t s){
	return __malloc(s);
}

void __free(void* ptr){
	aheader_t* chunk = &((aheader_t*)ptr)[-1];
	chunk->free |= (1<<1);
	memset(ptr, 0xCD, chunk->size);

	aheader_t* nchunk = (aheader_t*)chunk->next_chunk;
	while (true) {
		if (nchunk == 0)
			break;
		if ((nchunk->free & ((1<<2))) != 0) {
			// next is allocator chunk, stop this
			break;
		}
		if ((nchunk->free & ((1<<1))) != 0) {
			// chunk is free
			chunk->size += sizeof(aheader_t) + nchunk->size;
			chunk->next_chunk = nchunk->next_chunk;
		}
		nchunk = (aheader_t*)chunk->next_chunk;
		if (nchunk != 0) {
			((aheader_t*)nchunk)->prev_chunk = (uintptr_t)chunk;
		}
	}

	aheader_t* pchunk = (aheader_t*)chunk->prev_chunk;
	if (pchunk == NULL || ((chunk->free & ((1<<2))) != 0)) {
		// this is first chunk or NULL
		if (nchunk == NULL || ((nchunk->free & ((1<<2))) != 0)) {
			__kclib_deallocate((uintptr_t)chunk, chunk->size+sizeof(aheader_t));
			if (pchunk == NULL) {
				malloc_address = nchunk;
			} else {
				pchunk->next_chunk = (uintptr_t)nchunk;
			}
		}

	}
}

void free(void* ptr){
	__free(ptr);
}

void* calloc(size_t nmemb, size_t size){
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

void* __realloc(void* ptr, size_t size){
	aheader_t* chunk = &((aheader_t*)ptr)[-1];
	if (chunk->size > size && chunk->size-size >= __MINIMUM_CHUNK_SIZE) {
		__split_chunk(chunk, size);
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

void* realloc(void *ptr, size_t size){
	if (size == 0){
		free(ptr);
		return NULL;
	}
	return __realloc(ptr, size);
}
