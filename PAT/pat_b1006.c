/* Date : 2019/6/28
 * Author : ez
 * Desc :  PAT A 1011
 */

#include <stdio.h>

const char chs [] = {
	'X', 'B', 'S', '\0'
};

const int scale [] = {
	1, 100, 10, 1, 1
};

int main (int argc, char* argv []) {
	unsigned short n; int i = 1;
	scanf ("%hd", &n);
	do {
		int j = n / scale [i];
		while (j -- > 0) 
			putchar (chs [i]);
		n %= scale [i];
		i ++;
	} while (n >= 10);
	
	i = 1;
	while (i <= n)
		putchar ((i ++) + '0');

	return 0;
}
