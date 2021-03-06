/*
 * stdio.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef STDIO_H_
#define STDIO_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>
#include <sys/external.h>
#include <stdarg.h>

#ifdef __GNUC__
#define __FORMAT_CHECK(farg, startfrom) __attribute__ ((format (printf, farg, startfrom)))
#else
#define __FORMAT_CHECK(farg, startfrom)
#endif

#define SEEK_CUR 0
#define SEEK_END 1
#define SEEK_SET 2

#include <fragments/_file.h>

extern FILE* stderr;
extern FILE* stdout;
extern FILE* stdin;

#define EOF -1

/* _stdio_file.c */
int fclose(FILE* stream);
int fflush(FILE* stream);
FILE* fopen(const char* restrict filename,
		const char * restrict mode) __attribute__((nonnull (1, 2)));
size_t fread(void* restrict ptr,
		size_t size, size_t nmemb,
		FILE* restrict stream) __attribute__((nonnull (1, 4)));
size_t fwrite(const void* restrict ptr,
		size_t size, size_t nmemb,
		FILE* restrict stream) __attribute__((nonnull (1, 4)));
int fseek(FILE *stream, long int offset, int whence) __attribute__((nonnull (1)));
long int ftell(FILE *stream) __attribute__((nonnull (1)));

#define BUFSIZ 2048

#define _IONBF 0
#define _IOFBF 1
#define _IOLBF 2

#define __FERROR_READ    1
#define __FERROR_WRITE   2
#define __FERROR_BUFFULL 3

#define __FORMAT_ERROR_NOT_ENOUGH_DATA -2
#define __FORMAT_ERROR_LENSPEC_INCORRECT -3
#define __FORMAT_ERROR_PERCISION_INCORRECT -4
#define __FORMAT_ERROR_WRONG_SPECS -5

/* _stdio_buffer.h */
#define __BUF_ERROR_MALLOC_FAILURE 1
int setbuf(FILE* restrict stream, char* restrict buf) __attribute__((nonnull (1)));
int setvbuf(FILE* restrict stream, char* restrict buf, int mode, size_t size) __attribute__((nonnull (1)));

/* _stdio_printf.c */
/**
 * Completed stuff: s (no wchar support), c  (no wint support), n, %, d, i, o, u, x, X, p
 * Missing stuff: f, F, e, E, g, G, a, A
 */
int fprintf(FILE* restrict stream, const char* restrict format, ...) __attribute__((nonnull (1)));
int vfprintf(FILE* restrict stream, const char* restrict format, va_list arg) __attribute__((nonnull (1)));
int printf(const char* restrict format, ...) __attribute__((nonnull (1)));
int vprintf(const char* restrict format, va_list arg) __attribute__((nonnull (1)));
int sprintf(char* restrict s, const char* restrict format, ...) __attribute__((nonnull (1)));
int vsprintf(char* restrict s, const char* restrict format, va_list arg) __attribute__((nonnull (1)));
int snprintf(char* restrict s, size_t n, const char* restrict format, ...) __attribute__((nonnull (1)));
int vsnprintf(char* restrict s, size_t n, const char* restrict format, va_list arg)
	__attribute__((nonnull (1)));

#ifdef __cplusplus
}
#endif

#endif /* STDIO_H_ */
