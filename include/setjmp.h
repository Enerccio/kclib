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
	uintptr_t stack, frame;
};

typedef struct jmp_buf jmp_buf;

#define setjmp(env) _setjmp(&env)
#define longjmp(env, v) _longjmp(&env, v)

int _setjmp(jmp_buf* env);
_Noreturn void _longjmp(jmp_buf* env, int val);

#ifdef __cplusplus
}
#endif

#endif /* SETJMP_H_ */
