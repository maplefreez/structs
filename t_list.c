#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "sort.h"


/****** Pre-defination for test suits. ******/
static void t_arraylist_insert ();
static void t_linklist_insert ();
static void t_linklist_delete ();
static void t_linklist_find ();
static void t_linklist_create_by_arr ();
static void t_linklist_create_by_arr_revr ();
static void t_linklist_release ();
static void t_linklist_foreach ();
static void t_linklist_sort ();
static void t_linklist_getindex ();

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
	t_linklist_insert ();
	t_linklist_create_by_arr ();
	t_linklist_create_by_arr_revr ();
	t_linklist_find ();
	t_linklist_delete ();
	t_linklist_release ();
	t_linklist_foreach ();
	t_linklist_getindex ();
	t_linklist_sort ();

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


