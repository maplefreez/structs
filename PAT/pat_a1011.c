/* Date : 2019/6/27
 * Author : ez
 * Desc :  PAT A 1011
 */

#include <stdio.h>

const char select_char [] = {
	'X', 'W', 'T', 'L'
};

int main (int argc, char* argv []) {
	int select [3] = {0, }, i, j;
	double profile = 1.00f;

	i ^= i;
	while (i < 3) {
		double tmp, max = -1;
		for (j = 1; j <= 3; ++ j) {
			scanf ("%lf", &tmp);
			if (max < tmp) { 
				max = tmp;
				select [i] = j;
			}
		}
		profile *= max;

		i ++;
	}

	profile = (0.65 * profile - 1) * 2;

	/* Outputs. */
	printf ("%c %c %c %.2f", 
			select_char [select [0]], 
			select_char [select [1]], 
			select_char [select [2]], profile);

	return 0;
}
