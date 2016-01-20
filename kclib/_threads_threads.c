/*
 * _threads_threads.c
 *
 *  Created on: Dec 31, 2015
 *      Author: enerccio
 */

#include <threads.h>
#include <stdlib.h>
#include <sys/external.h>

#include "intinc/threads.h"

int thrd_create(thrd_t* thr, thrd_start_t func, void* arg) {
	return thrd_error;
}

thrd_t thrd_current(void) {
	return *__kclib_get_thread_structure_addr_u();
}

int thrd_detach(thrd_t thr) {
	return thrd_error;
}

int thrd_equal(thrd_t thr0, thrd_t thr1) {
	return thrd_error;
}

_Noreturn void thrd_exit(int res) {
	while (true) ;
}

int thrd_join(thrd_t thr, int* res) {
	return thrd_error;
}

int thrd_sleep(const struct timespec* duration, struct timespec* remaining) {
	return thrd_error;
}

void thrd_yield(void) {

}

void __initialize_threading(thrd_t ct) {
	ct->pid = __kclib_get_pid_u();
	ct->tid = __kclib_get_tid();

	thrd_t* saveloc = __kclib_get_thread_structure_addr_u();
	*saveloc = ct;
}
