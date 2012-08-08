/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _FCNTL_H
#define _FCNTL_H


#include <sys/target_types.h>
#include <sys/target_stat.h>
#include <target_unistd.h>


/* commands that can be passed to fcntl() */
#define _HAIKU_BUILD_F_DUPFD			0x0001		/* duplicate fd */
#define _HAIKU_BUILD_F_GETFD			0x0002		/* get fd flags */
#define _HAIKU_BUILD_F_SETFD			0x0004		/* set fd flags */
#define _HAIKU_BUILD_F_GETFL			0x0008		/* get file status flags and access mode */
#define _HAIKU_BUILD_F_SETFL			0x0010		/* set file status flags */
#define _HAIKU_BUILD_F_GETLK         0x0020		/* get locking information */
#define _HAIKU_BUILD_F_SETLK         0x0080		/* set locking information */
#define _HAIKU_BUILD_F_SETLKW        0x0100		/* as above, but waits if blocked */

/* advisory locking types */
#define _HAIKU_BUILD_F_RDLCK         0x0040		/* read or shared lock */
#define _HAIKU_BUILD_F_UNLCK         0x0200		/* unlock */
#define _HAIKU_BUILD_F_WRLCK         0x0400		/* write or exclusive lock */

/* file descriptor flags for fcntl() */
#define _HAIKU_BUILD_FD_CLOEXEC		1			/* close on exec */

/* file access modes for open() */
#define _HAIKU_BUILD_O_RDONLY		0x0000		/* read only */
#define _HAIKU_BUILD_O_WRONLY		0x0001		/* write only */
#define _HAIKU_BUILD_O_RDWR			0x0002		/* read and write */
#define _HAIKU_BUILD_O_ACCMODE   	0x0003		/* mask to get the access modes above */
#define _HAIKU_BUILD_O_RWMASK		O_ACCMODE

/* flags for open() */
#define _HAIKU_BUILD_O_EXCL			0x0100		/* exclusive creat */
#define _HAIKU_BUILD_O_CREAT			0x0200		/* create and open file */
#define _HAIKU_BUILD_O_TRUNC			0x0400		/* open with truncation */
#define _HAIKU_BUILD_O_NOCTTY		0x1000		/* don't make tty the controlling tty */
#define _HAIKU_BUILD_O_NOTRAVERSE	0x2000		/* do not traverse leaf link */

/* flags for open() and fcntl() */
#define _HAIKU_BUILD_O_CLOEXEC		0x00000040	/* close on exec */
#define _HAIKU_BUILD_O_NONBLOCK		0x00000080	/* non blocking io */
#define _HAIKU_BUILD_O_NDELAY		O_NONBLOCK
#define _HAIKU_BUILD_O_APPEND		0x00000800	/* to end of file */
#define _HAIKU_BUILD_O_SYNC			0x00010000	/* write synchronized I/O file integrity */
#define _HAIKU_BUILD_O_RSYNC			0x00020000	/* read synchronized I/O file integrity */
#define _HAIKU_BUILD_O_DSYNC			0x00040000	/* write synchronized I/O data integrity */
#define _HAIKU_BUILD_O_NOFOLLOW		0x00080000	/* fail on symlinks */
#define _HAIKU_BUILD_O_NOCACHE		0x00100000	/* do not use the file system cache if */
									/* possible */
#define _HAIKU_BUILD_O_DIRECT		O_NOCACHE
#define _HAIKU_BUILD_O_DIRECTORY		0x00200000	/* fail if not a directory */

/* flags for the *at() functions */
#define _HAIKU_BUILD_AT_FDCWD		(-1)		/* CWD FD for the *at() functions */

#define _HAIKU_BUILD_AT_SYMLINK_NOFOLLOW	0x01	/* fstatat(), fchmodat(), fchownat(),
										utimensat() */
#define _HAIKU_BUILD_AT_SYMLINK_FOLLOW	0x02	/* linkat() */
#define _HAIKU_BUILD_AT_REMOVEDIR		0x04	/* unlinkat() */
#define _HAIKU_BUILD_AT_EACCESS			0x08	/* faccessat() */

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
/* commands that can be passed to fcntl() */
#	define	F_DUPFD			_HAIKU_BUILD_F_DUPFD		/* duplicate fd */
#	define	F_GETFD			_HAIKU_BUILD_F_GETFD		/* get fd flags */
#	define	F_SETFD			_HAIKU_BUILD_F_SETFD		/* set fd flags */
#	define	F_GETFL			_HAIKU_BUILD_F_GETFL		/* get file status flags and access mode */
#	define	F_SETFL			_HAIKU_BUILD_F_SETFL		/* set file status flags */
#	define F_GETLK         _HAIKU_BUILD_F_GETLK		/* get locking information */
#	define F_SETLK         _HAIKU_BUILD_F_SETLK		/* set locking information */
#	define F_SETLKW        _HAIKU_BUILD_F_SETLKW		/* as above, but waits if blocked */

