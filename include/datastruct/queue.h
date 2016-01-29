/*
 * queue.h
 *
 *  Created on: Jan 27, 2016
 *      Author: enerccio
 */

#ifndef INCLUDE_DATASTRUCT_QUEUE_H_
#define INCLUDE_DATASTRUCT_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kclib.h>
#include <datastruct/dscommons.h>

#define QUEUE_TYPE(type) __queue_ ## type ## _t

#define QUEUE_HEADER(t) \
CE_TYPEDEF(t); \
CE_ELEMENT_GETTER(t); \
SEARCH_PREDICATE(t); \
typedef struct QUEUE_TYPE(t) {\
    bool is_static;\
    struct CE_TYPE(t)* first;\
    struct CE_TYPE(t)* last;\
    uint32_t size;\
    CE_ELEMENT_GETTER_TYPE(t) static_getter;\
} QUEUE_TYPE(t);\
QUEUE_TYPE(t)* create_queue ## t();\
QUEUE_TYPE(t)* create_queue_static ## t(CE_ELEMENT_GETTER_TYPE(t) getter);\
t queue_pop ## t(QUEUE_TYPE(t)* queue);\
t queue_peek ## t(QUEUE_TYPE(t)* queue);\
bool queue_has_elements ## t(QUEUE_TYPE(t)* queue);\
bool queue_push ## t(QUEUE_TYPE(t)* queue, t data);\
uint32_t queue_size ## t(QUEUE_TYPE(t)* queue);\
void free_queue ## t(QUEUE_TYPE(t)* queue);\
void queue_remove ## t(t element, QUEUE_TYPE(t)* queue);\
t queue_find_by_predicate ## t(void* data, SEARCH_PREDICATE_TYPE(t) func, QUEUE_TYPE(t)* queue);\

#define QUEUE_FUNCDEFS(t) \
QUEUE_TYPE(t)* create_queue ## t(){\
	QUEUE_TYPE(t)* queue = (QUEUE_TYPE(t)*) malloc(sizeof(QUEUE_TYPE(t)));\
	if (queue == NULL)\
		return NULL;\
	queue->first = 0;\
	queue->last = 0;\
	queue->size = 0;\
	queue->is_static = false;\
	return queue;\
}\
QUEUE_TYPE(t)* create_queue_static ## t(CE_ELEMENT_GETTER_TYPE(t) getter){\
	QUEUE_TYPE(t)* queue = (QUEUE_TYPE(t)*) malloc(sizeof(QUEUE_TYPE(t)));\
	if (queue == NULL)\
		return NULL;\
	queue->first = 0;\
	queue->last = 0;\
	queue->size = 0;\
	queue->static_getter = getter;\
	queue->is_static = true;\
	return queue;\
}\
t queue_pop ## t(QUEUE_TYPE(t)* queue){\
	struct CE_TYPE(t)* queue_head = queue->first;\
	if (queue_head == 0)\
		return 0;\
\
	if (queue->size == 1) {\
		queue->first = 0;\
		queue->last = 0;\
		queue->size = 0;\
		t data = queue_head->data;\
		if (queue->is_static != true)\
			free(queue_head);\
		return data;\
	}\
\
	t data = queue_head->data;\
	queue->first = queue_head->next;\
\
	if (queue->is_static != true)\
		free(queue_head);\
\
	queue->size--;\
	return data;\
}\
t queue_peek ## t(QUEUE_TYPE(t)* queue){\
	struct CE_TYPE(t)* queue_head = queue->first;\
	if (queue_head == 0)\
		return 0;\
\
	return queue_head->data;\
}\
bool queue_has_elements ## t(QUEUE_TYPE(t)* queue){\
	return queue_size(t, queue) > 0;\
}\
bool queue_push ## t(QUEUE_TYPE(t)* queue, t data){\
	struct CE_TYPE(t)* element;\
	if (queue->is_static == true)\
		element = queue->static_getter(data);\
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
	if (queue->first == 0) {\
		queue->first = queue->last = element;\
		queue->size = 1;\
	} else {\
		queue->last->next = element;\
		element->previous = queue->last;\
		queue->last = element;\
		queue->size++;\
	}\
