/* Date : 2019/12/30
 * Author : ez
 * Desc :  PAT B 1007
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int _is_prime (int);

/* TODO... To be submitted. */
int main (int argc, char * argv []) {
	int n, i = 3, count = 0;
	if (scanf ("%d", &n));
	
	for (; i + 2 <= n; i += 2) {
		if (_is_prime (i) && _is_prime (i + 2)) 
			count ++;
	}
	printf ("%d", count);
	return 0;
}


static int _is_prime (int x) {
	int i = 2, right = (int) sqrt (x);
	for (; i <= right; ++ i)
		if (x % i == 0) return 0;
	return 1;
}