/* advisory locking types */
#	define F_RDLCK         _HAIKU_BUILD_F_RDLCK		/* read or shared lock */
#	define F_UNLCK         _HAIKU_BUILD_F_UNLCK		/* unlock */
#	define F_WRLCK         _HAIKU_BUILD_F_WRLCK		/* write or exclusive lock */

/* file descriptor flags for fcntl() */
#	define FD_CLOEXEC		_HAIKU_BUILD_FD_CLOEXEC			/* close on exec */

/* file access modes for open() */
#	define O_RDONLY		_HAIKU_BUILD_O_RDONLY		/* read only */
#	define O_WRONLY		_HAIKU_BUILD_O_WRONLY		/* write only */
#	define O_RDWR			_HAIKU_BUILD_O_RDWR		/* read and write */
#	define O_ACCMODE   	_HAIKU_BUILD_O_ACCMODE		/* mask to get the access modes above */
#	define O_RWMASK		_HAIKU_BUILD_O_RWMASK

/* flags for open() */
#	define	O_EXCL			_HAIKU_BUILD_O_EXCL		/* exclusive creat */
#	define O_CREAT			_HAIKU_BUILD_O_CREAT		/* create and open file */
#	define O_TRUNC			_HAIKU_BUILD_O_TRUNC		/* open with truncation */
#	define O_NOCTTY		_HAIKU_BUILD_O_NOCTTY		/* don't make tty the controlling tty */
#	define	O_NOTRAVERSE	_HAIKU_BUILD_O_NOTRAVERSE		/* do not traverse leaf link */

/* flags for open() and fcntl() */
#	define O_CLOEXEC		_HAIKU_BUILD_O_CLOEXEC	/* close on exec */
#	define	O_NONBLOCK		_HAIKU_BUILD_O_NONBLOCK	/* non blocking io */
#	define	O_NDELAY		_HAIKU_BUILD_O_NDELAY
#	define O_APPEND		_HAIKU_BUILD_O_APPEND	/* to end of file */
#	define O_SYNC			_HAIKU_BUILD_O_SYNC	/* write synchronized I/O file integrity */
#	define O_RSYNC			_HAIKU_BUILD_O_RSYNC	/* read synchronized I/O file integrity */
#	define O_DSYNC			_HAIKU_BUILD_O_DSYNC	/* write synchronized I/O data integrity */
#	define O_NOFOLLOW		_HAIKU_BUILD_O_NOFOLLOW	/* fail on symlinks */
#	define O_NOCACHE		_HAIKU_BUILD_O_NOCACHE	/* do not use the file system cache if */
									/* possible */
#	define O_DIRECT		_HAIKU_BUILD_O_DIRECT
#	define O_DIRECTORY		_HAIKU_BUILD_O_DIRECTORY	/* fail if not a directory */

/* flags for the *at() functions */
#	define AT_FDCWD		_HAIKU_BUILD_AT_FDCWD		/* CWD FD for the *at() functions */

#	define AT_SYMLINK_NOFOLLOW	_HAIKU_BUILD_AT_SYMLINK_NOFOLLOW	/* fstatat(), fchmodat(), fchownat(),
										utimensat() */
#	define AT_SYMLINK_FOLLOW	_HAIKU_BUILD_AT_SYMLINK_FOLLOW	/* linkat() */
#	define AT_REMOVEDIR		_HAIKU_BUILD_AT_REMOVEDIR	/* unlinkat() */
#	define AT_EACCESS			_HAIKU_BUILD_AT_EACCESS	/* faccessat() */

#endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

/* advisory file locking */

struct _HAIKU_BUILD_IDENTIFIER(flock) {
	short	l_type;
	short	l_whence;
	_HAIKU_BUILD_IDENTIFIER(off_t)	l_start;
	_HAIKU_BUILD_IDENTIFIER(off_t)	l_len;
	_HAIKU_BUILD_IDENTIFIER(pid_t)	l_pid;
};


#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(int, creat, (const char *path,
	_haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, open, (const char *path, int openMode, ...))
	/* the third argument is the permissions of the created file when O_CREAT
	   is passed in oflags */
_HAIKU_BUILD_DECLARE_FUNCTION(int, openat, (int fd, const char *path,
	int openMode, ...))

_HAIKU_BUILD_DECLARE_FUNCTION(int, fcntl, (int fd, int op, ...))

#ifdef __cplusplus
}
#endif

#endif	/* _FCNTL_H */
