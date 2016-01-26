/*
 * _ds.c
 *
 *  Created on: Jan 25, 2016
 *      Author: enerccio
 */

#include <datastruct/dscommons.h>
#include <datastruct/random.h>

/******************************************************************************//**
 * \brief Converts uint32_t passed in as void* into hash
 *
 * Hash type is uint32_t.
 ********************************************************************************/
uint32_t uint32_hash_function(uint32_t integer) {
    uint32_t a = integer;
    a = (a + 0x7ed55d16) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    return a;
}

/******************************************************************************//**
 * Compares two uint32_t values passed in as void*
 ********************************************************************************/
bool uint32_eq_function(uint32_t a, uint32_t b) {
    return a == b ? true : false;
}

/******************************************************************************//**
 * \brief Converts uint64_t passed in as void* into hash
 *
 * Hash type is uint32_t.
 ********************************************************************************/
uint32_t uint64_hash_function(uint64_t integer) {
    return uint32_hash_function((integer >> 32 & 0xFFFFFFFF)) ^
            uint32_hash_function((integer & 0xFFFFFFFF));
}

/******************************************************************************//**
 * Compares two uint64_t values passed in as void*
 ********************************************************************************/
bool uint64_eq_function(uint64_t a, uint64_t b) {
    return a == b ? true : false;
}

/******************************************************************************//**
 * \brief Converts char* passed in as void* into hash
 *
 * Hash type is uint32_t.
 ********************************************************************************/
uint32_t string_hash_function(char* str) {
    uint32_t hash = 5381;
    char c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

/******************************************************************************//**
 * \brief Compares two char* values passed in as void*
 *
 * Uses strcmp.
 ********************************************************************************/
bool string_eq_function(char* a, char* b) {
    return strcmp(a, b) == 0;
}

/******************************************************************************//**
 * \brief Creates random generator state.
 *
 * Random generator state is seeded with provided seed.
 ********************************************************************************/
rg_t rg_create_random_generator(uint64_t seed) {
    rg_t rg;
    rg.state[0] = (seed = (seed * 2862933555777941757 + 3037000493));
    rg.state[1] = (seed * 2862933555777941757 + 3037000493);
    return rg;
}

/******************************************************************************//**
 * \brief Returns next random unsigned int value.
 *
 * Int type is ruint_t, which is register sized uint.
 ********************************************************************************/
ruint_t rg_next_uint(rg_t* rg) {
    ruint_t x = rg->state[0];
    ruint_t const y = rg->state[1];
    rg->state[0] = y;
    x ^= x << 23; // a
    rg->state[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return rg->state[1] + y;
}

/******************************************************************************//**
 * \brief Returns next random unsigned int from 0 to limit.
 *
 * Int type is ruint_t, which is register sized uint.
 ********************************************************************************/
ruint_t rg_next_uint_l(rg_t* rg, ruint_t limit) {
    return rg_next_uint(rg) % limit;
}
