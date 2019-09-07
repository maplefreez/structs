/* Date : 2019/9/7
 * Author : ez
 * Desc :  PAT B 1023
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int digit [0xA] = {0, };

int main (int argc, char* argv []) {
	int i = 0/*, num = 0, min = -1*/;
	/* Input. */
	while (i < 10)
		if (scanf ("%d", digit + i ++));

	/* Output. */
	/* First num. */
	i = 1;
	while (i < 0xA) {
		if (digit [i]) {
			printf ("%d", i);
			digit [i] --;
			break;
		}
		i ++;
	}

	/* Last num. */
	i ^= i;
	while (i < 0xA) {
		while (digit [i] --)
			printf ("%d", i);
		i ++;
	}

	return 0;
}

