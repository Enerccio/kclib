/*
 * setjmp.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef SETJMP_H_
#define SETJMP_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>
#include <stdnoreturn.h>

struct jmp_buf {
	uintptr_t rbx, rbp, rsp, r12, r13, r14, r15, rip;
} __attribute__((packed));

typedef struct jmp_buf jmp_buf;

extern int setjmp(void* stack) __attribute__((returns_twice)) __attribute__((nonnull (1)));
extern _Noreturn int longjmp(void* stack, int v) __attribute__((nonnull (1)));

#define setjmp(env) setjmp(&env)
#define longjmp(env, v) longjmp(&env, v)

#ifdef __cplusplus
}
#endif

#endif /* SETJMP_H_ */
