/*
 * _time.c
 *
 *  Created on: Dec 31, 2015
 *      Author: enerccio
 */

#include <time.h>
#include <sys/external.h>

clock_t clock(void) {
	return __kclib_clock();
}

double difftime(time_t time1, time_t time0) {
	return ((double)time1)-((double)time0);
}
