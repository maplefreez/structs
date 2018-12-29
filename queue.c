#include "queue.h"
#include <stdlib.h>


/* Create a new cycle queue entity with preallocated
 * space length of macro __DEF_QUEUE_INIT_LEN. Return
 * the ptr if successful, else return NULL. */
pcqueue new_cqueue () {
	pcqueue ret = NULL;
	ret = (pcqueue) malloc (sizeof (cqueue));
	if (! ret) return ret;

	ret -> array = malloc (sizeof (anytype) 
			* __DEF_QUEUE_INIT_LEN);
	if (! (ret -> array)) {
		free (ret);
		return NULL;
	}

	/* The rear points to the last index 
	 * of element in queue.
	 * The head points to the next enqueued 
	 * position in queue. 
	 * I initially set rear and head 
	 * to zero. */
	ret -> rear = 0; ret -> head = 0;
	ret -> capacity = __DEF_QUEUE_INIT_LEN;
	return ret;
}


extern pcqueue create_cqueue (int);
extern pcqueue create_cqueue_by_arr (anytype*, int);
extern int isempty_cqueue (pcqueue);
extern int isfull_cqueue (pcqueue);
extern int count_cqueue (pcqueue);
extern anytype enqueue_cqueue (pcqueue, anytype);
extern anytype dequeue_cqueue (pcqueue);

void release_cqueue (pcqueue _queue) {
	// TODO...
}


