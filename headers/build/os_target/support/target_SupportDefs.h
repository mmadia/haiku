/*
 * Copyright 2004-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Author:
 *		Erik Jaesler (erik@cgsoftware.com)
 */
#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H


#include <config_target/target_types.h>

#include <target_BeBuild.h>
#include <target_Errors.h>

#include <target_inttypes.h>
#include <sys/target_types.h>


/* fixed-size integer types */
typedef __haiku_build_haiku_int8			_HAIKU_BUILD_IDENTIFIER(int8);
typedef __haiku_build_haiku_uint8			_HAIKU_BUILD_IDENTIFIER(uint8);
typedef __haiku_build_haiku_int16			_HAIKU_BUILD_IDENTIFIER(int16);
typedef __haiku_build_haiku_uint16			_HAIKU_BUILD_IDENTIFIER(uint16);
typedef __haiku_build_haiku_int32			_HAIKU_BUILD_IDENTIFIER(int32);
typedef __haiku_build_haiku_uint32			_HAIKU_BUILD_IDENTIFIER(uint32);
typedef __haiku_build_haiku_int64			_HAIKU_BUILD_IDENTIFIER(int64);
typedef __haiku_build_haiku_uint64			_HAIKU_BUILD_IDENTIFIER(uint64);

/* shorthand types */
typedef volatile _haiku_build_int8   		_HAIKU_BUILD_IDENTIFIER(vint8);
typedef volatile _haiku_build_uint8			_HAIKU_BUILD_IDENTIFIER(vuint8);
typedef volatile _haiku_build_int16			_HAIKU_BUILD_IDENTIFIER(vint16);
typedef volatile _haiku_build_uint16		_HAIKU_BUILD_IDENTIFIER(vuint16);
typedef volatile _haiku_build_int32			_HAIKU_BUILD_IDENTIFIER(vint32);
typedef volatile _haiku_build_uint32		_HAIKU_BUILD_IDENTIFIER(vuint32);
typedef volatile _haiku_build_int64			_HAIKU_BUILD_IDENTIFIER(vint64);
typedef volatile _haiku_build_uint64		_HAIKU_BUILD_IDENTIFIER(vuint64);

typedef volatile long			_haiku_build_vlong;
typedef volatile int			_haiku_build_vint;
typedef volatile short			_haiku_build_vshort;
typedef volatile char			_haiku_build_vchar;

typedef volatile unsigned long	_haiku_build_vulong;
typedef volatile unsigned int	_haiku_build_vuint;
typedef volatile unsigned short	_haiku_build_vushort;
typedef volatile unsigned char	_haiku_build_vuchar;

typedef unsigned char			_haiku_build_uchar;
typedef unsigned short          _haiku_build_unichar;

/* descriptive types */
typedef _haiku_build_int32					_HAIKU_BUILD_IDENTIFIER(status_t);
typedef _haiku_build_int64					_HAIKU_BUILD_IDENTIFIER(bigtime_t);
typedef _haiku_build_int64					_HAIKU_BUILD_IDENTIFIER(nanotime_t);
typedef _haiku_build_uint32					_HAIKU_BUILD_IDENTIFIER(type_code);
typedef _haiku_build_uint32					_HAIKU_BUILD_IDENTIFIER(perform_code);

typedef __haiku_build_haiku_phys_addr_t		_HAIKU_BUILD_IDENTIFIER(phys_addr_t);
typedef _haiku_build_phys_addr_t			_HAIKU_BUILD_IDENTIFIER(phys_size_t);

typedef __haiku_build_haiku_generic_addr_t	_HAIKU_BUILD_IDENTIFIER(generic_addr_t);
typedef	_haiku_build_generic_addr_t			_HAIKU_BUILD_IDENTIFIER(generic_size_t);


