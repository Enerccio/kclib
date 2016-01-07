#ifndef STDLIB_H_
#define STDLIB_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <ctype.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <sys/external.h>

/* _stdlib_alloc.c */
void* malloc(size_t size) __attribute__((malloc));
void* calloc(size_t nmemb, size_t size) __attribute__((malloc));
void* realloc(void* ptr, size_t size) __attribute__((malloc)) __attribute__((nonnull (1)));
void  free(void* ptr);

/* _stdlib_rand.c */
#define RAND_MAX 65535
int rand();
void srand(unsigned int seed);

/* _stdlib_exit.c */
int atexit(void (*func)(void));
void abort(void);
void exit(int status);

/* _stdlib_searchops.c */
void* bsearch(const void* key, const void* base,
		size_t nmemb, size_t size,
		int (*compar)(const void *, const void *));
void qsort(void* base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *)) __attribute__((nonnull (1)));

/* _stdlib_numconv.c */
double atof(const char *nptr) __attribute__((nonnull (1)));
int atoi(const char *nptr) __attribute__((nonnull (1)));
long int atol(const char *nptr) __attribute__((nonnull (1)));
long long int atoll(const char *nptr) __attribute__((nonnull (1)));
double strtod(const char* restrict nptr,
		char** restrict endptr) __attribute__((nonnull (1)));
float strtof(const char* restrict nptr,
		char** restrict endptr) __attribute__((nonnull (1)));
long double strtold(const char* restrict nptr,
		char** restrict endptr) __attribute__((nonnull (1)));
long int strtol(const char* restrict nptr,
		char** restrict endptr,
		int base) __attribute__((nonnull (1)));
long long int strtoll(const char* restrict nptr,
		char** restrict endptr,
		int base) __attribute__((nonnull (1)));
unsigned long int strtoul(const char* restrict nptr,
		char** restrict endptr,
		int base) __attribute__((nonnull (1)));
unsigned long long int strtoull(const char* restrict nptr,
		char** restrict endptr,
		int base) __attribute__((nonnull (1)));

/* _stdlib_envc.c */
char* getenv(const char* name) __attribute__((nonnull (1)));

#ifdef __cplusplus
}
#endif

#endif /* STDLIB_H_ */
