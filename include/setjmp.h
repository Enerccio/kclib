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

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdbool.h>
#include <stdnoreturn.h>

struct jmp_buf {
	uintptr_t rbx, rbp, rsp, r12, r13, r14, r15, rip;
} __attribute__((packed));

typedef struct jmp_buf jmp_buf;

extern int __set_jump(void* stack);
extern _Noreturn int __long_jump(void* stack, int v);

#define setjmp(env) __set_jump(&env)
#define longjmp(env, v) __long_jump(&env, v)

#ifdef __cplusplus
}
#endif

#endif /* SETJMP_H_ */
