/*
 * _ds.c
 *
 *  Created on: Jan 25, 2016
 *      Author: enerccio
 */

#include <datastruct/dscommons.h>

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
