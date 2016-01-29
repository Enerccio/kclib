/*
 * hmap.h
 *
 *  Created on: Jan 27, 2016
 *      Author: enerccio
 */

#ifndef INCLUDE_DATASTRUCT_HMAP_H_
#define INCLUDE_DATASTRUCT_HMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>
#include <datastruct/dscommons.h>

#define HASH_STARTING_SIZE 97

#define FREE_CELL               0
#define DELETED_CELL    ((void*)1)

typedef enum state {
	empty, deleted, used
} state_t;

typedef uint32_t hash_it_t;

#define HMAP_TYPE(typek, typev) __hmap_ ## typek ## typev ## _t
#define HMAP_PTYPE(typek, typev) __hmap_pair_ ## typek ## typev ## _t

#define HMAP_HEADER(keyt, valuet) \
HASH_FUNC(keyt); \
EQ_FUNC(keyt); \
typedef struct {\
	state_t state;\
	keyt key;\
	valuet data;\
} HMAP_PTYPE(keyt, valuet);\
typedef struct {\
	HMAP_PTYPE(keyt, valuet)* hash_table;\
    HASH_FUNC_TYPE(keyt) hash_fn;\
    EQ_FUNC_TYPE(keyt) cmpr_fn;\
    uint32_t len;\
    uint32_t max_size;\
} HMAP_TYPE(keyt, valuet);\
HMAP_TYPE(keyt, valuet)* create_table ## keyt ## valuet (HASH_FUNC_TYPE(keyt) hash_fn, EQ_FUNC_TYPE(keyt) cmpr_fn);\
void destroy_table ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table);\
bool table_contains ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key);\
valuet table_get ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key);\
bool table_set ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key, valuet data);\
bool table_remove ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key);\
uint32_t table_size ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table);\
HMAP_TYPE(keyt, valuet)* copy_table ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table);\
valuet hash_it_next ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, hash_it_t* iterator);\

#define HMAP_FUNCDEFS(keyt, valuet) \
HMAP_TYPE(keyt, valuet)* create_table ## keyt ## valuet (HASH_FUNC_TYPE(keyt) hash_fn, EQ_FUNC_TYPE(keyt) cmpr_fn) {\
	HMAP_TYPE(keyt, valuet)* table = (HMAP_TYPE(keyt, valuet)*) malloc(sizeof(HMAP_TYPE(keyt, valuet)));\
	if (table == NULL)\
		return NULL;\
	table->hash_fn = hash_fn;\
	table->cmpr_fn = cmpr_fn;\
	table->max_size = HASH_STARTING_SIZE;\
	table->hash_table = (HMAP_PTYPE(keyt, valuet)*) malloc(sizeof(HMAP_PTYPE(keyt, valuet)) * table->max_size);\
	if (table->hash_table == NULL) {\
		free(table);\
		return NULL;\
	}\
	table->len = 0;\
	memset(table->hash_table, 0, sizeof(HMAP_PTYPE(keyt, valuet)) * table->max_size);\
	return table;\
}\
void destroy_table ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table) {\
	free(table->hash_table);\
	free(table);\
}\
static HMAP_PTYPE(keyt, valuet)*  find_cell ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key, uint32_t hashed, bool dont_skip_deleted) {\
    uint32_t primary_hash = hashed % table->max_size;\
    uint32_t secondary_hash = 1 + (hashed % (table->max_size - 1));\
    uint32_t hash = primary_hash;\
    uint32_t i = 1;\
\
    HMAP_PTYPE(keyt, valuet)* pair = &table->hash_table[hash];\
    while (pair->state != empty  || (dont_skip_deleted && pair->state == deleted)) {\
        if (pair->state != deleted)\
                if (table->cmpr_fn(key, pair->key) == true)\
                        return &table->hash_table[hash];\
\
        hash = (primary_hash + (secondary_hash * i++)) % table->max_size;\
        pair = &table->hash_table[hash];\
    }\
\
    return &table->hash_table[hash];\
}\
static bool resize_table ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table) {\
    HMAP_TYPE(keyt, valuet)* new_table = (HMAP_TYPE(keyt, valuet)*) malloc(sizeof(HMAP_TYPE(keyt, valuet)));\
    if (new_table == NULL)\
    	return true;\
\
    new_table->hash_fn = table->hash_fn;\
    new_table->cmpr_fn = table->cmpr_fn;\
    new_table->len = 0;\
    new_table->max_size = (table->max_size * 2) + 1;\
    new_table->hash_table = (HMAP_PTYPE(keyt, valuet)*) malloc(sizeof(HMAP_PTYPE(keyt, valuet)) * new_table->max_size);\
    if (new_table->hash_table == NULL) {\
    	free(new_table);\
    	return true;\
    }\
    memset(new_table->hash_table, 0, sizeof(HMAP_PTYPE(keyt, valuet)*) * new_table->max_size);\
\
    uint32_t i = 0;\
    for (; i<table->max_size; i++) {\
        HMAP_PTYPE(keyt, valuet)* cell = &table->hash_table[i];\
        if (cell->state != empty && cell->state != deleted) {\
            table_set(keyt, valuet, new_table, cell->key, cell->data);\
        }\
    }\
\
    free(table->hash_table);\
    table->hash_table = new_table->hash_table;\
    table->len = new_table->len;\
    free(new_table);\
    return false;\
}\
bool table_contains ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key) {\
	HMAP_PTYPE(keyt, valuet)* cell = find_cell ## keyt ## valuet (table, key, table->hash_fn(key), false);\
	if (cell->state != empty && cell->state != deleted)\
		return true;\
	else\
		return false;\
}\
valuet table_get ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key) {\
	HMAP_PTYPE(keyt, valuet)* cell = find_cell ## keyt ## valuet (table, key, table->hash_fn(key), false);\
	if (cell->state != empty && cell->state != deleted)\
		return cell->data;\
	else\
		return 0;\
}\
bool table_set ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key, valuet data) {\
	if (table->len > (table->max_size / 4) * 3)\
		if (resize_table ## keyt ## valuet (table))\
			return true;\
	HMAP_PTYPE(keyt, valuet)* cell = find_cell ## keyt ## valuet (table, key, table->hash_fn(key), true);\
	if (cell->state == empty || cell->state == deleted) {\
		cell->key = key;\
		cell->data = data;\
		cell->state = used;\
\
		++table->len;\
	} else if (table->cmpr_fn(key, cell->key) == true) {\
		cell->data = data;\
		cell->state = used;\
	} else {\
		\
	}\
	return false;\
}\
bool table_remove ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, keyt key) {\
	HMAP_PTYPE(keyt, valuet)* cell = find_cell ## keyt ## valuet (table, key, table->hash_fn(key), false);\
	if (cell->state != empty && cell->state != deleted) {\
		cell->state = deleted;\
		--table->len;\
		return true;\
	}\
	return false;\
}\
uint32_t table_size ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table) {\
	return table->len;\
}\
HMAP_TYPE(keyt, valuet)* copy_table ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table) {\
	HMAP_TYPE(keyt, valuet)* copy = (HMAP_TYPE(keyt, valuet)*) malloc(sizeof(HMAP_TYPE(keyt, valuet)));\
	if (copy == NULL)\
		return NULL;\
	copy->cmpr_fn = table->cmpr_fn;\
	copy->hash_fn = table->hash_fn;\
	copy->len = table->len;\
	copy->max_size = table->max_size;\
	copy->hash_table = (HMAP_PTYPE(keyt, valuet)*) malloc(sizeof(HMAP_PTYPE(keyt, valuet)) * copy->max_size);\
	if (copy->hash_table == NULL) {\
		free(copy);\
		return NULL;\
	}\
\
	uint32_t i = 0;\
	for (; i<table->max_size; i++) {\
		HMAP_PTYPE(keyt, valuet)* cell = &table->hash_table[i];\
		if (cell->state != empty && cell->state != deleted) {\
			copy->hash_table[i].state = used;\
			copy->hash_table[i].key = cell->key;\
			copy->hash_table[i].data = cell->data;\
		} else\
			copy->hash_table[i].state = cell->state;\
	}\
\
	return copy;\
}\
valuet hash_it_next ## keyt ## valuet (HMAP_TYPE(keyt, valuet)* table, hash_it_t* iterator) {\
	valuet data = 0;\
	while (data != 0 && *iterator < table->max_size) {\
		HMAP_PTYPE(keyt, valuet)* pair = &table->hash_table[*iterator];\
		if (pair->state != empty && pair->state != deleted)\
			data = pair->data;\
\
		*iterator += 1;\
	}\
	return data;\
}\

