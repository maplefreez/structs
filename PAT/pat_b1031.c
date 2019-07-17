/*
 * Author : ez
 * Date : 2019/7/2
 * Desc : PAT B 1031
 */

#include <stdio.h>

int powers [] = {
	7, 9, 10, 5, 8,
	4, 2, 1, 6, 3, 7,
	9, 10, 5, 8, 4, 2
};
char m [] = {
	'1', '0', 'X', '9',
	'8', '7', '6', '5',
	'4', '3', '2'
};

int main (int argc, char* argv []) {
	int i = 0, tmp = 0, 
			j = 0, num = 0, n;
	char serials [20] = {0, }, p;

	(void) scanf ("%d", &n);
	while (i ++ < n) {
		(void) scanf ("%s", serials);

		tmp ^= tmp;
		j ^= j;
		while (j < 17) {
			p = serials [j];
			if (p >= '0' && p <= '9') {
				tmp += (p - '0') * powers [j];
			} else {
				/* invalid. */
				puts (serials);
				break;
			}
			j ++;
		}

		if (j == 17)
			if (serials [17] != m [tmp % 11])
				puts (serials);
			else
				num ++;
		else { }
	}

	if (num == n) puts ("All passed");
	return 0;
}

