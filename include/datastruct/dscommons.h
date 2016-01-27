/*
 * dscommons.h
 *
 *  Created on: Jan 25, 2016
 *      Author: pvan
 */

#ifndef INCLUDE_DATASTRUCT_DSCOMMONS_H_
#define INCLUDE_DATASTRUCT_DSCOMMONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef REGISTER_UINT_TYPE
#define REGISTER_UINT_TYPE uint64_t
#endif
typedef REGISTER_UINT_TYPE ruint_t;

typedef char* string;

#define SEARCH_PREDICATE_TYPE(type) search_predicate_ ## type ## _t
#define SEARCH_PREDICATE(type) typedef bool (* SEARCH_PREDICATE_TYPE(type))(type element, void* passed_data)
#define CMP_FUNC_TYPE(type) cmp_func_ ## type ## _t
#define CMP_FUNC(type) typedef int  (*CMP_FUNC_TYPE(type))(const type a, const type b)
#define KEY_DEALLOC_FUNC_TYPE(type) key_deallocator_func ## type ## _t
#define KEY_DEALLOC_FUNC(type) typedef void (*KEY_DEALLOC_FUNC_TYPE(type))(type a)
#define VALUE_DEALLOC_FUNC_TYPE(type) value_deallocator_func ## type ## _t
#define VALUE_DEALLOC_FUNC(type) typedef void (*VALUE_DEALLOC_FUNC_TYPE(type))(type a)
#define HASH_FUNC_TYPE(type) hash_function_ ## type ## _t
#define HASH_FUNC(type) typedef uint32_t (* HASH_FUNC_TYPE(type)) (type key)
#define EQ_FUNC_TYPE(type) eq_function_ ## type ## _t
#define EQ_FUNC(type) typedef bool (* EQ_FUNC_TYPE(type)) (type key_a, type key_b)

/* Concrete func definitions */
uint32_t uint32_hash_function(uint32_t integer);
bool uint32_eq_function(uint32_t a, uint32_t b);
uint32_t uint64_hash_function(uint64_t integer);
bool uint64_eq_function(uint64_t a, uint64_t b);
uint32_t string_hash_function(string string);
bool string_eq_function(string a, string b);

#define CE_TYPE(type) __chained_element_ ## type ## _s
#define CE_TYPEDEF(type) \
	struct CE_TYPE(type) { \
		struct CE_TYPE(type)* previous; \
		struct CE_TYPE(type)* next; \
		type                  data; \
		uint32_t			  pq; \
	}
#define CE_ELEMENT_GETTER_TYPE(type) ce_getter_ ## type ## _t
#define CE_ELEMENT_GETTER(type) typedef struct CE_TYPE(type)* (*CE_ELEMENT_GETTER_TYPE(type))(type data)

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_DSCOMMONS_H_ */
