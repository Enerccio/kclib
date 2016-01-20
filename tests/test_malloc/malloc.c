/*
 * sanity.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>

void* __kclib_allocate(size_t aamount) {
	return NULL;
}

void __kclib_deallocate(uintptr_t afrom, size_t aamount) {

}

int run_tests() {
	TESTS_INIT;
		TESTSUITE("Malloc test");
	TESTS_END;
}
