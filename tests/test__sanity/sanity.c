/*
 * sanity.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>

#define MEMBYTES (8096*3)
unsigned char array[MEMBYTES];
unsigned char arrayu[MEMBYTES];

unsigned int cp;

void* __kclib_allocate(size_t aamount) {
	unsigned char* apos = &array[cp];
	for (unsigned int i=cp; i<cp+aamount; i++)
		arrayu[i] = 255;
	cp += aamount;
	return apos;
}

void __kclib_deallocate(uintptr_t afrom, size_t aamount) {
	size_t it = afrom-(uintptr_t)array;
	for (unsigned int i=it; i<it+aamount; i++)
		arrayu[i] = 0;
}

bool sanity_test() {
	return true;
}

extern void __initialize_malloc();
bool malloc_test() {
	__initialize_malloc();
	void* memory1 = malloc(10);
	if (memory1 == NULL)
		return false;
	void* memory2 = malloc(100);
	if (memory2 == NULL)
		return false;
	void* memory3 = malloc(1000);
	if (memory3 == NULL)
		return false;
	void* memory4 = malloc(10000);
	if (memory4 == NULL)
		return false;
	free(memory1);
	free(memory2);
	free(memory3);
	free(memory4);
	for (int i=0; i<MEMBYTES; i++) {
		if (arrayu[i] != 0)
			return false;
	}
	return true;
}

int run_tests() {
	cp = 0;
	for (int i=0; i<MEMBYTES; i++) {
		array[i] = 0;
		arrayu[i] = 0;
	}

	TESTS_INIT;
		TESTSUITE("Sanity test");
		TEST("Checking if environment is sane", sanity_test);
		TEST("Checking if malloc is working", malloc_test);
		cp = 0;
	TESTS_END;
}
