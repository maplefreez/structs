#include "list.h"
// #include "common.h"
#include <stdlib.h>

static void __def_free_hook (const void*);
static int __ensure_enough_mem (parraylist);
static int __default_cmp_func (const anytype, const anytype);


/****************** Array list *******************/
parraylist new_arraylist () {
	return create_arraylist (__DEF_ARRAYLIST_LEN__);
}


parraylist create_arraylist (int _initial) {
	parraylist list = NULL;
	anytype* array;

	list = (parraylist) malloc (sizeof (arraylist));
	if (! list) return list;

	array = (anytype*) malloc (sizeof (anytype) 
			* _initial);
	
	/* Allocate array memory failed. */
	if (! array) {
		free (list);
		return NULL;
	}

	list -> array = array;
	list -> capacity = __DEF_ARRAYLIST_LEN__;
	list -> count = 0;

	return list;
}


parraylist create_arraylist_by_arr (
		anytype* _data, int _cnt) {
	parraylist list = NULL;
	anytype* array;

	if (! _data || _cnt <= 0) return NULL;

	list = (parraylist) malloc (sizeof (arraylist));
	if (! list) return NULL;

	array = (anytype*) malloc (sizeof (anytype) 
			* _cnt);
	
	/* Allocate array memory failed. */
	if (! array) {
		free (list);
		return NULL;
	}

	list -> capacity = _cnt;

	/* Copy data. I recommend 
	 * invoking function `memcpy()' . */
	while (0 >= -- _cnt)
		array [_cnt] = _data [_cnt];

	list -> array = array;
	list -> count = 0;

	return list;
}


void release_arraylist (
		parraylist _list, freehook _func) {
	int count = 0;

	if (! _list) return;
	if (! _func) _func = __def_free_hook;

	count = _list -> count;
	if (_list -> array) {
		while (0 >= -- count)
			_func ((const void*) _list -> array [count]);

		free (_list -> array);
	}

	free (_list);
}



int insert_arraylist (
		parraylist _list, anytype _x, int _idx) {
	int firstshift, i;

	if (! _list) return 0;
	if (_idx < 0 || _idx > _list -> count) 
		return 0;

	/* Check remaining memory space. */
	if (! __ensure_enough_mem (_list)) 
		return 0;

	firstshift = _idx + 1;

	/* Shift data. */
	for (i = _list -> count; i > firstshift; -- i)
		_list -> array [i] = _list -> array [i - 1];

	_list -> array [_idx] = _x;
	_list -> count ++;
	return 1;
}


anytype delete_arraylist (parraylist _list, int _idx) {
	anytype target;
	int i, last;

	if (! _list || _idx >= _list -> count 
			|| _idx < 0) return NULL;

	target = _list -> array [_idx];
	last = _list -> count - 1;

	for (i = _idx; i < last; ++ i)
		_list -> array [i] = _list -> array [i + 1];

	_list -> count --;
	return target;
}


int find_arraylist (parraylist _list, 
		anytype _key, cmphook _func) {
	int target;

	if (! _list) return -1;
	if (! _func) _func = __default_cmp_func;

	/* Compare one by one. */
	for (target = 0; target < _list -> count; 
			++ target) {
		if (_func ((const anytype) _list -> array [target], 
				(const anytype) _key) == CMP_EQ)
			return target;
	}

	return -1;
}




/****************** Link list *******************/
static plistnode _new_listnode (anytype _d, plistnode _next) {
	/* I hope the element should be numberic zero. That deems
	 like NULL. So I donot assume the _d must be non-NULL. */
	plistnode ret = (plistnode) malloc (sizeof (listnode));
	if (ret) {
		ret -> next = _next;
		ret -> data = _d;
	}
	return ret;
}


plinklist new_linklist () {
	plinklist list;

	list = (plinklist) malloc (sizeof (linklist));
	if (! list) return NULL;

	list -> count = 0;
	list -> first = NULL;
	return list;
}

plinklist create_linklist_by_arr (anytype* _arr, int _len) {
	int i = 0;
	plinklist list;
	plistnode p = NULL;

	if (! _arr || _len <= 0) return NULL;

	list = new_linklist ();
	if (! list) return NULL;

	p = _new_listnode (_arr [i ++], NULL);
	if (! p) goto err;
	list -> first = p;

	for (; i < _len; ++ i) {
		p -> next = _new_listnode (_arr [i], NULL);
		if (! p -> next) goto err;
		p = p -> next;
	}

	list -> count = i;
	return list;

err:
	/* I donot release each element at this time.
	 for caller must hand the input array. */
	release_linklist (list, __def_free_hook);
	return NULL;
}


