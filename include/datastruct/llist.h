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
CE_TYPEDEF(t); \
CE_ELEMENT_GETTER(t); \
SEARCH_PREDICATE(t); \
typedef struct LLIST_TYPE(t) { \
	bool is_static; \
	CE_ELEMENT_GETTER_TYPE(t) getter; \
	struct CE_TYPE(t)* first; \
	struct CE_TYPE(t)* last; \
	uint32_t size; \
} LLIST_TYPE(t);\
typedef struct LLIST_ITER(t) { \
	struct CE_TYPE(t)* current; \
	struct CE_TYPE(t)** prev; \
	struct CE_TYPE(t)** pprev; \
	bool   static_list; \
} LLIST_ITER(t); \
\
LLIST_TYPE(t)* create_list ## t (); \
LLIST_TYPE(t)* create_list_static ## t (CE_ELEMENT_GETTER_TYPE(t) getter); \
t list_remove_left ## t (LLIST_TYPE(t)* list); \
t list_get_left ## t (LLIST_TYPE(t)* list);\
t list_remove_right ## t (LLIST_TYPE(t)* list);\
t list_get_right ## t (LLIST_TYPE(t)* list);\
bool list_push_left ## t (LLIST_TYPE(t)* list, t data);\
bool list_push_right ## t (LLIST_TYPE(t)* list, t data);\
bool list_has_elements ## t (LLIST_TYPE(t)* list);\
uint32_t list_size ## t (LLIST_TYPE(t)* list);\
void free_list ## t (LLIST_TYPE(t)* list);\
void list_remove ## t (t element, LLIST_TYPE(t)* list);\
t list_find_by_predicate ## t (void* data, SEARCH_PREDICATE_TYPE(t) func, LLIST_TYPE(t)* list);\
void list_remove_by_predicate ## t (void* data, SEARCH_PREDICATE_TYPE(t) func, LLIST_TYPE(t)* list);\
void list_create_iterator ## t (LLIST_TYPE(t)* list, LLIST_ITER(t)* li);\
bool list_has_next ## t (LLIST_ITER(t)* li);\
t list_next ## t (LLIST_ITER(t)* li);\
void list_remove_it ## t (LLIST_ITER(t)* li);

#define LLIST_FUNCDEFS(t) \
LLIST_TYPE(t)* create_list ## t () { \
	LLIST_TYPE(t)* list = (LLIST_TYPE(t)*) malloc(sizeof(LLIST_TYPE(t)));\
	if (list == NULL)\
		return NULL;\
	list->first = 0;\
	list->last = 0;\
	list->size = 0;\
	list->is_static = false;\
	return list;\
} \
LLIST_TYPE(t)* create_list_static ## t (CE_ELEMENT_GETTER_TYPE(t) getter) { \
	LLIST_TYPE(t)* list = (LLIST_TYPE(t)*) malloc(sizeof(LLIST_TYPE(t)));\
	if (list == NULL)\
		return NULL;\
	list->first = 0;\
	list->last = 0;\
	list->size = 0;\
	list->is_static = true;\
	list->getter = getter;\
	return list;\
} \
t list_remove_left ## t (LLIST_TYPE(t)* list) { \
	struct CE_TYPE(t)* list_head = list->first;\
	if (list_head == 0)\
		return 0;\
\
	if (list->size == 1) {\
		list->first = 0;\
		list->last = 0;\
		list->size = 0;\
		t data = list_head->data;\
		if (!list->is_static)\
			free(list_head);\
		return data;\
	}\
\
	t data = list_head->data;\
	list->first = list_head->next;\
\
	if (!list->is_static)\
		free(list_head);\
\
	list->size--;\
	return data;\
} \
t list_get_left ## t (LLIST_TYPE(t)* list) {\
	struct CE_TYPE(t)* list_head = list->first;\
	if (list_head == 0)\
		return 0;\
\
	return list_head->data;\
} \
t list_remove_right ## t (LLIST_TYPE(t)* list) {\
	struct CE_TYPE(t)* list_head = list->last;\
	if (list_head == 0)\
		return 0;\
\
	if (list->size == 1) {\
		list->first = 0;\
		list->last = 0;\
		list->size = 0;\
		t data = list_head->data;\
		if (!list->is_static)\
			free(list_head);\
		return data;\
	}\
