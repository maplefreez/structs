/* Date : 2018/12/29
 * Author : ez
 * Desc :  PAT B 1016
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	long long a, b, da, db;
	long long pa = 0, pb = 0;
	int i = 0;
	scanf ("%lld %lld %lld %lld", &a, &da, &b, &db);
	/* A */
	while (i ++ < 10) {
		if (a % 10 == da) pa = pa * 10 + da;
		a /= 10;
	}

	/* B */
	i = 0;
	while (i ++ < 10) {
		if (b % 10 == db) pb = pb * 10 + db;
		b /= 10;
	}

	/* Output */
	printf ("%lld", pa + pb);

	return 0;
}

