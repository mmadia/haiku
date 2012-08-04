/*
 * Copyright 2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H


#ifndef __HAIKU_BUILD__THROW
#	define __HAIKU_BUILD__THROW
#endif

#ifndef __HAIKU_BUILD__P
#	define	__HAIKU_BUILD__P(s) s
#endif

#ifndef __HAIKU_BUILD__CONCAT
#	define	__HAIKU_BUILD__CONCAT(x,y)	x ## y
#endif

#ifndef __HAIKU_BUILD__STRING
#	define	__HAIKU_BUILD__STRING(x)		#x
#endif

#if defined(__cplusplus)
#	define	__HAIKU_BUILD__BEGIN_DECLS	extern "C" {
#	define	__HAIKU_BUILD__END_DECLS	};
#else
#	define	__HAIKU_BUILD__BEGIN_DECLS
#	define	__HAIKU_BUILD__END_DECLS
#endif

#define __HAIKU_BUILD__dead
#define __HAIKU_BUILD__dead2

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	ifndef __HAIKU_BUILD__THROW
#		define __THROW
#	endif

#	ifndef __HAIKU_BUILD__P
#		define	__P(s)			__HAIKU_BUILD__P(s)
#	endif

#	ifndef __HAIKU_BUILD__CONCAT
#		define	__CONCAT(x,y)	__HAIKU_BUILD__CONCAT(x,y)
#	endif

#	ifndef __HAIKU_BUILD__STRING
#		define	__STRING(x)		__HAIKU_BUILD__STRING(x)
#	endif

#	if defined(__cplusplus)
#		define	__BEGIN_DECLS	extern "C" {
#		define	__END_DECLS	};
#	else
#		define	__BEGIN_DECLS
#		define	__END_DECLS
#	endif

#	define __dead
#	define __dead2

#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#endif
