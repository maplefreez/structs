/* Date : 2018/12/25
 * Author : ez
 * Desc :  PAT B 1001
 */

#include <stdio.h>
#include <math.h>

/* Shame on you! Foolish! */
int main (int argc, char* argv []) {
	int input, x, n, linemax, i, j;
	char c;
	scanf ("%d %c", &input, &c);

	n = linemax = (int) sqrt ((input + 1) / 2.0);
	j = 0; // front space;

	/* First n lines. */
	while (n > 0) {
		int count = (n << 1) - 1;
		x ^= x;
		/* Space */
		while (x ++ < j) putchar (' ');
		for (i ^= i; i < count; ++ i)
			printf ("%c", c);
		puts ("");
		j ++, n --;
	}

	/* Last n - 1 lines. */
	n = 2, j = 1;
	while (n <= linemax) {
		int count = (n << 1) - 1;
		x ^= x;
		/* Space */
		while (x ++ < j) putchar (' ');
		for (i ^= i; i < count; ++ i)
			printf ("%c", c);
		puts ("");
		j --, n ++;
	}

	x = ((linemax * linemax) << 1) - 1;
	printf ("%d", input - x);

	return 0;
}
