/* Date : 2019/9/14
 * Author : ez
 * Desc :  PAT A 1008
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	int count, i = 0;
	int last, dst, sum = 0;

	if (scanf ("%d", &count));

	last = 0;
	while (i < count) {
		int tmp = 0;
		if (scanf ("%d", &dst));
		tmp = dst - last;

		sum += tmp > 0 ?
			tmp * 6 + 5: (-tmp) * 4 + 5;

		++ i; last = dst;
	}

	printf ("%d", sum);

	return 0;
}