\
	return false;\
}\
uint32_t queue_size ## t(QUEUE_TYPE(t)* queue){\
	return queue->size;\
}\
void free_queue ## t(QUEUE_TYPE(t)* queue){\
	if (queue->is_static == true) {\
		free(queue);\
	} else {\
		struct CE_TYPE(t)* el = queue->first;\
		while (el != 0) {\
			struct CE_TYPE(t)* tmp = el->next;\
			free(el);\
			el = tmp;\
		}\
		free(queue);\
	}\
}\
void queue_remove ## t(t element, QUEUE_TYPE(t)* queue){\
	if (queue->size == 0)\
		return;\
\
	struct CE_TYPE(t)* e = queue->first;\
	while (e != 0 && e->data != element)\
		e = e->next;\
\
	if (e) {\
		if (e->previous)\
			e->previous->next = e->next;\
		if (e->next)\
			e->next->previous = e->previous;\
		if (queue->is_static != true)\
			free(e);\
	}\
}\
t queue_find_by_predicate ## t(void* data, SEARCH_PREDICATE_TYPE(t) func, QUEUE_TYPE(t)* queue){\
	if (queue->size == 0)\
		return 0;\
\
	struct CE_TYPE(t)* e = queue->first;\
	while (e != 0 && func(e->data, data) == false)\
		e = e->next;\
\
	if (e)\
		return e->data;\
	else\
		return 0;\
}\

/******************************************************************************//**
 * \brief Creates empty queue
 *
 * This queue can take any amount of elements and will resize itself when necessary.
 ********************************************************************************/
#define create_queue(type) create_queue ## type ()
/******************************************************************************//**
 * \brief Creates empty queue, using data as value
 *
 * This queue can take any amount of elements and will resize itself when necessary.
 ********************************************************************************/
#define create_queue_static(type, getter) create_queue_static ## type (getter)
/******************************************************************************//**
 * \brief Removes head of the queue and returns it.
 *
 * Returns NULL if queue is empty.
 ********************************************************************************/
#define queue_pop(type, queue) queue_pop ## type (queue)
/******************************************************************************//**
 * \brief Returns head of the queue without removing it.
 *
 * Returns NULL if queue is empty.
 ********************************************************************************/
#define queue_peek(type, queue) queue_peek ## type (queue)
/******************************************************************************//**
 * Returns true if queue is not empty.
 ********************************************************************************/
#define queue_has_elements(type, queue) queue_has_elements ## type (queue)
/******************************************************************************//**
 * \brief Adds element to the queue.
 *
 * Element is put at the end of the queue.
 * Returns true if failure happened.
 ********************************************************************************/
#define queue_push(type, queue, data) queue_push ## type (queue, data)
/******************************************************************************//**
 * Returns number of elements in the queue.
 ********************************************************************************/
#define queue_size(type, queue) queue_size ## type (queue)
/******************************************************************************//**
 * \brief Deallocates queue.
 *
 * Removes all memory used by this queue. Elements in the queue are NOT
 * deallocated.
 ********************************************************************************/
#define free_queue(type, queue) free_queue ## type (queue)
/******************************************************************************//**
 * \brief Removes element from queue at any position.
 *
 * Element is compared via ==.
 ********************************************************************************/
#define queue_remove(type, element, queue) queue_remove ## type (element, queue)
/******************************************************************************//**
 * \brief Returns element from queue found by search predicate.
 *
 * For more info, see array.
 ********************************************************************************/
#define queue_find_by_predicate(type, data, func, queue) queue_find_by_predicate ## type (data, func, queue)

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_DATASTRUCT_QUEUE_H_ */
