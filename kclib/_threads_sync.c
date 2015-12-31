/*
 * _threads_sync.c
 *
 *  Created on: Dec 31, 2015
 *      Author: enerccio
 */

#include <threads.h>
#include "intinc/threads.h"

int cnd_broadcast(cnd_t* cond) {

}

void cnd_destroy(cnd_t* cond) {

}

int cnd_init(cnd_t* cond) {

}

int cnd_signal(cnd_t* cond) {

}

int cnd_timedwait(cnd_t* restrict cond, mtx_t* restrict mtx, const struct timespec* restrict ts) {

}

int cnd_wait(cnd_t* cond, mtx_t* mtx) {

}

// __kclib_get_tid()

int mtx_init(mtx_t* mtx, int type) {
	mtx->__mtx_state = 1;
	mtx->__mtx_value = 0;

	mtx->__mtx_external_id = __kclib_get_mutex_global_identifier();
	if (mtx->__mtx_external_id == __SIZE_MAX__) {
		return thrd_error;
	}

	if ((type & mtx_plain) != 0) {
		mtx->__mtx_timed = false;
		mtx->__mtx_bthread = __TID_SENTINEL_VALUE;
		if ((type & mtx_recursive) != 0) {
			mtx->__mtx_reentrant = true;
		} else {
			mtx->__mtx_reentrant = false;
		}
		return thrd_success;
	}

	return thrd_error;
}

void mtx_destroy(mtx_t* mtx) {

}

int mtx_lock(mtx_t* mtx) {
	if (mtx->__mtx_state != 1)
		return thrd_error;
	if (mtx->__mtx_reentrant) {
		tid_t mtx_state = __TID_SENTINEL_VALUE;
		tid_t this_tid = __kclib_get_tid();
		while (mtx_state == __TID_SENTINEL_VALUE) {
			mtx_state = __sync_val_compare_and_swap(&mtx->__mtx_bthread, __TID_SENTINEL_VALUE, this_tid);
			__kclib_halt(mtx->__mtx_external_id);
		}
	} else {
		int mtx_state = 0;
		while (mtx_state == 0) {
			mtx_state = __sync_val_compare_and_swap(&mtx->__mtx_state, 1, mtx_state);
			__kclib_halt(mtx->__mtx_external_id);
		}
		mtx->__mtx_bthread = __kclib_get_tid();
	}
	return thrd_success;
}

int mtx_timedlock(mtx_t* restrict mtx, const struct timespec* restrict ts) {

}

int mtx_trylock(mtx_t* mtx) {
	if (mtx->__mtx_state != 1)
			return thrd_error;
	if (mtx->__mtx_reentrant) {
		tid_t mtx_state = __TID_SENTINEL_VALUE;
		tid_t this_tid = __kclib_get_tid();
		mtx_state = __sync_val_compare_and_swap(&mtx->__mtx_bthread, __TID_SENTINEL_VALUE, this_tid);
		if (mtx_state == this_tid)
			return thrd_success;
		else
			return thrd_busy;
	} else {
		int mtx_state = 0;
		mtx_state = __sync_val_compare_and_swap(&mtx->__mtx_state, 1, mtx_state);
		if (mtx_state == 1) {
			mtx->__mtx_bthread = __kclib_get_tid();
			return thrd_success;
		} else
			return thrd_busy;
	}
}

int mtx_unlock(mtx_t* mtx) {
	tid_t this_tid = __kclib_get_tid();
	if (mtx->__mtx_reentrant) {
		if (!__sync_bool_compare_and_swap(&mtx->__mtx_bthread, this_tid, __TID_SENTINEL_VALUE)) {
			// failure to unlock its own lock
			return thrd_error;
		}
	} else {
		tid_t mtx_state = __sync_val_compare_and_swap(&mtx->__mtx_bthread,
				this_tid, __TID_SENTINEL_VALUE);
		if (mtx_state != __TID_SENTINEL_VALUE) {
			// trying to unlock other threads process, da fuk
			return thrd_error;
		}
		if (!__sync_bool_compare_and_swap(&mtx->__mtx_state, 1, 0)) {
			// failure to unlock its own lock
			return thrd_error;
		}
	}
	__kclib_mutex_unlocked(mtx->__mtx_external_id);
	return thrd_success;
}
