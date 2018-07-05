#include "list.h"
#include <stdlib.h>

static void __def_free_hook (const void*);
static void __ensure_enough_mem (parraylist, int);


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

	firstshift = _idx + 1;

	/* Shift data. */
	for (i = _list -> count; i > firstshift; -- i)
		_list -> array [i] = _list -> array [i - 1];

	_list -> array [_idx] = _x;
	_list -> count ++;
	return 1;
}



anytype delete_arraylist (parraylist, int);
int find_arraylist (parraylist, anytype, cmphook);


static void __def_free_hook (const void* _x) 
	{ /* DOING NOTHING!!! */ }


static void __ensure_enough_mem (parraylist _list, int _expand) {
	/* Try to realloc memory for list room.  */
}


