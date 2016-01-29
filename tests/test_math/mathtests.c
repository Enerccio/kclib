/*
 * sanity.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */

#define WEAKSYMBOLS
#include "../base/testbase.h"

#include <stdlib.h>
#include <math.h>

bool signbit_test() {
	if (signbit(1.0) != 0)
		return false;
	if (signbit(-1.0) == 0)
		return false;
	if (signbit(1.0f) != 0)
		return false;
	if (signbit(-1.0f) == 0)
		return false;
	return true;
}

bool fpclassify_test() {
	if (fpclassify(__DNAN) != FP_NAN)
		return false;
	if (fpclassify(__DINFINITY) != FP_INFINITE)
		return false;
	if (fpclassify(3.14) != FP_NORMAL)
		return false;
	if (fpclassify(0.0) != FP_ZERO)
		return false;
	if (fpclassify(-0.0) != FP_ZERO)
		return false;
	if (fpclassify(NAN) != FP_NAN)
		return false;
	if (fpclassify(INFINITY) != FP_INFINITE)
		return false;
	if (fpclassify(3.14f) != FP_NORMAL)
		return false;
	if (fpclassify(0.0f) != FP_ZERO)
		return false;
	if (fpclassify(-0.0f) != FP_ZERO)
		return false;
	return true;
}

bool sincos_test() {
	float sinfv = sinf(2);
	double sindv = sin(2);
	if (sinfv != sindv)
		return false;

	return true;
}

int run_tests() {
	TESTS_INIT;
		TESTSUITE("Math test");
		TEST("Checking signbit of different types", signbit_test);
		TEST("Checking fpclassify of different types", fpclassify_test);
		TEST("Sin/cos test", sincos_test);
	TESTS_END;
}
