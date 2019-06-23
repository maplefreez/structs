#include <stdlib.h>
#include <stdint.h>
#include "list.h"
#include "sort.h"
// #include "common.h"

static void __def_free_hook (const void*);
static int __ensure_enough_mem (parraylist);
static int __default_cmp_func (const anytype, const anytype);
static plistnode __delete_linklist_key_recr (
		plinklist, plistnode, anytype, cmphook, freehook);
static void __foreach_linklist_revr_recr (plistnode, llist_visitf);


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
	// list -> capacity = __DEF_ARRAYLIST_LEN__;
	list -> capacity = _initial;
	list -> count = 0;

	return list;
}


parraylist create_arraylist_by_arr (
		anytype* _data, int _cnt) {
	int i = 0;
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
	list -> count = _cnt;

	/* Copy data. I recommend 
	 * invoking function `memcpy()' . */
	while (0 <= -- _cnt)
		array [_cnt] = _data [_cnt];

	list -> array = array;

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


void delete_arraylist_key (
		parraylist _l, anytype _key, 
		cmphook _cmp, freehook _fr) {
	int del, i;
	anytype* array;

	if (! _l) return;
	if (! _cmp) _cmp = __default_cmp_func;
	if (! _fr) _fr = __def_free_hook;

	array = _l -> array;

	/* The element from del to (i - 1) 
		 equals to the key. */
	for (i ^= i, del ^= 0; i < _l -> count; ++ i) {
		if (CMP_EQ != _cmp (array [i], _key)) {
			array [del] = array [i];
			del ++;
		}
	}
	
	_l -> count = del;
}

// TODO... testing.
void remove_same_arraylist (parraylist _l, 
		cmphook _cmp, freehook _fr) {
	int i = 0;
	if (! _l) return;
	if (! _cmp) _cmp = __default_cmp_func;
	if (! _fr) _fr = __def_free_hook;

	/* Ascentive order. */
	quick_sort (_l -> array, _l -> count, _cmp);

	

}

parraylist reverse_arraylist (parraylist _list) {
	int h, r;
	if (! _list) return NULL;

	h = 0; r = _list -> count - 1;
	while (h < r) {
		/* Switch array[h] and array [r]. */
		anytype temp = _list -> array [h];
		_list -> array [h] = _list -> array [r];
		_list -> array [r] = temp;
		// (intptr_t) (_list -> array [h]) ^= 
		// 	(intptr_t) (_list -> array [r]);
		// (intptr_t) (_list -> array [r]) ^= 
		// 	(intptr_t) (_list -> array [h]);
		// (intptr_t) (_list -> array [h]) ^= 
		// 	(intptr_t) (_list -> array [r]);
		++ h, -- r;
	}
	return _list;
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


parraylist merge_arraylist (
		parraylist _a, parraylist _b, cmphook _cmp) {
	int i, j, k, count;
	int ac, bc;
	parraylist c;

	if (!_a || !_b) return NULL;
	if (_a -> count <= 0 || _b -> count <= 0) return NULL;

	if (! _cmp) _cmp = __default_cmp_func;

	ac = _a -> count; bc = _b -> count;
	count = ac + bc;
	c = create_arraylist (count);

	/* Merge elements from the 2 list into c. */
	if (c) {
		i = j = k = 0;
		anytype* carr = c -> array;
		while (i < ac && j < bc) {
			if (CMP_GT == _cmp (_a -> array [i], _b -> array [j]))
				carr [k ++] = _b -> array [j ++];
			else
				carr [k ++] = _a -> array [i ++];
		}

		while (i < ac) carr [k ++] = _a -> array [i ++];
		while (j < bc) carr [k ++] = _b -> array [j ++];
		c -> count = count;
	}

	return c;
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


anytype get_linklist_index (plinklist _l, int _idx) {
	plistnode p = NULL;
	if (! _l || _idx <= 0 || _idx > _l -> count) 
		return NULL;

	p = _l -> first;
	while (p && _idx -- > 1)
		p = p -> next;
	return p -> data;
}


anytype get_linklist_max (plinklist _l, cmphook _cmp) {
	plistnode p, max;

	if (! _l || ! _l -> first) return NULL;
	if (! _cmp) _cmp = __default_cmp_func;

	max = _l -> first;
	p = _l -> first;
	while (p) {
		p = p -> next;
		if (p && CMP_LT == _cmp (max -> data, p -> data))
			{
				max = p;
			}
	}
	return max -> data;
}


anytype get_linklist_min (plinklist _l, cmphook _cmp) {
	plistnode p, min;

	if (! _l || ! _l -> first) return NULL;
	if (! _cmp) _cmp = __default_cmp_func;

	min = _l -> first;
	p = _l -> first;
	while (p) {
		p = p -> next;
		if (p && CMP_GT == _cmp (min -> data, p -> data))
			{
				min = p;
			}
	}
	return min -> data;
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


// TODO testing.
void delete_linklist_key_recr (plinklist _list, 
		anytype _key, cmphook _cmp, freehook _fr) {
	if (! _list) return;
	if (! _cmp) _cmp = __default_cmp_func;
	if (! _fr) _fr = __def_free_hook;

	_list -> first = __delete_linklist_key_recr (
			_list, _list -> first, _key, _cmp, _fr);
}

// TODO testing.
static plistnode __delete_linklist_key_recr (
		plinklist _l, plistnode _lsub, 
		anytype _k, cmphook _cmp, freehook _fr) {
	plistnode p = NULL;
	if (! _lsub) return NULL;
	if (CMP_EQ == _cmp (
				_lsub -> data, _k)) {
		p = _lsub -> next; 
		_fr (_lsub -> data);
		free (_lsub);
		_l -> count --;

		if (p)
			p -> next = __delete_linklist_key_recr (_l, 
					p -> next, _k, _cmp, _fr);
		return p;
	} else {
		_lsub -> next = __delete_linklist_key_recr (
				_l, _lsub -> next, _k, _cmp, _fr);
		return _lsub;
	}
}



void delete_linklist_key (plinklist _l, anytype _key, 
		cmphook _cmp, freehook _fr) {
	plistnode p, r, pre;
	listnode node;

	if (! _l) return;
	if (! _cmp) _cmp = __default_cmp_func;
	if (! _fr) _fr = __def_free_hook;

	/* The node is to help the process 
		 for first node deletion. */
	node.next = _l -> first;
	p = _l -> first;
	pre = &node;

	/* Process the remaining elements 
		 after the first one. */
	while (p) {
		r = p -> next;
		if (CMP_EQ == _cmp (p -> data, _key)) {
			pre -> next = p -> next;
			_fr (p -> data);
			free (p);
			_l -> count --;
		} else
			pre = p;
		p = r;
	}

	_l -> first = node.next;
}



plinklist create_linklist_by_arr_revr (
		anytype* _arr, int _len) {
	int i = 0;
	plinklist list;
	plistnode p = NULL;

	if (! _arr || _len <= 0) return NULL;

	list = new_linklist ();
	if (! list) return NULL;

	p = _new_listnode (_arr [i ++], NULL);
	if (! p) goto err;
	list -> first = p;

	while (i < _len) {
		p = _new_listnode (_arr [i ++], NULL);
		if (! p) goto err;
		p -> next = list -> first;
		list -> first = p;
	}

	list -> count = i;
	return list;

err:
	/* I donot release each element at this time.
	 for caller must hand the input array. */
	release_linklist (list, __def_free_hook);
	return NULL;
}


void foreach_linklist (
		plinklist _l, llist_visitf _vf) {
	plistnode p;
	if (! _l || ! _vf) return;

	p = _l -> first;
	while (p) {
		_vf (p);
		p = p -> next;
	}
}



void foreach_linklist_revr_recr (
		plinklist _l, llist_visitf _vf) {
	if (! _l || ! _vf) return;
	__foreach_linklist_revr_recr (_l -> first, _vf);
}


static void __foreach_linklist_revr_recr (
		plistnode _n, llist_visitf _vf) {
	if (_n) { 
		__foreach_linklist_revr_recr (_n -> next, _vf);
		_vf (_n);
	}
}


void sort_linklist (plinklist _l, cmphook _cmp) {
	plistnode pre, p, post = NULL, tmp;
	listnode node;

	if (! _l || ! _l -> first) return;
	if (! _cmp) _cmp = __default_cmp_func;

	node.next = _l -> first;
	p = _l -> first;
	if (p) post = p -> next;

	p -> next = NULL;
	p = post;

	while (p) {
		pre = &node;
		post = p -> next;

		while (pre -> next && 
				CMP_LT == _cmp (pre -> next -> data, 
					p -> data))
			pre = pre -> next;

		p -> next = pre-> next;
		pre -> next = p;

		p = post;
	}

	_l -> first = node.next;
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


