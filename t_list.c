#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "sort.h"


/****** Pre-defination for test suits. ******/
static void t_arraylist_insert ();
static void t_arraylist_reverse ();
static void t_arraylist_create_by_arr ();
static void t_arraylist_delete_key ();
static void t_arraylist_merge ();

static void t_linklist_insert ();
static void t_linklist_delete ();
static void t_linklist_find ();
static void t_linklist_create_by_arr ();
static void t_linklist_create_by_arr_revr ();
static void t_linklist_release ();
static void t_linklist_foreach ();
static void t_linklist_sort ();
static void t_linklist_getindex ();
static void t_linklist_getmaximum ();
static void t_linklist_getminimum ();
static void t_linklist_delete_key ();

/* For testing */
anytype input [16] = {0, };

static void __def_free_hook (const void*);
static void __llist_visitf1 (plistnode);
static void __llist_visitf2 (plistnode);
static void __llist_visitf3 (plistnode);
static void __init_for_testing ();
static void __exit_for_testing ();


/* Main test entry. */
int main (int argc, char* argv []) {
	__init_for_testing ();

	t_arraylist_insert ();
	t_arraylist_create_by_arr ();
	t_arraylist_delete_key ();
	t_arraylist_reverse ();
	t_arraylist_merge ();

	t_linklist_insert ();
	t_linklist_create_by_arr ();
	t_linklist_create_by_arr_revr ();
	t_linklist_find ();
	t_linklist_delete ();
	t_linklist_release ();
	t_linklist_foreach ();
	t_linklist_getindex ();
	t_linklist_getmaximum ();
	t_linklist_getminimum ();
	t_linklist_sort ();
	t_linklist_delete_key ();

	__exit_for_testing ();
	return 0;
}



/******* Implementation for each test suit. ******/
static void t_arraylist_insert () {
	int data [] = {
		10, 20, 30, 40,
		50, 60, 70, 80,
		90, 100, 200, 300
	};

	int count = sizeof (data) / sizeof (int);
	int i = 0;

	parraylist list = NULL;

	/* 0x01 */
	{
		list =create_arraylist (count + 4);
		assert (list);
		assert (list -> capacity == (count + 4));
		assert (list -> count == 0);

		while (i < count) {
			assert (
				insert_arraylist (list, (anytype) data [i], i)
			);
			assert (list -> count == (++ i));
		}
		
		/* Assert each element. */
		i = 0;
		while (i < count) {
			assert ((anytype) (list -> array [i]) == 
					(anytype) data [i]);
			i ++;
		}

		release_arraylist (list, NULL);
	}


}


static void t_arraylist_reverse () {
	{ // 0x01
		parraylist list = NULL;
		assert (reverse_arraylist (list) == NULL);
	}

	{ // 0x02
		anytype input [] = {
			1, 2, 3, 4, 5, 6, 7, 8,
			9, 10, 11, 12, 13, 14, 15, 16
		};
		int i, count = sizeof (input) / sizeof (anytype);
		parraylist list = create_arraylist_by_arr (input, count);
		assert (list);

		assert (reverse_arraylist (list) == list);

		for (i ^= i; i < count; ++ i)
			assert (list -> array [i] == input [count - i - 1]);

		release_arraylist (list, NULL);
	}
}

static void t_arraylist_create_by_arr () {
	{ // 0x02
		anytype input [] = {
			1, 2, 3, 4, 5, 6, 7, 8,
			9, 10, 11, 12, 13, 14, 15, 16
		};
		int i, count = sizeof (input) / sizeof (anytype);
		parraylist list = create_arraylist_by_arr (input, count);
		assert (list);
		assert (list -> count == count);

		for (i ^= i; i < count; ++ i)
			assert (list -> array [i] == input [i]);

		release_arraylist (list, NULL);
	}
}


static void t_arraylist_delete_key () {
	{ // 0x02
		anytype input [] = {
			1, 2, 3, 4, 8, 6, 6, 8,
			9, 6, 11, 6, 13, 6, 8, 4,
			6, 6, 6, 6, 6, 6, 7, 6, 6
		};
		anytype key = (anytype) 6;
		int i, j, count = sizeof (input) / sizeof (anytype);
		parraylist list = create_arraylist_by_arr (input, count);
		assert (list);
		assert (list -> count == count);

		delete_arraylist_key (list, key, NULL, NULL);

		for (i ^= i, j ^= j; i < count; ++ i) {
			if (input [i] == key) continue;
			else {
				assert (list -> array [j] == input [i]);
				j ++;
			}
		}

		release_arraylist (list, NULL);
	}
}

