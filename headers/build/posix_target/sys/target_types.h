/*
 * Copyright 2002-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <config_target/target_types.h>

#include <target_BeBuild.h>


/* BSD compatibility */
typedef unsigned long 					_haiku_build_u_long;
typedef unsigned int 					_haiku_build_u_int;
typedef unsigned short 					_haiku_build_u_short;
typedef unsigned char 					_haiku_build_u_char;


/* sysV compatibility */
typedef unsigned long 					_haiku_build_ulong;
typedef unsigned short 					_haiku_build_ushort;
typedef unsigned int 					_haiku_build_uint;
typedef unsigned char					_haiku_build_unchar;


typedef __haiku_build_haiku_int64 		_haiku_build_blkcnt_t;
typedef __haiku_build_haiku_std_int32	_haiku_build_blksize_t;
typedef __haiku_build_haiku_int64		_haiku_build_fsblkcnt_t;
typedef __haiku_build_haiku_int64		_haiku_build_fsfilcnt_t;
typedef __haiku_build_haiku_int64		_haiku_build_off_t;
typedef __haiku_build_haiku_int64		_haiku_build_ino_t;
typedef __haiku_build_haiku_std_int32	_haiku_build_cnt_t;
typedef __haiku_build_haiku_int32		_haiku_build_dev_t;
typedef __haiku_build_haiku_int32		_haiku_build_pid_t;
typedef __haiku_build_haiku_int32		_haiku_build_id_t;

typedef __haiku_build_haiku_std_uint32	_haiku_build_uid_t;
typedef __haiku_build_haiku_std_uint32	_haiku_build_gid_t;
typedef __haiku_build_haiku_std_uint32	_haiku_build_mode_t;
typedef __haiku_build_haiku_std_uint32	_haiku_build_umode_t;
typedef __haiku_build_haiku_std_int32	_haiku_build_nlink_t;

#ifdef __HAIKU_BEOS_COMPATIBLE_TYPES
	typedef int						_haiku_build_daddr_t;	/* disk address */
#else
	typedef _haiku_build_off_t		_haiku_build_daddr_t;	/* disk address */
#endif
typedef char*							_haiku_build_caddr_t;

typedef __haiku_build_haiku_addr_t		_haiku_build_addr_t;
typedef __haiku_build_haiku_int32 		_haiku_build_key_t;

typedef __haiku_build_haiku_std_int32	_haiku_build_clockid_t;
typedef struct _HAIKU_BUILD_IDENTIFIER(__timer_t)*	\
	_HAIKU_BUILD_IDENTIFIER(timer_t);


/* pthread types */
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_thread)		\
	*_HAIKU_BUILD_IDENTIFIER(pthread_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_attr)			\
	*_HAIKU_BUILD_IDENTIFIER(pthread_attr_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_mutex)			\
	_HAIKU_BUILD_IDENTIFIER(pthread_mutex_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_mutexattr)		\
	*_HAIKU_BUILD_IDENTIFIER(pthread_mutexattr_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_cond)			\
	_HAIKU_BUILD_IDENTIFIER(pthread_cond_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_condattr)		\
	*_HAIKU_BUILD_IDENTIFIER(pthread_condattr_t);
typedef int														\
	_HAIKU_BUILD_IDENTIFIER(pthread_key_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_once)			\
	_HAIKU_BUILD_IDENTIFIER(pthread_once_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_rwlock)		\
	_HAIKU_BUILD_IDENTIFIER(pthread_rwlock_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_rwlockattr)	\
	*_HAIKU_BUILD_IDENTIFIER(pthread_rwlockattr_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_spinlock)		\
	_HAIKU_BUILD_IDENTIFIER(pthread_spinlock_t);
/*
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_barrier)		\
	*_HAIKU_BUILD_IDENTIFIER(pthread_barrier_t);
typedef struct	_HAIKU_BUILD_IDENTIFIER(_pthread_barrierattr) 	\
	*_HAIKU_BUILD_IDENTIFIER(pthread_barrierattr_t);
*/

