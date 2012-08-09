/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_


#include <sys/target_types.h>
#include <target_time.h>


// TODO: #8730 -- how to handle 'stat'?
struct stat {
	_haiku_build_dev_t			st_dev;			/* device ID that this file resides on */
	_haiku_build_ino_t			st_ino;			/* this file's serial inode ID */
	_haiku_build_mode_t			st_mode;		/* file mode (rwx for user, group, etc) */
	_haiku_build_nlink_t		st_nlink;		/* number of hard links to this file */
	_haiku_build_uid_t			st_uid;			/* user ID of the owner of this file */
	_haiku_build_gid_t			st_gid;			/* group ID of the owner of this file */
	_haiku_build_off_t			st_size;		/* size in bytes of this file */
	_haiku_build_dev_t			st_rdev;		/* device type (not used) */
	_haiku_build_blksize_t		st_blksize;		/* preferred block size for I/O */
	struct _HAIKU_BUILD_IDENTIFIER(timespec)	st_atim;		/* last access time */
	struct _HAIKU_BUILD_IDENTIFIER(timespec)	st_mtim;		/* last modification time */
	struct _HAIKU_BUILD_IDENTIFIER(timespec)	st_ctim;		/* last change time, not creation time */
	struct _HAIKU_BUILD_IDENTIFIER(timespec)	st_crtim;		/* creation time */
	__haiku_build_haiku_uint32	st_type;		/* attribute/index type */
	_haiku_build_blkcnt_t		st_blocks;		/* number of blocks allocated for object */
};

/* source compatibility with old stat structure */
#define _haiku_build_st_atime	st_atim.tv_sec
#define _haiku_build_st_mtime	st_mtim.tv_sec
#define _haiku_build_st_ctime	st_ctim.tv_sec
#define _haiku_build_st_crtime	st_crtim.tv_sec


/* extended file types */
#define _HAIKU_BUILD_S_ATTR_DIR			01000000000	/* attribute directory */
#define _HAIKU_BUILD_S_ATTR				02000000000	/* attribute */
#define _HAIKU_BUILD_S_INDEX_DIR		04000000000	/* index (or index directory) */
#define _HAIKU_BUILD_S_STR_INDEX		00100000000	/* string index */
#define _HAIKU_BUILD_S_INT_INDEX		00200000000	/* int32 index */
#define _HAIKU_BUILD_S_UINT_INDEX		00400000000	/* uint32 index */
#define _HAIKU_BUILD_S_LONG_LONG_INDEX	00010000000	/* int64 index */
#define _HAIKU_BUILD_S_ULONG_LONG_INDEX	00020000000	/* uint64 index */
#define _HAIKU_BUILD_S_FLOAT_INDEX		00040000000	/* float index */
#define _HAIKU_BUILD_S_DOUBLE_INDEX		00001000000	/* double index */
#define _HAIKU_BUILD_S_ALLOW_DUPS		00002000000	/* allow duplicate entries (currently unused) */

/* link types */
#define _HAIKU_BUILD_S_LINK_SELF_HEALING	00001000000	/* link will be updated if you move its target */
#define _HAIKU_BUILD_S_LINK_AUTO_DELETE		00002000000	/* link will be deleted if you delete its target */

/* standard file types */
#define _HAIKU_BUILD_S_IFMT				00000170000 /* type of file */
#define _HAIKU_BUILD_S_IFSOCK			00000140000 /* socket */
#define _HAIKU_BUILD_S_IFLNK			00000120000 /* symbolic link */
#define _HAIKU_BUILD_S_IFREG			00000100000 /* regular */
#define _HAIKU_BUILD_S_IFBLK			00000060000 /* block special */
#define _HAIKU_BUILD_S_IFDIR			00000040000 /* directory */
#define _HAIKU_BUILD_S_IFCHR			00000020000 /* character special */
#define _HAIKU_BUILD_S_IFIFO			00000010000 /* fifo */

#define _HAIKU_BUILD_S_ISREG(mode)		(((mode) & S_IFMT) == S_IFREG)
#define _HAIKU_BUILD_S_ISLNK(mode)		(((mode) & S_IFMT) == S_IFLNK)
#define _HAIKU_BUILD_S_ISBLK(mode)		(((mode) & S_IFMT) == S_IFBLK)
#define _HAIKU_BUILD_S_ISDIR(mode)		(((mode) & S_IFMT) == S_IFDIR)
#define _HAIKU_BUILD_S_ISCHR(mode)		(((mode) & S_IFMT) == S_IFCHR)
#define _HAIKU_BUILD_S_ISFIFO(mode)		(((mode) & S_IFMT) == S_IFIFO)
#define _HAIKU_BUILD_S_ISSOCK(mode)		(((mode) & S_IFMT) == S_IFSOCK)
#define _HAIKU_BUILD_S_ISINDEX(mode)	(((mode) & S_INDEX_DIR) == S_INDEX_DIR)

