/*
 * Copyright 2004-2011 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _UNISTD_H_
#define _UNISTD_H_


#include <target_null.h>
#include <sys/target_types.h>


/* access modes */
#define _HAIKU_BUILD_R_OK			4
#define _HAIKU_BUILD_W_OK			2
#define _HAIKU_BUILD_X_OK			1
#define _HAIKU_BUILD_F_OK			0

/* standard file descriptors */
#define _HAIKU_BUILD_STDIN_FILENO	0
#define _HAIKU_BUILD_STDOUT_FILENO	1
#define _HAIKU_BUILD_STDERR_FILENO	2

/* function arguments needed by lockf() */
#define _HAIKU_BUILD_F_ULOCK	0	/* unlock locked sections */
#define _HAIKU_BUILD_F_LOCK		1	/* lock a section for exclusive use */
#define _HAIKU_BUILD_F_TLOCK	2	/* test and lock a section for exclusive use */
#define _HAIKU_BUILD_F_TEST		3	/* test a section for locks by other processes */

/* POSIX version support */
#define _HAIKU_BUILD_POSIX_VERSION			(199009L)	/* TODO: Update! */

#define _HAIKU_BUILD_POSIX_CHOWN_RESTRICTED				1
#define _HAIKU_BUILD_POSIX_JOB_CONTROL					1
#define _HAIKU_BUILD_POSIX_NO_TRUNC						0
#define _HAIKU_BUILD_POSIX_SAVED_IDS					1
#define _HAIKU_BUILD_POSIX_VDISABLE						((unsigned char)-2)
	/* TODO: Check this! */
/* TODO: Update these to the current POSIX version! Ideally after actually
	supporting the features. */
#define _HAIKU_BUILD_POSIX_SEMAPHORES					(200112L)
#define _HAIKU_BUILD_POSIX_THREADS						(200112L)
#define _HAIKU_BUILD_POSIX_MAPPED_FILES					(200809L)
#define _HAIKU_BUILD_POSIX_THREAD_PROCESS_SHARED		(200809L)
#define _HAIKU_BUILD_POSIX_THREAD_ATTR_STACKADDR		(-1)	/* currently unsupported */
#define _HAIKU_BUILD_POSIX_THREAD_ATTR_STACKSIZE		(200809L)
#define _HAIKU_BUILD_POSIX_THREAD_PRIORITY_SCHEDULING	(-1)	/* currently unsupported */
#define _HAIKU_BUILD_POSIX_REALTIME_SIGNALS				(200809L)
#define _HAIKU_BUILD_POSIX_MEMORY_PROTECTION			(200809L)
#define _HAIKU_BUILD_POSIX_MONOTONIC_CLOCK				(200809L)
#define _HAIKU_BUILD_POSIX_TIMERS						(200809L)
#define _HAIKU_BUILD_POSIX_CPUTIME						(200809L)
#define _HAIKU_BUILD_POSIX_THREAD_CPUTIME				(200809L)


/* pathconf() constants */
/* BeOS supported values, do not touch */
#define _HAIKU_BUILD_PC_CHOWN_RESTRICTED			1
#define _HAIKU_BUILD_PC_MAX_CANON					2
#define _HAIKU_BUILD_PC_MAX_INPUT					3
#define _HAIKU_BUILD_PC_NAME_MAX					4
#define _HAIKU_BUILD_PC_NO_TRUNC					5
#define _HAIKU_BUILD_PC_PATH_MAX					6
#define _HAIKU_BUILD_PC_PIPE_BUF					7
#define _HAIKU_BUILD_PC_VDISABLE					8
#define _HAIKU_BUILD_PC_LINK_MAX					25
/* new values */
#define _HAIKU_BUILD_PC_SYNC_IO						26
#define _HAIKU_BUILD_PC_ASYNC_IO					27
#define _HAIKU_BUILD_PC_PRIO_IO						28
#define _HAIKU_BUILD_PC_SOCK_MAXBUF					29
#define _HAIKU_BUILD_PC_FILESIZEBITS				30
#define _HAIKU_BUILD_PC_REC_INCR_XFER_SIZE			31
#define _HAIKU_BUILD_PC_REC_MAX_XFER_SIZE			32
#define _HAIKU_BUILD_PC_REC_MIN_XFER_SIZE			33
#define _HAIKU_BUILD_PC_REC_XFER_ALIGN				34
#define _HAIKU_BUILD_PC_ALLOC_SIZE_MIN				35
#define _HAIKU_BUILD_PC_SYMLINK_MAX					36
#define _HAIKU_BUILD_PC_2_SYMLINKS					37
#define _HAIKU_BUILD_PC_XATTR_EXISTS				38
#define _HAIKU_BUILD_PC_XATTR_ENABLED				39

