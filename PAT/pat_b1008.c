/* Date : 2018/12/29
 * Author : ez
 * Desc :  PAT B 1008
 */

#include <stdio.h>
static int array [0x80] = {0};
int main (int argc, char* argv []) {
	int i, n, tmp, move;
	scanf ("%d %d", &n, &move);
	i = 0;
	/* Input data. */
	while (i < n) {
		scanf ("%d", &tmp);
		array [i ++] = tmp;
	}

	/* Minimum step operation. */
	move %= n;
	if (move) {
		/* Process data. */
		while (move --) {
			i = n - 1;
			tmp = array [i --];
			while (i >= 0) {
				array [i + 1] = array [i];
				i --;
			}
			array [0] = tmp;
		}
	}

	/* Output */
	i = 0;
	while (i < n) {
		if (i != n - 1)
			printf ("%d ", array [i ++]);
		else
			printf ("%d", array [i ++]);
	}
	return 0;
}
