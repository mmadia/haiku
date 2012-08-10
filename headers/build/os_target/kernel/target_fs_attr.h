/*
 * Copyright 2002-2011, Haiku Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _FS_ATTR_H
#define	_FS_ATTR_H


#include <target_OS.h>
#include <target_dirent.h>


typedef struct _HAIKU_BUILD_IDENTIFIER(attr_info) {
	_haiku_build_uint32	type;
	_haiku_build_off_t	size;
} _HAIKU_BUILD_IDENTIFIER(attr_info);


#ifdef  __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(ssize_t, fs_read_attr, (int fd,
	const char *attribute, _haiku_build_uint32 type, _haiku_build_off_t pos,
		void *buffer, size_t readBytes))
_HAIKU_BUILD_DECLARE_FUNCTION(ssize_t, fs_write_attr, (int fd,
	const char *attribute, _haiku_build_uint32 type, haiku_build_off_t pos,
		const void *buffer, size_t readBytes))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fs_remove_attr(int fd, const char *attribute))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fs_stat_attr(int fd, const char *attribute,
	struct attr_info *attrInfo))

_HAIKU_BUILD_DECLARE_FUNCTION(int, fs_open_attr(const char *path,
	const char *attribute, _haiku_build_uint32 type, int openMode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fs_fopen_attr(int fd,
	const char *attribute, _haiku_build_uint32 type, int openMode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fs_close_attr(int fd))

_HAIKU_BUILD_DECLARE_FUNCTION(DIR*, fs_open_attr_dir, (const char *path))
_HAIKU_BUILD_DECLARE_FUNCTION(DIR*, fs_lopen_attr_dir, (const char *path))
_HAIKU_BUILD_DECLARE_FUNCTION(DIR*, fs_fopen_attr_dir, (int fd))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fs_close_attr_dir, (DIR *dir))
_HAIKU_BUILD_DECLARE_FUNCTION(struct _HAIKU_BUILD_IDENTIFIER(dirent)*,
	fs_read_attr_dir, (DIR *dir))
_HAIKU_BUILD_DECLARE_FUNCTION(void, fs_rewind_attr_dir, (DIR *dir))

#ifdef  __cplusplus
}
#endif


#endif	/* _FS_ATTR_H */
