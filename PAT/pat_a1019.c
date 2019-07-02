/* Author : ez
 * Date : 2019/7/1
 * Desc : PAT A 1019
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	int n, b, tmp = 0,
	num [40] = {0, };
	(void) scanf ("%d %d", &n, &b);

	do {
		num [tmp ++] = n % b;
		n /= b;
	} while (n);

	b ^= b; tmp --;
 	while (b <= tmp / 2) {
 		if (num [b] != num [tmp - b]) {
 			puts ("No"); goto OUTPUT;
 		}
 		b ++;
 	}

	puts ("Yes");

OUTPUT:
	b = tmp;
	while (b > 0)
		printf ("%d ", num [b --]);
	printf ("%d", num [b]);
	return 0;
}
