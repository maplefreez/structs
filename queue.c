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

	/* The head points to the first dequeued 
	 * element in queue.
	 * The rear points to the next enqueued 
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
	return count_cqueue (_queue) == (_queue -> capacity - 1);
}


int count_cqueue (pcqueue _queue) {
	int count = (_queue -> rear - _queue -> head 
			+ _queue -> capacity) % _queue -> capacity;
	return count;
}


anytype enqueue_cqueue (pcqueue _queue, anytype _e) {
	/* I hope its memory should be 
		 reallocated this time instead 
	   of directly returning NULL when
	   there is no remaining space. */
	if (! _queue || count_cqueue (_queue) + 1 >= 
			_queue -> capacity) return NULL;
	// if ((_queue -> rear + 1) % _queue -> capacity
	// 			== _queue -> head) return NULL;

	_queue -> array [_queue -> rear] = _e;
	/* Update rear pointer to next 
		 inserting position. */
	_queue -> rear = (_queue -> rear + 1) 
		% (_queue -> capacity);
	return _e;
}


anytype dequeue_cqueue (pcqueue _queue) {
	if (_queue && ! isempty_cqueue (_queue)) {
		anytype e = _queue -> array [_queue -> head];

		/* Update head pointer to next 
		 dequeueing position. */
		_queue -> head = (_queue -> head + 1) 
			% (_queue -> capacity);
		return e;
	}

	return NULL;
}


void release_cqueue (pcqueue _queue) {
	if (! _queue) return;
	free (_queue -> array);
	free (_queue);
}


