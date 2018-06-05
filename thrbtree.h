/* A threaded binary tree implementation. It making
 * all right child pointers that would normally be 
 * null point to the inorder successor of the node 
 * and all left child pointers that would normally
 * be null point to the inorder predecessor of the
 * node.
 *
 * Author : ez
 * Date : 2018/6/4
 */

#ifndef _THR_BTREE_H_
#	define _THR_BTREE_H_


/* ltag and rtag is to flag what
 * the right and left ptr are.
 * tag == 1 : ptr points to child.
 * tag == 0 : ptr points to next 
 *    inorder predecessor (left)
 *    or inorder successor (right)
 *    node. */
typedef struct _thrbtree {
	int ltag:16;
	int rtag:16;
	struct _thrbtree* left, *right;
	void* data;
} thrbtree, *pthrbtree;


/* Create a new threaded binary tree by its preorder 
 * and inorder traversal sequency. If one of $1 and 
 * $2 is NULL, function return NULL, and occurring 
 * error as well.
 *
 * $1  The preorder secuency.
 * $2  The inorder sequency.
 *
 * Return the new tree pointer while successful. */
extern thrpbtree thrbt_create_pre_inorder (char*, char*);


/* Create a new threaded binary tree by its postorder 
 * and inorder traversal sequency. If one of $1 and 
 * $2 is NULL, function return NULL, and occurring 
 * error as well.
 *
 * $1  The preorder secuency.
 * $2  The inorder sequency.
 *
 * Return the new tree pointer while successful. */
extern thrpbtree thrbt_create_post_inorder (char*, char*);


/* Preordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void thrbt_pretraversal (pthrbtree, bt_visitf);


/* Postordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void thrbt_posttraversal (pthrbtree, bt_visitf);


/* Inordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void thrbt_inordertraversal (pthrbtree, bt_visitf);


/* Release the memory from one pbtree entity.
 * This function is based on the following order:
 *	left -> right -> root.
 * Obviously a recursive implementation matches! 
 * $1  The tree to be released.
 * $2  The function invoked on each node.
 *
 * Note: If we special NULL to $2, nothing will be done
 * on data field, traveling each node. */
extern void thrbt_release (pthrbtree, bt_freef);

#endif // ~ _THR_BTREE_H_
