/* Date : 2019/8/15
 * Author : ez
 * Desc :  PAT A 1028
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _stud {
	int id; char name [16];
	int grade;
} stud, *pstud;
#	define STUD_SIZE (sizeof (stud))

/* Function definations. */
static int __cmp1 (const void*, const void*);
static int __cmp2 (const void*, const void*);
static int __cmp3 (const void*, const void*);
static int __empty_cmp (const void*, const void*);

/* Global variables. */
typedef int (*_cmp_func) (const void*, const void*);
static _cmp_func __cmp_funcs [4] = {
	__empty_cmp,
	__cmp1, __cmp2, __cmp3
};
static stud input_buffer [100008];

int main (int argc, char* argv []) {
	int key_column, count, i = 0;
	if (scanf ("%d %d", &count, &key_column)) ;
	if (key_column > 3 || key_column < 1) 
		abort ();

	/* Input. */
	while (i < count) {
		if (scanf ("%d %s %d", &input_buffer [i].id,
					input_buffer [i].name, &input_buffer [i].grade)) ;
		++ i;
	}

	/* Sort. */
	qsort (input_buffer, count, STUD_SIZE, 
			__cmp_funcs [key_column]);

	/* Output */
	i ^= i;
	while (i < count) {
		(void) printf ("%06d %s %d\n", input_buffer [i].id,
					input_buffer [i].name, input_buffer [i].grade);
		i ++;
	}

	return 0;
}


static int __cmp1 (const void* _a, const void* _b) {
	pstud a = (pstud) _a, b = (pstud) _b;
	return a -> id - b -> id;
}

static int __cmp2 (const void* _a, const void* _b) {
	int tmp;
	pstud a = (pstud) _a, b = (pstud) _b;
	tmp = strncmp (a -> name, b -> name, 8);
	if (tmp) return tmp;
	return a -> id - b -> id;
}

static int __cmp3 (const void* _a, const void* _b) {
	int tmp;
	pstud a = (pstud) _a, b = (pstud) _b;
	tmp = a -> grade - b -> grade;
	if (tmp) return tmp;
	return a -> id - b -> id;
}

static int __empty_cmp (const void* _a, const void* _b) {
	return 0;
}

