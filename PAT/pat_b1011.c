/* Date : 2018/12/29
 * Author : ez
 * Desc :  PAT B 1011
 */
#include <stdio.h>

static void _test_print (long long, long long, 
		long long, long long);
static void _input_process ();

/*
int main (int argc, char* argv []) {
	_input_process ();
	return 0;
}
*/


static void _test_print (long long _a, 
		long long _b, long long _c, long long _i) {
	if (_a + _b > _c)
		printf ("Case #%d: true\n", _i);
	else
		printf ("Case #%d: false\n", _i);
}


static void _input_process () {
	int n, i = 1;
	scanf ("%d", &n);

	while (i <= n) {
		int a, b, c;
		scanf ("%lld %lld %lld", &a, &b, &c);
		_test_print (a, b, c, i);
		++ i;
	}	
}

// Submit code.
int main (int argc, char* argv []) {
	int n, i = 1;
	scanf ("%d", &n);

	while (i <= n) {
		long long a, b, c;
		scanf ("%lld %lld %lld", &a, &b, &c);
		if (a + b > c)
			printf ("Case #%d: true\n", i);
		else
			printf ("Case #%d: false\n", i);
		++ i;
	}	

	return 0;
}




