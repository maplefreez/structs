#include <stdlib.h>
#include "common.h"
#include "thrbtree.h"


/* For function _thrbt_inorderthread. */
static thrpbtree __prenode_threading;
static void _thrbt_inorderthread (pthrbtree, pthrnode);


/* Create a threaded binary tree by preorder and inorder 
 * traversal sequence.*/
thrpbtree thrbt_create_pre_inorder (char* _preo, char* _ino) {
	// TODO...
}


thrpbtree thrbt_create_post_inorder (char*, char*);

/* TODO TEST... */
void thrbt_inorderthreaded (pthrbtree _t) {
	if (! _t) return;

	/* Firstly we set the global 
	 * variable to root node. */
	__prenode_threading = _t;
	_thrbt_inorderthread (_t /* , __prenode_threading */);

	/* The last node. */
	if (__prenode_threading && 
			(! __prenode_threading -> right || 
			__prenode_threading == _t)) {
		__prenode_threading -> rflag = THREAD;
		__prenode_threading -> right = NULL;
	}

	/* Reset global variable. */
	__prenode_threading = NULL;
}


/* Note: the last leaf a tree shell be
 * marked by the function caller. */
static pthrbtree _thrbt_inorderthread (
		pthrbtree _t /* , pthrnode _prenode */) {
	if (_t) {
		/* left child tree. */
		_thrbt_inorderthread (_t -> left);

		/* Current node. We just mark it's 
		 * immediate predecessor, and the 
		 * immediate successor in next 
		 * recursive calling. */
		if (! _t -> left) {
			_t -> ltag = THREAD;
			_t -> left = __prenode_threading;
		}

		/* It's predecessor. */
		if (__prenode_threading && 
				! __prenode_threading -> right) {
			__prenode_threading -> rflag = THREAD; 
			__prenode_threading -> right = _t;
		}

		__prenode_threading = _t;

		/* right child tree. */
		_thrbt_inorderthread (_t -> right);
	}

	return _t;
}


void thrbt_pretraversal (pthrbtree, bt_visitf);
void thrbt_posttraversal (pthrbtree, bt_visitf);
void thrbt_inordertraversal (pthrbtree, bt_visitf);
void thrbt_release (pthrbtree, bt_freef);




