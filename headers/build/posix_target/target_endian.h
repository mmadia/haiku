/*
 * Copyright 2003-2012 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _ENDIAN_H_
#define _ENDIAN_H_


#include <config_target/target_HaikuConfig.h>


/* Defines architecture dependent endian constants.
 * The constant reflects the byte order, "4" is the most
 * significant byte, "1" the least significant one.
 */

#if defined(__HAIKU_BUILD_HAIKU_LITTLE_ENDIAN)
#	define _HAIKU_BUILD_LITTLE_ENDIAN	1234
#	define _HAIKU_BUILD_BIG_ENDIAN		0
#	define _HAIKU_BUILD_BYTE_ORDER		LITTLE_ENDIAN
#elif defined(__HAIKU_BUILD_HAIKU_BIG_ENDIAN)
#	define _HAIKU_BUILD_BIG_ENDIAN		4321
#	define _HAIKU_BUILD_LITTLE_ENDIAN	0
#	define _HAIKU_BUILD_BYTE_ORDER		BIG_ENDIAN
#endif

#define __HAIKU_BUILD_BIG_ENDIAN		BIG_ENDIAN
#define __HAIKU_BUILD_LITTLE_ENDIAN		LITTLE_ENDIAN
#define __HAIKU_BUILD_BYTE_ORDER		BYTE_ORDER

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	if defined(_HAIKU_BUILD_LITTLE_ENDIAN)
#		define LITTLE_ENDIAN		_HAIKU_BUILD_LITTLE_ENDIAN
#		define BIG_ENDIAN			_HAIKU_BUILD_BIG_ENDIAN
#		define BYTE_ORDER			_HAIKU_BUILD_BYTE_ORDER
#	elif defined(_HAIKU_BUILD_BIG_ENDIAN)
#		define BIG_ENDIAN			_HAIKU_BUILD_BIG_ENDIAN
#		define LITTLE_ENDIAN		_HAIKU_BUILD_LITTLE_ENDIAN
#		define BYTE_ORDER			_HAIKU_BUILD_BYTE_ORDER
#	endif

#	define __BIG_ENDIAN				__HAIKU_BUILD_BIG_ENDIAN
#	define __LITTLE_ENDIAN			__HAIKU_BUILD_LITTLE_ENDIAN
#	define __BYTE_ORDER				__HAIKU_BUILD_BYTE_ORDER

#	endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#endif	/* _ENDIAN_H_ */
