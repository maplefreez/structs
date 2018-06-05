#include <stdlib.h>
#include "common.h"
#include "thrbtree.h"

static void _thrbt_inorderthread (pthrbtree, pthrnode);


/* Create a threaded binary tree by preorder and inorder 
 * traversal sequence.*/
thrpbtree thrbt_create_pre_inorder (char* _preo, char* _ino) {
	// TODO...
}


thrpbtree thrbt_create_post_inorder (char*, char*);

void thrbt_inorderthreaded (pthrbtree _t) {
}


/* Note: the last leaf a tree shell be
 * marked by the function caller. */
static pthrbtree _thrbt_inorderthread (
		pthrbtree _t, pthrnode _prenode) {
	if (_t) {
		/* left child tree. */
		_thrbt_inorderthread (_t -> left, _t);

		/* Current node. We just mark it's 
		 * immediate predecessor, and the 
		 * immediate successor in next 
		 * recursive calling. */
		if (! _t -> left) {
			_t -> ltag = THREAD;
			_t -> left = _prenode;
		}

		/* It's predecessor. */
		if (! _prenode -> right) {
			_prenode -> rflag = THREAD; 
			_prenode -> right = _t;
		}

		_thrbt_inorderthread (_t -> right, _t);
		/* right child tree. */
	}

	/* TODO: NOTE the _prenode parameter. */
	return _t;
}

void thrbt_pretraversal (pthrbtree, bt_visitf);
void thrbt_posttraversal (pthrbtree, bt_visitf);
void thrbt_inordertraversal (pthrbtree, bt_visitf);
void thrbt_release (pthrbtree, bt_freef);




