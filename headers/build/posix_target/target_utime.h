/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _UTIME_H_
#define _UTIME_H_


#include <sys/target_types.h>


struct _HAIKU_BUILD_IDENTIFIER(utimbuf) {
	_HAIKU_BUILD_IDENTIFIER(time_t) actime;		/* access time */
	_HAIKU_BUILD_IDENTIFIER(time_t) modtime;		/* modification time */
};


extern
#ifdef __cplusplus
"C"
#endif
_HAIKU_BUILD_DECLARE_FUNCTION(int, utime, (const char *path, const struct _HAIKU_BUILD_IDENTIFIER(utimbuf) *buffer))

#endif	/* _UTIME_H_ */
