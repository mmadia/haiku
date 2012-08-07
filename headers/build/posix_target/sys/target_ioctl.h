/*
 * Copyright 2006-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H


#include <target_termios.h>

/* These only work on sockets for now */
#define _HAIKU_BUILD_FIONBIO 	0xbe000000
#define _HAIKU_BUILD_FIONREAD	0xbe000001

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define FIONBIO 	_HAIKU_BUILD_FIONBIO
#	define FIONREAD	_HAIKU_BUILD_FIONREAD
#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#endif	/* _SYS_IOCTL_H */
