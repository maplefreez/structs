/* Date : 2019/9/7
 * Author : ez
 * Desc :  PAT A 1083
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct _stud {
	char name[16]; char ID[16]; 
	int grade;
} stud, *pstud;

#	define STUD_SIZE (sizeof (stud))
#	define INPUT_BUFFER_SIZE  64

/* Global variables. */
static int count, minscore, maxscore;
static stud input_buffer [INPUT_BUFFER_SIZE];

/* Function definations. */
static int __cmp (const void*, const void*);


int main (int argc, char* argv []) {
	int i = 0, output_num; pstud p;
	if (scanf ("%d", &count));

	/* Input. */
	p = input_buffer;
	while (i < count) {
		if (scanf ("%s %s %d", p -> name, 
					p -> ID, &p -> grade));
		++ p, ++ i;
	}
	if (scanf ("%d %d", &minscore, &maxscore));
	
	/* Sort, Process. */
	qsort (input_buffer, count, STUD_SIZE, __cmp);

	/* Search, Output. */
	output_num = 0, i ^= i;
	p = input_buffer;
	while (i < count) {
		if (p -> grade >= minscore && p -> grade <= maxscore) {
			printf ("%s %s\n", p -> name, p -> ID);
			output_num ++;
		}
		p ++; i ++;
	}
	if (! output_num) puts ("NONE");

	return 0;
}


static int __cmp (const void* _a, const void* _b) {
	pstud a = (pstud) _a, b = (pstud) _b;
	return b -> grade - a -> grade;
}