\
	t data = list_head->data;\
	list->last = list_head->previous;\
\
	if (!list->is_static)\
		free(list_head);\
\
	list->size--;\
	return data;\
} \
t list_get_right ## t (LLIST_TYPE(t)* list) {\
	struct CE_TYPE(t)* list_head = list->last;\
	if (list_head == 0)\
		return 0;\
\
	return list_head->data;\
} \
bool list_push_left ## t (LLIST_TYPE(t)* list, t data) {\
	struct CE_TYPE(t)* element;\
	if (list->is_static)\
		element = list->getter(data);\
	else\
		element = (struct CE_TYPE(t)*) malloc(sizeof(struct CE_TYPE(t)));\
\
	if (element == 0)\
		return true;\
\
	element->data = data;\
	element->next = 0;\
	element->previous = 0;\
\
	if (list->first == 0) {\
		list->first = list->last = element;\
		list->size = 1;\
	} else {\
		element->next = list->first;\
		list->first->previous = element;\
		list->first = element;\
		list->size++;\
	}\
\
	return false;\
} \
bool list_push_right ## t (LLIST_TYPE(t)* list, t data) {\
	struct CE_TYPE(t)* element;\
	if (list->is_static)\
		element = list->getter(data);\
	else\
		element = (struct CE_TYPE(t)*) malloc(sizeof(struct CE_TYPE(t)));\
\
	if (element == 0)\
		return true;\
\
	element->data = data;\
	element->next = 0;\
	element->previous = 0;\
\
	if (list->first == 0) {\
		list->first = list->last = element;\
		list->size = 1;\
	} else {\
		list->last->next = element;\
		element->previous = list->last;\
		list->last = element;\
		list->size++;\
	}\
\
	return false;\
} \
bool list_has_elements ## t (LLIST_TYPE(t)* list) {\
	return list_size(t, list) > 0;\
} \
uint32_t list_size ## t (LLIST_TYPE(t)* list) {\
	return list->size;\
} \
void free_list ## t (LLIST_TYPE(t)* list) {\
	if (!list->is_static) {\
		struct CE_TYPE(t)* el = list->first;\
		while (el != 0) {\
			struct CE_TYPE(t)* tmp = el->next;\
			free(el);\
			el = tmp;\
		}\
	}\
	free(list);\
} \
void list_remove ## t (t element, LLIST_TYPE(t)* list) {\
	if (list->size == 0)\
		return;\
\
	struct CE_TYPE(t)* e = list->first;\
	while (e != 0 && e->data != element)\
		e = e->next;\
\
	if (e) {\
		if (e->previous)\
			e->previous->next = e->next;\
		if (e->next)\
			e->next->previous = e->previous;\
		if (!list->is_static)\
			free(e);\
	}\
} \
t list_find_by_predicate ## t (void* data, SEARCH_PREDICATE_TYPE(t) func, LLIST_TYPE(t)* list) {\
	if (list->size == 0)\
		return 0;\
\
	struct CE_TYPE(t)* e = list->first;\
	while (e != 0 && func(e->data, data) == false)\
		e = e->next;\
\
	if (e)\
		return e->data;\
	else\
		return 0;\
} \
void list_remove_by_predicate ## t (void* data, SEARCH_PREDICATE_TYPE(t) func, LLIST_TYPE(t)* list) {\
	if (list->size == 0)\
		return;\
\
	struct CE_TYPE(t)* e = list->first;\
	while (e != 0) {\
		if (func(e->data, data)) {\
			if (e->previous != NULL)\
				e->previous->next = e->next;\
			if (e->next != NULL)\
				e->next->previous = e->previous;\
			struct CE_TYPE(t)* el = e;\
			e = e->next;\
			if (!list->is_static)\
				free(el);\
		} else\
			e = e->next;\
	}\
} \
void list_create_iterator ## t (LLIST_TYPE(t)* list, LLIST_ITER(t)* li) {\
	li->current = list->first;\
	li->prev = &list->first;\
	li->pprev = NULL;\
	li->static_list = list->is_static;\
} \
bool list_has_next ## t (LLIST_ITER(t)* li) {\
	return li->current != NULL;\
} \
t list_next ## t (LLIST_ITER(t)* li) {\
	struct CE_TYPE(t)* le = li->current;\
	li->pprev = li->prev;\
	li->prev = &le->next;\
	li->current = le->next;\
	return le->data;\
} \
void list_remove_it ## t (LLIST_ITER(t)* li) {\
	struct CE_TYPE(t)* remel = *li->pprev;\
	struct CE_TYPE(t)* prev = remel->previous;\
	struct CE_TYPE(t)* next = remel->next;\
