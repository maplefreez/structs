#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"


/****** Pre-defination for test suits. ******/
static void t_cqueue_new ();
static void t_linklist_insert ();


/* Main test entry. */
int main (int argc, char* argv []) {
	t_cqueue_new ();
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

