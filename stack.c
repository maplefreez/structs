#include <stdio.h>
#include "stack.h"

static int _arrstack_full (parrstack);
static int _arrstack_expand (parrstack);

parrstack arrstack_create (int _capa) {
	parrstack res = NULL;

	if (_capa <= 0) 
		_capa = DEFAULT_STACK_CAPACITY;

	res = (parrstack) malloc (arrstack);
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


void arrstack_push (parrstack _s, anytype _d) {
	if (! _s || ! _d) return;

	/* If the stack has no space and 
	 * reallocating memory fault, then 
	 * return. */
	if (_arrstack_full (_s) && 
			! _arrstack_expand (_s)) return;

	(_s -> base) [_s -> top ++] = _d;
}


/* Test if the stack remains space for push 
 * function. Note: $1 must not be NULL, cuz 
 * no asserting for this condition. That is,
 * the function assumes $1 isn't NULL. 
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


