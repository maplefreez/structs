#include "sort.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


/****** Pre-defination for test suits. ******/
static void t_straight_insertsort ();


int main (int argc, char* argv []) {
	t_straight_insertsort ();
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
		assert (sorted_seq [i] == sequence [i]);
	}

}



