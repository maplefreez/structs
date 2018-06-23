#include "sort.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


/****** Pre-defination for test suits. ******/
static void t_straight_insertsort ();
static void t_binary_insertsort ();

static void t_select_sort ();


int main (int argc, char* argv []) {
	t_straight_insertsort ();
	t_binary_insertsort ();
	t_select_sort ();
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