#define _HAIKU_BUILD_S_IUMSK 07777		/* user settable bits */

#define _HAIKU_BUILD_S_ISUID 04000		/* set user id on execution */
#define _HAIKU_BUILD_S_ISGID 02000		/* set group id on execution */

#define _HAIKU_BUILD_S_ISVTX 01000		/* save swapped text even after use (sticky bit) */

#define _HAIKU_BUILD_S_IRWXU 00700		/* read, write, execute: owner */
#define _HAIKU_BUILD_S_IRUSR 00400		/* read permission: owner */
#define _HAIKU_BUILD_S_IWUSR 00200		/* write permission: owner */
#define _HAIKU_BUILD_S_IXUSR 00100		/* execute permission: owner */
#define _HAIKU_BUILD_S_IRWXG 00070		/* read, write, execute: group */
#define _HAIKU_BUILD_S_IRGRP 00040		/* read permission: group */
#define _HAIKU_BUILD_S_IWGRP 00020		/* write permission: group */
#define _HAIKU_BUILD_S_IXGRP 00010		/* execute permission: group */
#define _HAIKU_BUILD_S_IRWXO 00007		/* read, write, execute: other */
#define _HAIKU_BUILD_S_IROTH 00004		/* read permission: other */
#define _HAIKU_BUILD_S_IWOTH 00002		/* write permission: other */
#define _HAIKU_BUILD_S_IXOTH 00001		/* execute permission: other */

/* BSD extensions */
#define _HAIKU_BUILD_S_IREAD		S_IRUSR
#define _HAIKU_BUILD_S_IWRITE		S_IWUSR
#define _HAIKU_BUILD_S_IEXEC		S_IXUSR

#define _HAIKU_BUILD_ACCESSPERMS 	(S_IRWXU | S_IRWXG | S_IRWXO)
#define _HAIKU_BUILD_ALLPERMS		(S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO)
#define	_HAIKU_BUILD_DEFFILEMODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
	/* default file mode, everyone can read/write */

/* special values for _HAIKU_BUILD_IDENTIFIER(timespec)::tv_nsec passed to utimensat(), futimens() */
#define _HAIKU_BUILD_UTIME_NOW		1000000000
#define _HAIKU_BUILD_UTIME_OMIT		1000000001

#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(int, chmod,
	(const char *path, _haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fchmod, (int fd, _haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fchmodat,
	(int fd, const char *path, _haiku_build_mode_t mode, int flag))
// TODO: #8730 -- how to handle 'stat'?
_HAIKU_BUILD_DECLARE_FUNCTION(int, stat, (const char *path, struct stat *st))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fstat, (int fd, struct stat *st))
_HAIKU_BUILD_DECLARE_FUNCTION(int, lstat, (const char *path, struct stat *st))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fstatat,
	(int fd, const char *path, struct stat *st, int flag))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mkdir,
	(const char *path, _haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mkdirat,
	(int fd, const char *path, _haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mkfifo,
	(const char *path, _haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mkfifoat,
	(int fd, const char *path, _haiku_build_mode_t mode))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_mode_t, umask,
	(_haiku_build_mode_t cmask))

_HAIKU_BUILD_DECLARE_FUNCTION(int, utimensat, (int fd, const char *path,
	const struct _HAIKU_BUILD_IDENTIFIER(timespec) times[2], int flag))
_HAIKU_BUILD_DECLARE_FUNCTION(int, futimens,
	(int fd, const struct _HAIKU_BUILD_IDENTIFIER(timespec) times[2]))

#ifdef __cplusplus
}
#endif


#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
/* source compatibility with old stat structure */
#	define st_atime		_haiku_build_st_atime
#	define st_mtime		_haiku_build_st_mtime
#	define st_ctime		_haiku_build_st_ctime
#	define st_crtime	_haiku_build_st_crtime


/* extended file types */
#	define S_ATTR_DIR			_HAIKU_BUILD_S_ATTR_DIR	/* attribute directory */
#	define S_ATTR				_HAIKU_BUILD_S_ATTR	/* attribute */
#	define S_INDEX_DIR			_HAIKU_BUILD_S_INDEX_DIR	/* index (or index directory) */
#	define S_STR_INDEX			_HAIKU_BUILD_S_STR_INDEX	/* string index */
#	define S_INT_INDEX			_HAIKU_BUILD_S_INT_INDEX	/* int32 index */
#	define S_UINT_INDEX			_HAIKU_BUILD_S_UINT_INDEX	/* uint32 index */
#	define S_LONG_LONG_INDEX	_HAIKU_BUILD_S_LONG_LONG_INDEX	/* int64 index */
#	define S_ULONG_LONG_INDEX	_HAIKU_BUILD_S_ULONG_LONG_INDEX	/* uint64 index */
#	define S_FLOAT_INDEX		_HAIKU_BUILD_S_FLOAT_INDEX	/* float index */
#	define S_DOUBLE_INDEX		_HAIKU_BUILD_S_DOUBLE_INDEX	/* double index */
#	define S_ALLOW_DUPS			_HAIKU_BUILD_S_ALLOW_DUPS	/* allow duplicate entries (currently unused) */

