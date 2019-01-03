#include "queue.h"
#include <stdlib.h>


/* Create a new cycle queue entity with preallocated
 * space length of macro __DEF_QUEUE_INIT_LEN. Return
 * the ptr if successful, else return NULL. */
pcqueue new_cqueue () {
	return create_cqueue (__DEF_QUEUE_INIT_LEN);
}


pcqueue create_cqueue (int _n) {
	pcqueue ret = NULL;
	ret = (pcqueue) malloc (sizeof (cqueue));
	if (! ret) return ret;

	ret -> array = malloc (sizeof (anytype) * _n);
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
	
extern pcqueue create_cqueue_by_arr (anytype*, int);


int isempty_cqueue (pcqueue _queue) {
	return _queue -> rear == _queue -> head;
}


int isfull_cqueue (pcqueue _queue) {
	return count_cqueue (_queue) == _queue -> capacity;
}


int count_cqueue (pcqueue _queue) {
	int count = (_queue -> head - _queue -> rear
			+ _queue -> capacity) % _queue -> capacity;
	return count;
}


anytype enqueue_cqueue (pcqueue _queue, anytype _e) {
	// TODO...
}


extern anytype dequeue_cqueue (pcqueue);


void release_cqueue (pcqueue _queue) {
	if (! _queue) return;
	free (_queue -> array);
	free (_queue);
}


