/*
 * array.h
 *
 *  Created on: Jan 26, 2016
 *      Author: enerccio
 */

#ifndef INCLUDE_DATASTRUCT_ARRAY_H_
#define INCLUDE_DATASTRUCT_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <datastruct/dscommons.h>
#include <datastruct/random.h>

/** Number of elements in starting size */
#define ARRAY_STARTING_SIZE 32

#define ARRAY_TYPE(type) __array_ ## type ## _t

#define ARRAY_HEADER(t) \
SEARCH_PREDICATE(t); \
typedef struct ARRAY_TYPE(t) { \
    t* data; \
    uint32_t size; \
    uint32_t data_size;\
    uint32_t starting_size;\
} ARRAY_TYPE(t);\
ARRAY_TYPE(t)* create_array ## t();\
ARRAY_TYPE(t)* create_array_spec ## t(uint32_t starting_element_size);\
uint32_t array_push_data ## t(ARRAY_TYPE(t)* array, t data);\
int32_t array_find_data ## t(ARRAY_TYPE(t)* array, t data);\
void array_insert_at ## t(ARRAY_TYPE(t)* array, uint32_t pos, t data);\
t array_get_at ## t(ARRAY_TYPE(t)* array, uint32_t position);\
void array_set_at ## t(ARRAY_TYPE(t)* array, uint32_t position, t data);\
void array_remove_at ## t(ARRAY_TYPE(t)* array, uint32_t position);\
uint32_t array_get_size ## t(ARRAY_TYPE(t)* array);\
void destroy_array ## t(ARRAY_TYPE(t)* array);\
t array_find_by_pred ## t(ARRAY_TYPE(t)* array, SEARCH_PREDICATE_TYPE(t) predicate, void* data);\
t array_get_random ## t(ARRAY_TYPE(t)* array, rg_t* rg);\
void array_clean ## t(ARRAY_TYPE(t)* array);

#define ARRAY_FUNCDEFS(t)\
ARRAY_TYPE(t)* create_array ## t() {\
	return create_array_spec(t, ARRAY_STARTING_SIZE);\
} \
ARRAY_TYPE(t)* create_array_spec ## t(uint32_t starting_element_size) {\
	ARRAY_TYPE(t)* array = (ARRAY_TYPE(t)*) malloc(sizeof(ARRAY_TYPE(t))); \
	if (array == NULL)\
		return NULL;\
	array->size = 0;\
	array->data_size = starting_element_size * sizeof(t);\
	array->data = (t*) malloc(array->data_size);\
	if (array->data == NULL) {\
		free(array);\
		return NULL;\
	}\
	array->starting_size = starting_element_size;\
	return array;\
} \
uint32_t array_push_data ## t(ARRAY_TYPE(t)* array, t data) {\
	if (array->size == array->data_size/sizeof(t)) {\
		t* reallocdata = (t*) realloc(array->data, array->data_size +\
				(array->starting_size * sizeof(t)));\
		if (reallocdata == NULL) {\
			return 0;\
		}\
		array->data = reallocdata;\
		array->data_size += array->starting_size * sizeof(t);\
	}\
\
	array->data[array->size++] = data;\
	return array->size;\
} \
int32_t array_find_data ## t(ARRAY_TYPE(t)* array, t data) {\
	uint32_t iterator = 0;\
	for (; iterator<array->size; iterator++)\
		if (array_get_at(t, array, iterator) == data)\
			return iterator;\
	return -1;\
} \
void array_insert_at ## t(ARRAY_TYPE(t)* array, uint32_t position, t data) {\
	if (position == array->size-1) {\
		array_push_data(t, array, data);\
		return;\
	}\
\
	if (position > array->size-1)\
		return;\
\
	if (array->size == 0) {\
		if (position == 0) {\
			array_push_data(t, array, data);\
			return;\
		} else\
			return;\
	}\
\
	uint32_t it = position;\
	t prev = data;\
	while (it <= array->size-1) {\
		t tmp = prev;\
		prev = array->data[it];\
		array->data[it] = tmp;\
		++it;\
	}\
\
	array_push_data(t, array, prev); /*to ensure that we only have one code that will enlarge array*/\
} \
t array_get_at ## t(ARRAY_TYPE(t)* array, uint32_t position) {\
	if (position > array->size-1)\
		return 0;\
\
	return array->data[position];\
} \
void array_set_at ## t(ARRAY_TYPE(t)* array, uint32_t position, t data) {\
	if (position < array->size-1)\
		array->data[position] = data;\
} \
void array_remove_at ## t(ARRAY_TYPE(t)* array, uint32_t position) {\
	if (position == array->size-1) {\
		--array->size;\
		return;\
	}\
