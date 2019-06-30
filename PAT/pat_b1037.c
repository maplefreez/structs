/* Date : 2019/6/29
 * Author : ez
 * Desc :  PAT B 1037
 */

#include <stdio.h>

#	define total(__X)  ((__X[0])*29*17+(__X[1])*29+(__X[2]))

int main (int argc, char* argv []) {
	int payment [3] = {0, };
	int get [3] = {0, };
	int temp;

	(void) scanf ("%d.%d.%d %d.%d.%d",
			payment, payment + 1, payment + 2,
			get, get + 1, get + 2);

	temp = total (get) - total (payment);
	if (temp < 0) {
		putchar ('-');
		temp = -temp;
	}

	get [0] = (temp / (29 * 17));
	temp %= 29 * 17;
	get [1] = temp / 29;
	get [2] = temp % 29;
	printf ("%d.%d.%d", get [0], get [1], get [2]);

	return 0;
}

