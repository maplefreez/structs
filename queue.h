/* Author : ez
 * Date : 2018/12/29
 *
 */

#ifndef _QUEUE_H_
#	define _QUEUE_H_

#include "common.h"

#	define __DEF_QUEUE_INIT_LEN	 16

/* A simple circle queue definition whose
 * element stored in array. 
 *
 * Status about the three variables:
 * 1) Empty queue :  rear == head
 * 2) The number of element in queue:
 *     C = (rear - head + capacity) mod capacity
 * 3) Full queue :  C == capacity; */
typedef struct _cqueue {
	anytype* array;

	/* The head points to the first dequeued 
	 * element in queue.
	 * The rear points to the next enqueued 
	 * position in queue. 
	 * I initially set rear and head 
	 * to zero. */
	int rear; int head;

	/* Note: Cause an extra space, that is 
		 pointed to by the rear is used to 
		 flag the state of full, the actual 
		 available space loses it. */
	int capacity;
} cqueue, *pcqueue;


extern pcqueue new_cqueue ();
extern pcqueue create_cqueue (int);
extern pcqueue create_cqueue_by_arr (anytype*, int);

/* Return 1 if the queue entity is empty. Else 
 * return 0;
 * $1  The cycle queue entity ptr. It must not
 *      be NULL.
 *
 * Note: I use the statement below:
 *    'queue -> rear == queue -> head';
 */
extern int isempty_cqueue (pcqueue);

/* Return 1 if the queue entity is full. Else
 * return 0;
 * $1  The cycle queue entity ptr. It must not
 *      be NULL.
 */
extern int isfull_cqueue (pcqueue);

/* Return the number of elements in the queue 
 * entity.
 * $1  The cycle queue entity ptr. It must not
 *      be NULL.
 *
 * Note: I use the statement below to calculate:
 *    '((rear - head) + capacity) % capacity'
 */
extern int count_cqueue (pcqueue);


extern anytype enqueue_cqueue (pcqueue, anytype);

/* Return the element at the header of queue.
 * $1  The cycle queue entity ptr. If the function
 *      get a NULL ptr, it directly returns NULL.
 */
extern anytype dequeue_cqueue (pcqueue);


extern void release_cqueue (pcqueue);

#endif // ~ _QUEUE_H_

