/*
 * Copyright 2004-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Erik Jaesler (erik@cgsoftware.com)
 *		Matt Madia (mattmadia@gmail.com)
 */
#ifndef _SUPPORT_DEFS_H
#define _SUPPORT_DEFS_H


#include <config_target/target_types.h>

#include <target_BeBuild.h>
#include <target_Errors.h>

#include <target_inttypes.h>
#include <sys/target_types.h>


/* fixed-size integer types */
typedef __haiku_build_haiku_int8			_haiku_build_int8;
typedef __haiku_build_haiku_uint8			_haiku_build_uint8;
typedef __haiku_build_haiku_int16			_haiku_build_int16;
typedef __haiku_build_haiku_uint16			_haiku_build_uint16;
typedef __haiku_build_haiku_int32			_haiku_build_int32;
typedef __haiku_build_haiku_uint32			_haiku_build_uint32;
typedef __haiku_build_haiku_int64			_haiku_build_int64;
typedef __haiku_build_haiku_uint64			_haiku_build_uint64;

/* shorthand types */
typedef volatile _haiku_build_int8			_haiku_build_vint8;
typedef volatile _haiku_build_uint8			_haiku_build_vuint8;
typedef volatile _haiku_build_int16			_haiku_build_vint16;
typedef volatile _haiku_build_uint16		_haiku_build_vuint16;
typedef volatile _haiku_build_int32			_haiku_build_vint32;
typedef volatile _haiku_build_uint32		_haiku_build_vuint32;
typedef volatile _haiku_build_int64			_haiku_build_vint64;
typedef volatile _haiku_build_uint64		_haiku_build_vuint64;

typedef volatile long						_haiku_build_vlong;
typedef volatile int						_haiku_build_vint;
typedef volatile short						_haiku_build_vshort;
typedef volatile char						_haiku_build_vchar;

typedef volatile unsigned long				_haiku_build_vulong;
typedef volatile unsigned int				_haiku_build_vuint;
typedef volatile unsigned short				_haiku_build_vushort;
typedef volatile unsigned char				_haiku_build_vuchar;

typedef unsigned char						_haiku_build_uchar;
typedef unsigned short						_haiku_build_unichar;

/* descriptive types */
typedef _haiku_build_int32					_haiku_build_status_t;
typedef _haiku_build_int64					_haiku_build_bigtime_t;
typedef _haiku_build_int64					_haiku_build_nanotime_t;
typedef _haiku_build_uint32					_haiku_build_type_code;
typedef _haiku_build_uint32					_haiku_build_perform_code;

typedef __haiku_build_haiku_phys_addr_t		_haiku_build_phys_addr_t;
typedef _haiku_build_phys_addr_t			_haiku_build_phys_size_t;

typedef __haiku_build_haiku_generic_addr_t	_haiku_build_generic_addr_t;
typedef	_haiku_build_generic_addr_t			_haiku_build_generic_size_t;


/* printf()/scanf() format strings for [u]int* types */
#define _HAIKU_BUILD_B_PRId8			"d"
#define _HAIKU_BUILD_B_PRIi8			"i"
#define _HAIKU_BUILD_B_PRId16			"d"
#define _HAIKU_BUILD_B_PRIi16			"i"
#define _HAIKU_BUILD_B_PRId32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "d"
#define _HAIKU_BUILD_B_PRIi32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "i"
#define _HAIKU_BUILD_B_PRId64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "d"
#define _HAIKU_BUILD_B_PRIi64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "i"
#define _HAIKU_BUILD_B_PRIu8			"u"
#define _HAIKU_BUILD_B_PRIo8			"o"
#define _HAIKU_BUILD_B_PRIx8			"x"
#define _HAIKU_BUILD_B_PRIX8			"X"
#define _HAIKU_BUILD_B_PRIu16			"u"
#define _HAIKU_BUILD_B_PRIo16			"o"
#define _HAIKU_BUILD_B_PRIx16			"x"
#define _HAIKU_BUILD_B_PRIX16			"X"
#define _HAIKU_BUILD_B_PRIu32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "u"
#define _HAIKU_BUILD_B_PRIo32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "o"
#define _HAIKU_BUILD_B_PRIx32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "x"
#define _HAIKU_BUILD_B_PRIX32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "X"
#define _HAIKU_BUILD_B_PRIu64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "u"
#define _HAIKU_BUILD_B_PRIo64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "o"
#define _HAIKU_BUILD_B_PRIx64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "x"
#define _HAIKU_BUILD_B_PRIX64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "X"

