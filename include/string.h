/*
 * string.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef STRING_H_
#define STRING_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>
#include <stddef.h>
#include <stdint.h>

/* _string_memops.c */
void* memset(void* ptr, int32_t c, size_t n) __attribute__((nonnull (1)));
void* memcpy(void* restrict s1, const void* restrict s2, size_t n) __attribute__((nonnull (1, 2)));
void* memmove(void* s1, const void* s2, size_t n) __attribute__((nonnull (1, 2)));

/* _string_compops.c */
int memcmp(const void* s1, const void* s2, size_t n) __attribute__((nonnull (1, 2)));
int strcmp(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
int strcoll(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
int strncmp(const char* s1, const char* s2, size_t n) __attribute__((nonnull (1, 2)));
size_t strxfrm(char* restrict s1, const char* restrict s2,
		size_t n) __attribute__((nonnull (1, 2)));

/* _string_string.c */ // yeah I know, very cool name
size_t strlen(const char *s) __attribute__((nonnull (1)));
char* strcpy(char* restrict s1, const char* restrict s2) __attribute__((nonnull (1, 2)));
char* strncpy(char* restrict s1, register const char* restrict s2, size_t n) __attribute__((nonnull (1, 2)));

/* _string_searchops.c */
void* memchr(const void* s, int c, size_t n) __attribute__((nonnull (1)));
char* strchr(const char* s, int c) __attribute__((nonnull (1)));
size_t strcspn(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
char* strpbrk(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
char* strrchr(const char* s, int c) __attribute__((nonnull (1)));
size_t strspn(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
char* strstr(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
char* strtok(char* restrict s1, const char* restrict s2) __attribute__((nonnull (2)));
#ifdef __KCLIB_EXTENSIONS
char* strcpbrk(const char* s1, const char* s2) __attribute__((nonnull (1, 2)));
#endif

#ifdef __cplusplus
}
#endif

#endif /* STRING_H_ */
