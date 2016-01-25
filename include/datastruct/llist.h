/*
 * llist.h
 *
 *  Created on: Jan 25, 2016
 *      Author: pvan
 */

#ifndef INCLUDE_DATASTRUCT_LLIST_H_
#define INCLUDE_DATASTRUCT_LLIST_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <datastruct/dscommons.h>

#define LLIST_TYPE(type) __llist_ ## type ## _t
#define LLIST_ITER(type) __llist_ ## type ## _iter_t

#define LLIST_HEADER(t) \
SEARCH_PREDICATE(t); \
typedef struct LLIST_TYPE(t) { \
	size_t size; \
\
} LLIST_TYPE(t);\
typedef struct LLIST_ITER(t) { \
\
} LLIST_ITER(t); \
\
LLIST_TYPE(t)* create_list(); \
t list_remove_left(LLIST_TYPE(t)* list); \
t list_get_left(LLIST_TYPE(t)* list);\
t list_remove_right(LLIST_TYPE(t)* list);\
t list_get_right(LLIST_TYPE(t)* list);\
bool list_push_left(LLIST_TYPE(t)* list, t data);\
bool list_push_right(LLIST_TYPE(t)* list, t data);\
bool list_has_elements(LLIST_TYPE(t)* list);\
uint32_t list_size(LLIST_TYPE(t)* list);\
void free_list(LLIST_TYPE(t)* list);\
void list_remove(t element, LLIST_TYPE(t)* list);\
t list_find_by_predicate(t data, SEARCH_PREDICATE_TYPE(t) func, LLIST_TYPE(t)* list);\
void list_remove_by_predicate(t data, SEARCH_PREDICATE_TYPE(t) func, LLIST_TYPE(t)* list);\
void list_create_iterator(LLIST_TYPE(t)* list, LLIST_ITER(t)* li);\
bool list_has_next(LLIST_ITER(t)* li);\
t list_next(LLIST_ITER(t)* li);\
void list_remove_it(LLIST_ITER(t)* li);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_LLIST_H_ */
