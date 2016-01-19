/*
 * _threads_sync.c
 *
 *  Created on: Dec 31, 2015
 *      Author: enerccio
 */

#include <threads.h>
#include <sys/external.h>
#include "intinc/threads.h"

int cnd_broadcast(cnd_t* cond) {
	return thrd_error;
}

void cnd_destroy(cnd_t* cond) {

}

int cnd_init(cnd_t* cond) {
	return thrd_error;
}

int cnd_signal(cnd_t* cond) {
	return thrd_error;
}

int cnd_timedwait(cnd_t* restrict cond, mtx_t* restrict mtx, const struct timespec* restrict ts) {
	return thrd_error;
}

int cnd_wait(cnd_t* cond, mtx_t* mtx) {
	return thrd_error;
}

int mtx_init(mtx_t* mtx, int type) {
	mtx->__mtx_state.lock = 0;
	mtx->__mtx_bthread = __TID_MAX__;
	mtx->__mtx_reentrant = false;
	mtx->__mtx_timed = false;

	if ((type & mtx_recursive) != 0) {
		// TODO
		return thrd_error;
	}

	if ((type & mtx_timed) != 0) {
		// TODO
		return thrd_error;
	}

	return thrd_success;
}

void mtx_destroy(mtx_t* mtx) {

}

int mtx_lock(mtx_t* mtx) {
	for (int i=0; i<100; i++) {
		if (!__atomic_exchange_n(&mtx->__mtx_state.state.locked, 1, __ATOMIC_SEQ_CST)) {
			mtx->__mtx_bthread = __kclib_get_tid();
			return thrd_success;
		}

		__asm__ __volatile__ ("\tpause\n");
	}

	while (__atomic_exchange_n(&mtx->__mtx_state.lock, 257, __ATOMIC_SEQ_CST) & 1) {
		__kclib_futex_wait((void*)&mtx->__mtx_state, 257);
	}

	mtx->__mtx_bthread = __kclib_get_tid();
	return thrd_success;
}

int mtx_timedlock(mtx_t* restrict mtx, const struct timespec* restrict ts) {
	return thrd_error;
}

int mtx_trylock(mtx_t* mtx) {
	uint8_t state = __atomic_exchange_n(&mtx->__mtx_state.state.locked, 1, __ATOMIC_SEQ_CST);
	if (!state)
		return thrd_success;
	else
		return thrd_busy;
}

int mtx_unlock(mtx_t* mtx) {
	tid_t this_tid = __kclib_get_tid();
	tid_t mtx_state = __atomic_load_n(&mtx->__mtx_bthread, __ATOMIC_SEQ_CST);

	if (mtx_state != this_tid) {
		// trying to unlock other threads process, da fuk
		return thrd_error;
	}

	uint32_t expected = 1;

	mtx->__mtx_bthread = __TID_MAX__;
	if (mtx->__mtx_state.lock == 1 &&
			__atomic_compare_exchange_n(&mtx->__mtx_state.lock, &expected, 0,
					false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
		return thrd_success;

	__asm__ __volatile__ ("" : : :"memory");

	for (int i=0; i<200; i++) {
		if (mtx->__mtx_state.state.locked) {
			return thrd_success;
		}

		__asm__ __volatile__ ("\tpause\n");
	}

	mtx->__mtx_state.state.contented = 0;
	__kclib_futex_wake((void*)&mtx->__mtx_state, 1);

	return thrd_success;
}
