/*
 * Copyright 2001-2012 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _LIBC_LIMITS_H_
#define _LIBC_LIMITS_H_
	/* Note: The header guard is checked in gcc's limits.h. */

#include <config_target/target_types.h>

#define _HAIKU_BUILD_LONGLONG_MIN			_HAIKU_BUILD_FEATURE_LLONG_MIN
#define _HAIKU_BUILD_LONGLONG_MAX			_HAIKU_BUILD_FEATURE_LLONG_MAX
#define _HAIKU_BUILD_ULONGLONG_MAX			_HAIKU_BUILD_FEATURE_ULLONG_MAX

#define _HAIKU_BUILD_ULLONG_MAX				_HAIKU_BUILD_ULONGLONG_MAX
#define _HAIKU_BUILD_LLONG_MAX				_HAIKU_BUILD_LONGLONG_MAX
#define _HAIKU_BUILD_LLONG_MIN				_HAIKU_BUILD_LONGLONG_MIN

#define _HAIKU_BUILD_MB_LEN_MAX				16

#define _HAIKU_BUILD_OFF_MAX				_HAIKU_BUILD_LLONG_MAX
#define _HAIKU_BUILD_OFF_MIN				_HAIKU_BUILD_LLONG_MIN

#define _HAIKU_BUILD_ARG_MAX				(32768)
#define _HAIKU_BUILD_ATEXIT_MAX				(32)
#define _HAIKU_BUILD_CHILD_MAX				(1024)
#define _HAIKU_BUILD_IOV_MAX				(1024)
#define _HAIKU_BUILD_FILESIZEBITS			(64)
#define _HAIKU_BUILD_HOST_NAME_MAX			(255)
#define _HAIKU_BUILD_LINE_MAX				(2048)
#define _HAIKU_BUILD_LINK_MAX				(1)
#define _HAIKU_BUILD_LOGIN_NAME_MAX			(32)
#define _HAIKU_BUILD_MAX_CANON				(255)
#define _HAIKU_BUILD_MAX_INPUT				(255)
#define _HAIKU_BUILD_NAME_MAX				(256)
#define _HAIKU_BUILD_NGROUPS_MAX			(32)
#define _HAIKU_BUILD_OPEN_MAX				(128)
#define _HAIKU_BUILD_PAGE_SIZE				(4096)
#define _HAIKU_BUILD_PAGESIZE				(4096)
#define _HAIKU_BUILD_PATH_MAX				(1024)
#define _HAIKU_BUILD_PIPE_MAX				(512)
#define _HAIKU_BUILD_PTHREAD_KEYS_MAX		256
#define _HAIKU_BUILD_PTHREAD_STACK_MIN		4096
#define _HAIKU_BUILD_SSIZE_MAX				__HAIKU_BUILD_HAIKU_SADDR_MAX
#define _HAIKU_BUILD_TTY_NAME_MAX			(256)
#define _HAIKU_BUILD_TZNAME_MAX				(32)
#define _HAIKU_BUILD_SYMLINK_MAX			(1024)
#define _HAIKU_BUILD_SYMLOOP_MAX			(16)

#define _HAIKU_BUILD_POSIX_ARG_MAX			(32768)
#define _HAIKU_BUILD_POSIX_CHILD_MAX		(1024)
#define _HAIKU_BUILD_POSIX_HOST_NAME_MAX	(255)
#define _HAIKU_BUILD_POSIX_LINK_MAX			(1)
#define _HAIKU_BUILD_POSIX_LOGIN_NAME_MAX	(9)
#define _HAIKU_BUILD_POSIX_MAX_CANON		(255)
#define _HAIKU_BUILD_POSIX_MAX_INPUT		(255)
#define _HAIKU_BUILD_POSIX_NAME_MAX			(255)
#define _HAIKU_BUILD_POSIX_NGROUPS_MAX		(8)
#define _HAIKU_BUILD_POSIX_OPEN_MAX			(128)
#define _HAIKU_BUILD_POSIX_PATH_MAX			(1024)
#define _HAIKU_BUILD_POSIX_PIPE_BUF			(512)
#define _HAIKU_BUILD_POSIX_SSIZE_MAX		__HAIKU_BUILD_HAIKU_SADDR_MAX
#define _HAIKU_BUILD_POSIX_STREAM_MAX		(8)
#define _HAIKU_BUILD_POSIX_TTY_NAME_MAX		(256)
#define _HAIKU_BUILD_POSIX_TZNAME_MAX		(3)
#define _HAIKU_BUILD_POSIX_SEM_VALUE_MAX	_HAIKU_BUILD_INT_MAX
#define _HAIKU_BUILD_POSIX_SIGQUEUE_MAX		32
#define _HAIKU_BUILD_POSIX_RTSIG_MAX		8
#define _HAIKU_BUILD_POSIX_CLOCKRES_MIN		20000000
#define _HAIKU_BUILD_POSIX_TIMER_MAX		32
#define _HAIKU_BUILD_POSIX_DELAYTIMER_MAX	32

#define _HAIKU_BUILD_POSIX2_LINE_MAX		(2048)

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define LONGLONG_MIN						_HAIKU_BUILD_LONGLONG_MIN
#	define LONGLONG_MAX						_HAIKU_BUILD_LONGLONG_MAX
#	define ULONGLONG_MAX					_HAIKU_BUILD_ULONGLONG_MAX

