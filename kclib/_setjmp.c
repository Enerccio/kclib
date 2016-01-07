/*
 * _setjmp.c
 *
 *  Created on: Jan 7, 2016
 *      Author: enerccio
 */

#include <setjmp.h>

extern int __set_jump(void* stack, void* instruction, void* frame);
extern _Noreturn int __long_jump(void* stack, void* instruction, void* frame, int v);

int _setjmp(jmp_buf* env) {
	return __set_jump(&env->stack, &env->operation, &env->frame);
}

_Noreturn void _longjmp(jmp_buf* env, int val) {
	__long_jump(&env->stack, &env->operation, &env->frame, val);
}
