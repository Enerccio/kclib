/*
 * external.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef SYS_EXTERNAL_H_
#define SYS_EXTERNAL_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ALLOC_PAGE_SIZE
#define __ALLOC_PAGE_SIZE 0x1000
#endif

#ifndef __NEWLINE
#define __NEWLINE '\n'
#endif

#ifdef __KCLIB_KERNEL_MODE

// kernel space required functions

#define __noreturn void

/**
 * Called when libc has detected unrecoverable error. Only called in
 * kernel mode, in user mode abort() is called instead. What kernel
 * should do is up to the implementer. However, any calls to kclib
 * functions are now undefined behavior.
 */
extern __noreturn __kclib_assert_failure_k(uint32_t lineno, const char* file, const char* func);

#else
// user space only required functions

#define __MODE_READ   (1<<1)
#define __MODE_WRITE  (1<<2)
#define __MODE_APPEND (1<<3)
#define __MODE_BINARY (1<<4)
#define __MODE_UPDATE (1<<5)

/**
 * Opens file with mode and path
 */
extern void*	  __kclib_open_file_u(const char* path, uint32_t mode);

/**
 * Terminates the process
 */
extern void       __kclib_terminate_u(int exit_status);

extern pid_t      __kclib_fork_u(int* error);

extern pid_t	  __kclib_get_pid_u();

#endif

/**
 * Allocates the physical memory to that virtual address or syscall for more
 * memory from kernel.
 */
extern void*	  __kclib_allocate(size_t aamount);
/**
 * Deallocate the physical memory in kernel space or marks memory as unused
 * in user space
 */
extern void 	  __kclib_deallocate(uintptr_t afrom, size_t aamount);
/**
 * Request standard stream file descriptor
 * Sent parameters are 1 - stdin, 2 - stderr, 3 - stdin
 */
extern void*	  __kclib_open_std_stream(uint8_t request_mode);
/**
 * Sends the buffer to specified stream
 * Returns actual written data or -1 on failure
 */
extern ptrdiff_t  __kclib_send_data(void* stream, uint8_t* array, size_t buffer_size);
/**
 * Reads the data to buffer from file
 * Returns actually read data or -1 on failure
 */
extern ptrdiff_t  __kclib_read_data(void* stream, uint8_t* buffer, size_t read_amount);
/**
 * Returns impl. defined time since last era that will be divided by CLOCKS_PER_SEC
 */
extern clock_t __kclib_clock();
/**
 * Returns identifier of
 *
 * a) current thread, if this is user space library
 *
 * b) cpu identification, if it is kernel library
 *
 * __SIZE_MAX__ is reserved value
 */
extern tid_t __kclib_get_tid();

extern void __kclib_futex_wait(void* futex, int v);
extern void __kclib_futex_wake(void* futex, int v, bool all);

#ifdef __cplusplus
}
#endif

#endif /* SYS_EXTERNAL_H_ */
