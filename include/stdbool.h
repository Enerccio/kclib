/*
 * stdbool.h
 *
 *  Created on: Dec 8, 2015
 *      Author: enerccio
 */

#ifndef STDBOOL_H_
#define STDBOOL_H_

#ifdef __CDT_INDEXER__
#include <gcc_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>
#include <stdint.h>

#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1

#ifdef __cplusplus
}
#endif

#endif /* STDBOOL_H_ */
