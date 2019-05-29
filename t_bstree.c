#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <assert.h>


/****** Pre-defination for test suits. ******/
static void t_bst_insert ();
static void t_bst_search ();
static void t_bst_delete ();
static void t_bst_getmax ();
static void t_bst_getmin ();
static void t_bst_visit_func (pbstnode);
static int _cmp_integer (void*, void*);

int main (int argc, char* argv []) {
	t_bst_insert ();
	t_bst_search ();
	t_bst_delete ();
	t_bst_getmax ();
	t_bst_getmin ();
	return 0;
}

static void t_bst_insert () {
	int num = 0;

	/* Note, if the input array contains nagetive integer,
	 * then default comparation function should probably return
	 * 1(Greater) cuz -1 (for example) represents 0xffffffff as an
	 * unsigned integer. And that's the way the function works. */
	int array [] = {
		88, 34, 43, 
		193, 20, 32, 
		-1, 33
	};
	pbstree tree = NULL;
	num = sizeof (array) / sizeof (int);
	// for (-- i; i >= 0; -- i)
	// 	tree = bst_insert (tree, (void*) (array [i]), _cmp_integer);
	tree = bst_create_int_array (array, num);

	bst_pretraversal (tree, t_bst_visit_func);
	puts ("");
	bt_inordertraversal ((pbtree) tree, (bt_visitf) t_bst_visit_func);
	bst_release (tree, NULL);
}

static void t_bst_visit_func (pbstnode _node) {
	if (_node) 
		printf ("%d ", _node -> data);
}


static void t_bst_delete () {
	int i = 0, num = 0;;
	int array [] = { 
		32, 15, 5, 16, 4, 6,
		10, 8, 12, 2, 3,
		43, 35, 34, 33, 36,
		92, 500
	};

	pbstree tree = NULL;
	pbstnode node = NULL;
	num = sizeof (array) / sizeof (int);

	tree = bst_create_int_array (array, num);
	puts ("");
	bt_inordertraversal ((pbtree) tree, (bt_visitf) t_bst_visit_func);
	assert (tree != NULL);

	/* Delete 500 */
	tree = bst_delete1 (tree, (void*) 500, _cmp_integer, NULL);
	assert 
	(
		NULL == bst_search (tree, (void*) 500, _cmp_integer)
	);

	puts ("");
	bt_inordertraversal ((pbtree) tree, (bt_visitf) t_bst_visit_func);

	/* Delete 5 */
	tree = bst_delete1 (tree, (void*) 5, _cmp_integer, NULL);
	assert 
	(
		NULL == bst_search (tree, (void*) 5, _cmp_integer)
	);

	puts ("");
	bt_inordertraversal ((pbtree) tree, (bt_visitf) t_bst_visit_func);

	/* Delete 10 */
	tree = bst_delete1 (tree, (void*) 10, _cmp_integer, NULL);
	assert 
	(
		NULL == bst_search (tree, (void*) 5, _cmp_integer)
	);

	puts ("");
	bt_inordertraversal ((pbtree) tree, (bt_visitf) t_bst_visit_func);

	/* Release */
	bst_release (tree, NULL);
}


static void t_bst_getmax () {
	{
		int num = 0;
		int array [] = { 
			32, 43, 92, 1, 
			31, 8, 12, 500, 
			2, 4 
		};

		pbstree tree = NULL;
		pbstnode node = NULL;
		num = sizeof (array) / sizeof (int);

		tree = bst_create_int_array (array, num);
		assert (tree != NULL);

		node = bst_getmax (tree);
		assert (node -> data == (anytype) 500);
		bst_release (tree, NULL);
	}
}

static void t_bst_getmin () {
	{
		int num = 0;
		int array [] = { 
			92, 1, 31, 8, 12, 500, 
			2, 4, 99, 324, 7823, 
			1234, 0x32, 55, 12, 9 
		};

		pbstree tree = NULL;
		pbstnode node = NULL;
		num = sizeof (array) / sizeof (int);

		tree = bst_create_int_array (array, num);
		assert (tree != NULL);

		node = bst_getmin (tree);
		assert (node -> data == (anytype) 1);
		bst_release (tree, NULL);
	}
}

static void t_bst_search () {
	int i = 0, num = 0;;
	int array [] = { 
		32, 43, 92, 1, 
		31, 8, 12, 500, 
		2, 4 
	};

	pbstree tree = NULL;
	pbstnode node = NULL;
	num = sizeof (array) / sizeof (int);

	tree = bst_create_int_array (array, num);
	assert (tree != NULL);

	node = bst_search (tree, (void*) 500, _cmp_integer);
	assert (node != NULL);
	assert ((node -> data) == (anytype) 500);

	bst_release (tree, NULL);
}

static int _cmp_integer (void* _a, void* _b) {
	signed long long a = (signed long long) _a;
	signed long long b = (signed long long) _b;
	if (a == b) return CMP_EQ;
	return a > b ? CMP_GT : CMP_LT;
}