/* sysconf() constants */
/* BeOS supported values, do not touch */
#define _HAIKU_BUILD_SC_ARG_MAX						15
#define _HAIKU_BUILD_SC_CHILD_MAX					16
#define _HAIKU_BUILD_SC_CLK_TCK						17
#define _HAIKU_BUILD_SC_JOB_CONTROL					18
#define _HAIKU_BUILD_SC_NGROUPS_MAX					19
#define _HAIKU_BUILD_SC_OPEN_MAX					20
#define _HAIKU_BUILD_SC_SAVED_IDS					21
#define _HAIKU_BUILD_SC_STREAM_MAX					22
#define _HAIKU_BUILD_SC_TZNAME_MAX					23
#define _HAIKU_BUILD_SC_VERSION						24
/* new values */
#define _HAIKU_BUILD_SC_GETGR_R_SIZE_MAX			25
#define _HAIKU_BUILD_SC_GETPW_R_SIZE_MAX			26
#define _HAIKU_BUILD_SC_PAGE_SIZE					27
#define _HAIKU_BUILD_SC_PAGESIZE					_SC_PAGE_SIZE
#define _HAIKU_BUILD_SC_SEM_NSEMS_MAX				28
#define _HAIKU_BUILD_SC_SEM_VALUE_MAX				29
#define _HAIKU_BUILD_SC_SEMAPHORES					30
#define _HAIKU_BUILD_SC_THREADS						31
/* TODO: check */
#define _HAIKU_BUILD_SC_IOV_MAX						32
#define _HAIKU_BUILD_SC_UIO_MAXIOV					_SC_IOV_MAX
#define _HAIKU_BUILD_SC_NPROCESSORS_MAX				33
#define _HAIKU_BUILD_SC_NPROCESSORS_CONF			34
#define _HAIKU_BUILD_SC_NPROCESSORS_ONLN			35
#define _HAIKU_BUILD_SC_CPUID_MAX					36
#define _HAIKU_BUILD_SC_ATEXIT_MAX					37
#define _HAIKU_BUILD_SC_PASS_MAX					39
#define _HAIKU_BUILD_SC_PHYS_PAGES					40
#define _HAIKU_BUILD_SC_AVPHYS_PAGES				41
#define _HAIKU_BUILD_SC_PIPE						42
#define _HAIKU_BUILD_SC_SELECT						43
#define _HAIKU_BUILD_SC_POLL						44
#define _HAIKU_BUILD_SC_MAPPED_FILES				45
#define _HAIKU_BUILD_SC_THREAD_PROCESS_SHARED		46
#define _HAIKU_BUILD_SC_THREAD_STACK_MIN			47
#define _HAIKU_BUILD_SC_THREAD_ATTR_STACKADDR		48
#define _HAIKU_BUILD_SC_THREAD_ATTR_STACKSIZE		49
#define _HAIKU_BUILD_SC_THREAD_PRIORITY_SCHEDULING	50
#define _HAIKU_BUILD_SC_REALTIME_SIGNALS			51
#define _HAIKU_BUILD__MEMORY_PROTECTION				52
#define _HAIKU_BUILD_SC_SIGQUEUE_MAX				53
#define _HAIKU_BUILD_SC_RTSIG_MAX					54
#define _HAIKU_BUILD_SC_MONOTONIC_CLOCK				55
#define _HAIKU_BUILD_SC_DELAYTIMER_MAX				56
#define _HAIKU_BUILD_SC_TIMER_MAX					57
#define _HAIKU_BUILD__TIMERS						58
#define _HAIKU_BUILD__CPUTIME						59
#define _HAIKU_BUILD__THREAD_CPUTIME				60


/* confstr() constants */
#define _HAIKU_BUILD_CS_PATH						1

