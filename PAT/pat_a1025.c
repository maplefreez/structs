/* Date : 2019/8/15
 * Author : ez
 * Desc :  PAT A 1025
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _rcd {
	char id [16];
	int score; int localnum;
	int localrank; int rank;
} rcd, *prcd;

#	define RCD_SIZE (sizeof (rcd))

/* Global variables. */
static rcd input_buffer [30002];
static int input_count, input_group;

/* Function definations. */
static int __cmp (const void*, const void*);
static int _process_group (int, int, int);
static void _rank_group (int, int);
static void _rank ();
static void _output ();
static void _process_all ();
static void _init_global ();

/* Main function. */
int main (int argc, char* argv []) {
	int i = 1, group_num;

	_init_global ();
	if (scanf ("%d", &input_group)) ;
	while (i <= input_group) {
		if (scanf ("%d", &group_num)) ;
		_process_group (input_count, group_num, i);
		++ i;
	}

	_process_all ();
	
	return 0;
}

static int __cmp (const void* _a, const void* _b) {
	int tmp;
	prcd a = (prcd) _a, b = (prcd) _b;
	tmp = b -> score - a -> score;
	if (tmp) return tmp;
	return strncmp (a -> id, b -> id, 13);
}

static int _process_group (int _start, int _count, int _localnum) {
	int i = _start, end = _start + _count - 1,
		group_count = 0;
	while (i <= end) {
		if (scanf ("%s %d", input_buffer [i].id, 
					&(input_buffer [i].score))) ;
		group_count ++;
		input_buffer [i].localnum = _localnum;
		++ i;
	}

	input_count += group_count;
	qsort (input_buffer + _start, _count, RCD_SIZE, __cmp);
	_rank_group (_start, _count);

	return group_count;
}

static void _rank_group (int _start, int _cnt) {
	int i = _start, end = _cnt + _start - 1, 
			rank, last_score, num;
	rank = num = 1; last_score = -100;
	while (i <= end) {
		if (last_score != input_buffer [i].score) {
			input_buffer [i].localrank = rank = num;
			last_score = input_buffer [i].score;
		} else
			input_buffer [i].localrank = rank;
		num ++; ++ i;
	}
}

static void _output () {
	int i = 0;
	(void) printf ("%d\n", input_count);
	while (i < input_count) {
		printf ("%s %d %d %d\n", input_buffer [i].id,
				input_buffer [i].rank, input_buffer [i].localnum,
				input_buffer [i].localrank);
		++ i;
	}
}

static void _process_all () {
	qsort (input_buffer, input_count, RCD_SIZE, __cmp);
	_rank ();
	_output ();
}

static void _rank () {
	int i = 0, end = input_count - 1, 
			rank, last_score, num;
	rank = num = 1; last_score = -100;
	while (i <= end) {
		if (last_score != input_buffer [i].score) {
			input_buffer [i].rank = rank = num;
			last_score = input_buffer [i].score;
		} else
			input_buffer [i].rank = rank;
		num ++;
		++ i;
	}
}

static void _init_global () {
	input_count = input_group = 0;
}


