#include "lstring.h"
#include <string.h>
#include <stdlib.h>

plstring str_assume (const char* _str) {
	plstring ret;
	size_t len;

	if (! _str /* || ! *_str*/) return NULL;

	len = strlen (_str);
	ret = (plstring) malloc (sizeof (lstring));

	if (! ret) return NULL;

	/* For each structure field. */
	if (0 >= len) {
		ret -> chunk = NULL;
		ret -> length = 0;
	} else {
		ret -> chunk = (char*) malloc (len * sizeof (char));
		if (! ret -> chunk) goto err; 
		
		strncpy (ret -> chunk, _str, len);
		ret -> length = len;
	}

	return ret;

err:
	if (ret) {
		if (ret -> chunk) 
			free (ret -> chunk);
		free (ret);
	}

	return NULL;
}


int str_length (plstring _str) {
	if (_str)
		return _str -> length;

	return STAT_ERR;
}


int str_cmp (const plstring _s1, const plstring _s2) {
	int len1, len2, i;
	if (! _s1 || ! _s2) return STAT_ERR;

	len1 = _s1 -> length;
	len2 = _s2 -> length;

	if (len1 == len2) {
		for (; i < len1; ++ i)
			if (_s1 -> chunk [i] != _s2 -> chunk [i])
				return _s2 -> chunk [i] - _s1 -> chunk [i];
		return CMP_EQ;
	}

	return len2 - len1;
}


rtn_status str_clear (plstring _str) {
	if (! _str) return STAT_ERR;
	
	if (_str -> chunk)
		free (_str -> chunk);
	_str -> length = 0;

	return STAT_SUCC;
}


plstring str_substring (plstring _str, int _pos, int _len) {
	int len = 0, remain = 0;
	plstring ret = NULL;
	if (! _str) return NULL;

	len = _str -> length;
	remain = len - _pos + 1;
	if (_pos < 0 || _pos >= len || _len <= 0) 
		return NULL;

	ret = (plstring) malloc (sizeof (lstring));
	if (ret) {
		int actual_len = remain > len ? len : remain;
		ret -> chunk = (char*) malloc (actual_len * sizeof (char));

		if (! ret -> chunk) return NULL;
		strncpy (ret -> chunk, _str -> chunk + _pos, actual_len);
	}

	return ret;
err:
	if (ret && ret -> chunk) 
		free (ret -> chunk);
	return NULL;
}


plstring str_concat (const plstring _s1, const plstring _s2) {
	int len1, len2, total_len;
	plstring ret = NULL;
	if (! _s1 || ! _s2) return NULL;

	len1 = _s1 -> length;
	len2 = _s2 -> length;
	total_len = len1 + len2;

	ret = (plstring) malloc (sizeof (lstring));
	if (! ret) return NULL;

	/* Construct new plstring entity. */
	if (! total_len) {
		ret -> length = 0;
		ret -> chunk = NULL;
	} else {
		ret -> chunk = (char*) malloc (total_len * sizeof (char));
		if (! ret -> chunk) { free (ret); return NULL; }

		strncpy (ret -> chunk, _s1 -> chunk, len1);
		strncpy (ret -> chunk + len1, _s2 -> chunk, len2);
		ret -> length = total_len;
	}

	return ret;
}


void str_destroy (plstring _str) {
	if (_str) {
		if (_str -> chunk) 
			free (_str -> chunk);
		free (_str);
	}
}


