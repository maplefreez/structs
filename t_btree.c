#include "btree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
// #include <string.h>

/****** Pre-defination for test suits. ******/
static void t_bt_create_pre_inorder ();
static void t_bt_visit_func (pbtnode);

/* Main test entry. */
int main (int argc, char* argv []) {
	t_bt_create_pre_inorder ();
	return 0;
}


/******* Implementation for each test suit. ******/
static void t_bt_create_pre_inorder () {
	char* preorder = "CBKEDFMGHQS";
	char* inorder = "KDEBCMGHFSQ";

	pbtree tree = bt_create_pre_inorder (preorder, inorder);
	bt_pretraversal (tree, t_bt_visit_func);
	puts ("");
	bt_posttraversal (tree, t_bt_visit_func);
	puts ("");
	bt_inordertraversal (tree, t_bt_visit_func);

	bt_release (tree, NULL);
}


static void t_bt_visit_func (pbtnode _node) {
	if (_node) 
		printf ("%c ", _node -> data);
}


