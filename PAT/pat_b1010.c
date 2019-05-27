/* Date : 2019/5/23
 * Author : ez
 * Desc :  PAT A 1065
 */

#include <stdio.h>


/* TO BE SUBMITTED. */
int main (int argc, char* argv []) {
	int output [0x400] = {0, };
	int a, e, i = 0;
	while (EOF != scanf ("%d %d", &a, &e)) {
		if (e != 0) {
			output [i ++] = a * e;
			output [i ++] = e - 1;
		} 
	}

	if (i > 0) {
		a ^= a;
		while (a < i - 1) {
			printf ("%d %d ", output [a ++], output [a ++]);
		}
		printf ("%d %d", output [a ++], output [a]);
	} else 
		puts ("0 0");

	return 0;
}


