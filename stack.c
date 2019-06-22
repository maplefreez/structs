#include <stdlib.h>
#include <string.h>
#include "stack.h"

static int _arrstack_full (parrstack);
static int _arrstack_expand (parrstack);
static void _default_free_func (const void*);

parrstack arrstack_create (int _capa) {
	parrstack res = NULL;

	if (_capa <= 0) 
		_capa = DEFAULT_STACK_CAPACITY;

	res = (parrstack) malloc (sizeof (arrstack));
	if (! res) return res;

	res -> capacity = _capa;
	res -> base = (anytype*) malloc (
			sizeof (anytype) * _capa);

	if (! (res -> base)) {
		/* Memory allocation fault 
		 * for array. */
		free (res);
		return NULL;
	}

	res -> top = 0;
	return res;
}

// TODO testing....
parrstack arrstack_create_by_arr (
		anytype* _arr, int _n) {
	parrstack res = NULL;
	if (! _arr || _n <= 0) return NULL;

	res = arrstack_create (_n);
	if (! res) return NULL;

	res -> base = memcpy (res -> base, _arr, 
			sizeof (anytype) * _n);
	
	res -> top = _n - 1;
	return res;
}


void arrstack_push (parrstack _s, anytype _d) {
	if (! _s || ! _d) return;

	/* If the stack has no space and 
	 * reallocating memory fault, then 
	 * return. */
	if (_arrstack_full (_s) && 
			! _arrstack_expand (_s)) return;

	(_s -> base) [_s -> top ++] = _d;
}

static void _default_free_func (const void* _e) { }

/* Test if the stack remains enough space for 
 * push function. Note: $1 must not be NULL, 
 * cuz no asserting for this condition. That 
 * is, the function assumes $1 isn't NULL. 
 *
 * $1  The stack to be tested.
 *
 * Return non-zero if it's full, otherwise zero. */
static int _arrstack_full (parrstack _s) {
	return (_s -> capacity == _s -> top);
}

/* Expand memory for a stack entity allocated 
 * former due to space shortage. Note: $1 must
 * not be NULL, cuz no asserting for this 
 * condition. That is, the function assumes $1
 * isn't NULL.
 *
 * $1  The stack to be reallocated.
 *
 * Return 1 successfully, or 0 unsuccessfully. */
static int _arrstack_expand (parrstack _s) {
	size_t new_capa = _s -> capacity;
	anytype* ptr = NULL;

	new_capa <<= 1; /* capacity * 2 */
	ptr = realloc (_s -> base, new_capa);
	if (! ptr) return 0;

	_s -> base = ptr;
	_s -> top = _s -> capacity;
	_s -> capacity = new_capa;
	return 1;
}


/* Maybe we'd better redefine this function
 * qualified with the keyword `inline'. */
int arrstack_isempty (parrstack _s) {
	return (_s -> top == 0);
}


anytype arrstack_peak (parrstack _s) {
	if (! _s || arrstack_isempty (_s)) 
		return NULL;

	return _s -> base [_s -> top - 1];
}



anytype arrstack_pop (parrstack _s) {
	anytype res = NULL;
	if (! _s || arrstack_isempty (_s)) 
		return res;

	res = (_s -> base) [-- _s -> top];
	return res;
}

void arrstack_release (parrstack _s, freehook _freef) {
	int tmp = 0;

	if (! _s) return;
	if (! _freef) 
		_freef = _default_free_func;

	for (tmp = _s -> top - 1; 
			tmp != -1; -- tmp)
		_freef (_s -> base [tmp]);

	/* In effect it should not 
	 * get NULL. */
	if (_s -> base) free (_s -> base);
	free (_s);
}


