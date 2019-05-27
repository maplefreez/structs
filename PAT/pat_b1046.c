/* Date : 2018/12/29
 * Author : ez
 * Desc :  PAT B 1046
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	int a = 0, b = 0, 
			n, i = 0;
	scanf ("%d", &n);
	while (i ++ < n) {
		int avoice, ahand, bvoice, bhand, sum;
		scanf ("%d %d %d %d", &avoice, &ahand,
				&bvoice, &bhand);
		sum = avoice + bvoice;
		if (ahand == sum && bhand != sum) b ++;
		else if (bhand == sum && ahand != sum) a ++;
	}
	printf ("%d %d\n", a, b);
	return 0;
}
