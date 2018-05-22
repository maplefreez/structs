#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"


/****** Pre-defination for test suits. ******/
static void t_bst_insert ();
static void t_bst_visit_func (pbstnode);
static int _cmp_integer (void*, void*);

int main (int argc, char* argv []) {
	t_bst_insert ();
	return 0;
}

static void t_bst_insert () {
	int i = 0;

	/* Note, if the input array contains nagetive integer,
	 * then default comparation function should probably return
	 * 1(Greater) cuz -1 (for example) represents 0xffffffff as an
	 * unsigned integer. And that's the way the function works. */
	int array [] = {88, 34, 43, 193, 20, 32, -1, 33};
	pbstree tree = NULL;
	i = sizeof (array) / sizeof (int);
	for (-- i; i >= 0; -- i)
		tree = bst_insert (tree, (void*) (array [i]), _cmp_integer);

	bst_pretraversal (tree, t_bst_visit_func);
	puts ("");
	bt_inordertraversal ((pbtree) tree, (bt_visitf) t_bst_visit_func);
	bst_release (tree, NULL);
}

static void t_bst_visit_func (pbstnode _node) {
	if (_node) 
		printf ("%d ", _node -> data);
}


static int _cmp_integer (void* _a, void* _b) {
	signed long long a = (signed long long) _a;
	signed long long b = (signed long long) _b;
	if (a == b) return CMP_EQ;
	return a > b ? CMP_GT : CMP_LT;
}