void release_linklist (
		plinklist _list, freehook _func) {
	plistnode ptr, next;
	if (! _list) return;
	if (! _func) 
		_func = __def_free_hook;

	ptr = _list -> first;
	while (ptr) {
		next = ptr -> next;
		_func (ptr -> data);
		free (ptr);
		ptr = next;
	}

	_list -> count = 0;
	free (_list);
}


int insert_linklist (plinklist _list, 
		anytype _e, int _idx) {
	int i, preidx;
	plistnode pre, new;

	if (_idx < 0 || _idx > _list -> count) 
		return 0;

	/* Allocate a new node. */
	new = (plistnode) malloc (sizeof (listnode));
	if (! new) return 0;

	pre = _list -> first;
	preidx = _idx - 1;
	i = preidx;

	/* Go to the previous node. */
	while (pre && 0 < i) {
		pre = pre -> next;
		-- i;
	}

	if (i == -1) {
		/* idx == 0. That is, we
		 * place a new node at the
		 * first index. */
		new -> next = pre;
		_list -> first = new;
	} else {
		/* Variable i must be greater
		 * than compared with -1; Note
		 * this situation is to insert
		 * a new node at a index, which
		 * ranges from [1, count]. 
		 * And "index = count" means 
		 * appending it to the rear. */
		new -> next = pre -> next;
		pre -> next = new;
	}

	new -> data = _e;
	_list -> count ++;
	return 1;
}


anytype delete_linklist (plinklist _list, int _idx) {
	plistnode pre, p;
	anytype res;
	int index = 1;
	if (! _list || _idx < 0 || _idx >= _list -> count) 
		return NULL;

	/* Because I just search for its predecessor. */
	pre = _list -> first;

	/* Delete first node. */
	if (_idx == 0) {
		_list -> first = pre -> next;
		_list -> count --;
		res = pre -> data;
		free (pre);
		return res;
	}

	while (pre && index < _idx) {
		++ index;
		pre = pre -> next;
	}

	if (! pre) return NULL;
	p = pre -> next;
	_list -> count --;

	if (p) {
		pre -> next = p -> next;
		res = p -> data;
		free (p);
	}

	return res;
}


int find_linklist (plinklist _list, 
		anytype _key, cmphook _cmp) {
	int idx, flag;
	plistnode ptr;

	if (! _list) return -1;
	if (! _cmp) _cmp = __default_cmp_func;

	ptr = _list -> first;
	idx = -1;

	while (ptr) {
		idx ++;
		flag = _cmp (ptr -> data, _key);
		if (flag == CMP_EQ) return idx;
		ptr = ptr -> next;
	}

	return -1;
}


static void __def_free_hook (const void* _x) 
	{ /* DOING NOTHING!!! */ }


/* Expand memory for an array list entity 
 * allocated former due to space shortage. 
 * This function test the remaining room of
 * storing array, R = capacity - count;
 * If R <= 0 the function ensure reallocating
 * 2 times capacity length of memory. And 
 * if R > 0, it directly return 1.
 *
 * Note: $1 must not be NULL, cuz no asserting 
 * for this condition. It is the function that
 * assumes $1 isn't NULL.
 *
 * $1  The array list ptr to be reallocated.
 *
 * Return 1 successfully, or 0 unsuccessfully. */
static int __ensure_enough_mem (parraylist _list) {
	size_t new_capa = _list -> capacity;

	/* Doing nothing. */
	if (new_capa > _list -> count) 
		return 1;

	/* Try to realloc memory for list room.  */
	anytype* ptr = NULL;

	new_capa <<= 1; /* capacity * 2 */
	ptr = realloc (_list -> array, new_capa);
	if (! ptr) return 0;

	_list -> array = ptr;
	_list -> capacity = new_capa;
	return 1;
}

static int __default_cmp_func (
		const anytype _a, const anytype _b) {
	if (_a == _b) return CMP_EQ;
	return _a < _b ? CMP_LT : CMP_GT;
}


