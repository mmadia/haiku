/*
 * Copyright 2004, François Revol.
 * Copyright 2007-2010, Axel Dörfler, axeld@pinc-software.de.
 * Copyright 2011, Oliver Tappe <zooey@hirschkaefer.de>
 * Copyright 2011, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Distributed under the terms of the MIT License.
 */


#include <target_FindDirectory.h>

#include <target_errno.h>
#include <target_string.h>
#include <sys/target_stat.h>
#include <target_stdlib.h>
#include <target_unistd.h>

#include <target_StorageDefs.h>


#ifndef HAIKU_BUILD_GENERATED_DIRECTORY
#	error HAIKU_BUILD_GENERATED_DIRECTORY not defined!
#endif


/*! make dir and its parents if needed */
static int
create_path(const char *path, _haiku_build_mode_t mode)
{
	char buffer[_HAIKU_BUILD_B_PATH_NAME_LENGTH + 1];
	int pathLength;
	int i = 0;

	if (path == _HAIKU_BUILD_NULL || ((pathLength = _haiku_build_strlen(path)) > _HAIKU_BUILD_B_PATH_NAME_LENGTH))
		return _HAIKU_BUILD_EINVAL;

	while (++i < pathLength) {
		const char *slash = _haiku_build_strchr(&path[i], '/');
		// TODO: #8730 -- how to handle 'stat'?
		struct stat st;

		if (slash == _HAIKU_BUILD_NULL)
			i = pathLength;
		else if (i != slash - path)
			i = slash - path;
		else
			continue;

		_haiku_build_strlcpy(buffer, path, i + 1);
		if (stat(buffer, &st) < 0) {
			_haiku_build_errno = 0;
			if (_haiku_build_mkdir(buffer, mode) < 0)
				return _haiku_build_errno;
		}
	}

	return 0;
}


_haiku_build_status_t
find_directory(_HAIKU_BUILD_IDENTIFIER(directory_which) which,
	_haiku_build_dev_t device, bool createIt, char *returnedPath,
		_haiku_build_int32 pathLength)
{
	// we support only the handful of paths we need
	const char* path;
	switch (which) {
		case _HAIKU_BUILD_IDENTIFIER(B_COMMON_TEMP_DIRECTORY):
			path = HAIKU_BUILD_GENERATED_DIRECTORY "/tmp";
			break;
		case _HAIKU_BUILD_IDENTIFIER(B_COMMON_SETTINGS_DIRECTORY):
			path = HAIKU_BUILD_GENERATED_DIRECTORY "/common/settings";
			break;
		case _HAIKU_BUILD_IDENTIFIER(B_COMMON_CACHE_DIRECTORY):
			path = HAIKU_BUILD_GENERATED_DIRECTORY "/common/cache";
			break;
		case _HAIKU_BUILD_IDENTIFIER(B_USER_SETTINGS_DIRECTORY):
			path = HAIKU_BUILD_GENERATED_DIRECTORY "/user/settings";
			break;
		case _HAIKU_BUILD_IDENTIFIER(B_USER_CACHE_DIRECTORY):
			path = HAIKU_BUILD_GENERATED_DIRECTORY "/user/cache";
			break;
		default:
			return _HAIKU_BUILD_B_BAD_VALUE;
	}

	// create, if necessary
	_haiku_build_status_t error = _HAIKU_BUILD_B_OK;
	// TODO: #8730 -- how to handle 'stat'?
	struct stat st;
	if (createIt && stat(path, &st) < 0)
		error = create_path(path, 0755);

	if (error == _HAIKU_BUILD_B_OK)
		_haiku_build_strlcpy(returnedPath, path, pathLength);

	return error;
}

