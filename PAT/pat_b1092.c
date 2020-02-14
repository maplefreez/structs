/* Date : 2020/2/14
 * Author : ez
 * Desc :  PAT B 1092
 */

#include <stdio.h>

static int customs [1024] = {0, };

int main (int argc, char* argv []) {
	int n, m; int ni, mi = 0;
	int firstmax_idx = 0, firstmax = -1;
	if (scanf ("%d %d", &n, &m));

	while (mi ++ < m) {
		ni = 0;
		int custom = 0;
		while (++ ni <= n) {
			if (scanf ("%d", &custom));
			customs [ni] += custom;
			/* Select maximum. */
			if (customs [ni] > firstmax) {
				firstmax = customs [ni];
				firstmax_idx = ni;
			}
		}
	}

	/* Output */
	printf ("%d\n%d", firstmax, firstmax_idx);
	ni = firstmax_idx; 
	while (++ ni <= n) {
		if (customs [ni] == firstmax)
			printf (" %d", ni);
	}


	return 0;
}
