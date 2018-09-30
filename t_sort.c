#include "sort.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


/****** Pre-defination for test suits. ******/
static void t_straight_insertsort ();
static void t_binary_insertsort ();

static void t_select_sort ();
static void t_bubble_sort ();
static void t_shell_sort ();


int main (int argc, char* argv []) {
	t_straight_insertsort ();
	t_binary_insertsort ();
	t_select_sort ();
	t_bubble_sort ();
	t_shell_sort ();
	return 0;
}


static void t_straight_insertsort () {
	int64_t sequence [] = {
		8, 3, 9, 4, 12, 
		83, 1, 0, 10, 32
	};

	int64_t sorted_seq [] = {
		0, 1, 3, 4, 8, 
		9, 10, 12, 32, 83
	};

	int num = sizeof (sequence) / sizeof (int64_t);
	int i = 0;
	anytype* res;
	res = straight_insertsort ((anytype*) sequence, num, NULL);

	assert (res != NULL);
	for (; i < num; ++ i) {
		assert (sorted_seq [i] == res [i]);
	}

}


static void t_binary_insertsort () {
	int64_t sequence [] = {
		8, 3, 9, 4, 12, 
		83, 1, 0, 10, 32
	};

	int64_t sorted_seq [] = {
		0, 1, 3, 4, 8, 
		9, 10, 12, 32, 83
	};

	int num = sizeof (sequence) / sizeof (int64_t);
	int i = 0;
	anytype* res;
	res = binary_insertsort ((anytype*) sequence, num, NULL);

	assert (res != NULL);
	for (; i < num; ++ i) {
		assert (sorted_seq [i] == res [i]);
	}
}



static void t_select_sort () {
	int64_t sequence [] = {
		8, 3, 9, 4, 12, 
		83, 1, 0, 10, 32
	};

	int64_t sorted_seq [] = {
		0, 1, 3, 4, 8, 
		9, 10, 12, 32, 83
	};

	int num = sizeof (sequence) / sizeof (int64_t);
	int i = 0;
	anytype* res;
	res = select_sort ((anytype*) sequence, num, NULL);

	assert (res != NULL);
	for (; i < num; ++ i) {
		assert (sorted_seq [i] == res [i]);
	}
}

static void t_bubble_sort () {
	int64_t sorted_seq [] = {
		0, 1, 3, 4, 8, 
		9, 10, 12, 32, 83
	};

	const int num = 
		sizeof (sorted_seq) / sizeof (int64_t);
	int i = 0;
	anytype* res;

	{
		int64_t sequence [] = {
			8, 3, 9, 4, 12, 
			83, 1, 0, 10, 32
		};

		res = bubble_sort ((anytype*) sequence, num, NULL);

		assert (res != NULL);
		for (; i < num; ++ i) {
			assert (sorted_seq [i] == res [i]);
		}
	}


	{
		int64_t sequence [] = {
			8, 3, 9, 4, 12, 
			83, 1, 0, 10, 32
		};

		res = bubble_sort1 ((anytype*) sequence, num, NULL);

		assert (res != NULL);
		for (; i < num; ++ i) {
			assert (sorted_seq [i] == res [i]);
		}
	}

}

static void t_shell_sort () {
	int64_t sequence [] = {
		8, 3, 9, 4, 12, 
		83, 1, 0, 10, 32
	};

	int64_t sorted_seq [] = {
		0, 1, 3, 4, 8, 
		9, 10, 12, 32, 83
	};

	const int num = 
		sizeof (sorted_seq) / sizeof (int64_t);
	int i = 0;
	anytype* res;

	res = shell_sort ((anytype*) sequence, num, NULL);

	assert (res != NULL);
	for (; i < num; ++ i)
		assert (sorted_seq [i] == (int64_t) res [i]);

}