struct _HAIKU_BUILD_IDENTIFIER(_pthread_mutex) {
	__haiku_build_haiku_std_uint32				flags;
	__haiku_build_haiku_std_int32				lock;
	__haiku_build_haiku_std_int32				unused;
	__haiku_build_haiku_std_int32				owner;
	__haiku_build_haiku_std_int32				owner_count;
};

struct _HAIKU_BUILD_IDENTIFIER(_pthread_cond) {
	__haiku_build_haiku_std_uint32				flags;
	__haiku_build_haiku_std_int32				unused;
	_HAIKU_BUILD_IDENTIFIER(pthread_mutex_t)*	mutex;
	__haiku_build_haiku_std_int32				waiter_count;
	__haiku_build_haiku_std_int32				lock;
};

struct _HAIKU_BUILD_IDENTIFIER(_pthread_once) {
	__haiku_build_haiku_std_int32				state;
};

struct _HAIKU_BUILD_IDENTIFIER(_pthread_rwlock) {
	__haiku_build_haiku_std_uint32				flags;
	__haiku_build_haiku_std_int32				owner;
	union {
		struct {
			__haiku_build_haiku_std_int32		sem;
		} _HAIKU_BUILD_IDENTIFIER(shared);
		struct {
			__haiku_build_haiku_std_int32		lock_sem;
			__haiku_build_haiku_std_int32		lock_count;
			__haiku_build_haiku_std_int32		reader_count;
			__haiku_build_haiku_std_int32		writer_count;
			void*								waiters[2];
		} _HAIKU_BUILD_IDENTIFIER(local);
	} _HAIKU_BUILD_IDENTIFIER(u);
};

struct _HAIKU_BUILD_IDENTIFIER(_pthread_spinlock) {
	__haiku_build_haiku_std_int32				lock;
};

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
	/* BSD compatibility */
	typedef _haiku_build_u_long 		u_long;
	typedef _haiku_build_u_int 		u_int;
	typedef _haiku_build_u_short 		u_short;
	typedef _haiku_build_u_char 		u_char;


	/* sysV compatibility */
	typedef _haiku_build_ulong 		ulong;
	typedef _haiku_build_ushort 		ushort;
	typedef _haiku_build_uint 			uint;
	typedef _haiku_build_unchar		unchar;


	typedef _haiku_build_blkcnt_t 		blkcnt_t;
	typedef _haiku_build_blksize_t		blksize_t;
	typedef _haiku_build_fsblkcnt_t		fsblkcnt_t;
	typedef _haiku_build_fsfilcnt_t		fsfilcnt_t;
	typedef _haiku_build_off_t			off_t;
	typedef _haiku_build_ino_t			ino_t;
	typedef _haiku_build_cnt_t			cnt_t;
	typedef _haiku_build_dev_t			dev_t;
	typedef _haiku_build_pid_t			pid_t;
	typedef _haiku_build_id_t			id_t;

	typedef _haiku_build_uid_t			uid_t;
	typedef _haiku_build_gid_t			gid_t;
	typedef _haiku_build_mode_t 		mode_t;
	typedef _haiku_build_umode_t		umode_t;
	typedef _haiku_build_nlink_t		nlink_t;

#	ifdef __HAIKU_BEOS_COMPATIBLE_TYPES
		typedef _haiku_build_daddr_t	daddr_t;	/* disk address */
#	else
		typedef _haiku_build_daddr_t	daddr_t;	/* disk address */
#	endif
	typedef _haiku_build_caddr_t*		caddr_t;

	typedef _haiku_build_addr_t		addr_t;
	typedef _haiku_build_key_t 		key_t;

	typedef _haiku_build_clockid_t	clockid_t;

#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#include <target_null.h>
#include <target_size_t.h>
#include <target_time.h>

#endif
