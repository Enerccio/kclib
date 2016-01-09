/*
 * errno.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef ERRNO_H_
#define ERRNO_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define EDEFAULTERR  0
#define EDOM		 1
#define EILSEQ		 2
#define ERANGE		 3
#define EIO			 4
#define ENOPROC		 5
#define ENOMEM		 6
#define EINVAL	     7
#define E2BIG		 8
#define EACCES		 9
#define	ENAMETOOLONG 10
#define ENOENT		 11
#define ENOTDIR		 12
#define ENOEXEC		 13
#define ELOOP		 14
#define ENAMETOOLONG 15
#define ETXTBSY		 16

extern int err;
#define errno err

#ifdef __cplusplus
}
#endif

#endif /* ERRNO_H_ */