static void t_arraylist_merge () {
	{ // 0x01
		anytype input [] = {
			1, 3, 5, 7, 9, 11, 13,
			15, 17, 19,
			2, 4, 6, 8, 10, 12, 14,
			16, 18, 20, 22, 24, 26,
			30
		};
		const int count = sizeof (input) / sizeof (anytype);
		const int ac = 10;
		const int bc = 14;
		int i = 0, j = 0;

		parraylist alist = create_arraylist_by_arr (input, ac);
		parraylist blist = create_arraylist_by_arr (input + ac, bc);

		assert (alist && alist -> count == ac);
		assert (blist && blist -> count == bc);

		parraylist c = merge_arraylist (alist, blist, NULL);
		assert (c && c -> count == count);
		
		/* For each element. */
		straight_insertsort (input, count, NULL);
		for (; i < count; ++ i)
			assert (c -> array [i] == input [i]);

		release_arraylist (alist, NULL);
		release_arraylist (blist, NULL);
		release_arraylist (c, NULL);
	}

	{ // 0x02
		arraylist zerolist = { NULL, 0, 0 };
		arraylist zerolist1 = { NULL, 0, 0 };

		parraylist l = merge_arraylist (NULL, NULL, NULL);
		assert (l == NULL);

		l = merge_arraylist (&zerolist, &zerolist1, NULL);
		assert (l == NULL);
	}

	{ // 0x03
		anytype input [] = {
			1, 2, 3, 4, 9
		};
		anytype input1 [] = { 8 };
		int count = 0, i;

		count = sizeof (input) / sizeof (anytype);
		arraylist onelist = { input1, 1, 1 };
		parraylist list = create_arraylist_by_arr (input, count);
		parraylist res = NULL;

		assert (list && list -> count == count);
		res = merge_arraylist (&onelist, list, NULL);

		assert (res && res -> count == count + 1);

		/* For each element. */
		for (i = 0; i < 4; ++ i)
			assert (input [i] == res -> array [i]);

		assert (res -> array [i ++] == input1 [0]);
		assert (res -> array [i ++] == input [4]);

		release_arraylist (list, NULL);
		release_arraylist (res, NULL);
	}

	{ // 0x04
		anytype input [] = { 0x400 };
		anytype input1 [] = { 0x800 };
		arraylist onelist = { input, 1, 1 };
		arraylist onelist1 = { input1, 1, 1 };
		parraylist res = merge_arraylist (&onelist, &onelist1, NULL);

		assert (res && res -> count == 2 && res -> capacity == 2);
		assert (res -> array [0] == input [0]);
		assert (res -> array [1] == input1 [0]);
		
		release_arraylist (res, NULL);
	}

	{ // 0x05
		anytype input [] = { 0x400 };
		arraylist onelist = { input, 1, 1 };
		arraylist zerolist = { NULL, 0, 0 };
		parraylist res = merge_arraylist (&onelist, &zerolist, NULL);

		assert (! res);
	}
}


static void t_linklist_insert () {
	int flag;
	plinklist list;
	plistnode ptr;


	{
		/* 0x0. Add to the first index. */
		list = new_linklist ();
		assert (list && list -> count == 0
				&& list -> first == NULL);

		flag = insert_linklist (list, (anytype) 32, 0);
		assert (flag);

		assert (list -> count == 1 &&
				list -> first != NULL);
		assert (list -> first -> data == (anytype) 32);
		assert (list -> first -> next == NULL);

		/* 0x2. Append to the rear. */
		flag = insert_linklist (list, (anytype) 0xFFFFFFFF, 1);
		/* First element. */
		assert (flag);
		assert (list -> count == 2 &&
				list -> first != NULL);

		/* Second element (The last one). */
		ptr = list -> first -> next;
		assert (ptr && ptr -> next == NULL);
		assert (ptr -> data == (anytype) 0xFFFFFFFF);

		release_linklist (list, __def_free_hook);
	}


}


static void t_linklist_create_by_arr () {
	int i = 0;
	anytype data [] = {
		10, 20, 30, 40,
		50, 60, 70, 80,
		90, 100, 200, 300
	};
	plistnode node = NULL;
	int count = sizeof (data) / sizeof (anytype);

	plinklist list = create_linklist_by_arr (data, count);
	assert (list);
	assert (list -> count == count);

	node = list -> first;
	while (i < count && node) {
		assert (node -> data == data [i ++]);
		node = node -> next;
	}

	release_linklist (list, NULL);
}