\
	int32_t p = ((int32_t)position)-1;\
	while ((++p)<(int32_t)array->size-1)\
		array->data[p] = array->data[p+1];\
	--array->size;\
} \
uint32_t array_get_size ## t(ARRAY_TYPE(t)* array) {\
	return array->size;\
} \
void destroy_array ## t(ARRAY_TYPE(t)* array) {\
	free(array->data);\
	free(array);\
} \
t array_find_by_pred ## t(ARRAY_TYPE(t)* array, SEARCH_PREDICATE_TYPE(t) predicate, void* data) {\
	uint32_t i = 0;\
\
	for (; i<array->size; i++)\
		if (predicate(array->data[i], data) == true)\
			return array->data[i];\
\
	return 0;\
} \
t array_get_random ## t(ARRAY_TYPE(t)* array, rg_t* rg) {\
	if (array->size == 0)\
		return 0;\
	ruint_t idx = rg_next_uint_l(rg, array->size);\
	return array->data[idx];\
} \
void array_clean ## t(ARRAY_TYPE(t)* array) {\
	array->size = 0;\
}

/******************************************************************************//**
 * \brief Creates array with ARRAY_STARTING_SIZE preallocation count.
 *
 * Starting allocation size will be set to ARRAY_STARTING_SIZE * sizeof(void*).
 ********************************************************************************/
#define create_array(type) create_array ## type ()
/******************************************************************************//**
 * \brief Creates array with starting_elementa_size preallocation count.
 *
 * Starting allocation size will be set to starting_elementa_size * sizeof(void*).
 ********************************************************************************/
#define create_array_spec(type, starting_element_size) create_array_spec ## type (starting_element_size)
/******************************************************************************//**
 * \brief Adds data on the end of the array.
 *
 * This is O(1) operation most of the time, unless array has to resize, then it
 * is O(n) operation. data is always placed as last element.
 ********************************************************************************/
#define array_push_data(type, array, data) array_push_data ## type (array, data)
/******************************************************************************//**
 * \brief Returns index to the data in the array.
 *
 * Returns -1 if data is not found in the array. Compares data via ==.
 ********************************************************************************/
#define array_find_data(array, data) array_find_data ## type (array, data)
/******************************************************************************//**
 * \brief Inserts data at position.
 *
 * This operation is O(n) at worst case due to shifting. If n == size of array-1,
 * then this operation is same as array_push_data.
 ********************************************************************************/
#define array_insert_at(type, array, pos, data) array_insert_at ## type (array, pos, data)
/******************************************************************************//**
 * \brief Returns data at position.
 *
 * Returns NULL if position is larger than size of an array or equal.
 ********************************************************************************/
#define array_get_at(type, array, position) array_get_at ## type (array, position)
/******************************************************************************//**
 * \brief Replaces content at position with data.
 *
 * Does nothing if position is larger than size of an array or equal.
 ********************************************************************************/
#define array_set_at(type, array, position, data) array_set_at ## type (array, position, data)
/******************************************************************************//**
 * \brief Removes item at position.
 *
 * O(n) operation, due to shifting. If position == size of array, it is O(1)
 * operation instead.
 ********************************************************************************/
#define array_remove_at(type, array, position) array_remove_at ## type (array, position)
/******************************************************************************//**
 * Returns number of elements in the array
 ********************************************************************************/
#define array_get_size(type, array) array_get_size ## type (array)
/******************************************************************************//**
 * \brief Deallocates all memory used by this array.
 *
 * Elements itself are NOT deallocated!
 ********************************************************************************/
#define destroy_array(type, array) destroy_array ## type (array)
/******************************************************************************//**
 * \brief Returns first element that matches predicate.
 *
 * Calls predicate function with each element of an array and with data provided,
 * first true returned from the predicate is returned or NULL if nothing matched
 * the predicate.
 ********************************************************************************/
#define array_find_by_pred(type, array, predicate, data) array_find_by_pred ## type (array, predicate, data)
/******************************************************************************//**
 * \brief Returns random element from array.
 *
 * Returns NULL if array is empty.
 ********************************************************************************/
#define array_get_random(type, array, rg) array_get_random ## type (array, rg)
/******************************************************************************//**
 * Removes all elements from array.
 ********************************************************************************/
#define array_clean(type, array) array_clean ## type (array)


#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_ARRAY_H_ */
