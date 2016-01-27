/*
 * queue.h
 *
 *  Created on: Jan 26, 2016
 *      Author: enerccio
 */

#ifndef TESTS_TEST_DS_QUEUE_H_
#define TESTS_TEST_DS_QUEUE_H_

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>
#include <datastruct/queue.h>

typedef void* void_ptr_t;

QUEUE_HEADER(int)
QUEUE_HEADER(uint64_t)
QUEUE_HEADER(void_ptr_t)

#endif /* TESTS_TEST_DS_QUEUE_H_ */
