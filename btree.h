/*
 * A simple binary tree defination of chained 
 * storage structure.
 *
 * Author : ez
 * Date : 2018/5/11
 *
 *  _     _                 
 * | |__ | |_ _ __ ___  ___ 
 * | '_ \| __| '__/ _ \/ _ \
 * | |_) | |_| | |  __/  __/
 * |_.__/ \__|_|  \___|\___|
 *                           
 */

#ifndef _BTREE_H_
#	define _BTREE_H_

#	define INIT_STACK_LEN    0x8

#include <stdbool.h>
#include "common.h"

typedef struct _btree btree, btnode, 
				*pbtree, *pbtnode;

typedef struct _btree {
	/* Pointer to exactual data block. 
	 * If your data block length is less 
	 * than the width of sizeof(void*),
	 * just keep it with explicity conversion. 
	 * E.g.:  data = (void*) 0x340f; */
	void* data;

	/* Pointer field to left, right child. */
	btnode* left, *right;
} btree, *pbtree,
	btnode, *pbtnode;


/* A function signature for visiting
 * each `btree' empty. */
typedef void (*bt_visitf) (pbtnode);

/* A function signature for releasing
 * each data field on node. */
typedef void (*bt_freef) (pbtnode);

/* A function signature for comparation. */
typedef int (*bt_cmpf) (const anytype, const anytype);


/* Create a new tree by inputing data list
 * and it's length. The list shell be supposed
 * as a preorder traversal sequency.
 * $1  The data list. 
 * $2  The length of $1. 
 * 
 * Return the new tree pointer while successful. 
 * Or NULL if $1 is NULL, empty or another unexpected
 * error (e.g. out of memory). */
// extern pbtree bt_create (void**, int);


/* Create a new tree by its preorder and inorder
 * traversal sequency. If one of $1 and $2 is NULL,
 * function return NULL, and occurring error as well.
 * $1  The preorder secuency.
 * $2  The inorder sequency.
 *
 * Return the new tree pointer while successful. */
extern pbtree bt_create_pre_inorder (char*, char*);


/* Create a new tree by its postorder and inorder
 * traversal sequency. If one of $1 and $2 is NULL,
 * function return NULL, and occurring error as well.
 * $1  The preorder secuency.
 * $2  The inorder sequency.
 *
 * Return the new tree pointer while successful. */
extern pbtree bt_create_post_inorder (char*, char*);

/* TODO  */
extern pbtree bt_create_post_inorder (char*, char*);


/* Create a new tree node by inputing data.
 * $1  The data pointer. 
 * 
 * Return a new tree node while successful. 
 * Or NULL if $1 is NULL or another unexpected
 * error (e.g. out of memory). */
extern pbtnode bt_create_node (void*);


/* Preordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void bt_pretraversal (pbtree, bt_visitf);


/* Postordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void bt_posttraversal (pbtree, bt_visitf);


/* Inordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void bt_inordertraversal (pbtree, bt_visitf);

/* Inordering traverse each node of a tree by invoke 
 * the input function pointer $2. This function use 
 * non-recursively implemention. A default $2 
 * implementation will be used when caller gets a 
 * NULL function. */
extern void bt_inordertraversal1 (pbtree, bt_visitf);


/* Traverse tree node with each level, by invoke the
 * input function pointer $2. A default implementation
 * will be used when caller gets a NULL function. */
extern void bt_leveltraversal (pbtree, bt_visitf);


/* Release the memory from one pbtree entity.
 * This function is based on the following order:
 *	left -> right -> root.
 * Obviously a recursive implementation matches! 
 * $1  The tree to be released.
 * $2  The function invoked on each node.
 *
 * Note: If we special NULL to $2, nothing will be done
 * on data field, traveling each node. */
extern void bt_release (pbtree, bt_freef);


/* Judge whether the specified tree is a BST. 
 * We treat a NULL as a non-BST. The algorighm
 * is based on the inorder traversal. */
extern bool bt_is_bst (pbtree, bt_cmpf);


#endif // ~ _BTREE_H_