static void t_linklist_create_by_arr_revr () {
	{ // 0x01
		anytype* data = NULL;
		assert (! create_linklist_by_arr_revr (NULL, 0));
		assert (! create_linklist_by_arr_revr (data, 0));
		assert (! create_linklist_by_arr_revr (NULL, 512));
	}

	{ // 0x02
		int i = 0;
		anytype data [] = {
			0, 1, 2, 3, 4, 5,
			6, 7, 8, 9, 10,
			20, 30, 40, 50,
			60, 70, 80, 90,
			100, 120
		};
		plistnode node = NULL;
		int count = sizeof (data) / sizeof (anytype);

		plinklist list = create_linklist_by_arr_revr (
				data, count);
		assert (list);
		assert (list -> count == count);

		node = list -> first;
		while (i < count && node) {
			assert (node -> data == data [count - (++ i)]);
			node = node -> next;
		}

		release_linklist (list, NULL);
	}

	{ // 0x03
		anytype data [2] = { 0x80, 0xEF };
		plistnode node = NULL;
		plinklist list = create_linklist_by_arr_revr (
				data, 2);
		assert (list);
		assert (list -> count == 2);

		/* 1st(= 0xEF) */
		node = list -> first;
		assert (node && node -> data == data [1]);

		/* 2nd(= 0x80) */
		node = node -> next;
		assert (node && node -> data == data [0]);

		/* 3rd(= NULL) */
		node = node -> next;
		assert (! node);

		release_linklist (list, NULL);
	}

}


static void t_linklist_delete () {
	int i = 0;
	anytype data [] = {
		1, 2, 3, 4, 5, 6,
		7, 8, 9, 0xA, 0xB
	}, deleted;
	plistnode node = NULL;
	int count = sizeof (data) / sizeof (anytype);

	plinklist list = create_linklist_by_arr (data, count);
	assert (list);
	assert (list -> count == count);

	/* Delete 4. */
	deleted = delete_linklist (list, 3);
	assert (deleted == (anytype) 4);
	assert (list -> count == count - 1);

	node = list -> first;
	while (i < count && node) {
		if (i == 3) { i ++; continue; }
		assert (node -> data == data [i ++]);
		node = node -> next;
	}

	/* Delete 0xB */
	deleted = delete_linklist (list, 9);
	assert (deleted == (anytype) 0xB);
	assert (list -> count == count - 2);

	node = list -> first;
	while (i < count && node) {
		if (i == 3 || i == 10) { i ++; continue; }
		assert (node -> data == data [i ++]);
		node = node -> next;
	}

	/* Delete 0x1 */
	deleted = delete_linklist (list, 0);
	assert (deleted == (anytype) 0x1);
	assert (list -> count == count - 3);

	node = list -> first;
	while (i < count && node) {
		if (i == 0 || i == 3 || i == 10) { 
			i ++; continue; 
		}
		assert (node -> data == data [i ++]);
		node = node -> next;
	}


	release_linklist (list, __def_free_hook);

}

static void t_linklist_find () {
	int i = 0, ret;
	anytype data [] = {
		9, 2, 41, 8, 3, 16,
		217, 88, 0xff, 0xA, 0xB
	};
	plistnode node = NULL;
	plinklist list = NULL;
	int count = sizeof (data) / sizeof (anytype);

	/* Input list ptr is NULL. Must return -1. */
	ret = find_linklist (list, (anytype) 9999, NULL);
	assert (ret == -1);

	list = create_linklist_by_arr (data, count);
	assert (list);
	assert (list -> count == count);

	/* Find element 0x3. Index is 4. */
	ret = find_linklist (list, (anytype) 0x3, NULL);
	assert (ret == 4);

	/* Find element 0xB. Index is 10. */
	ret = find_linklist (list, (anytype) 0xB, NULL);
	assert (ret == 10);

	/* Find element 9. Index is 0. */
	ret = find_linklist (list, (anytype) 0x9, NULL);
	assert (ret == 0);

	/* Find element 512. It's not existing.  */
	ret = find_linklist (list, (anytype) 512, NULL);
	assert (ret == -1);

	release_linklist (list, __def_free_hook);
}


