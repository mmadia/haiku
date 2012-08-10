/*
 * Copyright 2007-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _BYTEORDER_H
#define _BYTEORDER_H


#include <target_BeBuild.h>
#include <target_endian.h>
#include <target_SupportDefs.h>
#include <target_TypeConstants.h>
	/* for convenience */


/* swap directions */
typedef enum {
	_HAIKU_BUILD_IDENTIFIER(B_SWAP_HOST_TO_LENDIAN),
	_HAIKU_BUILD_IDENTIFIER(B_SWAP_HOST_TO_BENDIAN),
	_HAIKU_BUILD_IDENTIFIER(B_SWAP_LENDIAN_TO_HOST),
	_HAIKU_BUILD_IDENTIFIER(B_SWAP_BENDIAN_TO_HOST),
	_HAIKU_BUILD_IDENTIFIER(B_SWAP_ALWAYS)
} _HAIKU_BUILD_IDENTIFIER(swap_action);


/* BSD/networking macros */
#ifndef _haiku_build_htonl
#	define _haiku_build_htonl(x) _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT32(x)
#	define _haiku_build_ntohl(x) _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT32(x)
#	define _haiku_build_htons(x) _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT16(x)
#	define _haiku_build_ntohs(x) _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT16(x)
#endif

/* always swap macros */
#define _HAIKU_BUILD_B_SWAP_DOUBLE(arg)   _haiku_build___swap_double(arg)
#define _HAIKU_BUILD_B_SWAP_FLOAT(arg)    _haiku_build___swap_float(arg)
#define _HAIKU_BUILD_B_SWAP_INT64(arg)    _haiku_build___swap_int64(arg)
#define _HAIKU_BUILD_B_SWAP_INT32(arg)    _haiku_build___swap_int32(arg)
#define _HAIKU_BUILD_B_SWAP_INT16(arg)    _haiku_build___swap_int16(arg)

#if _HAIKU_BUILD_BYTE_ORDER == __HAIKU_BUILD_LITTLE_ENDIAN
/* Host is little endian */

#define _HAIKU_BUILD_B_HOST_IS_LENDIAN 1
#define _HAIKU_BUILD_B_HOST_IS_BENDIAN 0

