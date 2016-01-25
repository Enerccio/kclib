/*
 * list.h
 *
 *  Created on: Jan 25, 2016
 *      Author: pvan
 */

#ifndef TESTS_TEST_LLIST_LIST_H_
#define TESTS_TEST_LLIST_LIST_H_

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>
#include <datastruct/llist.h>

typedef void* void_ptr_t;

LLIST_HEADER(int)
LLIST_HEADER(uint64_t)
LLIST_HEADER(void_ptr_t)


#endif /* TESTS_TEST_LLIST_LIST_H_ */
