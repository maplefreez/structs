/*
 * Author : ez
 * Date : 2019/6/30
 * Desc : PAT A 1058
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	int A [3] = {0, }, B [3] = {0, };
	unsigned int temp;
	(void) scanf ("%d.%d.%d %d.%d.%d",
			A, A + 1, A + 2,
			B, B + 1, B + 2);

	temp = A [2] + B [2];
	if (temp >= 29) {
		A [1] ++;
		temp -= 29;
	}
	A [2] = temp;

	temp = A [1] + B [1];
	if (temp >= 17) {
		A [0] ++;
		temp -= 17;
	}
	A [1] = temp;
	
	temp = A [0] + B [0];
	printf ("%d.%d.%d", temp, A [1], A [2]);

	return 0;
}
