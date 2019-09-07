/* Date : 2019/8/16
 * Author : ez
 * Desc :  PAT A 1055
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct _rcd {
	char name [16];
	int age; int worth;
} rcd, *prcd;

#	define RCD_SIZE (sizeof (rcd))

/* Global variables. */
static rcd input_buffer [100010], valid_buffer [200000];
static int input_count, valid_count;
static uint8_t count_per_age [208] = {0, };

/* Function definations. */
static int _cmp (const void*, const void*);
static void _pre_select ();
static void _process_case (int, int, int);

int main (int argc, char* argv []) {
	int case_num, i = 0, amin, amax, top_num;
	/* Input. */
	if (scanf ("%d %d", &input_count, &case_num)) ;
	while (i < input_count) {
		if (scanf ("%s %d %d", input_buffer [i].name,
					&input_buffer [i].age, 
					&input_buffer [i].worth)); 
		++ i;
	}

	/* Pre-selection. */
	_pre_select ();

	/* Process. */
	i ^= i;
	while (i ++ < case_num) {
		if (scanf ("%d %d %d", &top_num, &amin, &amax)) ;
		printf ("Case #%d:\n", i);
		_process_case (amin, amax, top_num);
	}
	return 0;
}


static int _cmp (const void* _a, const void* _b) {
	int tmp = 0;
	prcd a = (prcd) _a, b = (prcd) _b;
	/* Worth non-increasing. */
	tmp = b -> worth - a -> worth;
	if (tmp) return tmp;
	/* Age non-decreasing. */
	tmp = a -> age - b -> age;
	/* Name non-decreasing. */
	if (tmp) return tmp;
	return strncmp (a -> name, b -> name, 16);
}

static void _process_case (int _amin, 
		int _amax, int top_num) {
	int output_num = 0, i = 0;
	while (i < valid_count && 
			output_num < top_num) {
		if (valid_buffer [i].age >= _amin && 
				valid_buffer [i].age <= _amax) {
			printf ("%s %d %d\n", valid_buffer [i].name, 
					valid_buffer [i].age, valid_buffer [i].worth);
			++ output_num;
		} 
		++ i;
	}
	
	if (! output_num) puts ("None"); 
	return;
}

static void _pre_select () {
	int i = 0; valid_count = 0;

	qsort (input_buffer, input_count, RCD_SIZE, _cmp);

	while (i < input_count) {
		prcd p = input_buffer + (i ++);
		if (count_per_age [p -> age] < 100) {
			count_per_age [p -> age] ++;
			valid_buffer [valid_count ++] = *p;
		}
	}
	return;
}

