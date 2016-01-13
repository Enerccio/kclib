/*
 * _threads_tss.c
 *
 *  Created on: Dec 31, 2015
 *      Author: enerccio
 */

#include <threads.h>
#include <sys/external.h>

int tss_create(tss_t* key, tss_dtor_t dtor) {
	return thrd_error;
}

void tss_delete(tss_t key) {

}

void* tss_get(tss_t key) {
	return NULL;
}

int tss_set(tss_t key, void *val) {
	return thrd_error;
}