\
	if (prev != NULL) {\
		prev->next = next;\
		li->prev = &prev->next;\
	} else {\
		li->prev = NULL;\
	}\
\
	if (next != NULL) {\
		next->previous = prev;\
	}\
\
	li->pprev = NULL;\
	if (!li->static_list)\
		free(remel);\
}

/******************************************************************************//**
 * \brief Creates empty list
 *
 * This list can take any amount of elements and will resize itself when necessary.
 ********************************************************************************/
#define create_list(type) create_list ## type ()
/******************************************************************************//**
 * \brief Creates empty list, static type
 ********************************************************************************/
#define create_list_static(type, getter) create_list_static ## type (getter)
/******************************************************************************//**
 * \brief Removes left side of the list.
 *
 * Returns NULL if list is empty.
 ********************************************************************************/
#define list_remove_left(type, list) list_remove_left ## type (list)
/******************************************************************************//**
 * \brief Removes right side of the list.
 *
 * Returns NULL if list is empty.
 ********************************************************************************/
#define list_remove_right(type, list) list_remove_right ## type (list)
/******************************************************************************//**
 * \brief Returns head of the list without removing it.
 *
 * Returns NULL if list is empty.
 ********************************************************************************/
#define list_get_left(type, list) list_get_left ## type (list)
/******************************************************************************//**
 * \brief Returns last element of the list without removing it.
 *
 * Returns NULL if list is empty.
 ********************************************************************************/
#define list_get_right(type, list) list_get_right ## type (list)
/******************************************************************************//**
 * \brief Adds element to the list.
 *
 * Element is put at the head of the list.
 * Returns true if failure happened.
 ********************************************************************************/
#define list_push_left(type, list, value) list_push_left ## type (list, value)
/******************************************************************************//**
 * \brief Adds element to the list.
 *
 * Element is put at the end of the list.
 * Returns true if failure happened.
 ********************************************************************************/
#define list_push_right(type, list, value) list_push_right ## type (list, value)
/******************************************************************************//**
 * Returns true if list is not empty.
 ********************************************************************************/
#define list_has_elements(type, list) list_has_elements ## type (list)
/******************************************************************************//**
 * Returns number of elements in the list.
 ********************************************************************************/
#define list_size(type, list) list_size ## type (list)
/******************************************************************************//**
 * \brief Deallocates list.
 *
 * Removes all memory used by this list. Elements in the list are NOT
 * deallocated.
 ********************************************************************************/
#define free_list(type, list) free_list ## type (list)
/******************************************************************************//**
 * \brief Removes element from list at any position.
 *
 * Element is compared via ==.
 ********************************************************************************/
#define list_remove(type, element, list) list_remove ## type (element, list)
/******************************************************************************//**
 * \brief Returns element from list found by search predicate.
 *
 * For more info, see array.
 ********************************************************************************/
#define list_find_by_predicate(type, data, predicate, list) list_find_by_predicate ## type (data, predicate, list)
/******************************************************************************//**
 * \brief Deletes the element from list if predicate returns true
 *
 * Delete all elements that return true for predicate
 ********************************************************************************/
#define list_remove_by_predicate(type, data, predicate, list) list_remove_by_predicate ## type (data, predicate, list)
/******************************************************************************//**
 * Creates iterator for list
 ********************************************************************************/
#define list_create_iterator(type, list, iterator) list_create_iterator ## type (list, iterator)
/******************************************************************************//**
 * Returns true if list iterator has any element, or false if it does not.
 ********************************************************************************/
#define list_has_next(type, iterator) list_has_next ## type (iterator)
/******************************************************************************//**
 * \brief Returns next element of the list.
 *
 * Asking list iterator that has no elements left is UB.
 ********************************************************************************/
#define list_next(type, iterator) list_next ## type (iterator)
/******************************************************************************//**
 * \brief Removes current head from the iterator.
 *
 * Removes previously returned element from list_next.
 ********************************************************************************/
#define list_remove_it(type, iterator) list_remove_it ## type (iterator)

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_LLIST_H_ */