static void t_linklist_release () {
	int i = 0, ret;
	anytype data [] = {
		9, 2, 41, 8, 3, 16,
		217, 88, 0xff, 0xA, 0xB
	};
	int count = sizeof (data) / sizeof (anytype);

	plinklist list = new_linklist ();
	assert (list);

	release_linklist (list, NULL);
	release_linklist (NULL, NULL);

	list = create_linklist_by_arr (data, count);
	assert (list); assert (list -> count == count);
	release_linklist (list, NULL);
}


static void t_linklist_foreach () {
	{ // 0x01
		plinklist l = NULL;
		foreach_linklist (l, NULL);
		foreach_linklist (l, __llist_visitf1);
	}

	{ // 0x02
		plinklist l = create_linklist_by_arr_revr (input, 16);
		assert (l);

		foreach_linklist (l, __llist_visitf1);
		foreach_linklist_revr_recr (l, __llist_visitf2);

		release_linklist (l, __def_free_hook);
	}

	{ // 0x03
		anytype arr [1] = { 9999 };
		plinklist l = create_linklist_by_arr_revr (arr, 1);

		foreach_linklist (l, __llist_visitf3);
		foreach_linklist_revr_recr (l, __llist_visitf3);

		release_linklist (l, NULL);
	}
}



static void t_linklist_sort () {
	{ // 0x01
		plinklist l = NULL;
		linklist L = { NULL, 0 };
		sort_linklist (l, NULL);
		sort_linklist (&L, NULL);
	}

	{ // 0x02
		int i;
		anytype array [16] = {
			64, 62, 60, 58,
			56, 54, 52, 50,
			48, 46, 44, 42,
			40, 38, 36, 32
		}; 

		plinklist l = create_linklist_by_arr (array, 16);
		plistnode p = NULL;
		assert (l && l -> count == 16);
		sort_linklist (l, NULL);

		/* Sort array. */
		straight_insertsort (array, 16, NULL);

		for (i ^= i; i < 16; i ++) {
			anytype x = get_linklist_index (l, i + 1);
			assert (array [i] == x);
		}
		
		p = l -> first; i ^= i;
		while (p) { p = p -> next; i ++; }
		assert (i == l -> count);

		release_linklist (l, NULL);
	}

	{ // 0x03
		anytype array [1] = { 4096 }; int i;
		plistnode p = NULL;
		plinklist l = create_linklist_by_arr (array, 1);
		assert (l && l -> count == 1);

		sort_linklist (l, NULL);
		anytype x = get_linklist_index (l, 1);
		assert (array [0] == x);

		p = l -> first; i ^= i;
		while (p) { p = p -> next; i ++; }
		assert (i == l -> count);

		release_linklist (l, NULL);
	}

}


static void t_linklist_getindex () {
	{ // 0x01
		plinklist l = NULL;
		linklist L = { NULL, 0 };
		assert (! get_linklist_index (l, 0));
		assert (! get_linklist_index (&L, 12));
	}

	{ // 0x02
		int i;
		anytype array [16] = {
			1, 2, 3, 4, 5, 
			6, 7, 8, 9, 10,
			11, 12, 13, 14,
			15, 16
		}; 

		plinklist l = create_linklist_by_arr (array, 16);
		assert (l && l -> count == 16);

		for (i ^= i; i < 16; i ++) {
			anytype x = get_linklist_index (l, i + 1);
			assert (array [i] == x);
		}

		release_linklist (l, NULL);
	}

	{ // 0x03
		anytype array [12] = {
			1, 2, 3, 4, 5, 
			6, 7, 8, 9, 10,
			11, 12 
		}, x;

		plinklist l = create_linklist_by_arr (array, 12);
		assert (l && l -> count == 12);

		x = get_linklist_index (l, 32);
		assert (NULL == x);
		x = get_linklist_index (l, 0);
		assert (NULL == x);
		x = get_linklist_index (l, 9);
		assert ((anytype) 9 == x);
		x = get_linklist_index (l, 13);
		assert (NULL == x);
		x = get_linklist_index (l, 12);
		assert ((anytype) 12 == x);

		release_linklist (l, NULL);
	}
}


