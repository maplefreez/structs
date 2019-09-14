/* Date : 2019/9/13
 * Author : ez
 * Desc :  PAT B 1049 / A 1104
 */

#include <stdio.h>

int main (int argc, char* argv []) {
	int i = 0, input_count; 
	double sum = 0.0d;
	if (scanf ("%d", &input_count));
	while (i < input_count) {
		double x = 0;
		if (scanf ("%lf", &x));
		sum += x* (i + 1) * (input_count - i);
		i ++;
	}

	printf ("%.2f\n", sum);
	return 0;
}