/* Host native to little endian */
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_DOUBLE(arg)	(double)(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_FLOAT(arg)	(float)(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_INT64(arg)	(_haiku_build_uint64)(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_INT32(arg)	(_haiku_build_uint32)(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_INT16(arg)	(_haiku_build_uint16)(arg)

/* Little endian to host native */
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_DOUBLE(arg)	(double)(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_FLOAT(arg)	(float)(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_INT64(arg)	(_haiku_build_uint64)(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_INT32(arg)	(_haiku_build_uint32)(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_INT16(arg)	(_haiku_build_uint16)(arg)

/* Host native to big endian */
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_DOUBLE(arg)	_haiku_build___swap_double(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_FLOAT(arg)	_haiku_build___swap_float(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT64(arg)	_haiku_build___swap_int64(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT32(arg)	_haiku_build___swap_int32(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT16(arg)	_haiku_build___swap_int16(arg)

/* Big endian to host native */
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_DOUBLE(arg)	_haiku_build___swap_double(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_FLOAT(arg)	_haiku_build___swap_float(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT64(arg)	_haiku_build___swap_int64(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT32(arg)	_haiku_build___swap_int32(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT16(arg)	_haiku_build___swap_int16(arg)

#else	/* BYTE_ORDER */
/* Host is big endian */

#define _HAIKU_BUILD_B_HOST_IS_LENDIAN 0
#define _HAIKU_BUILD_B_HOST_IS_BENDIAN 1

/* Host native to little endian */
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_DOUBLE(arg)	_haiku_build___swap_double(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_FLOAT(arg)	_haiku_build___swap_float(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_INT64(arg)	_haiku_build___swap_int64(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_INT32(arg)	_haiku_build___swap_int32(arg)
#define _HAIKU_BUILD_B_HOST_TO_LENDIAN_INT16(arg)	_haiku_build___swap_int16(arg)

/* Little endian to host native */
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_DOUBLE(arg)	_haiku_build___swap_double(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_FLOAT(arg)	_haiku_build___swap_float(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_INT64(arg)	_haiku_build___swap_int64(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_INT32(arg)	_haiku_build___swap_int32(arg)
#define _HAIKU_BUILD_B_LENDIAN_TO_HOST_INT16(arg)	_haiku_build___swap_int16(arg)

/* Host native to big endian */
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_DOUBLE(arg)	(double)(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_FLOAT(arg)	(float)(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT64(arg)	(_haiku_build_uint64)(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT32(arg)	(_haiku_build_uint32)(arg)
#define _HAIKU_BUILD_B_HOST_TO_BENDIAN_INT16(arg)	(_haiku_build_uint16)(arg)

/* Big endian to host native */
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_DOUBLE(arg)	(double)(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_FLOAT(arg)	(float)(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT64(arg)	(_haiku_build_uint64)(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT32(arg)	(_haiku_build_uint32)(arg)
#define _HAIKU_BUILD_B_BENDIAN_TO_HOST_INT16(arg)	(_haiku_build_uint16)(arg)

#endif	/* BYTE_ORDER */


#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_status_t, swap_data,
	(_haiku_build_type_code type, void *data, size_t length,
		_HAIKU_BUILD_IDENTIFIER(swap_action) action))
_HAIKU_BUILD_DECLARE_FUNCTION(bool, is_type_swapped,
	(_haiku_build_type_code type))


/* Private implementations */
_HAIKU_BUILD_DECLARE_FUNCTION(double, __swap_double, (double arg))
_HAIKU_BUILD_DECLARE_FUNCTION(float, __swap_float, (float arg))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_uint64, __swap_int64,
	(_haiku_build_uint64 arg))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_uint32, __swap_int32,
	(_haiku_build_uint32 arg))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_uint16, __swap_int16,
	(_haiku_build_uint16 arg))

#ifdef __cplusplus
}
#endif
#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
	/* BSD/networking macros */
#	ifndef htonl
#		define htonl(x) _haiku_build_htonl(x)
#		define ntohl(x) _haiku_build_ntohl(x)
#		define htons(x) _haiku_build_htons(x)
#		define ntohs(x) _haiku_build_ntohs(x)
#	endif

	/* always swap macros */
#	define B_SWAP_DOUBLE(arg)   _HAIKU_BUILD_B_SWAP_DOUBLE(arg)
#	define B_SWAP_FLOAT(arg)    _HAIKU_BUILD_B_SWAP_FLOAT(arg)
#	define B_SWAP_INT64(arg)    _HAIKU_BUILD_B_SWAP_INT64(arg)
#	define B_SWAP_INT32(arg)    _HAIKU_BUILD_B_SWAP_INT32(arg)
#	define B_SWAP_INT16(arg)    _HAIKU_BUILD_B_SWAP_INT16(arg)


#	if BYTE_ORDER == __LITTLE_ENDIAN
	/* Host is little endian */

#	define B_HOST_IS_LENDIAN				_HAIKU_BUILD_B_HOST_IS_LENDIAN
#	define B_HOST_IS_BENDIAN				_HAIKU_BUILD_B_HOST_IS_BENDIAN

	/* Host native to little endian */
#	define B_HOST_TO_LENDIAN_DOUBLE(arg)	_HAIKU_BUILD_B_HOST_TO_LENDIAN_DOUBLE(arg)
#	define B_HOST_TO_LENDIAN_FLOAT(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_FLOAT(arg)
#	define B_HOST_TO_LENDIAN_INT64(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_INT64(arg)
#	define B_HOST_TO_LENDIAN_INT32(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_INT32(arg)
#	define B_HOST_TO_LENDIAN_INT16(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_INT16(arg)

	/* Little endian to host native */
#	define B_LENDIAN_TO_HOST_DOUBLE(arg)	_HAIKU_BUILD_B_LENDIAN_TO_HOST_DOUBLE(arg)
#	define B_LENDIAN_TO_HOST_FLOAT(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_FLOAT(arg)
#	define B_LENDIAN_TO_HOST_INT64(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_INT64(arg)
#	define B_LENDIAN_TO_HOST_INT32(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_INT32(arg)
#	define B_LENDIAN_TO_HOST_INT16(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_INT16(arg)

	/* Host native to big endian */
#	define B_HOST_TO_BENDIAN_DOUBLE(arg)	_HAIKU_BUILD_B_HOST_TO_BENDIAN_DOUBLE(arg)
#	define B_HOST_TO_BENDIAN_FLOAT(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_FLOAT(arg)
#	define B_HOST_TO_BENDIAN_INT64(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_INT64(arg)
#	define B_HOST_TO_BENDIAN_INT32(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_INT32(arg)
#	define B_HOST_TO_BENDIAN_INT16(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_INT16(arg)

	/* Big endian to host native */
#	define B_BENDIAN_TO_HOST_DOUBLE(arg)	_HAIKU_BUILD_B_BENDIAN_TO_HOST_DOUBLE(arg)
#	define B_BENDIAN_TO_HOST_FLOAT(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_FLOAT(arg)
#	define B_BENDIAN_TO_HOST_INT64(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_INT64(arg)
#	define B_BENDIAN_TO_HOST_INT32(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_INT32(arg)
#	define B_BENDIAN_TO_HOST_INT16(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_INT16(arg)

#	else	/* BYTE_ORDER */
	/* Host is big endian */

#	define B_HOST_IS_LENDIAN				_HAIKU_BUILD_B_HOST_IS_LENDIAN
#	define B_HOST_IS_BENDIAN				_HAIKU_BUILD_B_HOST_IS_BENDIAN

	/* Host native to little endian */
#	define B_HOST_TO_LENDIAN_DOUBLE(arg)	_HAIKU_BUILD_B_HOST_TO_LENDIAN_DOUBLE(arg)
#	define B_HOST_TO_LENDIAN_FLOAT(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_FLOAT(arg)
#	define B_HOST_TO_LENDIAN_INT64(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_INT64(arg)
#	define B_HOST_TO_LENDIAN_INT32(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_INT32(arg)
#	define B_HOST_TO_LENDIAN_INT16(arg)		_HAIKU_BUILD_B_HOST_TO_LENDIAN_INT16(arg)

	/* Little endian to host native */
#	define B_LENDIAN_TO_HOST_DOUBLE(arg)	_HAIKU_BUILD_B_LENDIAN_TO_HOST_DOUBLE(arg)
#	define B_LENDIAN_TO_HOST_FLOAT(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_FLOAT(arg)
#	define B_LENDIAN_TO_HOST_INT64(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_INT64(arg)
#	define B_LENDIAN_TO_HOST_INT32(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_INT32(arg)
#	define B_LENDIAN_TO_HOST_INT16(arg)		_HAIKU_BUILD_B_LENDIAN_TO_HOST_INT16(arg)

	/* Host native to big endian */
#	define B_HOST_TO_BENDIAN_DOUBLE(arg)	_HAIKU_BUILD_B_HOST_TO_BENDIAN_DOUBLE(arg)
#	define B_HOST_TO_BENDIAN_FLOAT(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_FLOAT(arg)
#	define B_HOST_TO_BENDIAN_INT64(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_INT64(arg)
#	define B_HOST_TO_BENDIAN_INT32(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_INT32(arg)
#	define B_HOST_TO_BENDIAN_INT16(arg)		_HAIKU_BUILD_B_HOST_TO_BENDIAN_INT16(arg)

	/* Big endian to host native */
#	define B_BENDIAN_TO_HOST_DOUBLE(arg)	_HAIKU_BUILD_B_BENDIAN_TO_HOST_DOUBLE(arg)
#	define B_BENDIAN_TO_HOST_FLOAT(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_FLOAT(arg)
#	define B_BENDIAN_TO_HOST_INT64(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_INT64(arg)
#	define B_BENDIAN_TO_HOST_INT32(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_INT32(arg)
#	define B_BENDIAN_TO_HOST_INT16(arg)		_HAIKU_BUILD_B_BENDIAN_TO_HOST_INT16(arg)

#	endif	/* BYTE_ORDER */

#endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#endif	/* _BYTEORDER_H */
