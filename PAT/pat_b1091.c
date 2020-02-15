/* Date : 2020/2/14
 * Author : ez
 * Desc :  PAT B 1092
 */

#include <stdio.h>

static int marge [5] = {1, 10, 100, 1000, 10000};

int main (int argc, char* argv []) {
	int m = 0, n;
	int k = 0, k2 = 0, k2n = 0, bit;
	if (scanf ("%d", &m));
	/* Input */
	while (m -- > 0) {
		bit = 3; n = 0;
		if (scanf ("%d", &k));
		k2 = k * k;

		while (bit >= 1) {
			if (k >= marge [bit]) 
				break;
			bit --;
		}

		++ bit;

		/* Check */
		while (++ n < 10) {
			k2n = k2 * n;
			if (k2n % marge [bit] == k) {
				printf ("%d %d\n", n, k2n);
				break;
			}
		}

		if (n >= 10) puts ("No");
	}
	return 0;
}

