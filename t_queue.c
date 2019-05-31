#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"


/****** Pre-defination for test suits. ******/
static void t_cqueue_new ();
static void t_linklist_insert ();
static void t_cqueue_isempty ();
static void t_cqueue_isfull ();
static void t_cqueue_count ();
static void t_cqueue_enqueue ();


/* Main test entry. */
int main (int argc, char* argv []) {
	t_cqueue_new ();
	t_cqueue_isempty ();
	t_cqueue_isfull ();
	t_cqueue_count ();
	t_cqueue_enqueue ();
	return 0;
}


static void t_cqueue_new () {
	pcqueue queue = new_cqueue ();
	assert (queue);
	assert (queue -> rear == queue -> head && 
			queue -> head == 0);
	assert (queue -> capacity == __DEF_QUEUE_INIT_LEN);
	release_cqueue (queue);
}


static void t_cqueue_isempty () {
	int res = 0;
	pcqueue queue = new_cqueue ();
	assert (queue);

	res = isempty_cqueue (queue);
	assert (res == 1);
	// TODO...
}

static void t_cqueue_isfull () {
	{ // 0x01
		int res = 0;
		pcqueue queue = new_cqueue ();
		assert (queue);

		res = isfull_cqueue (queue);
		assert (res == 0);
		release_cqueue (queue);
	}

	{
		int x = 1; int count; 
		pcqueue q = new_cqueue ();
		assert (q);

		for (; x <= 14; ++ x) {
			assert (enqueue_cqueue (q, (anytype) x));
			assert (! isfull_cqueue (q));
		}

		count = count_cqueue (q);
		assert (enqueue_cqueue (q, (anytype) x));
		assert (isfull_cqueue (q));

		release_cqueue (q);
	}

}

static void t_cqueue_count () {
	int res = 0;
	pcqueue queue = new_cqueue ();
	assert (queue);

	res = count_cqueue (queue);
	assert (res == 0);
	// TODO...
}


static void t_cqueue_enqueue () {
	{ // 0x1
		pcqueue queue = new_cqueue ();
		assert (queue);

		anytype ret = enqueue_cqueue (queue, (anytype) 323);
		assert (ret == (anytype*) 323);

		assert (queue -> head == 0);
		assert (queue -> rear == 1);
		release_cqueue (queue);
	}

	{ // 0x2
		int x, y; anytype ret = NULL;
		pcqueue queue = new_cqueue ();
		assert (queue);
#	define _a_func_for_the_test_(___X)  ((___X)<<1 + 6)
		
		for (x ^=x; x < 15; ++ x) {
			y = _a_func_for_the_test_(x);
			ret = enqueue_cqueue (queue, (anytype) y);
			assert (ret == (anytype*) y);
			assert (queue -> head == 0);
			assert (queue -> rear == (x + 1));
		}

		/* Enqueue the 16th element. */
		y = _a_func_for_the_test_(x);
		ret = enqueue_cqueue (queue, (anytype) y);
		// assert (ret == (anytype*) y);
		assert (ret == NULL);

		assert (queue -> head == 0);
		assert (queue -> rear == 15);

		/* Doing nothing. */
		for (x ^= x; x < 1024; ++ x) {
			y = _a_func_for_the_test_ (x);
			assert (enqueue_cqueue (queue, (anytype) y) 
					== NULL);
			assert (queue -> head == 0);
			assert (queue -> rear == 15);
		}

#undef _a_func_for_the_test_
		release_cqueue (queue);
	}
}


