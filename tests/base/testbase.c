/*
 * testbase.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */


#include "testbase.h"

void ___exit(int x) {
	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(60), "D"((long)x)
			: "cc", "rcx", "r11", "memory"
	);
}

void ___output(const char* message, size_t chlen) {
	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(1), "D"((long)0), "S" (message), "rdx" (chlen)
			: "cc", "rcx", "r11", "memory"
	);
}

extern int run_tests();
int testmain(int argc, char** argv) {
	return run_tests();
}