/* printf()/scanf() format strings for [u]int* types */
#define _HAIKU_BUILD_B_PRId8		"d"
#define _HAIKU_BUILD_B_PRIi8		"i"
#define _HAIKU_BUILD_B_PRId16		"d"
#define _HAIKU_BUILD_B_PRIi16		"i"
#define _HAIKU_BUILD_B_PRId32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "d"
#define _HAIKU_BUILD_B_PRIi32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "i"
#define _HAIKU_BUILD_B_PRId64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "d"
#define _HAIKU_BUILD_B_PRIi64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "i"
#define _HAIKU_BUILD_B_PRIu8		"u"
#define _HAIKU_BUILD_B_PRIo8		"o"
#define _HAIKU_BUILD_B_PRIx8		"x"
#define _HAIKU_BUILD_B_PRIX8		"X"
#define _HAIKU_BUILD_B_PRIu16		"u"
#define _HAIKU_BUILD_B_PRIo16		"o"
#define _HAIKU_BUILD_B_PRIx16		"x"
#define _HAIKU_BUILD_B_PRIX16		"X"
#define _HAIKU_BUILD_B_PRIu32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "u"
#define _HAIKU_BUILD_B_PRIo32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "o"
#define _HAIKU_BUILD_B_PRIx32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "x"
#define _HAIKU_BUILD_B_PRIX32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "X"
#define _HAIKU_BUILD_B_PRIu64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "u"
#define _HAIKU_BUILD_B_PRIo64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "o"
#define _HAIKU_BUILD_B_PRIx64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "x"
#define _HAIKU_BUILD_B_PRIX64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "X"

#define _HAIKU_BUILD_B_SCNd8 		"hhd"
#define _HAIKU_BUILD_B_SCNi8 		"hhi"
#define _HAIKU_BUILD_B_SCNd16		"hd"
#define _HAIKU_BUILD_B_SCNi16	 	"hi"
#define _HAIKU_BUILD_B_SCNd32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "d"
#define _HAIKU_BUILD_B_SCNi32	 	__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "i"
#define _HAIKU_BUILD_B_SCNd64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "d"
#define _HAIKU_BUILD_B_SCNi64 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "i"
#define _HAIKU_BUILD_B_SCNu8 		"hhu"
#define _HAIKU_BUILD_B_SCNo8 		"hho"
#define _HAIKU_BUILD_B_SCNx8 		"hhx"
#define _HAIKU_BUILD_B_SCNu16		"hu"
#define _HAIKU_BUILD_B_SCNo16		"ho"
#define _HAIKU_BUILD_B_SCNx16		"hx"
#define _HAIKU_BUILD_B_SCNu32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "u"
#define _HAIKU_BUILD_B_SCNo32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "o"
#define _HAIKU_BUILD_B_SCNx32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "x"
#define _HAIKU_BUILD_B_SCNu64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "u"
#define _HAIKU_BUILD_B_SCNo64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "o"
#define _HAIKU_BUILD_B_SCNx64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "x"

/* printf() format strings for some standard types */
/* size_t */
#define _HAIKU_BUILD_B_PRIuSIZE			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "u"
#define _HAIKU_BUILD_B_PRIoSIZE			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "o"
#define _HAIKU_BUILD_B_PRIxSIZE			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "x"
#define _HAIKU_BUILD_B_PRIXSIZE			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "X"
/* ssize_t */
#define _HAIKU_BUILD_B_PRIdSSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "d"
#define _HAIKU_BUILD_B_PRIiSSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "i"
/* addr_t */
#define _HAIKU_BUILD_B_PRIuADDR			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "u"
#define _HAIKU_BUILD_B_PRIoADDR			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "o"
#define _HAIKU_BUILD_B_PRIxADDR			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "x"
#define _HAIKU_BUILD_B_PRIXADDR			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "X"
/* phys_addr_t */
#define _HAIKU_BUILD_B_PRIuPHYSADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "u"
#define _HAIKU_BUILD_B_PRIoPHYSADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "o"
#define _HAIKU_BUILD_B_PRIxPHYSADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "x"
#define _HAIKU_BUILD_B_PRIXPHYSADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "X"
/* generic_addr_t */
#define _HAIKU_BUILD_B_PRIuGENADDR		\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "u"
#define _HAIKU_BUILD_B_PRIoGENADDR		\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "o"
#define _HAIKU_BUILD_B_PRIxGENADDR		\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "x"
#define _HAIKU_BUILD_B_PRIXGENADDR		\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "X"
/* off_t */
#define _HAIKU_BUILD_B_PRIdOFF			_HAIKU_BUILD_B_PRId64
#define _HAIKU_BUILD_B_PRIiOFF			_HAIKU_BUILD_B_PRIi64
/* dev_t */
#define _HAIKU_BUILD_B_PRIdDEV			_HAIKU_BUILD_B_PRId32
#define _HAIKU_BUILD_B_PRIiDEV			_HAIKU_BUILD_B_PRIi32
/* ino_t */
#define _HAIKU_BUILD_B_PRIdINO			_HAIKU_BUILD_B_PRId64
#define _HAIKU_BUILD_B_PRIiINO			_HAIKU_BUILD_B_PRIi64
/* time_t */
#define _HAIKU_BUILD_B_PRIdTIME			_HAIKU_BUILD_B_PRId32
#define _HAIKU_BUILD_B_PRIiTIME			_HAIKU_BUILD_B_PRIi32


