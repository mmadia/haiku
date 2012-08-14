/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _DIRENT_H
#define _DIRENT_H


#include <sys/target_types.h>


typedef struct _HAIKU_BUILD_IDENTIFIER(dirent) {
	_HAIKU_BUILD_IDENTIFIER(dev_t)			d_dev;		/* device */
	_HAIKU_BUILD_IDENTIFIER(dev_t)			d_pdev;		/* parent device (only for queries) */
	_HAIKU_BUILD_IDENTIFIER(ino_t)			d_ino;		/* inode number */
	_HAIKU_BUILD_IDENTIFIER(ino_t)			d_pino;		/* parent inode (only for queries) */
	unsigned short	d_reclen;	/* length of this record, not the name */
	char			d_name[1];	/* name of the entry (null byte terminated) */
} _HAIKU_BUILD_IDENTIFIER(dirent_t);

struct _HAIKU_BUILD_IDENTIFIER(_DIR);
typedef struct _HAIKU_BUILD_IDENTIFIER(_DIR) _HAIKU_BUILD_IDENTIFIER(DIR);

#ifndef _HAIKU_BUILD_MAXNAMLEN
#	ifdef  _HAIKU_BUILD_NAME_MAX
#		define _HAIKU_BUILD_MAXNAMLEN _HAIKU_BUILD_NAME_MAX
#	else
#		define _HAIKU_BUILD_MAXNAMLEN 256
#	endif
#endif

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	ifdef _HAIKU_BUILD_MAXNAMLEN
#		ifdef  _HAIKU_BUILD_NAME_MAX
#			define MAXNAMLEN _HAIKU_BUILD_MAXNAMLEN
#		else
#			define MAXNAMLEN _HAIKU_BUILD_MAXNAMLEN
#		endif
#	endif
#endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(DIR)*, fdopendir,
	(int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(DIR)*, opendir,
	(const char* dirName))
_HAIKU_BUILD_DECLARE_FUNCTION(struct _HAIKU_BUILD_IDENTIFIER(dirent_t)*,
	readdir, (_HAIKU_BUILD_IDENTIFIER(DIR)* dir))
_HAIKU_BUILD_DECLARE_FUNCTION(int, readdir_r,
	(_HAIKU_BUILD_IDENTIFIER(DIR)* dir,
		struct _HAIKU_BUILD_IDENTIFIER(dirent_t)* entry,
			struct _HAIKU_BUILD_IDENTIFIER(dirent_t)** _result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, closedir,
	(_HAIKU_BUILD_IDENTIFIER(DIR)* dir))
_HAIKU_BUILD_DECLARE_FUNCTION(void, rewinddir,
	(_HAIKU_BUILD_IDENTIFIER(DIR)* dir))
_HAIKU_BUILD_DECLARE_FUNCTION(void, seekdir,
	(_HAIKU_BUILD_IDENTIFIER(DIR)* dir, long int position))
_HAIKU_BUILD_DECLARE_FUNCTION(long int, telldir,
	(_HAIKU_BUILD_IDENTIFIER(DIR)* dir))
_HAIKU_BUILD_DECLARE_FUNCTION(int, dirfd,
	(_HAIKU_BUILD_IDENTIFIER(DIR)* dir))

_HAIKU_BUILD_DECLARE_FUNCTION(int, alphasort,
	(const struct _HAIKU_BUILD_IDENTIFIER(dirent_t)** entry1,
		const struct _HAIKU_BUILD_IDENTIFIER(dirent_t)** entry2))
_HAIKU_BUILD_DECLARE_FUNCTION(int, scandir,
	(const char* dir, struct _HAIKU_BUILD_IDENTIFIER(dirent_t)*** _entryArray,
		int (*selectFunc)(const struct _HAIKU_BUILD_IDENTIFIER(dirent_t)*),
			int (*compareFunc)
				(const struct _HAIKU_BUILD_IDENTIFIER(dirent_t)** entry1,
					const struct _HAIKU_BUILD_IDENTIFIER(dirent_t)** entry2)))

#ifdef __cplusplus
}
#endif

#endif	/* _DIRENT_H */
