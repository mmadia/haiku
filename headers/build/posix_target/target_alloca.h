/*
 * Copyright 2003-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef	_ALLOCA_H
#define	_ALLOCA_H


#include <sys/target_types.h>


#undef	__alloca
#undef	alloca

#ifdef __cplusplus
extern "C" {
#endif

// NOTE: #8730 -- uncertain if these functions need to have the same names as
//		the macro definitions.
_HAIKU_BUILD_DECLARE_FUNCTION(void*, __alloca, (size_t __size))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, alloca, (size_t __size))

#ifdef __cplusplus
}
#endif

#define	_haiku_build___alloca(size)	__builtin_alloca (size)
#define _haiku_build_alloca(size)	_haiku_build___alloca (size)

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define __alloca(size)			_haiku_build___alloca (size)
#	define alloca(size)				_haiku_build_alloca (size)
#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#endif	/* _ALLOCA_H */
