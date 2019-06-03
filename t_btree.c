#include "btree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
// #include <string.h>

/****** Pre-defination for test suits. ******/
static void t_bt_create_pre_inorder ();
static void t_bt_inordertraversal1 ();
static void t_bt_visit_func (pbtnode);
static void t_bt_leveltraversal ();

/* Main test entry. */
int main (int argc, char* argv []) {
	t_bt_create_pre_inorder ();
	t_bt_inordertraversal1 ();
	t_bt_leveltraversal ();
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


static void t_bt_inordertraversal1 () {
	char* preorder = "CBKEDFMGHQS";
	char* inorder = "KDEBCMGHFSQ";

	pbtree tree = bt_create_pre_inorder (preorder, inorder);
	puts ("");
	bt_inordertraversal1 (tree, t_bt_visit_func);

	bt_release (tree, NULL);
}


static void t_bt_leveltraversal () {
	{ // 0x01
		pbtree tree = NULL;
		bt_leveltraversal (NULL, t_bt_visit_func);
		
		bt_release (tree, NULL);
	}

	{ // 0x02
		char* preorder = "ABDHMRPCENQJ";
		char* inorder = "BHDRMPACEQNJ";
		pbtree tree = bt_create_pre_inorder (preorder, inorder);

		puts ("\n---------------------------------");
		bt_leveltraversal (tree, t_bt_visit_func);
		
		bt_release (tree, NULL);
	}
}


static void t_bt_visit_func (pbtnode _node) {
	if (_node) 
		printf ("%c ", _node -> data);
}


