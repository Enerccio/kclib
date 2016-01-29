/*
 * threads.h
 *
 *  Created on: Dec 31, 2015
 *      Author: enerccio
 */

#ifndef INCLUDE_THREADS_H_
#define INCLUDE_THREADS_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#include <sys/kclib.h>
#include <time.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdnoreturn.h>
#include <stddef.h>

typedef size_t mtx_id_t;
typedef size_t pid_t;
typedef size_t tid_t;
#define __TID_MAX__ __SIZE_MAX__

#ifndef SSIZE_MAX
#define SSIZE_MAX INTMAX_MAX
#endif

#define thread_local _Thread_local;
#define ONCE_FLAG_INIT (0)
#define TSS_DTOR_ITERATIONS (4096)

typedef struct cnd cnd_t;
typedef struct thrd* thrd_t;
typedef struct tss tss_t;
typedef struct mtx mtx_t;
typedef struct once_flag once_flag;

typedef void (*tss_dtor_t)  (void*);
typedef int  (*thrd_start_t)(void*);

#define mtx_plain     (1<<0)
#define mtx_recursive (1<<1)
#define mtx_timed     (1<<2)

#define thrd_success  0
#define thrd_timedout 1
#define thrd_busy     2
#define thrd_error   -1
#define thrd_nomem   -2

struct mtx {
	/* internal state of mutex, 1 if valid mutex */
	volatile union {
		uint32_t lock;
		struct {
			uint8_t locked;
			uint8_t contented;
		} state;
	} __mtx_state;


	/* type of mutex */
	volatile bool      __mtx_reentrant; // TODO
	volatile bool      __mtx_timed;

	/* mutex lock values */
	volatile tid_t     __mtx_bthread;
};

struct cnd {

};

struct tss {

};

struct once_flag {

};

struct thrd {
	pid_t pid;
	tid_t tid;
};

// _threads_co.c
void call_once(once_flag* flag, void (*func)(void));
// _threads_sync.c
int cnd_broadcast(cnd_t* cond) __attribute__((nonnull (1)));
void cnd_destroy(cnd_t* cond) __attribute__((nonnull (1)));
int cnd_init(cnd_t* cond) __attribute__((nonnull (1)));
int cnd_signal(cnd_t* cond) __attribute__((nonnull (1)));
int cnd_timedwait(cnd_t* restrict cond, mtx_t* restrict mtx, const struct timespec* restrict ts)
	__attribute__((nonnull (1, 2, 3)));
int cnd_wait(cnd_t* cond, mtx_t* mtx) __attribute__((nonnull (1, 2)));
void mtx_destroy(mtx_t* mtx) __attribute__((nonnull (1)));
int mtx_init(mtx_t* mtx, int type) __attribute__((nonnull (1)));
int mtx_lock(mtx_t* mtx) __attribute__((nonnull (1)));
int mtx_timedlock(mtx_t* restrict mtx, const struct timespec* restrict ts) __attribute__((nonnull (1, 2)));
int mtx_trylock(mtx_t* mtx) __attribute__((nonnull (1)));
int mtx_unlock(mtx_t* mtx) __attribute__((nonnull (1)));
// _threads_threads.c
int thrd_create(thrd_t* thr, thrd_start_t func, void* arg) __attribute__((nonnull (1, 3)));
thrd_t thrd_current(void);
int thrd_detach(thrd_t thr);
int thrd_equal(thrd_t thr0, thrd_t thr1);
_Noreturn void thrd_exit(int res);
int thrd_join(thrd_t thr, int* res) __attribute__((nonnull (2)));
int thrd_sleep(const struct timespec* duration, struct timespec* remaining) __attribute__((nonnull (1, 2)));
void thrd_yield(void);
// _threads_tss.c
int tss_create(tss_t* key, tss_dtor_t dtor) __attribute__((nonnull (1)));
void tss_delete(tss_t key);
void* tss_get(tss_t key);
int tss_set(tss_t key, void *val);



#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_THREADS_H_ */
