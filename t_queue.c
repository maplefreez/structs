#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "queue.h"


/****** Pre-defination for test suits. ******/
static void t_cqueue_new ();
static void t_linklist_insert ();
static void t_cqueue_isempty ();
static void t_cqueue_isfull ();
static void t_cqueue_count ();
static void t_cqueue_enqueue ();
static void t_cqueue_dequeue ();
static void t_cqueue_create_by_arr ();


/* Main test entry. */
int main (int argc, char* argv []) {
	t_cqueue_new ();
	t_cqueue_dequeue ();
	t_cqueue_enqueue ();
	t_cqueue_count ();
	t_cqueue_isempty ();
	t_cqueue_isfull ();
	t_cqueue_create_by_arr ();
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
	{ // 0x01
		int res = 0;
		pcqueue queue = new_cqueue ();
		assert (queue);

		res = isempty_cqueue (queue);
		assert (res == 1);
		release_cqueue (queue);
	}

	{ // 0x02
		int res = 0, i;
		pcqueue queue = new_cqueue ();
		assert (queue);

		res = isempty_cqueue (queue);
		assert (res == 1);
		
		/* Enqueue 15 elements. */
		for (i = 1; i < __DEF_QUEUE_INIT_LEN; ++ i) 
			{
				assert (enqueue_cqueue (queue, (anytype) i));
				assert (! isempty_cqueue (queue));
			}

		/* Dequeue 15 elements. */
		i ^= i;
		while (++ i < __DEF_QUEUE_INIT_LEN - 1) {
			assert (dequeue_cqueue (queue));
			assert (! isempty_cqueue (queue));
		}

		assert (dequeue_cqueue (queue));
		assert (isempty_cqueue (queue));

		release_cqueue (queue);
	}
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

	{ // 0x02
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

	{ // 0x03 
		int x = 1;
		pcqueue q = new_cqueue ();
		assert (q);

		for (; x <= 14; ++ x) {
			assert (enqueue_cqueue (q, (anytype) x));
			assert (! isfull_cqueue (q));
		}
		assert (enqueue_cqueue (q, (anytype) x));
		assert (isfull_cqueue (q));

		/* Dequeue 9 elements. */
		while (x ++ <= 23) {
			assert (dequeue_cqueue (q));
			assert (! isfull_cqueue (q));
		}

		/* Enqueue 9 elements. */
		while (x ++ <= 32) {
			assert (enqueue_cqueue (q, (anytype) x));
			assert (! isfull_cqueue (q));
		}

		assert (enqueue_cqueue (q, (anytype) x));
		assert (isfull_cqueue (q));

		release_cqueue (q);
	}

}

static void t_cqueue_count () {
	{ // 0x01
		int i, flag, c = 0;
		int num = 0;
		pcqueue q = new_cqueue ();
		assert (q);

		assert (0 == count_cqueue (q));

		srand (time (NULL));
		for (i = 1; i <= 4096; ++ i) {
			num = rand ();
			srand (num);
			flag = num >= RAND_MAX / 2;

			if (flag) {
				c += !! (flag && !! enqueue_cqueue (q, (anytype) i));
				assert (c == count_cqueue (q));
			} else {
				c -= !! dequeue_cqueue (q);
				assert (c == count_cqueue (q));
			}
		}

		release_cqueue (q);
	}
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

		/* Enqueue the 16th element. This might
		   trigger memory auto-extending. */
		y = _a_func_for_the_test_(x);
		ret = enqueue_cqueue (queue, (anytype) y);
		assert (ret == (anytype*) y);

		assert (queue -> head == 0);
		assert (queue -> rear == 16);

		/* Doing nothing. */
		clean_cqueue (queue);
		for (x ^= x; x < 1023; ++ x) {
			y = _a_func_for_the_test_ (x);
			assert (enqueue_cqueue (queue, (anytype) y) 
					== (anytype) y);
			assert (queue -> head == 0);
			assert (queue -> rear == x + 1);
			assert (x + 1 == count_cqueue (queue));
		}

		/* Enqueue the 1024th element. */
		assert (! enqueue_cqueue (queue, 
					(anytype) _a_func_for_the_test_ (x)));
		assert (isfull_cqueue (queue));

		/* Dequeue each element. */
		for (x ^= x; x < 1023; ++ x) {
			anytype y = dequeue_cqueue (queue);
			assert (y == (anytype) _a_func_for_the_test_ (x));
			assert (count_cqueue (queue) == 1022 - x);
			assert (queue -> head == x + 1);
			assert (queue -> rear == 1023);
		}

		assert (isempty_cqueue (queue));

#undef _a_func_for_the_test_
		release_cqueue (queue);
	}
}


