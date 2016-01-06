/*
 * sys_unistd.c
 *
 *  Created on: Jan 6, 2016
 *      Author: enerccio
 */

#include <sys/unistd.h>
#include <sys/external.h>
#include <errno.h>

pid_t fork(void) {
#ifdef __KCLIB_KERNEL_MODE
	errno = ENOPROC;
	return 0;
#else
	int e = 0;
	tid_t t = __kclib_fork_u(&e);
	if (e != 0) {
		errno = e;
	}
	return t;
#endif
}
