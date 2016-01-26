/*
 * random.h
 *
 *  Created on: Jan 26, 2016
 *      Author: enerccio
 */

#ifndef INCLUDE_DATASTRUCT_RANDOM_H_
#define INCLUDE_DATASTRUCT_RANDOM_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************//**
 * Random generator state.
 ********************************************************************************/
typedef struct random_generator {
    uint64_t state[2];
} rg_t;

rg_t rg_create_random_generator(uint64_t seed);
uint64_t rg_next_uint(rg_t* rg);
uint64_t rg_next_uint_l(rg_t* rg, uint64_t limit);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_RANDOM_H_ */
