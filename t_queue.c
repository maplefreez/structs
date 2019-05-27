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
	int res = 0;
	pcqueue queue = new_cqueue ();
	assert (queue);

	res = isfull_cqueue (queue);
	assert (res == 0);
	// TODO...
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
	}
}


