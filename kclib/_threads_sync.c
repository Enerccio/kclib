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
		tid_t mtx_state;
		tid_t this_tid = __kclib_get_tid();
		while (true) {
			mtx_state = __TID_SENTINEL_VALUE;
			bool success = __atomic_compare_exchange_n(&mtx->__mtx_bthread, &mtx_state,
					this_tid, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
			if (success || mtx_state == this_tid)
				break;
			__kclib_mutex_halt(mtx->__mtx_external_id);
		}
	} else {
		int mtx_state;
		while (true) {
			mtx_state = 0;
			bool success = __atomic_compare_exchange_n(&mtx->__mtx_state, &mtx_state,
								1, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
			if (success)
				break;
			__kclib_mutex_halt(mtx->__mtx_external_id);
		}
		__atomic_store_n(&mtx->__mtx_bthread, __kclib_get_tid(), __ATOMIC_SEQ_CST);
	}
	return thrd_success;
}

int mtx_timedlock(mtx_t* restrict mtx, const struct timespec* restrict ts) {
	return thrd_error;
}

int mtx_trylock(mtx_t* mtx) {
	if (mtx->__mtx_state != 1)
			return thrd_error;
	if (mtx->__mtx_reentrant) {
		tid_t mtx_state = __TID_SENTINEL_VALUE;
		tid_t this_tid = __kclib_get_tid();
		bool success = __atomic_compare_exchange_n(&mtx->__mtx_bthread, &mtx_state,
							this_tid, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
		if (success || mtx_state == this_tid)
			return thrd_success;
		else
			return thrd_busy;
	} else {
		int mtx_state = 0;
		mtx_state = 0;
		bool success = __atomic_compare_exchange_n(&mtx->__mtx_state, &mtx_state,
							1, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
		if (success) {
			__atomic_store_n(&mtx->__mtx_bthread, __kclib_get_tid(), __ATOMIC_SEQ_CST);
			return thrd_success;
		} else
			return thrd_busy;
	}
}

int mtx_unlock(mtx_t* mtx) {
	tid_t this_tid = __kclib_get_tid();
	if (mtx->__mtx_reentrant) {
		if (__atomic_exchange_n(&mtx->__mtx_bthread,
				__TID_SENTINEL_VALUE, __ATOMIC_SEQ_CST) != this_tid) {
			// unlocked the mutex, but failed to get his own tid back mean some bug
			return thrd_error;
		}
	} else {
		tid_t mtx_state = __atomic_load_n(&mtx->__mtx_bthread, __ATOMIC_SEQ_CST);
		if (mtx_state != this_tid) {
			// trying to unlock other threads process, da fuk
			return thrd_error;
		}
		__atomic_store_n(&mtx->__mtx_bthread, __TID_SENTINEL_VALUE, __ATOMIC_SEQ_CST);
		if (__atomic_exchange_n(&mtx->__mtx_state,
				0, __ATOMIC_SEQ_CST) != 1) {
			// unlocked the mutex, but it was not locked before, which is an error
			return thrd_error;
		}
	}
	__kclib_mutex_unlocked(mtx->__mtx_external_id);
	return thrd_success;
}
