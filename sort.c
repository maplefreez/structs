#include "sort.h"
#include <stdlib.h>
#include <stdio.h>

static int _default_cmp_func (const anytype, const anytype);

anytype* straight_insertsort (
		anytype* _seq, int _num, cmphook _cmp) {
	int i = 0, j = 0;
	if (! _seq) return NULL;
	if (! _cmp) _cmp = _default_cmp_func;

	for (i = 1; i < _num; ++ i) {
		anytype x = _seq [i];
		for (j = i - 1; j >= 0; -- j) {
			if (x < _seq [j]) 
				_seq [j + 1] = _seq [j];
			else break;
		}
		_seq [j + 1] = x;
	}

	return _seq;
}


anytype* binary_insertsort (
		anytype* _seq, int _num, cmphook _cmp) {
	return NULL;
}

static int _default_cmp_func (const anytype _a, const anytype _b) {
	if (_a == _b) return CMP_EQ;
	return _a < _b ? CMP_LT : CMP_GT;
}

