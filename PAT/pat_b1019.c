/* Date : 2019/9/12
 * Author : ez
 * Desc :  PAT B 1019
 */
#include <stdio.h>

static int* __to_array (int, int*);
static int __to_int (int*, int);

static int* __isort_decent (int*, int);
static int* __isort_ascent (int*, int);

int main (int argc, char* argv []) {
	int num = 0, max, min; 
	int tmparr [4] = {0, };
	if (scanf ("%d", &num));
	
	while (1) {
		__to_array (num, tmparr);
	
		__isort_decent (tmparr, 4);
		max = __to_int (tmparr, 4);
	
		__isort_ascent (tmparr, 4);
		min = __to_int (tmparr, 4);
	
		num = max - min;
		printf ("%04d - %04d = %04d\n", max, min, num);
		if (num == 0 || num == 6174)
			break;
	}

	return 0;
}

static int* __isort_decent (int* _arr, int _n) {
	int tmp = 0, i = 1, j;
	while (i < _n) {
		tmp = _arr [i]; j = i - 1;
		while (j >= 0 && _arr [j] < tmp) {
			_arr [j + 1] = _arr [j]; j --;
		}
		_arr [j + 1] = tmp;
		i ++;
	}
	return _arr;
}

static int* __isort_ascent (int* _arr, int _n) {
	int tmp = 0, i = 1, j;
	while (i < _n) {
		tmp = _arr [i]; j = i - 1;
		while (j >= 0 && _arr [j] > tmp) {
			_arr [j + 1] = _arr [j]; j --;
		}
		_arr [j + 1] = tmp;
		i ++;
	}
	return _arr;
}


static int* __to_array (int _num, int* _out) {
	int i = 3;
	do {
		_out [i --] = _num % 10;
		_num /= 10;
	} while (_num && i >= 0);
	return _out;
}

static int __to_int (int* _arr, int _count) {
	int sum = 0, i = 0;
	while (i < _count) {
		sum *= 10;
		sum += _arr [i ++];
	}
	return sum;
}