static void t_cqueue_dequeue () {
	{ // 0x1
		anytype ret = dequeue_cqueue (NULL);
		assert (! ret);
	}

	{ // 0x2
		pcqueue q = new_cqueue ();
		assert (q);
		anytype ret = dequeue_cqueue (q);
		assert (! ret);
		release_cqueue (q);
	}

	{ // 0x03
		int sequence [] = {
			834, 2323, 88, 923,
			15, 20, 7834, -123,
			478, -843, 2304-23, 78,
			32, 7832, 97 - 23 
		}, count, i;

		pcqueue q = new_cqueue ();
		assert (q);
		
		for (i = 0; i < 0xf; ++ i) {
			assert (enqueue_cqueue (q, 
					(anytype) (sequence [i])));
		}

		for (i = 0; i < 0xf; ++ i) {
			anytype res = dequeue_cqueue (q);
			assert (res == (anytype) sequence [i]);
		}

		release_cqueue (q);
	}

	{ // 0x04
		int sequence [] = {
			1, 2, 3, 4, 5, 6, 
			7, 8, 9, 10, 11, 12,
			13, 14, 15
		}, count, i;

		pcqueue q = new_cqueue ();
		assert (q);
		
		/* We consider index 9 as the 
			 rear, which points to the 
			 next inserted position. And
		   index 10 is the head. */
		q -> head = 10; q -> rear = 9;
		/* Indexes from 10 to 15 store 
		   Sequence[0, 5]. */
		for (i = 10; i <= 15; ++ i)
			q -> array [i] = sequence [i - 10];
		/* Indexes from 0 to 8 store 
		   Sequence[6, 14]. */
		for (i = 0; i <= 8; ++ i)
			q -> array [i] = sequence [i + 6];

		/* The dequeue sequence must be ascending
		   as to the construction. */
		count = count_cqueue (q);
		assert (count == __DEF_QUEUE_INIT_LEN - 1);
		for (i = 0; i < count; ++ i) {
			anytype res = dequeue_cqueue (q);
			assert (res == (anytype) sequence [i]);
		}

		assert (isempty_cqueue (q));
		release_cqueue (q);
	}


}

static void t_cqueue_create_by_arr () {
	{ // 0x01
		anytype array [1024] = {0, };
		assert (! create_cqueue_by_arr (array, 1024));
		assert (! create_cqueue_by_arr (NULL, 512));
		assert (! create_cqueue_by_arr (NULL, 0));
		assert (! create_cqueue_by_arr (NULL, -128));
		assert (! create_cqueue_by_arr (array, -513));
	}

	{ // 0x02
		int i; pcqueue q = NULL;
		anytype array [__MAX_QUEUE_LEN] = {0, };

		/* Initialize array. */
		for (i = 0; i < __MAX_QUEUE_LEN - 1; ++ i)
			array [i] = i + 1;

		/* A cycle queue with (__MAX_QUEUE_LEN - 1) elements. */
		q = create_cqueue_by_arr (array, __MAX_QUEUE_LEN - 1);
		assert (q); assert (isfull_cqueue (q));
		assert (q -> capacity == __MAX_QUEUE_LEN);
		assert (q -> head == 0); 
		assert (q -> rear == __MAX_QUEUE_LEN - 1);

		/* Dequeue each element. */
		for (i = 0; i < __MAX_QUEUE_LEN - 1; ++ i)
			assert (array [i] == dequeue_cqueue (q));

		assert (isempty_cqueue (q));
		release_cqueue (q);
	}

	{ // 0x03
		int i; pcqueue q = NULL;
		anytype array [__MAX_QUEUE_LEN] = {0, };

		/* Initialize the input array. */
		for (i = 0; i < __MAX_QUEUE_LEN - 1; ++ i)
			array [i] = i + 1;

		q = create_cqueue_by_arr (array, __MAX_QUEUE_LEN - 1);
		assert (q); 
		assert (q -> capacity == __MAX_QUEUE_LEN);
		assert (q -> head == 0); 
		assert (q -> rear == __MAX_QUEUE_LEN - 1);

		release_cqueue (q);
	}

}


