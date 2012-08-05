/*
 * Copyright 2008-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SIZE_T_H_
#define _SIZE_T_H_


/* ATM we don't define ssize_t for GCC2 */
#if __GNUC__ > 2 && !defined(_HAIKU_BUILD_ssize_t__)
#	define __HAIKU_BUILD_ssize_t__
typedef long signed int	_HAIKU_BUILD_IDENTIFIER(ssize_t);
#endif

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	ifdef __HAIKU_BUILD_ssize_t__
#		define __ssize_t__
#	endif
#endif


#endif	/* _SIZE_T_H_ */