/* lseek() constants */
#ifndef _HAIKU_BUILD_SEEK_SET
#	define _HAIKU_BUILD_SEEK_SET					0
#endif
#ifndef _HAIKU_BUILD_SEEK_CUR
#	define _HAIKU_BUILD_SEEK_CUR					1
#endif
#ifndef _HAIKU_BUILD_SEEK_END
#	define _HAIKU_BUILD_SEEK_END					2
#endif

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
/* access modes */
#	define R_OK	_HAIKU_BUILD_R_OK
#	define W_OK	_HAIKU_BUILD_W_OK
#	define X_OK	_HAIKU_BUILD_X_OK
#	define F_OK	_HAIKU_BUILD_F_OK

/* standard file descriptors */
#	define STDIN_FILENO	_HAIKU_BUILD_STDIN_FILENO
#	define STDOUT_FILENO	_HAIKU_BUILD_STDOUT_FILENO
#	define STDERR_FILENO	_HAIKU_BUILD_STDERR_FILENO

/* function arguments needed by lockf() */
#	define F_ULOCK		_HAIKU_BUILD_F_ULOCK	/* unlock locked sections */
#	define F_LOCK		_HAIKU_BUILD_F_LOCK	/* lock a section for exclusive use */
#	define F_TLOCK		_HAIKU_BUILD_F_TLOCK	/* test and lock a section for exclusive use */
#	define F_TEST		_HAIKU_BUILD_F_TEST	/* test a section for locks by other processes */

/* POSIX version support */
#	define _POSIX_VERSION			_HAIKU_BUILD_POSIX_VERSION	/* TODO: Update! */

#	define _POSIX_CHOWN_RESTRICTED	_HAIKU_BUILD_POSIX_CHOWN_RESTRICTED
#	define _POSIX_JOB_CONTROL		_HAIKU_BUILD_POSIX_JOB_CONTROL
#	define _POSIX_NO_TRUNC			_HAIKU_BUILD_POSIX_NO_TRUNC
#	define _POSIX_SAVED_IDS			_HAIKU_BUILD_POSIX_SAVED_IDS
#	define _POSIX_VDISABLE			_HAIKU_BUILD_POSIX_VDISABLE
	/* TODO: Check this! */
/* TODO: Update these to the current POSIX version! Ideally after actually
	supporting the features. */
#	define _POSIX_SEMAPHORES					_HAIKU_BUILD_POSIX_SEMAPHORES
#	define _POSIX_THREADS						_HAIKU_BUILD_POSIX_THREADS
#	define _POSIX_MAPPED_FILES					_HAIKU_BUILD_POSIX_MAPPED_FILES
#	define _POSIX_THREAD_PROCESS_SHARED			_HAIKU_BUILD_POSIX_THREAD_PROCESS_SHARED
#	define _POSIX_THREAD_ATTR_STACKADDR			_HAIKU_BUILD_POSIX_THREAD_ATTR_STACKADDR	/* currently unsupported */
#	define _POSIX_THREAD_ATTR_STACKSIZE			_HAIKU_BUILD_POSIX_THREAD_ATTR_STACKSIZE
#	define _POSIX_THREAD_PRIORITY_SCHEDULING	_HAIKU_BUILD_POSIX_THREAD_PRIORITY_SCHEDULING	/* currently unsupported */
#	define _POSIX_REALTIME_SIGNALS				_HAIKU_BUILD_POSIX_REALTIME_SIGNALS
#	define _POSIX_MEMORY_PROTECTION				_HAIKU_BUILD_POSIX_MEMORY_PROTECTION
#	define _POSIX_MONOTONIC_CLOCK				_HAIKU_BUILD_POSIX_MONOTONIC_CLOCK
#	define _POSIX_TIMERS						_HAIKU_BUILD_POSIX_TIMERS
#	define _POSIX_CPUTIME						_HAIKU_BUILD_POSIX_CPUTIME
#	define _POSIX_THREAD_CPUTIME				_HAIKU_BUILD_POSIX_THREAD_CPUTIME


