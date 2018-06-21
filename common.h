#ifndef _COMMON_H_
#	define _COMMON_H_

typedef int rtn_status;

#	define STAT_SUCC  0
// #	define STAT_FAIL  1
#	define STAT_ERR   -2

#	define CMP_GT  -1
#	define CMP_EQ   0
#	define CMP_LT   1


/* Any type for data. */
typedef void* anytype;

/* Common comparation function prototype. */
typedef int (*cmphook) (const anytype, const anytype);

/* A free-memory callback prototype. */
typedef void (*freehook) (const void*);

#endif // ~ _COMMON_H_