#define _HAIKU_BUILD_B_SCNd8			"hhd"
#define _HAIKU_BUILD_B_SCNi8			"hhi"
#define _HAIKU_BUILD_B_SCNd16			"hd"
#define _HAIKU_BUILD_B_SCNi16			"hi"
#define _HAIKU_BUILD_B_SCNd32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "d"
#define _HAIKU_BUILD_B_SCNi32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "i"
#define _HAIKU_BUILD_B_SCNd64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "d"
#define _HAIKU_BUILD_B_SCNi64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "i"
#define _HAIKU_BUILD_B_SCNu8			"hhu"
#define _HAIKU_BUILD_B_SCNo8			"hho"
#define _HAIKU_BUILD_B_SCNx8			"hhx"
#define _HAIKU_BUILD_B_SCNu16			"hu"
#define _HAIKU_BUILD_B_SCNo16			"ho"
#define _HAIKU_BUILD_B_SCNx16			"hx"
#define _HAIKU_BUILD_B_SCNu32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "u"
#define _HAIKU_BUILD_B_SCNo32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "o"
#define _HAIKU_BUILD_B_SCNx32			__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "x"
#define _HAIKU_BUILD_B_SCNu64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "u"
#define _HAIKU_BUILD_B_SCNo64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "o"
#define _HAIKU_BUILD_B_SCNx64			__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "x"

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
	_HAIKU_BUILD_DECLARE_VARIABLE(const char*, B_EMPTY_STRING)
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

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
/* fixed-size integer types */
	typedef	_haiku_build_int8					int8;
	typedef _haiku_build_uint8					uint8;
	typedef	_haiku_build_int16					int16;
	typedef _haiku_build_uint16					uint16;
	typedef	_haiku_build_int32					int32;
	typedef _haiku_build_uint32					uint32;
	typedef	_haiku_build_int64					int64;
	typedef _haiku_build_uint64					uint64;

/* shorthand types */
	typedef volatile _haiku_build_vint8			vint8;
	typedef volatile _haiku_build_vuint8		vuint8;
	typedef volatile _haiku_build_vint16		vint16;
	typedef volatile _haiku_build_vuint16		vuint16;
	typedef volatile _haiku_build_vint32		vint32;
	typedef volatile _haiku_build_vuint32		vuint32;
	typedef volatile _haiku_build_vint64		vint64;
	typedef volatile _haiku_build_vuint64		vuint64;

/* NOTE: #8730	Just to make sure, are these not needed?
				Are the libroot versions correct?		*/
//	typedef volatile _haiku_build_vlong				vlong;
//	typedef volatile _haiku_build_vint				vint;
//	typedef volatile _haiku_build_vshort			vshort;
//	typedef volatile _haiku_build_vchar				vchar;
//
//	typedef volatile unsigned _haiku_build_vulong	vulong;
//	typedef volatile unsigned _haiku_build_vuint	vuint;
//	typedef volatile unsigned _haiku_build_vushort	vushort;
//	typedef volatile unsigned _haiku_build_vuchar	vuchar;
//
//	typedef unsigned _haiku_build_uchar				uchar;
//	typedef unsigned _haiku_build_unichar			unichar;

/* descriptive types */
	typedef _haiku_build_status_t				status_t;
	typedef _haiku_build_bigtime_t				bigtime_t;
	typedef _haiku_build_nanotime_t				nanotime_t;
	typedef _haiku_build_type_code				type_code;
	typedef _haiku_build_perform_code			perform_code;

	typedef _haiku_build_phys_addr_t			phys_addr_t;
	typedef _haiku_build_phys_size_t			phys_size_t;

	typedef _haiku_build_generic_addr_t			generic_addr_t;
	typedef	_haiku_build_generic_size_t			generic_size_t;

/* printf()/scanf() format strings for [u]int* types */
#	define B_PRId8			_HAIKU_BUILD_B_PRId8
#	define B_PRIi8			_HAIKU_BUILD_B_PRIi8
#	define B_PRId16			_HAIKU_BUILD_B_PRId16
#	define B_PRIi16			_HAIKU_BUILD_B_PRIi16
#	define B_PRId32			_HAIKU_BUILD_B_PRId32
#	define B_PRIi32			_HAIKU_BUILD_B_PRId64
#	define B_PRId64			_HAIKU_BUILD_B_PRId64
#	define B_PRIi64			_HAIKU_BUILD_B_PRIi64
#	define B_PRIu8			_HAIKU_BUILD_B_PRIu8
#	define B_PRIo8			_HAIKU_BUILD_B_PRIo8
#	define B_PRIx8			_HAIKU_BUILD_B_PRIx8
#	define B_PRIX8			_HAIKU_BUILD_B_PRIX8
#	define B_PRIu16			_HAIKU_BUILD_B_PRIu16
#	define B_PRIo16			_HAIKU_BUILD_B_PRIo16
#	define B_PRIx16			_HAIKU_BUILD_B_PRIx16
#	define B_PRIX16			_HAIKU_BUILD_B_PRIX16
#	define B_PRIu32			_HAIKU_BUILD_B_PRIu32
#	define B_PRIo32			_HAIKU_BUILD_B_PRIo32
#	define B_PRIx32			_HAIKU_BUILD_B_PRIx32
#	define B_PRIX32			_HAIKU_BUILD_B_PRIX32
#	define B_PRIu64			_HAIKU_BUILD_B_PRIu64
#	define B_PRIo64			_HAIKU_BUILD_B_PRIo64
#	define B_PRIx64			_HAIKU_BUILD_B_PRIx64
#	define B_PRIX64			_HAIKU_BUILD_B_PRIX64

