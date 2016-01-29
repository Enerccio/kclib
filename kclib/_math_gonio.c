/*
 * _math_classify.c
 *
 *  Created on: Jan 29, 2016
 *      Author: enerccio
 */

#define __INCLUDED_FROM_CLIB
#include <math.h>
#include "intinc/math.h"

#ifndef __APPROX_COUNT_D
#define __APPROX_COUNT_D (9)
#endif
#ifndef __APPROX_COUNT_F
#define __APPROX_COUNT_F (8)
#endif

double sin(double x) {
	double sinv = x;
	unsigned int ex = 3;

	for (int i=1; i<__APPROX_COUNT_D+1; i++) {
		if (i % 2 == 1) {
			sinv -= pow(x, ex)/__factd(ex);
		} else {
			sinv += pow(x, ex)/__factd(ex);
		}
		ex += 2;
	}
	return sinv;
}

float sinf(float x) {
	float sinv = x;
	unsigned int ex = 3;

	for (int i=1; i<__APPROX_COUNT_F+1; i++) {
		if (i % 2 == 1) {
			sinv -= powf(x, ex)/__fact(ex);
		} else {
			sinv += powf(x, ex)/__fact(ex);
		}
		ex += 2;
	}
	return sinv;
}
