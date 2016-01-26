/*
 * array.h
 *
 *  Created on: Jan 26, 2016
 *      Author: enerccio
 */

#ifndef TESTS_TEST_DS_ARRAY_H_
#define TESTS_TEST_DS_ARRAY_H_

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>
#include <datastruct/array.h>

typedef void* void_ptr_t;

ARRAY_HEADER(int)
ARRAY_HEADER(uint64_t)
ARRAY_HEADER(void_ptr_t)

#endif /* TESTS_TEST_DS_ARRAY_H_ */
