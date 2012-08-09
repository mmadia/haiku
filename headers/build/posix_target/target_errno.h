/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _POSIX_ERRNO_H
#define _POSIX_ERRNO_H


#ifdef __cplusplus
extern "C"
{
#endif

#include <target_Errors.h>

#define _HAIKU_BUILD_ENOERR		0
#define _HAIKU_BUILD_EOK		ENOERR	/* some code assumes EOK exists */

_HAIKU_BUILD_DECLARE_FUNCTION(int*, _errnop, (void))
#define _haiku_build_errno		(*(_haiku_build__errnop()))

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define ENOERR				_HAIKU_BUILD_ENOERR
#	define EOK					_HAIKU_BUILD_EOK

#	define errno				_haiku_build_errno
#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#ifdef __cplusplus
} /* "C" */
#endif

#endif /* _POSIX_ERRNO_H */
