#ifndef _LSTRING_H_
#	define _LSTRING_H_

#include "common.h"

// #	define _MIN_CHUNK  8

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
 * Return the length of string chunk.
 */
extern int str_length (plstring);
extern int str_cmp (const plstring, const plstring);
extern rtn_status str_clear (plstring);
extern plstring str_substring (plstring, int, int);
extern plstring str_concat (const plstring, const plstring);


/* Free the memory of an existing lstring entity, including
 * the chunk buffer. Nothing will be done if $1 is NULL.
 *
 * $1   the lstring ptr to be destroyed.
 */
extern void str_destroy (plstring);

#endif // ~ _LSTRING_H_


