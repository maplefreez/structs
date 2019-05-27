/* Date : 2018/12/25
 * Author : ez
 * Desc :  PAT B 1001
 */

#include <stdio.h>

int step_counter (int _n) {
	int i = 0;

	while (_n != 1) {
		_n = _n & 0x1 ? 
			_n >> 1 : 
			(3 * _n + 1) >> 1;
		++ i;
	}

	return i;
}

int main (int argc, char* argv []) {
	printf ("%d, %d", 323, step_counter (323));
	return 0;
}

/*
// Submit code.
int main (int argc, char* argv []) {
	int step = 0, n = 0;

	scanf ("%d", &n);
	while (n != 1) {
		n = n & 0x1 ? 
			(3 * n + 1) >> 1 :
			n >> 1; 
		++ step;
	}

	printf ("%d\n", step);
	return 0;
}
*/