static void t_linklist_getmaximum () {
	{ // 0x01
		plinklist l = NULL;
		linklist L = { NULL, 0 };
		assert (! get_linklist_max (l, NULL));
		assert (! get_linklist_max (&L, NULL));
	}

	{ // 0x02
		int i; int count;
		anytype array [] = {
			1, 2, 3, 4, 5, 
			6, 7, 8, 9, 10,
			11, 12, 13, 14,
			15, 16, 78, 23, 0,
			233431, 87, 91, 6553, 21
		}, x; 

		count = sizeof (array) / sizeof (anytype);

		plinklist l = create_linklist_by_arr (array, count);
		assert (l && l -> count == count);

		x = get_linklist_max (l, NULL);
		assert (x == array [19]);

		release_linklist (l, NULL);
	}

	{ // 0x03
		anytype array [1] = {
			-65535
		}, x;

		plinklist l = create_linklist_by_arr (array, 1);
		assert (l && l -> count == 1);

		x = get_linklist_max (l, NULL);
		assert (array [0] == x);

		release_linklist (l, NULL);
	}
}

static void t_linklist_getminimum () {
	{ // 0x01
		plinklist l = NULL;
		linklist L = { NULL, 0 };
		assert (! get_linklist_min (l, NULL));
		assert (! get_linklist_min (&L, NULL));
	}

	{ // 0x02
		int i; int count;
		anytype array [] = {
			1, 2, 3, 4, 5, 
			6, 7, 8, 9, 10,
			11, 12, 13, 14,
			15, 16, 78, 23, 0,
			233431, 87, 91, 6553, 21
		}, x; 

		count = sizeof (array) / sizeof (anytype);

		plinklist l = create_linklist_by_arr (array, count);
		assert (l && l -> count == count);

		x = get_linklist_min (l, NULL);
		assert (x == array [18]);

		release_linklist (l, NULL);
	}

	{ // 0x03
		anytype array [1] = {
			-65535
		}, x;

		plinklist l = create_linklist_by_arr (array, 1);
		assert (l && l -> count == 1);

		x = get_linklist_min (l, NULL);
		assert (array [0] == x);

		release_linklist (l, NULL);
	}
}


static void t_linklist_delete_key () {
	{ // 0x01
		delete_linklist_key (NULL, (anytype) 123, NULL, NULL);
	}

	{ // 0x02
		int i = 0;
		int count = 0;
		plinklist l;
		plistnode p;
		anytype array [] = {
			1, 2, 3, 4, 5, 6,
			7, 8, 8, 9, 8, 10,
			12, 39, 53, 0, -9,
			893, -8, 98, 8, 7
		};

		count = sizeof (array) / sizeof (anytype);
		l = create_linklist_by_arr (array, count);
		assert (l && l -> count == count);

		/* Delete all the element whose 
			 value is 8. */
		delete_linklist_key (l, (anytype) 8, NULL, NULL);

		/* Check. */
		p = l -> first;
		while (i < count && p) {
			if (array [i] != (anytype) 8) {
				assert (array [i] == p -> data);
				p = p -> next;
			}
			++ i;
		}

		release_linklist (l, NULL);
	}

	{ // 0x03
		int i = 0;
		int count = 0;
		plinklist l;
		plistnode p;
		anytype array [] = {
			9, 9, 9, 9, 9, 9, 
			9, 9, 9, 9, 9, 9, 
			9, 9, 9, 9, 9, 9
		};

		count = sizeof (array) / sizeof (anytype);
		l = create_linklist_by_arr (array, count);
		assert (l && l -> count == count);

		/* Delete all the element whose 
			 value is 8. */
		delete_linklist_key (l, (anytype) 8, NULL, NULL);
		assert (l -> count == count);
		
		p = l -> first;
		while (p) {
			assert (p -> data == (anytype) 9);
			p = p -> next;
			++ i;
		}

		assert (i == count);

		delete_linklist_key (l, (anytype) 9, NULL, NULL);
		p = l -> first;
		assert (l -> count == 0);
		assert (p == NULL);

		release_linklist (l, NULL);
	}
}


static void __init_for_testing () {
		int i;
		for (i = 0; i < 16; ++ i)
			input [i] = (anytype) (i + 1);
}

static void __exit_for_testing () {
}


static void __llist_visitf1 (plistnode _node) {
	static int c = 0;
	if (_node) {
		int index = 15 - c;
		assert (_node -> data == input [index]);
		c ++;
	}
}

static void __llist_visitf2 (plistnode _node) {
	static int c = 0;
	if (_node)
		assert (_node -> data == input [c ++]);
}

static void __llist_visitf3 (plistnode _node) {
	if (_node)
		assert (_node -> data == (anytype) 9999);
}

static void __def_free_hook (const void* x) 
	{ /* Doing nothing. */ }


