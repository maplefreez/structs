/* Date : 2018/12/25
 * Author : ez
 * Desc :  PAT B 1032
 */

#include <stdio.h>
#	define MAX_LENGTH    100016

static int score [MAX_LENGTH] = {0};

/* Select maximum score with its school. */
int compare (int _n, int* _school) {
	int i, max_score = -1;
	for (i = 1; i <= _n; ++ i)
		if (score [i] > max_score) {
			max_score = score [i];
			*_school = i;
		}
	return max_score;
}

/* Record input data, return 
 * the number of school. */
int proc_input () {
	int n = 0, i, num, s;
	scanf ("%d", &n); // Quantity.
	for (i = 0; i < n; ++ i) {
		scanf ("%d %d", &num, &s);
		score [num] += s;
	}
	return n;
}

/*
int main (int argc, char* argv []) {
	int max_score, school, n;
	n = proc_input ();
	max_score = compare (n, &school);

	printf ("%d %d", school, max_score);
	return 0;
}
*/

// Submit code
int main (int argc, char* argv []) {
	int n = 0, i, num, s;
	scanf ("%d", &n); // Quantity.
	for (i = 0; i < n; ++ i) {
		scanf ("%d %d", &num, &s);
		score [num] += s;
	}

	s = -1;
	for (i = 1; i <= n; ++ i)
		if (score [i] > s) {
			s = score [i];
			num = i;
		}
	printf ("%d %d", num, s);
}