#	define ULLONG_MAX						_HAIKU_BUILD_ULLONG_MAX
#	define LLONG_MAX						_HAIKU_BUILD_LLONG_MAX
#	define LLONG_MIN						_HAIKU_BUILD_LLONG_MIN

#	define MB_LEN_MAX						_HAIKU_BUILD_MB_LEN_MAX

#	define OFF_MAX							_HAIKU_BUILD_OFF_MAX
#	define OFF_MIN							_HAIKU_BUILD_OFF_MIN

#	define ARG_MAX							_HAIKU_BUILD_ARG_MAX
#	define ATEXIT_MAX						_HAIKU_BUILD_ATEXIT_MAX
#	define CHILD_MAX						_HAIKU_BUILD_CHILD_MAX
#	define IOV_MAX							_HAIKU_BUILD_IOV_MAX
#	define FILESIZEBITS						_HAIKU_BUILD_FILESIZEBITS
#	define HOST_NAME_MAX					_HAIKU_BUILD_HOST_NAME_MAX
#	define LINE_MAX							_HAIKU_BUILD_LINE_MAX
#	define LINK_MAX							_HAIKU_BUILD_LINK_MAX
#	define LOGIN_NAME_MAX					_HAIKU_BUILD_LOGIN_NAME_MAX
#	define MAX_CANON						_HAIKU_BUILD_MAX_CANON
#	define MAX_INPUT						_HAIKU_BUILD_MAX_INPUT
#	define NAME_MAX							_HAIKU_BUILD_NAME_MAX
#	define NGROUPS_MAX						_HAIKU_BUILD_NGROUPS_MAX
#	define OPEN_MAX							_HAIKU_BUILD_OPEN_MAX
#	define PAGE_SIZE						_HAIKU_BUILD_PAGE_SIZE
#	define PAGESIZE							_HAIKU_BUILD_PAGESIZE
#	define PATH_MAX							_HAIKU_BUILD_PATH_MAX
#	define PIPE_MAX							_HAIKU_BUILD_PIPE_MAX
#	define PTHREAD_KEYS_MAX					_HAIKU_BUILD_PTHREAD_KEYS_MAX
#	define PTHREAD_STACK_MIN				_HAIKU_BUILD_PTHREAD_STACK_MIN
#	define SSIZE_MAX						_HAIKU_BUILD_SSIZE_MAX
#	define TTY_NAME_MAX						_HAIKU_BUILD_TTY_NAME_MAX
#	define TZNAME_MAX						_HAIKU_BUILD_TZNAME_MAX
#	define SYMLINK_MAX						_HAIKU_BUILD_SYMLINK_MAX
#	define SYMLOOP_MAX						_HAIKU_BUILD_SYMLOOP_MAX

#	define _POSIX_ARG_MAX					_HAIKU_BUILD_POSIX_ARG_MAX
#	define _POSIX_CHILD_MAX					_HAIKU_BUILD_POSIX_CHILD_MAX
#	define _POSIX_HOST_NAME_MAX				_HAIKU_BUILD_POSIX_HOST_NAME_MAX
#	define _POSIX_LINK_MAX					_HAIKU_BUILD_POSIX_LINK_MAX
#	define _POSIX_LOGIN_NAME_MAX			_HAIKU_BUILD_POSIX_LOGIN_NAME_MAX
#	define _POSIX_MAX_CANON					_HAIKU_BUILD_POSIX_MAX_CANON
#	define _POSIX_MAX_INPUT					_HAIKU_BUILD_POSIX_MAX_INPUT
#	define _POSIX_NAME_MAX					_HAIKU_BUILD_POSIX_NAME_MAX
#	define _POSIX_NGROUPS_MAX				_HAIKU_BUILD_POSIX_NGROUPS_MAX
#	define _POSIX_OPEN_MAX					_HAIKU_BUILD_POSIX_OPEN_MAX
#	define _POSIX_PATH_MAX					_HAIKU_BUILD_POSIX_PATH_MAX
#	define _POSIX_PIPE_BUF					_HAIKU_BUILD_POSIX_PIPE_BUF
#	define _POSIX_SSIZE_MAX					_HAIKU_BUILD_POSIX_SSIZE_MAX
#	define _POSIX_STREAM_MAX				_HAIKU_BUILD_POSIX_STREAM_MAX
#	define _POSIX_TTY_NAME_MAX				_HAIKU_BUILD_POSIX_TTY_NAME_MAX
#	define _POSIX_TZNAME_MAX				_HAIKU_BUILD_POSIX_TZNAME_MAX
#	define _POSIX_SEM_VALUE_MAX				_HAIKU_BUILD_POSIX_SEM_VALUE_MAX
#	define _POSIX_SIGQUEUE_MAX				_HAIKU_BUILD_POSIX_SIGQUEUE_MAX
#	define _POSIX_RTSIG_MAX					_HAIKU_BUILD_POSIX_RTSIG_MAX
#	define _POSIX_CLOCKRES_MIN				_HAIKU_BUILD_POSIX_CLOCKRES_MIN
#	define _POSIX_TIMER_MAX					_HAIKU_BUILD_POSIX_TIMER_MAX
#	define _POSIX_DELAYTIMER_MAX			_HAIKU_BUILD_POSIX_DELAYTIMER_MAX

#	define _POSIX2_LINE_MAX					_HAIKU_BUILD_POSIX2_LINE_MAX
#endif

#endif /* _LIBC_LIMITS_H_ */
