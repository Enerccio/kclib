/*
 * testbase.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */


#include "testbase.h"

void* __kclib_open_file_u(const char* path, uint32_t mode) {
	return NULL;
}

void __kclib_terminate_u(int exit_status) {

}

pid_t __kclib_get_pid_u() {
	return 0;
}

thrd_t* __kclib_get_thread_structure_addr_u() {
	return NULL;
}

void* __kclib_allocate(size_t aamount) {
	return NULL;
}

void __kclib_deallocate(uintptr_t afrom, size_t aamount) {

}

void* __kclib_open_std_stream(uint8_t request_mode) {
	return NULL;
}

ptrdiff_t  __kclib_send_data(void* stream, uint8_t* array, size_t buffer_size) {
	return 0;
}

ptrdiff_t  __kclib_read_data(void* stream, uint8_t* buffer, size_t read_amount) {
	return 0;
}

clock_t __kclib_clock() {
	return 0;
}

tid_t __kclib_get_tid() {
	return 0;
}

void __kclib_futex_wait(void* futex, int v) {

}

void __kclib_futex_wake(void* futex, int v) {

}

void ___exit(int x) {
	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(60), "D"((long)x)
			: "cc", "rcx", "r11", "memory"
	);
}

void ___output(const char* message, size_t chlen, bool err) {
	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(1), "D"((long)err? 2 : 0), "S" (message), "rdx" (chlen)
			: "cc", "rcx", "r11", "memory"
	);
	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(74), "D"((long)err? 2 : 0)
			: "cc", "rcx", "r11", "memory"
	);
}

void shuffle(void** array, size_t l) {
	for (size_t i=0; i<l-2; i++) {
		size_t j = rand()%(l-i);
		void* tmp = array[i];
		array[i] = array[i+j];
		array[i+j] = tmp;
	}
}

extern int run_tests();
int testmain(int argc, char** argv) {
	return run_tests();
}
