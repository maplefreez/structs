/* Date : 2019/6/28
 * Author : ez
 * Desc :  PAT B 1021
 */

#include <stdio.h>

int statistic [10] = {0, };

int main (int argc, char* argv []) {
	int i = 0/*, length*/;
	char num [1024] = {0, }, *p;
	scanf ("%s", num);

	p = num;
	while (*p)
		statistic [*(p++) - '0'] ++;

	// length = p - num;
	while (i < 10) {
		if (statistic [i])
			printf ("%d:%d\n", i, statistic [i]);
		++ i;
	}

	return 0;
}
