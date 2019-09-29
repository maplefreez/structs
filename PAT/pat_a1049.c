/* Date : 2019/9/29
 * Author : ez
 * Desc :  PAT A 1049
 */

#include <stdlib.h>
#include <stdio.h>

/* To be testing. */
int main (int arg, char* argv []) {
	int n = 0, bit = 1, statistic = 0;
	int left = 0, right = 0, p;
	if (scanf ("%d", &n));

	do {
		right = n % bit;
		p = (n / bit) % 10;
		left = n / (bit * 10);

		if (p == 0) 
			statistic += left * bit;
		else if (p == 1) 
			statistic += left * bit + right + 1;
		else
			statistic += (left + 1) * bit;

		bit *= 10;
	} while (left);

	printf ("%d", statistic);

	return 0;
}
