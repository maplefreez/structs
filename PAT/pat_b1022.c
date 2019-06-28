/* Date : 2019/6/28
 * Author : ez
 * Desc :  PAT B 1022
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	unsigned int a, b, add, scale;
	int i = 0;
	int ans [0x20];

	(void) scanf ("%d %d %d", &a, &b, &scale);
	add = a + b;

	do {
		ans [i ++] = add % scale;
		add /= scale;
	} while (add);

	a ^= a;
	while (a ++ < i) {
		putchar (ans [i - a] + '0');
	}

	return 0;
}