/* pathconf() constants */
/* BeOS supported values, do not touch */
#	define _PC_CHOWN_RESTRICTED		_HAIKU_BUILD_PC_CHOWN_RESTRICTED
#	define _PC_MAX_CANON			_HAIKU_BUILD_PC_MAX_CANON
#	define _PC_MAX_INPUT			_HAIKU_BUILD_PC_MAX_INPUT
#	define _PC_NAME_MAX				_HAIKU_BUILD_PC_NAME_MAX
#	define _PC_NO_TRUNC				_HAIKU_BUILD_PC_NO_TRUNC
#	define _PC_PATH_MAX				_HAIKU_BUILD_PC_PATH_MAX
#	define _PC_PIPE_BUF				_HAIKU_BUILD_PC_PIPE_BUF
#	define _PC_VDISABLE				_HAIKU_BUILD_PC_VDISABLE
#	define _PC_LINK_MAX				_HAIKU_BUILD_PC_LINK_MAX
/* new values */
#	define _PC_SYNC_IO				_HAIKU_BUILD_PC_SYNC_IO
#	define _PC_ASYNC_IO				_HAIKU_BUILD_PC_ASYNC_IO
#	define _PC_PRIO_IO				_HAIKU_BUILD_PC_PRIO_IO
#	define _PC_SOCK_MAXBUF			_HAIKU_BUILD_PC_SOCK_MAXBUF
#	define _PC_FILESIZEBITS			_HAIKU_BUILD_PC_FILESIZEBITS
#	define _PC_REC_INCR_XFER_SIZE	_HAIKU_BUILD_PC_REC_INCR_XFER_SIZE
#	define _PC_REC_MAX_XFER_SIZE	_HAIKU_BUILD_PC_REC_MAX_XFER_SIZE
#	define _PC_REC_MIN_XFER_SIZE	_HAIKU_BUILD_PC_REC_MIN_XFER_SIZE
#	define _PC_REC_XFER_ALIGN		_HAIKU_BUILD_PC_REC_XFER_ALIGN
#	define _PC_ALLOC_SIZE_MIN		_HAIKU_BUILD_PC_ALLOC_SIZE_MIN
#	define _PC_SYMLINK_MAX			_HAIKU_BUILD_PC_SYMLINK_MAX
#	define _PC_2_SYMLINKS			_HAIKU_BUILD_PC_2_SYMLINKS
#	define _PC_XATTR_EXISTS			_HAIKU_BUILD_PC_XATTR_EXISTS
#	define _PC_XATTR_ENABLED		_HAIKU_BUILD_PC_XATTR_ENABLED

