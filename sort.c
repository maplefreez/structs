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
	int i = 0, j = 0, cmp;
	int high = 0, low = 0, mid;
	anytype x;

	if (! _seq) return NULL;
	if (! _cmp) _cmp = _default_cmp_func;

	for (i = 1; i < _num; ++ i) {
		low = 0, high = i - 1;
		x = _seq [i];

		/* Search a appropriate slot for
		 * inserting element. With binary
		 * search. */
		while (low <= high) {
			mid = (low + high) >> 1;
			cmp = _cmp (_seq [mid], x);

			if (cmp == CMP_GT) {
				/* We place smaller one to 
				 * left subsequence. */
				high = mid - 1;
			} else {
				/* And the greater or equal one
				 * to right subsequence.
				 * Because binary-insert-sort is
				 * not a stable sort method. We 
				 * treat same elements as to put
				 * inserted one ahead the sorted
				 * one. */
				low = mid + 1;
			}
		}

		/* Move afterwards. */
		for (j = i - 1; j >= high + 1; -- j)
			_seq [j + 1] = _seq [j];
		_seq [high + 1] = x;

	}

	return _seq;
}


anytype* select_sort (
		anytype* _seq, int _num, cmphook _cmp) {
	int i = 0, j = 0, cmp;
	int min_idx;
	anytype x;

	if (! _seq) return NULL;
	if (! _cmp) _cmp = _default_cmp_func;

	for (i = 0; i < _num - 1; ++ i) {
		x = _seq [i];

		/* Search the index of minimum element
		 * in right subsequence. */
		min_idx = i + 1;
		for (j = i; j < _num; ++ j) {
			cmp = _cmp (_seq [min_idx], _seq [j]);
			if (cmp == CMP_GT)
				min_idx = j;
		}

		if (i != min_idx) {
			/* Exchange. */
			_seq [i] = _seq [min_idx];
			_seq [min_idx] = x;
		}
	}

	return _seq;

}


anytype* bubble_sort (
		anytype* _seq, int _num, cmphook _cmp) {
	int i, j, cmp;
	anytype x;

	if (! _seq) return NULL;
	if (! _cmp) _cmp = _default_cmp_func;

	for (i = 0; i < _num; ++ i) {
		for (j = 0; j < _num - i - 1; ++ j) {
			x = _seq [j + 1];

			cmp = _cmp (_seq [j], x);
			if (cmp == CMP_GT) {
				_seq [j + 1] = _seq [j];
				_seq [j] = x;
			}
		}
	}

	return _seq;
}


anytype* bubble_sort1 (
		anytype* _seq, int _num, cmphook _cmp) {
	int i, j, cmp;
	anytype x;

	if (! _seq) return NULL;
	if (! _cmp) _cmp = _default_cmp_func;

	for (i = 0; i < _num; ++ i) {
		for (j = _num - 1; j >= i; -- j) {
			x = _seq [j + 1];

			cmp = _cmp (_seq [j], x);
			if (cmp == CMP_GT) {
				_seq [j + 1] = _seq [j];
				_seq [j] = x;
			}
		}
	}

	return _seq;
}

/* By default, I implement ascending sort. */
anytype* shell_sort (
		anytype* _seq, int _num, cmphook _cmp) {
	if (! _seq) return NULL;
	if (! _cmp) _cmp = _default_cmp_func;

	_shell_sort (_seq, _num, _cmp);
	return _seq;
}


void _shell_sort (anytype* _seq, int _num, cmphook _cmp) {
	/* As a cache. Note the index begin from zero.*/
	anytype tmp; int i, j, d;

	/* Generate distance sequence: 
	 * d(n) = [d(n-1) / 2]
	 * d(1) = [n / 2] */
	for (d = _num / 2; d >= 1; d /= 2) {
		/* First element for each group. */
		for (i = d; i < _num; i ++) {
			/* We use direct insertion sort as 
			 * inner sort algo. */
			tmp = _seq [i];
			if (CMP_GT == _cmp (_seq [i - d], tmp)) {
				for (j = i - d; j >= 0 &&
						CMP_GT == _cmp (_seq [j], tmp); j -= d)
						_seq [j + d] = _seq [j];
				_seq [j + d] = tmp;
			}
		}
	}

}


anytype* quick_sort (anytype* _seq, 
		int _num, cmphook _cmp) {
	// TODO...
}


static int _default_cmp_func (const anytype _a, const anytype _b) {
	if (_a == _b) return CMP_EQ;
	return _a < _b ? CMP_LT : CMP_GT;
}

