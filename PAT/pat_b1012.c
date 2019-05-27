/* Date : 2019/1/3
 * Author : ez
 * Desc :  PAT B 1012
 */

#include <stdio.h>

static int output [5] = {0, };
static int data_count [5] = {0, };
static char factorA2 = 0;

static void process (int);
static void print_result ();

int main (int argc, char* argv []) {
	int n = 0;
	scanf ("%d", &n);

	while (n --) {
		int num;
		scanf ("%d", &num);
		process (num);
	}
	print_result ();
	return 0;
}

static void process (int _num) {
	register int tmp = _num % 5;
	if (tmp == 0) { // A1
		tmp = _num & 0x01;
		output [0] += tmp ? 0 : _num;
		// data_count [0] += tmp;
	} else if (tmp == 1) { // A2
		output [1] += factorA2 ? (-_num) : _num;
		factorA2 = ! factorA2;
		data_count [1] ++;
	} else if (tmp == 2) { // A3
		output [2] ++;
	} else if (tmp == 3) { // A4
		output [3] += _num;
		++ data_count [3];
	} else { // A5
		if (output [4] < _num) 
			output [4] = _num;
	}
}

static void print_result () {
	// A1
	if (output [0])
		printf ("%d ", output [0]);
	else
		printf ("N ");
	// A2
	if (data_count [1])
		printf ("%d ", output [1]);
	else
		printf ("N ");
	// A3
	if (output [2])
		printf ("%d ", output [2]);
	else
		printf ("N ");
	// A4
	if (data_count [3]) {
		double mean = (double) output[3]
			/ data_count [3];
		printf ("%.1f ", mean);
	} else 
		printf ("N ");
	// A5
	if (output [4])
		printf ("%d", output [4]);
	else
		printf ("N");
}