/******************************************************************************//**
 * \brief Creates new hash table.
 *
 * This hash table will use provided hash_fn and cmpr_fn to hash/compare keys.
 * Default size of inner table is HASH_STARTING_SIZE.
 ********************************************************************************/
#define create_table(ktype, vtype, hash_fn, cmpr_fn) create_table ## ktype ## vtype (hash_fn, cmpr_fn)
/******************************************************************************//**
 * \brief Deallocates table.
 *
 * Removes all data from the table and table itself from memory.
 * Will NOT deallocate table keys nor entries!
 ********************************************************************************/
#define destroy_table(ktype, vtype, table) destroy_table ## ktype ## vtype (table)
/******************************************************************************//**
 * Returns whether key is in the table or not.
 ********************************************************************************/
#define table_contains(ktype, vtype, table, key) table_contains ## ktype ## vtype (table, key)
/******************************************************************************//**
 * \brief Returns value of key in the table.
 *
 * Returns NULL if key is not in the table.
 ********************************************************************************/
#define table_get(ktype, vtype, table, key) table_get ## ktype ## vtype (table, key)
/******************************************************************************//**
 * \brief Sets the key in the table to the data.
 *
 * Will remove old key-data pair if it exists (does not deallocate old data value!).
 ********************************************************************************/
#define table_set(ktype, vtype, table, key, data) table_set ## ktype ## vtype (table, key, data)
/******************************************************************************//**
 * \brief Removes key from the table.
 *
 * Returns true if operation was done successfully, false if there was no such
 * key.
 ********************************************************************************/
#define table_remove(ktype, vtype, table, key) table_remove ## ktype ## vtype (table, key)
/******************************************************************************//**
 * Returns number of elements in the table.
 ********************************************************************************/
#define table_size(ktype, vtype, table) table_size ## ktype ## vtype (table)
/******************************************************************************//**
 * Copies table to another table.
 ********************************************************************************/
#define copy_table(ktype, vtype, table) copy_table ## ktype ## vtype (table)
/******************************************************************************//**
 * Returns value from iterator and moves iterator to next element.
 ********************************************************************************/
#define hash_it_next(ktype, vtype, table, iterator) hash_it_next ## ktype ## vtype (table, iterator)

#define create_uint32_table(value_type) create_table(uint32_t, value_type, uint32_hash_function, uint32_eq_function)
#define create_uint64_table(value_type) create_table(uint64_t, value_type, uint64_hash_function, uint64_eq_function)
#define create_string_table(value_type) create_table(string, value_type, string_hash_function, string_eq_function)

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_HMAP_H_ */
