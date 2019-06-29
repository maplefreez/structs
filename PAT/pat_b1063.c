/* Date : 2019/6/28
 * Author : ez
 * Desc :  PAT B 1063
 */

#include <stdio.h>
#include <math.h>

int main (int argc, char* argv []) {
	int n = 0;
	double real = .0f, vir = .0f, max = -1024.0f;

	(void) scanf ("%d", &n);
	while (n -- > 0) {
		(void) scanf ("%lf %lf", &real, &vir);
		real  = sqrt (real * real + vir * vir);
		real > max ? max = real : 0;
	}

	printf ("%.2f", max);
	return 0;
}
