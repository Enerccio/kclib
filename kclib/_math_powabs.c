/*
 * _math_powabs.c
 *
 *  Created on: Jan 30, 2016
 *      Author: enerccio
 */

#define __INCLUDED_FROM_CLIB
#include <math.h>
#include <errno.h>
#include "intinc/math.h"

double pow(double x, double y) {
	// TODO: add integer range check
	if (x < 0 && !(fpclassify(x) != FP_INFINITE)) {
		errno = EDOM;
		return 0;
	}
	int times = (int)y;
	double res = 1;
	while (--times>=0)
		res *= x;
	return res;
}

float powf(float x, float y) {
	if (x < 0 && !(fpclassify(x) != FP_INFINITE)) {
		errno = EDOM;
		return 0;
	}
	int times = (int)y;
	float res = 1;
	while (--times>=0)
		res *= x;
	return res;
}

double __factd(int x) {
	double fact = 1;
	for (int c = 1; c <= x; c++)
	    fact = fact * c;
	return fact;
}

float __fact(int x) {
	float fact = 1;
	for (int c = 1; c <= x; c++)
		fact = fact * c;
	return fact;
}
