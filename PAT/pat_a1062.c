/* Date : 2019/7/18
 * Author : ez
 * Desc :  PAT A 1001
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _stud {
	char NO [10];
	int D; int C;
	int class;
} stud, *pstud;

stud all [100010];

static int __cmp (const void* _a, const void* _b) {
	int sumA, sumB;
	pstud a = (pstud)_a, b = (pstud)_b;
	if (a -> class != b -> class) 
		return b -> class - a -> class;
	sumA = a -> D + a -> C;
	sumB = b -> D + b -> C;
	/* The same class. */
	if (sumA != sumB) return (sumA - sumB);
	/* The same total scores. */
	if (a -> D != b -> D)
		return a -> D - b -> D;

	return strncmp (a -> NO, b -> NO, 8);
}

int main (int argc, char* argv []) {
	int n, L, H, i = 0, past = 0;
	if (scanf ("%d %d %d", &n, &L, &H)) ;

	past = n;
	while (i < n) {
		if (scanf ("%s %d %d", all [i].NO, 
					&all [i].D, &all [i].C)) ;
		if (all [i].D < L || all [i].C < L) {
			all [i].class = 5;
			-- past;
		}
		else if (all [i].D >= H && all [i].C >= H)
			all [i].class = 1;
		else if (all [i].D >= H && all [i].C < H)
			all [i].class = 2;
		else if (all [i].D >= all [i].C)
			all [i].class = 3;
		else 
			all [i].class = 4;
			
		++ i;
	}

	qsort (all, n, sizeof (stud), __cmp);
	i ^= i;

	printf ("%d\n", past);
	while (i < past) {
		printf ("%s %d %d\n", all [i].NO, all [i].D, all [i].C);
		++ i;
	}

	return 0;
}

