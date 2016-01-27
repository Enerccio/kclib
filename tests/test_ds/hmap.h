/*
 * hmap.h
 *
 *  Created on: Jan 26, 2016
 *      Author: enerccio
 */

#ifndef TESTS_TEST_DS_HMAP_H_
#define TESTS_TEST_DS_HMAP_H_

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>
#include <datastruct/hmap.h>

typedef void* void_ptr_t;

HMAP_HEADER(int, int)
HMAP_HEADER(uint64_t, int)
HMAP_HEADER(void_ptr_t, int)

#endif /* TESTS_TEST_DS_HMAP_H_ */
