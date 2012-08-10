/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H


#include <config_target/target_types.h>

#include <sys/target_time.h>
#include <target_signal.h>


/* If _HAIKU_BUILD_FD_SET is already defined, only the select() prototype is
 * exported in this header.
 */
#ifndef _HAIKU_BUILD_FD_SET

/* You can define your own FDSETSIZE if you need more bits - but
 * it should be enough for most uses.
 */
#ifndef _HAIKU_BUILD_FD_SETSIZE
#	define _HAIKU_BUILD_FD_SETSIZE 1024
#endif

typedef __haiku_build_haiku_uint32 _haiku_build_fd_mask;

#ifndef __haiku_build_howmany
#	define __haiku_build_howmany(x, y) (((x) + ((y) - 1)) / (y))
#endif

#ifndef _haiku_build_howmany
#	define _haiku_build_howmany(x, y) (((x) + ((y) - 1)) / (y))
#endif

#define _HAIKU_BUILD_NFDBITS (sizeof(fd_mask) * 8)	/* bits per mask */

typedef struct _HAIKU_BUILD_IDENTIFIER(fd_set) {
	_HAIKU_BUILD_IDENTIFIER(fd_mask) bits[_howmany(FD_SETSIZE, NFDBITS)];
} _HAIKU_BUILD_IDENTIFIER(fd_set);

#define _HAIKU_BUILD_FD_BITSINDEX(fd) ((fd) / NFDBITS)
#define _HAIKU_BUILD_FD_BIT(fd) (1L << ((fd) % NFDBITS))

#define _HAIKU_BUILD_FD_ZERO(set) memset((set), 0, sizeof(fd_set))
#define _HAIKU_BUILD_FD_SET(fd, set) \
	((set)->bits[_FD_BITSINDEX(fd)] |= _FD_BIT(fd))
#define _HAIKU_BUILD_FD_CLR(fd, set) \
	((set)->bits[_FD_BITSINDEX(fd)] &= ~_FD_BIT(fd))
#define _HAIKU_BUILD_FD_ISSET(fd, set) \
	((set)->bits[_FD_BITSINDEX(fd)] & _FD_BIT(fd))
#define _HAIKU_BUILD_FD_COPY(source, target) (*(target) = *(source))

#endif	/* _HAIKU_BUILD_FD_SET */

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
	/* If FD_SET is already defined, only the select() prototype is
	 * exported in this header.
	 */
#	ifndef FD_SET

	/* You can define your own FDSETSIZE if you need more bits - but
	 * it should be enough for most uses.
	 */
#	ifdef _HAIKU_BUILD_FD_SETSIZE
#		define FD_SETSIZE			_HAIKU_BUILD_FD_SETSIZE
#	endif

	typedef _haiku_build_fd_mask 	fd_mask;

#	ifdef __haiku_build_howmany
#		define _howmany(x, y)		__haiku_build_howmany(x, y)
#	endif

#	ifdef _haiku_build_howmany
#		define howmany(x, y)		_haiku_build_howmany(x, y)
#	endif

#	define NFDBITS					_HAIKU_BUILD_NFDBITS	/* bits per mask */

#	define _FD_BITSINDEX(fd)		_HAIKU_BUILD_FD_BITSINDEX(fd)
#	define _FD_BIT(fd)				_HAIKU_BUILD_FD_BIT(fd)

#	define FD_ZERO(set) 			_HAIKU_BUILD_FD_ZERO(set)
#	define FD_SET(fd, set)			_HAIKU_BUILD_FD_SET(fd, set)
#	define FD_CLR(fd, set)			_HAIKU_BUILD_FD_CLR(fd, set)
#	define FD_ISSET(fd, set)		_HAIKU_BUILD_FD_ISSET(fd, set)
#	define FD_COPY(source, target)	_HAIKU_BUILD_FD_COPY(source, target)

#	endif	/* FD_SET */

#endif	/* _SYS_SELECT_H */


#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(int, pselect, (int numBits,
	struct _HAIKU_BUILD_IDENTIFIER(fd_set) *readBits,
		struct _HAIKU_BUILD_IDENTIFIER(fd_set) *writeBits,
			struct _HAIKU_BUILD_IDENTIFIER(fd_set) *errorBits,
				const struct _HAIKU_BUILD_IDENTIFIER(timespec) *timeout,
					const _haiku_build_sigset_t *sigMask))
_HAIKU_BUILD_DECLARE_FUNCTION(int, select, (int numBits,
	struct _HAIKU_BUILD_IDENTIFIER(fd_set) *readBits,
		struct _HAIKU_BUILD_IDENTIFIER(fd_set) *writeBits,
			struct _HAIKU_BUILD_IDENTIFIER(fd_set) *errorBits,
				struct _HAIKU_BUILD_IDENTIFIER(timeval) *timeout))

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_SELECT_H */
