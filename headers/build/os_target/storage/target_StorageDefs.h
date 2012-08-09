/*
 * Copyright 2002-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _DEF_STORAGE_H
#define _DEF_STORAGE_H


#include <target_fcntl.h>
#include <sys/target_param.h>
#include <target_limits.h>


// Limits
#define _HAIKU_BUILD_B_DEV_NAME_LENGTH		128
#define _HAIKU_BUILD_B_FILE_NAME_LENGTH		_HAIKU_BUILD_NAME_MAX
#define _HAIKU_BUILD_B_PATH_NAME_LENGTH 	_HAIKU_BUILD_MAXPATHLEN
#define _HAIKU_BUILD_B_ATTR_NAME_LENGTH		(_HAIKU_BUILD_B_FILE_NAME_LENGTH-1)
#define _HAIKU_BUILD_B_MIME_TYPE_LENGTH		(_HAIKU_BUILD_B_ATTR_NAME_LENGTH - 15)
#define _HAIKU_BUILD_B_MAX_SYMLINKS			_HAIKU_BUILD_SYMLOOP_MAX

// Open Modes
#define _HAIKU_BUILD_B_READ_ONLY 		_HAIKU_BUILD_O_RDONLY	// read only
#define _HAIKU_BUILD_B_WRITE_ONLY 		_HAIKU_BUILD_O_WRONLY 	// write only
#define _HAIKU_BUILD_B_READ_WRITE		_HAIKU_BUILD_O_RDWR   	// read and write

#define	_HAIKU_BUILD_B_FAIL_IF_EXISTS	_HAIKU_BUILD_O_EXCL		// exclusive create
#define _HAIKU_BUILD_B_CREATE_FILE		_HAIKU_BUILD_O_CREAT		// create the file
#define _HAIKU_BUILD_B_ERASE_FILE		_HAIKU_BUILD_O_TRUNC		// erase the file's data
#define _HAIKU_BUILD_B_OPEN_AT_END	   	_HAIKU_BUILD_O_APPEND	// point to the end of the data

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
// Limits
#	define B_DEV_NAME_LENGTH			_HAIKU_BUILD_B_DEV_NAME_LENGTH
#	define B_FILE_NAME_LENGTH			_HAIKU_BUILD_B_FILE_NAME_LENGTH
#	define B_PATH_NAME_LENGTH 			_HAIKU_BUILD_B_PATH_NAME_LENGTH
#	define B_ATTR_NAME_LENGTH			_HAIKU_BUILD_B_ATTR_NAME_LENGTH
#	define B_MIME_TYPE_LENGTH			_HAIKU_BUILD_B_MIME_TYPE_LENGTH
#	define B_MAX_SYMLINKS				_HAIKU_BUILD_B_MAX_SYMLINKS

// Open Modes
#	define B_READ_ONLY 		_HAIKU_BUILD_B_READ_ONLY	// read only
#	define B_WRITE_ONLY 	_HAIKU_BUILD_B_WRITE_ONLY 	// write only
#	define B_READ_WRITE		_HAIKU_BUILD_B_READ_WRITE  	// read and write

#	define	B_FAIL_IF_EXISTS	_HAIKU_BUILD_B_FAIL_IF_EXISTS	// exclusive create
#	define B_CREATE_FILE		_HAIKU_BUILD_B_CREATE_FILE		// create the file
#	define B_ERASE_FILE			_HAIKU_BUILD_B_ERASE_FILE		// erase the file's data
#	define B_OPEN_AT_END	   	_HAIKU_BUILD_B_OPEN_AT_END	// point to the end of the data

#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

// Node Flavors
enum node_flavor {
  _HAIKU_BUILD_IDENTIFIER(B_FILE_NODE)		= 0x01,
  _HAIKU_BUILD_IDENTIFIER(B_SYMLINK_NODE)	= 0x02,
  _HAIKU_BUILD_IDENTIFIER(B_DIRECTORY_NODE)	= 0x04,
  _HAIKU_BUILD_IDENTIFIER(B_ANY_NODE)		= 0x07
};

#endif /* _DEF_STORAGE_H */
