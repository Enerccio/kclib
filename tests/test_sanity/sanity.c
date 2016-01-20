/*
 * sanity.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */

#include "../base/testbase.h"

bool sanity_test() {
	return true;
}

int run_tests() {
	TESTS_INIT;
		TESTSUITE("Sanity test");
		TEST("Checking if environment is sane", sanity_test);
	TESTS_END;
}