/* sysconf() constants */
/* BeOS supported values, do not touch */
#	define _SC_ARG_MAX				_HAIKU_BUILD_SC_ARG_MAX
#	define _SC_CHILD_MAX			_HAIKU_BUILD_SC_CHILD_MAX
#	define _SC_CLK_TCK				_HAIKU_BUILD_SC_CLK_TCK
#	define _SC_JOB_CONTROL			_HAIKU_BUILD_SC_JOB_CONTROL
#	define _SC_NGROUPS_MAX			_HAIKU_BUILD_SC_NGROUPS_MAX
#	define _SC_OPEN_MAX				_HAIKU_BUILD_SC_OPEN_MAX
#	define _SC_SAVED_IDS			_HAIKU_BUILD_SC_SAVED_IDS
#	define _SC_STREAM_MAX			_HAIKU_BUILD_SC_STREAM_MAX
#	define _SC_TZNAME_MAX			_HAIKU_BUILD_SC_TZNAME_MAX
#	define _SC_VERSION				_HAIKU_BUILD_SC_VERSION
/* new values */
#	define _SC_GETGR_R_SIZE_MAX		_HAIKU_BUILD_SC_GETGR_R_SIZE_MAX
#	define _SC_GETPW_R_SIZE_MAX		_HAIKU_BUILD_SC_GETPW_R_SIZE_MAX
#	define _SC_PAGE_SIZE			_HAIKU_BUILD_SC_PAGE_SIZE
#	define _SC_PAGESIZE				_HAIKU_BUILD_SC_PAGESIZE
#	define _SC_SEM_NSEMS_MAX		_HAIKU_BUILD_SC_SEM_NSEMS_MAX
#	define _SC_SEM_VALUE_MAX		_HAIKU_BUILD_SC_SEM_VALUE_MAX
#	define _SC_SEMAPHORES			_HAIKU_BUILD_SC_SEMAPHORES
#	define _SC_THREADS				_HAIKU_BUILD_SC_THREADS
/* TODO: check */
#	define _SC_IOV_MAX						_HAIKU_BUILD_SC_IOV_MAX
#	define _SC_UIO_MAXIOV					_HAIKU_BUILD_SC_UIO_MAXIOV
#	define _SC_NPROCESSORS_MAX				_HAIKU_BUILD_SC_NPROCESSORS_MAX
#	define _SC_NPROCESSORS_CONF				_HAIKU_BUILD_SC_NPROCESSORS_CONF
#	define _SC_NPROCESSORS_ONLN				_HAIKU_BUILD_SC_NPROCESSORS_ONLN
#	define _SC_CPUID_MAX					_HAIKU_BUILD_SC_CPUID_MAX
#	define _SC_ATEXIT_MAX					_HAIKU_BUILD_SC_ATEXIT_MAX
#	define _SC_PASS_MAX						_HAIKU_BUILD_SC_PASS_MAX
#	define _SC_PHYS_PAGES					_HAIKU_BUILD_SC_PHYS_PAGES
#	define _SC_AVPHYS_PAGES					_HAIKU_BUILD_SC_AVPHYS_PAGES
#	define _SC_PIPE							_HAIKU_BUILD_SC_PIPE
#	define _SC_SELECT						_HAIKU_BUILD_SC_SELECT
#	define _SC_POLL							_HAIKU_BUILD_SC_POLL
#	define _SC_MAPPED_FILES					_HAIKU_BUILD_SC_MAPPED_FILES
#	define _SC_THREAD_PROCESS_SHARED		_HAIKU_BUILD_SC_THREAD_PROCESS_SHARED
#	define _SC_THREAD_STACK_MIN				_HAIKU_BUILD_SC_THREAD_STACK_MIN
#	define _SC_THREAD_ATTR_STACKADDR		_HAIKU_BUILD_SC_THREAD_ATTR_STACKADDR
#	define _SC_THREAD_ATTR_STACKSIZE		_HAIKU_BUILD_SC_THREAD_ATTR_STACKSIZE
#	define _SC_THREAD_PRIORITY_SCHEDULING	_HAIKU_BUILD_SC_THREAD_PRIORITY_SCHEDULING
#	define _SC_REALTIME_SIGNALS				_HAIKU_BUILD_SC_REALTIME_SIGNALS
#	define	_SC_MEMORY_PROTECTION			_HAIKU_BUILD__MEMORY_PROTECTION
#	define _SC_SIGQUEUE_MAX					_HAIKU_BUILD_SC_SIGQUEUE_MAX
#	define _SC_RTSIG_MAX					_HAIKU_BUILD_SC_RTSIG_MAX
#	define _SC_MONOTONIC_CLOCK				_HAIKU_BUILD_SC_MONOTONIC_CLOCK
#	define _SC_DELAYTIMER_MAX				_HAIKU_BUILD_SC_DELAYTIMER_MAX
#	define _SC_TIMER_MAX					_HAIKU_BUILD_SC_TIMER_MAX
#	define	_SC_TIMERS						_HAIKU_BUILD__TIMERS
#	define	_SC_CPUTIME						_HAIKU_BUILD__CPUTIME
#	define	_SC_THREAD_CPUTIME				_HAIKU_BUILD__THREAD_CPUTIME


/* confstr() constants */
#	define _CS_PATH							_HAIKU_BUILD_CS_PATH

/* lseek() constants */
#	ifdef _HAIKU_BUILD_SEEK_SET
#		define SEEK_SET						_HAIKU_BUILD_SEEK_SET
#	endif
#	ifdef _HAIKU_BUILD_SEEK_CUR
#		define SEEK_CUR 					_HAIKU_BUILD_SEEK_CUR
#	endif
#	ifdef _HAIKU_BUILD_SEEK_END
#		define SEEK_END						_HAIKU_BUILD_SEEK_END
#	endif

