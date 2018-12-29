/* Author : ez
 * Date : 2018/12/29
 *
 */

#ifndef _QUEUE_H_
#	define _QUEUE_H_

#include "common.h"

#	define __DEF_QUEUE_INIT_LEN	 16

/* A simple circle queue definition whose
 * element stored in array. */
typedef struct _cqueue {
	anytype* array;

	/* The rear points to the last index 
	 * of element in queue.
	 * The head points to the next enqueued 
	 * position in queue. 
	 * I initially set rear and head 
	 * to zero. */
	int rear; int head;
	int capacity;
} cqueue, *pcqueue;


extern pcqueue new_cqueue ();
extern pcqueue create_cqueue (int);
extern pcqueue create_cqueue_by_arr (anytype*, int);

/* Return 1 if the queue entity is empty. Else 
 * return 0;
 * $1  The cycle queue entity ptr. 
 *
 * Note: I use the statement below:
 *    'queue -> rear == queue -> head';
 */
extern int isempty_cqueue (pcqueue);

/* Return 1 if the queue entity is full. Else
 * return 0;
 * $1  The cycle queue entity ptr. */
extern int isfull_cqueue (pcqueue);

/* Return the number of elements in the queue 
 * entity.
 * $1  The cycle queue entity ptr.
 *
 * Note: I use the statement below to calculate:
 *    '((head - rear) + capacity) % capacity'
 */
extern int count_cqueue (pcqueue);
extern anytype enqueue_cqueue (pcqueue, anytype);
extern anytype dequeue_cqueue (pcqueue);
extern void release_cqueue (pcqueue);

#endif // ~ _QUEUE_H_
