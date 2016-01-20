/*
 * testbase.h
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */

#ifndef TESTS_BASE_TESTBASE_H_
#define TESTS_BASE_TESTBASE_H_

#include <sys/external.h>

void* __kclib_open_file_u(const char* path, uint32_t mode) __attribute__((weak));
void __kclib_terminate_u(int exit_status) __attribute__((weak));
pid_t __kclib_get_pid_u() __attribute__((weak));
thrd_t* __kclib_get_thread_structure_addr_u() __attribute__((weak));
void* __kclib_allocate(size_t aamount) __attribute__((weak));
void __kclib_deallocate(uintptr_t afrom, size_t aamount) __attribute__((weak));
void* __kclib_open_std_stream(uint8_t request_mode) __attribute__((weak));
ptrdiff_t  __kclib_send_data(void* stream, uint8_t* array, size_t buffer_size) __attribute__((weak));
ptrdiff_t  __kclib_read_data(void* stream, uint8_t* buffer, size_t read_amount) __attribute__((weak));
clock_t __kclib_clock() __attribute__((weak));
tid_t __kclib_get_tid() __attribute__((weak));
void __kclib_futex_wait(void* futex, int v) __attribute__((weak));
void __kclib_futex_wake(void* futex, int v) __attribute__((weak));

void ___exit(int x);
void ___output(const char* message, size_t chlen);

#define TEST(testname, fnc, ...) __TEST(fnc, testname, __DATE__, __TIME__, __FILE__, __LINE__, __VA_ARGS__)
#define __TEST(fnc, testname, date, time, file, line, ...) \
	do {\
		if (fnc(__VA_ARGS__) == 1) { \
			___output(__SUCCESS(testname, date, time, file, line), sizeof(__SUCCESS(testname, date, time, file, line))); \
		} else { \
			___output(__FAILURE(testname, date, time, file, line), sizeof(__SUCCESS(testname, date, time, file, line))); \
			ret = 1; \
		} \
	} while (0)
#define __SUCCESS(testname, date, time, file, line) __GENERAL_INFO(testname, date, time, file, line) "- passed \n"
#define __FAILURE(testname, date, time, file, line) __GENERAL_INFO(testname, date, time, file, line) "- failed \n"
#define __GENERAL_INFO(tn, d, ti, fi, li) d ", " ti ": " tn " (at " fi ", " #li ") "

#define TESTS_INIT { \
	int ret = 0;
#define TESTS_END \
	return ret; \
	}

#endif /* TESTS_BASE_TESTBASE_H_ */
