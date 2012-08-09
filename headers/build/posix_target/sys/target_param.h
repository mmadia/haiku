/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H


#include <target_limits.h>


#define _HAIKU_BUILD_MAXPATHLEN			_HAIKU_BUILD_PATH_MAX
#define _HAIKU_BUILD_MAXSYMLINKS		_HAIKU_BUILD_SYMLOOP_MAX

#define _HAIKU_BUILD_NOFILE				_HAIKU_BUILD_OPEN_MAX

#ifndef _HAIKU_BUILD_MIN
#	define _HAIKU_BUILD_MIN(a,b)		(((a) < (b)) ? (a) : (b))
#endif
#ifndef _HAIKU_BUILD_MAX
#	define _HAIKU_BUILD_MAX(a,b)		(((a) > (b)) ? (a) : (b))
#endif

#define _HAIKU_BUILD_ALIGNBYTES			(sizeof(long) - 1)
#define _HAIKU_BUILD_ALIGN(p) \
	(((u_long)(p) + _ALIGNBYTESALIGNBYTES) &~ _ALIGNBYTESALIGNBYTES)

/* maximum possible length of this machine's hostname */
#ifndef _HAIKU_BUILD_MAXHOSTNAMELEN
#	define _HAIKU_BUILD_MAXHOSTNAMELEN	256
#endif

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define MAXPATHLEN					_HAIKU_BUILD_MAXPATHLEN
#	define MAXSYMLINKS					_HAIKU_BUILD_MAXSYMLINKS

#	define NOFILE						_HAIKU_BUILD_NOFILE

#	ifdef _HAIKU_BUILD_MIN
#		define MIN(a,b)					_HAIKU_BUILD_MIN(a,b)
#	endif
#	ifdef _HAIKU_BUILD_MAX
#		define MAX(a,b)					_HAIKU_BUILD_MAX(a,b)
#	endif

#	define _ALIGNBYTES					_HAIKU_BUILD_ALIGNBYTES
#	define _ALIGN(p)					_HAIKU_BUILD_ALIGN(p)

	/* maximum possible length of this machine's hostname */
#	ifdef _HAIKU_BUILD_MAXHOSTNAMELEN
#		define MAXHOSTNAMELEN			_HAIKU_BUILD_MAXHOSTNAMELEN
#	endif

#	endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#endif	/* _SYS_PARAM_H */