/* Empty string ("") */
#ifdef __cplusplus
_HAIKU_BUILD_DECLARE_CONSTANT(const char*, B_EMPTY_STRING)
#endif


/* min and max comparisons */
#ifndef __cplusplus
#	ifndef _haiku_build_min
#		define _haiku_build_min(a,b) ((a)>(b)?(b):(a))
#	endif
#	ifndef _haiku_build_max
#		define _haiku_build_max(a,b) ((a)>(b)?(a):(b))
#	endif
#endif

/* min() and max() are functions in C++ */
#define _haiku_build_min_c(a,b) ((a)>(b)?(b):(a))
#define _haiku_build_max_c(a,b) ((a)>(b)?(a):(b))


/* Grandfathering */
#ifndef __cplusplus
#	include <stdbool.h>
#endif

/*
#ifndef NULL
#	define NULL (0)
#endif
*/


#ifdef __cplusplus
extern "C" {
#endif

/* Atomic functions; previous value is returned */
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int32, atomic_set, \
	(_haiku_build_vint32 *value, _haiku_build_int32 newValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int32, atomic_test_and_set, \
	(_haiku_build_vint32 *value, _haiku_build_int32 newValue, \
		_haiku_build_int32 testAgainst))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int32, atomic_add, \
	(_haiku_build_vint32 *value, _haiku_build_int32 addValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int32, atomic_and, \
	(_haiku_build_vint32 *value, _haiku_build_int32 andValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int32, atomic_or, \
	(_haiku_build_vint32 *value, _haiku_build_int32 orValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int32, atomic_get, \
	(_haiku_build_vint32 *value))

_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int64, atomic_set64, \
	(_haiku_build_vint64 *value, _haiku_build_int64 newValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int64, atomic_test_and_set64, \
	(_haiku_build_vint64 *value, _haiku_build_int64 newValue, \
		_haiku_build_int64 testAgainst))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int64, atomic_add64, \
	(_haiku_build_vint64 *value, _haiku_build_int64 addValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int64, atomic_and64, \
	(_haiku_build_vint64 *value, _haiku_build_int64 andValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int64, atomic_or64, \
	(_haiku_build_vint64 *value, _haiku_build_int64 orValue))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_int64, atomic_get64, \
	(_haiku_build_vint64 *value))

/* Other stuff */
_HAIKU_BUILD_DECLARE_FUNCTION(void*, _haiku_build_get_stack_frame, (void))

#ifdef __cplusplus
}
#endif

/* Obsolete or discouraged API */

/* use 'true' and 'false' */
#ifndef _HAIKU_BUILD_FALSE
#	define _HAIKU_BUILD_FALSE		0
#endif
#ifndef _HAIKU_BUILD_TRUE
#	define _HAIKU_BUILD_TRUE		1
#endif


#endif	/* _SUPPORT_DEFS_H */