#	endif  /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#ifdef __cplusplus
extern "C" {
#endif


// TODO: #8730 prefix function parameters as necessary.
/* file functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, access, (const char *path, int accessMode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, faccessat,
	(int fd, const char *path, int accessMode, int flag))

_HAIKU_BUILD_DECLARE_FUNCTION(int, chdir, (const char *path))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fchdir, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, getcwd, (char *buffer,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ size))

_HAIKU_BUILD_DECLARE_FUNCTION(int, pipe, (int fildes[2]))
_HAIKU_BUILD_DECLARE_FUNCTION(int, dup, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(int, dup2, (int fd1, int fd2))
_HAIKU_BUILD_DECLARE_FUNCTION(int, close, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(int, link, (const char *toPath,
	const char *path))
_HAIKU_BUILD_DECLARE_FUNCTION(int, linkat, (int toFD, const char *toPath,
	int pathFD, const char *path, int flag))
_HAIKU_BUILD_DECLARE_FUNCTION(int, unlink, (const char *name))
_HAIKU_BUILD_DECLARE_FUNCTION(int, unlinkat, (int fd, const char *path,
	int flag))
_HAIKU_BUILD_DECLARE_FUNCTION(int, rmdir, (const char *path))

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), readlink,
	(const char *path, char *buffer,
		_HAIKU_BUILD_FEATURE___SIZE_TYPE__ bufferSize))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), readlinkat,
	(int fd, const char *path, char *buffer,
		_HAIKU_BUILD_FEATURE___SIZE_TYPE__  bufferSize))
_HAIKU_BUILD_DECLARE_FUNCTION(int, symlink, (const char *toPath,
	const char *symlinkPath))
_HAIKU_BUILD_DECLARE_FUNCTION(int, symlinkat, (const char *toPath, int fd,
	const char *symlinkPath))

_HAIKU_BUILD_DECLARE_FUNCTION(int, ftruncate, (int fd,
	_haiku_build_off_t newSize))
_HAIKU_BUILD_DECLARE_FUNCTION(int, truncate, (const char *path,
	_haiku_build_off_t newSize))
_HAIKU_BUILD_DECLARE_FUNCTION(int, ioctl, (int fd, unsigned long op, ...))

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), read,
	(int fd, void *buffer, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ count))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), read_pos,
	(int fd, _haiku_build_off_t pos, void *buffer,
		_HAIKU_BUILD_FEATURE___SIZE_TYPE__ count))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), pread,
	(int fd, void *buffer, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ count,
		_haiku_build_off_t pos))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), write,
	(int fd, const void *buffer, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ count))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), write_pos,
	(int fd, _haiku_build_off_t pos, const void *buffer, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ count))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ssize_t), pwrite,
	(int fd, const void *buffer, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ count,
		_haiku_build_off_t pos))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_off_t, lseek, (int fd,
	_haiku_build_off_t offset, int whence))

_HAIKU_BUILD_DECLARE_FUNCTION(int, sync, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fsync, (int fd))

_HAIKU_BUILD_DECLARE_FUNCTION(int, chown, (const char *path,
	_haiku_build_uid_t owner, _haiku_build_gid_t group))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fchown, (int fd,
	_haiku_build_uid_t owner, _haiku_build_gid_t group))
_HAIKU_BUILD_DECLARE_FUNCTION(int, lchown, (const char *path,
	_haiku_build_uid_t owner, _haiku_build_gid_t group))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fchownat, (int fd, const char *path,
	_haiku_build_uid_t owner, _haiku_build_gid_t group, int flag))

_HAIKU_BUILD_DECLARE_FUNCTION(int, mknod, (const char *name,
	_haiku_build_mode_t mode, _haiku_build_dev_t dev))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mknodat, (int fd, const char *name,
	_haiku_build_mode_t mode, _haiku_build_dev_t dev))

_HAIKU_BUILD_DECLARE_FUNCTION(int, getpagesize, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, getdtablesize, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(long, sysconf, (int name))
_HAIKU_BUILD_DECLARE_FUNCTION(long, fpathconf, (int fd, int name))
_HAIKU_BUILD_DECLARE_FUNCTION(long, pathconf, (const char *path, int name))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, confstr,
	(int name, char *buf, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ len))
_HAIKU_BUILD_DECLARE_FUNCTION(int, lockf, (int fd, int function,
	_haiku_build_off_t size))

/* process functions */
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, fork, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, vfork, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, execve, (const char *path,
	char * const argv[], char * const envp[]))
_HAIKU_BUILD_DECLARE_FUNCTION(int, execl, (const char *path, const char *arg,
	...))
_HAIKU_BUILD_DECLARE_FUNCTION(int, execv, (const char *path, char *const *argv))
_HAIKU_BUILD_DECLARE_FUNCTION(int, execlp, (const char *file, const char *arg,
	...))