/* link types */
#	define	S_LINK_SELF_HEALING	_HAIKU_BUILD_S_LINK_SELF_HEALING	/* link will be updated if you move its target */
#	define S_LINK_AUTO_DELETE	_HAIKU_BUILD_S_LINK_AUTO_DELETE	/* link will be deleted if you delete its target */

/* standard file types */
#	define S_IFMT				_HAIKU_BUILD_S_IFMT /* type of file */
#	define	S_IFSOCK			_HAIKU_BUILD_S_IFSOCK /* socket */
#	define	S_IFLNK				_HAIKU_BUILD_S_IFLNK /* symbolic link */
#	define S_IFREG				_HAIKU_BUILD_S_IFREG /* regular */
#	define S_IFBLK				_HAIKU_BUILD_S_IFBLK /* block special */
#	define S_IFDIR				_HAIKU_BUILD_S_IFDIR /* directory */
#	define S_IFCHR				_HAIKU_BUILD_S_IFCHR /* character special */
#	define S_IFIFO				_HAIKU_BUILD_S_IFIFO /* fifo */

#	define S_ISREG(mode)		_HAIKU_BUILD_S_ISREG(mode)
#	define S_ISLNK(mode)		_HAIKU_BUILD_S_ISLNK(mode)
#	define S_ISBLK(mode)		_HAIKU_BUILD_S_ISBLK(mode)
#	define S_ISDIR(mode)		_HAIKU_BUILD_S_ISDIR(mode)
#	define S_ISCHR(mode)		_HAIKU_BUILD_S_ISCHR(mode)
#	define S_ISFIFO(mode)		_HAIKU_BUILD_S_ISFIFO(mode)
#	define S_ISSOCK(mode)		_HAIKU_BUILD_S_ISSOCK(mode)
#	define S_ISINDEX(mode)		_HAIKU_BUILD_S_ISINDEX(mode)

#	define	S_IUMSK				_HAIKU_BUILD_S_IUMSK		/* user settable bits */

#	define S_ISUID		_HAIKU_BUILD_S_ISUID	/* set user id on execution */
#	define S_ISGID		_HAIKU_BUILD_S_ISGID	/* set group id on execution */

#	define S_ISVTX		_HAIKU_BUILD_S_ISVTX	/* save swapped text even after use (sticky bit) */

#	define S_IRWXU		_HAIKU_BUILD_S_IRWXU	/* read, write, execute: owner */
#	define S_IRUSR		_HAIKU_BUILD_S_IRUSR	/* read permission: owner */
#	define S_IWUSR		_HAIKU_BUILD_S_IWUSR	/* write permission: owner */
#	define S_IXUSR		_HAIKU_BUILD_S_IXUSR	/* execute permission: owner */
#	define S_IRWXG		_HAIKU_BUILD_S_IRWXG	/* read, write, execute: group */
#	define S_IRGRP		_HAIKU_BUILD_S_IRGRP	/* read permission: group */
#	define S_IWGRP		_HAIKU_BUILD_S_IWGRP	/* write permission: group */
#	define S_IXGRP		_HAIKU_BUILD_S_IXGRP	/* execute permission: group */
#	define S_IRWXO		_HAIKU_BUILD_S_IRWXO	/* read, write, execute: other */
#	define S_IROTH		_HAIKU_BUILD_S_IROTH	/* read permission: other */
#	define S_IWOTH		_HAIKU_BUILD_S_IWOTH	/* write permission: other */
#	define S_IXOTH		_HAIKU_BUILD_S_IXOTH	/* execute permission: other */

/* BSD extensions */
#	define S_IREAD				_HAIKU_BUILD_S_IREAD
#	define S_IWRITE				_HAIKU_BUILD_S_IWRITE
#	define S_IEXEC				_HAIKU_BUILD_S_IEXEC

#	define ACCESSPERMS			_HAIKU_BUILD_ACCESSPERMS
#	define ALLPERMS				_HAIKU_BUILD_ALLPERMS
#	define	DEFFILEMODE			_HAIKU_BUILD_DEFFILEMODE
	/* default file mode, everyone can read/write */

/* special values for timespec::tv_nsec passed to utimensat(), futimens() */
#	define UTIME_NOW			_HAIKU_BUILD_UTIME_NOW
#	define UTIME_OMIT			_HAIKU_BUILD_UTIME_OMIT

#endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#endif	/* _SYS_STAT_H_ */
