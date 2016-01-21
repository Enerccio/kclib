/*
 * sanity.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>

#define NUMTESTS 3
#define TEST_COUNT (2000*NUMTESTS)
uint64_t tests[TEST_COUNT];
size_t itc = 0;
bool failure = false;

void* __kclib_allocate(size_t aamount) {
	if (aamount > 8224) {
		failure = true;
	}
	void* rv;
	__asm__ __volatile__ (
			"   mov $0x22, %%r10\n"
			"   mov $-1, %%r8		\n"
			"   xor %%r9, %%r9 		\n"
			"   syscall				\n"
			: "=a" (rv)
			: "a" (9), "D"(0), "S" (aamount), "rdx" (0x2|0x1)
			: "cc", "rcx", "r11", "memory"
	);
	tests[itc++] = (uint64_t)rv;
	return rv;
}

void __kclib_deallocate(uintptr_t afrom, size_t aamount) {
	if (aamount > 8224) {
		failure = true;
	}

	bool f = true;
	for (int i=0; i<TEST_COUNT; i++) {
		if (tests[i] == afrom && f) {
			tests[i] = 0;
			f = false;
		} else if (tests[i] == afrom) {
			failure = true;
			return;
		}
	}
	if (f) {
		failure = true;
		return;
	}

	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(11), "D"(afrom), "S" (aamount)
			: "cc", "rcx", "r11", "memory"
	);
}

bool endcheck() {
	if (failure)
		return false;
	for (int i=0; i<TEST_COUNT; i++)
		if (tests[i] != 0)
			return false;
	return true;
}

bool malloc_simple_test() {
	void* addr = malloc(0x2000);
	srand((uintptr_t)addr);
	free(addr);

	return endcheck();
}

bool malloc_mf_complex_test() {
	void* array[TEST_COUNT/NUMTESTS];
	for (int i=0; i<TEST_COUNT/NUMTESTS; i++)
		array[i] = 0;

	for (int i=0; i<TEST_COUNT/NUMTESTS; i++) {
		array[i] = malloc((rand()%0x2000));
	}

	for (int i=0; i<TEST_COUNT/NUMTESTS; i++) {
		free(array[i]);
	}

	return endcheck();
}

bool malloc_mf_complex_random_test() {
	void* array[TEST_COUNT/NUMTESTS];
	for (int i=0; i<TEST_COUNT/NUMTESTS; i++)
		array[i] = 0;

	for (int i=0; i<TEST_COUNT/NUMTESTS; i++) {
		array[i] = malloc((rand()%0x2000));
	}

	shuffle(array, TEST_COUNT/NUMTESTS);

	for (int i=0; i<TEST_COUNT/NUMTESTS; i++) {
		free(array[i]);
	}

	return endcheck();
}

int run_tests() {
	TESTS_INIT;
		TESTSUITE("_stdlib_alloc test");
		for (int i=0; i<TEST_COUNT; i++)
			tests[i] = 0;
		TEST("Checking malloc/free simple test", malloc_simple_test);
		TEST("Checking malloc/free complex test", malloc_mf_complex_test);
		TEST("Checking malloc/free complex random order test", malloc_mf_complex_random_test);
	TESTS_END;
}
