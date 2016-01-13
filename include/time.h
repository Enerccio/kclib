/*
 * time.h
 *
 *  Created on: Dec 8, 2015
 *Author: enerccio
 */

#ifndef TIME_H_
#define TIME_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef uintmax_t time_t;
typedef size_t    clock_t;

#define CLOCKS_PER_SEC  ((clock_t) 1000000)
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC	1
#define CLOCK_PROCESS_CPUTIME_ID2
#define CLOCK_THREAD_CPUTIME_ID	3
#define CLOCK_MONOTONIC_RAW	4
#define CLOCK_REALTIME_COARSE 5
#define CLOCK_MONOTONIC_COARSE 6
#define CLOCK_BOOTTIME 7
#define CLOCK_REALTIME_ALARM 8
#define CLOCK_BOOTTIME_ALARM 9
#define CLOCK_TAI 11

struct timespec {
	time_t tv_sec; // whole seconds — ≥ 0
	long tv_nsec; // nanoseconds — [0, 999999999]
};

struct tm {
	int tm_sec; // seconds after the minute — [0, 60]
	int tm_min; // minutes after the hour — [0, 59]
	int tm_hour; // hours since midnight — [0, 23]
	int tm_mday; // day of the month — [1, 31]
	int tm_mon; // months since January — [0, 11]
	int tm_year; // years since 1900
	int tm_wday; // days since Sunday — [0, 6]
	int tm_yday; // days since January 1 — [0, 365]
	int tm_isdst; // Daylight Saving Time flag
};

clock_t clock(void);
double difftime(time_t time1, time_t time0);

#ifdef __cplusplus
}
#endif

#endif /* TIME_H_ */
