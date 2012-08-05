/*
 * Copyright 2008-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _NULL_H
#define _NULL_H

#ifndef _HAIKU_BUILD_NULL
#	define _HAIKU_BUILD_NULL 0
#endif

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	ifdef _HAIKU_BUILD_NULL
#		define NULL _HAIKU_BUILD_NULL
#	endif
#endif

#endif