_HAIKU_BUILD_DECLARE_FUNCTION(int, execle, (const char *path, const char *arg,
	... /*, char **envp */))
_HAIKU_BUILD_DECLARE_FUNCTION(int, exect, (const char *path,
	char *const *argv))
_HAIKU_BUILD_DECLARE_FUNCTION(int, execvp, (const char *file,
	char *const *argv))

_HAIKU_BUILD_DECLARE_FUNCTION(void, _exit, (int status))

_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, tcgetpgrp, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(int, tcsetpgrp, (int fd,
	_haiku_build_pid_t pgrpid))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, sbrk, (long incr))

_HAIKU_BUILD_DECLARE_FUNCTION(unsigned int, alarm, (unsigned int seconds))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_useconds_t, ualarm,
	(_haiku_build_useconds_t microSeconds, _haiku_build_useconds_t interval))
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned int, sleep, (unsigned int seconds))
_HAIKU_BUILD_DECLARE_FUNCTION(int, usleep, (unsigned int microSeconds))
_HAIKU_BUILD_DECLARE_FUNCTION(int, pause, (void))

/* process */
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, getpid, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, getpgrp, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, getppid, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, getsid,
	(_haiku_build_pid_t pid))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, getpgid,
	(_haiku_build_pid_t pid))

_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, setsid, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setpgid, (_haiku_build_pid_t pid,
	_haiku_build_pid_t pgid))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_pid_t, setpgrp, (void))

_HAIKU_BUILD_DECLARE_FUNCTION(int, chroot, (const char *path))

/* access permissions */
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_gid_t, getegid, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_uid_t, geteuid, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_gid_t, getgid, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_uid_t, getuid, (void))

_HAIKU_BUILD_DECLARE_FUNCTION(int, setgid, (_haiku_build_gid_t gid))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setuid, (_haiku_build_uid_t uid))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setegid, (_haiku_build_gid_t gid))
_HAIKU_BUILD_DECLARE_FUNCTION(int, seteuid, (_haiku_build_uid_t uid))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setregid, (_haiku_build_gid_t rgid,
	_haiku_build_gid_t egid))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setreuid, (_haiku_build_uid_t ruid,
	_haiku_build_uid_t euid))

_HAIKU_BUILD_DECLARE_FUNCTION(int, getgrouplist, (const char* user,
	_haiku_build_gid_t baseGroup, _haiku_build_gid_t* groupList,
		int* groupCount))
_HAIKU_BUILD_DECLARE_FUNCTION(int, getgroups, (int groupCount,
	_haiku_build_gid_t groupList[]))
_HAIKU_BUILD_DECLARE_FUNCTION(int, initgroups, (const char* user,
	_haiku_build_gid_t baseGroup))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setgroups, (int groupCount,
	const _haiku_build_gid_t* groupList))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, getlogin, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, getlogin_r, (char *name,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ nameSize))

/* host name */
_HAIKU_BUILD_DECLARE_FUNCTION(int, sethostname, (const char *hostName,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ nameSize))
_HAIKU_BUILD_DECLARE_FUNCTION(int, gethostname, (char *hostName,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ nameSize))

/* tty */
_HAIKU_BUILD_DECLARE_FUNCTION(int, isatty, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, ttyname, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(int, ttyname_r, (int fd, char *buffer,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ bufferSize))

/* misc */
_HAIKU_BUILD_DECLARE_FUNCTION(char*, crypt, (const char *key,
	const char *salt))
_HAIKU_BUILD_DECLARE_FUNCTION(void, encrypt, (char block[64],
	int edflag))
_HAIKU_BUILD_DECLARE_FUNCTION(int, getopt, (int argc, char *const *argv,
	const char *shortOpts))
_HAIKU_BUILD_DECLARE_FUNCTION(void, swab, (const void *src, void *dest,
	_HAIKU_BUILD_IDENTIFIER(ssize_t) nbytes))

/* getopt() related external variables */
_HAIKU_BUILD_DECLARE_VARIABLE(char*, optarg)
_HAIKU_BUILD_DECLARE_VARIABLE(int, optind)
_HAIKU_BUILD_DECLARE_VARIABLE(int, opterr)
_HAIKU_BUILD_DECLARE_VARIABLE(int, optopt)

#ifdef __cplusplus
}
#endif

#endif  /* _UNISTD_H_ */
