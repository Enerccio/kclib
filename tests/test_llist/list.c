/*
 * list.c
 *
 *  Created on: Jan 25, 2016
 *      Author: pvan
 */

#include "list.h"

LLIST_FUNCDEFS(int)

int run_tests() {
	TESTS_INIT;
		TESTSUITE("linked list test");

	TESTS_END;
}