#	define B_SCNd8			_HAIKU_BUILD_B_SCNd8
#	define B_SCNi8			_HAIKU_BUILD_B_SCNi8
#	define B_SCNd16			_HAIKU_BUILD_B_SCNd16
#	define B_SCNi16			_HAIKU_BUILD_B_SCNi16
#	define B_SCNd32			_HAIKU_BUILD_B_SCNd32
#	define B_SCNi32			_HAIKU_BUILD_B_SCNi32
#	define B_SCNd64			_HAIKU_BUILD_B_SCNd64
#	define B_SCNi64			_HAIKU_BUILD_B_SCNi64
#	define B_SCNu8			_HAIKU_BUILD_B_SCNu8
#	define B_SCNo8			_HAIKU_BUILD_B_SCNo8
#	define B_SCNx8			_HAIKU_BUILD_B_SCNx8
#	define B_SCNu16			_HAIKU_BUILD_B_SCNu16
#	define B_SCNo16			_HAIKU_BUILD_B_SCNo16
#	define B_SCNx16			_HAIKU_BUILD_B_SCNx16
#	define B_SCNu32			_HAIKU_BUILD_B_SCNu32
#	define B_SCNo32			_HAIKU_BUILD_B_SCNo32
#	define B_SCNx32			_HAIKU_BUILD_B_SCNx32
#	define B_SCNu64			_HAIKU_BUILD_B_SCNu64
#	define B_SCNo64			_HAIKU_BUILD_B_SCNo64
#	define B_SCNx64			_HAIKU_BUILD_B_SCNx64

/* printf() format strings for some standard types */
/* size_t */
#	define B_PRIuSIZE		_HAIKU_BUILD_B_PRIuSIZE
#	define B_PRIoSIZE		_HAIKU_BUILD_B_PRIoSIZE
#	define B_PRIxSIZE		_HAIKU_BUILD_B_PRIxSIZE
#	define B_PRIXSIZE		_HAIKU_BUILD_B_PRIXSIZE
/* ssize_t */
#	define B_PRIdSSIZE		_HAIKU_BUILD_B_PRIdSSIZE
#	define B_PRIiSSIZE		_HAIKU_BUILD_B_PRIiSSIZE
/* addr_t */
#	define B_PRIuADDR		_HAIKU_BUILD_B_PRIuADDR
#	define B_PRIoADDR		_HAIKU_BUILD_B_PRIoADDR
#	define B_PRIxADDR		_HAIKU_BUILD_B_PRIxADDR
#	define B_PRIXADDR		_HAIKU_BUILD_B_PRIXADDR
/* phys_addr_t */
#	define B_PRIuPHYSADDR	_HAIKU_BUILD_B_PRIuPHYSADDR
#	define B_PRIoPHYSADDR	_HAIKU_BUILD_B_PRIoPHYSADDR
#	define B_PRIxPHYSADDR	_HAIKU_BUILD_B_PRIxPHYSADDR
#	define B_PRIXPHYSADDR	_HAIKU_BUILD_B_PRIXPHYSADDR
/* generic_addr_t */
#	define B_PRIuGENADDR	_HAIKU_BUILD_B_PRIuGENADDR
#	define B_PRIoGENADDR	_HAIKU_BUILD_B_PRIoGENADDR
#	define B_PRIxGENADDR	_HAIKU_BUILD_B_PRIxGENADDR
#	define B_PRIXGENADDR	_HAIKU_BUILD_B_PRIXGENADDR
/* off_t */
#	define B_PRIdOFF		_HAIKU_BUILD_B_PRIdOFF
#	define B_PRIiOFF		_HAIKU_BUILD_B_PRIiOFF
/* dev_t */
#	define B_PRIdDEV		_HAIKU_BUILD_B_PRIdDEV
#	define B_PRIiDEV		_HAIKU_BUILD_B_PRIiDEV
/* ino_t */
#	define B_PRIdINO		_HAIKU_BUILD_B_PRIdINO
#	define B_PRIiINO		_HAIKU_BUILD_B_PRIiINO
/* time_t */
#	define B_PRIdTIME		_HAIKU_BUILD_B_PRIdTIME
#	define B_PRIiTIME		_HAIKU_BUILD_B_PRIiTIME

/* min and max comparisons */
#	ifndef __cplusplus
#		ifdef _haiku_build_min
#			define min(a,b) _haiku_build_min(a,b)
#		endif
#		ifdef _haiku_build_max
#			define max(a,b) _haiku_build_max(a,b)
#		endif
#	endif

/* min() and max() are functions in C++ */
#	define min_c(a,b) _haiku_build_min_c(a,b)
#	define max_c(a,b) _haiku_build_max_c(a,b)


/* Obsolete or discouraged API */

/* use 'true' and 'false' */
#	ifdef _HAIKU_BUILD_FALSE
#		define FALSE	_HAIKU_BUILD_FALSE
#	endif
#	ifdef _HAIKU_BUILD_TRUE
#		define TRUE		_HAIKU_BUILD_TRUE
#	endif

#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#endif	/* _SUPPORT_DEFS_H */
