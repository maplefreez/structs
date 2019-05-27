/*
 * Author : ez
 * Date : 2019/2/16
 * Desc : PAT B 1018
 */
#include <stdio.h>

static char sign[3] = {'B', 'C', 'J'};

static int map (char _sign) {
	if (sign [0] == _sign) return 0;
	else if (sign [1] == _sign) return 1;
	else return 2;
}

/* Statistic for A and B players. 
 * <Win, Tied, Failure>.  */
static int A_statis [3] = {0, 0, 0},
					 B_statis [3] = {0, 0, 0};

/* Statistic for A and B players.
 * <B, C, J>. */
static int A_input [3] = {0, 0, 0},
					 B_input [3] = {0, 0, 0};

int main (int argc, char* argv []) {
	int n = 0, mostA = 0, mostB = 0;
	scanf ("%d", &n);

	while (n --) {
		char a, b;
		int ai, bi;
		getchar ();
		scanf ("%c %c", &a, &b);

		ai = map (a);
		bi = map (b);

		if (((ai + 1) % 3) == bi) {
			// A win 
			A_statis [0] ++;
			B_statis [2] ++;
			A_input [ai] ++;
		} else if (ai == bi) {
			// Tied
			A_statis [1] ++;
			B_statis [1] ++;
		} else {
			// B win
			A_statis [2] ++;
			B_statis [0] ++;
			B_input [bi] ++;
		}
	}

	printf ("%d %d %d\n", A_statis [0], A_statis [1], A_statis [2]);
	printf ("%d %d %d\n", B_statis [0], B_statis [1], B_statis [2]);

	for (n = 0; n < 3; n ++) {
		if (A_input [mostA] < A_input [n]) mostA = n;
		if (B_input [mostB] < B_input [n]) mostB = n;
	}

	printf ("%c %c\n", sign [mostA], sign [mostB]);

	return 0;
}
