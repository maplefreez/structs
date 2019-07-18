/* Date : 2019/7/18
 * Author : ez
 * Desc :  PAT A 1001
 */

#include <stdio.h>

const char encode [0xA] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9'
};

int main (int argc, char* argv []) {
	int a, b, sum, i, n;
	char positive [0x10] = {0, };
	if (scanf ("%d %d", &a, &b)) ;

	i = n = 0;
	sum = a + b;
	// if (! sum) puts ("0");
	if (sum < 0) { 
		putchar ('-');
		sum = -sum;
	}

	do {
		positive [i ++] = encode [sum % 0xA];
		sum /= 10;
		++ n;
		if (n % 3 == 0) positive [i ++] = ',';
	} while (sum);

	if (n % 3 == 0) positive [i --] = '\0'; 
	while (i -- > 0)
		putchar (positive [i]);
	
	return 0;
}
