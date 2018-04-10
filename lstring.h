#ifndef _LSTRING_H_
#	define _LSTRING_H_

#include "common.h"


/*
 * A minimum set of line string definiation.
 */
typedef struct _lstring {
	/* Store charactors. */
	char* chunk;

	/* Identify the length of chunk memory. */
	int length;
} lstring, *plstring;


/* Assume a new line-string entity with an
 * existing C string (char*).
 *
 * $1  The C string.
 *
 * Return a new entity of lstring structure while
 * successful. When $1 is NULL, or syscall
 * malloc fails unexpectedly, NULL will be returned.
 * If $1 is an empty string (''), a new lstring entity
 * with NULL assumed for charactor chunk will be returned.
 */
extern plstring str_assume (const char*);


/*
 * Return the length of string chunk. We've substracted 
 * the terminal byte ('\0',1 byte).
 *
 * $1  The lstring ptr.
 *
 * If $1 is NULL, return -1 (Maybe it 
 * should rationally be 0).
 */
extern int str_length (plstring);
extern int str_cmp (const plstring, const plstring);

/*
 * Clear the data chunk. This function calls free() for
 * data chunk field, setting it to NULL.
 *
 * $1  The lstring ptr.
 *
 * Note: Actually I personally guess the function useless. 
 * We'd rather invoke str_destroy(). I shell change the 
 * function so that it but clean up the data chunk without 
 * freeing it's occupation.
 */
extern rtn_status str_clear (plstring);

/*
 * Slice the string, then return the substring ranges
 * from position $2 to ($2 + $3 - 1). $1 is the 
 * substring length, including bytes at index $2.
 *
 * $1  An input string to be sliced.
 * $2  The beginning location of substring.
 * $3  The total length of substring.
 *
 * Note: Return NULL if $1 is NULL or an empty string.
 * $2 ranges [0, strlen ($1) - 1], or NULL will be returned.
 * $3 ranges [1, +INF], or NULL will be returned. 
 *
 * If $3 is greater than the remaining data length, we 
 * directly return the remaining data.
 * The length $3 including one byte indexed at $2.
 */
extern plstring str_substring (plstring, int, int);
extern plstring str_concat (const plstring, const plstring);


/* Free the memory of an existing lstring entity, including
 * the chunk buffer. Nothing will be done if $1 is NULL.
 *
 * $1   the lstring ptr to be destroyed.
 */
extern void str_destroy (plstring);

#endif // ~ _LSTRING_H_


