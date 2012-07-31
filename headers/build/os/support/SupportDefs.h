/*
 * Copyright 2004-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Author:
 *		Erik Jaesler (erik@cgsoftware.com)
 */
#ifndef _HAIKU_BUILD_SUPPORT_DEFS_H
#define _HAIKU_BUILD_SUPPORT_DEFS_H


#include <config_build/types.h>

#include <BeBuild.h>
#include <Errors.h>

#include <inttypes.h>
#include <sys/types.h>


/* fixed-size integer types */
typedef	__haiku_build_haiku_int8			haiku_build_int8;
typedef __haiku_build_haiku_uint8			haiku_build_uint8;
typedef	__haiku_build_haiku_int16			haiku_build_int16;
typedef __haiku_build_haiku_uint16			haiku_build_uint16;
typedef	__haiku_build_haiku_int32			haiku_build_int32;
typedef __haiku_build_haiku_uint32			haiku_build_uint32;
typedef	__haiku_build_haiku_int64			haiku_build_int64;
typedef __haiku_build_haiku_uint64			haiku_build_uint64;

/* shorthand types */
typedef volatile haiku_build_int8   		haiku_build_vint8;
typedef volatile haiku_build_uint8			haiku_build_vuint8;
typedef volatile haiku_build_int16			haiku_build_vint16;
typedef volatile haiku_build_uint16			haiku_build_vuint16;
typedef volatile haiku_build_int32			haiku_build_vint32;
typedef volatile haiku_build_uint32			haiku_build_vuint32;
typedef volatile haiku_build_int64			haiku_build_vint64;
typedef volatile haiku_build_uint64			haiku_build_vuint64;

typedef volatile long			haiku_build_vlong;
typedef volatile int			haiku_build_vint;
typedef volatile short			haiku_build_vshort;
typedef volatile char			haiku_build_vchar;

typedef volatile unsigned long	haiku_build_vulong;
typedef volatile unsigned int	haiku_build_vuint;
typedef volatile unsigned short	haiku_build_vushort;
typedef volatile unsigned char	haiku_build_vuchar;

typedef unsigned char			haiku_build_uchar;
typedef unsigned short          haiku_build_unichar;

/* descriptive types */
typedef haiku_build_int32		haiku_build_status_t;
typedef haiku_build_int64		haiku_build_bigtime_t;
typedef haiku_build_int64		haiku_build_nanotime_t;
typedef haiku_build_uint32		haiku_build_type_code;
typedef haiku_build_uint32		haiku_build_perform_code;

typedef __haiku_build_haiku_phys_addr_t		haiku_build_phys_addr_t;
typedef haiku_build_phys_addr_t				haiku_build_phys_size_t;

typedef	__haiku_build_haiku_generic_addr_t	haiku_build_generic_addr_t;
typedef	haiku_build_generic_addr_t			haiku_build_generic_size_t;


/* printf()/scanf() format strings for [u]int* types */
#define HAIKU_BUILD_B_PRId8			"d"
#define HAIKU_BUILD_B_PRIi8			"i"
#define HAIKU_BUILD_B_PRId16		"d"
#define HAIKU_BUILD_B_PRIi16		"i"
#define HAIKU_BUILD_B_PRId32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "d"
#define HAIKU_BUILD_B_PRIi32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "i"
#define HAIKU_BUILD_B_PRId64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "d"
#define HAIKU_BUILD_B_PRIi64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "i"
#define HAIKU_BUILD_B_PRIu8			"u"
#define HAIKU_BUILD_B_PRIo8			"o"
#define HAIKU_BUILD_B_PRIx8			"x"
#define HAIKU_BUILD_B_PRIX8			"X"
#define HAIKU_BUILD_B_PRIu16		"u"
#define HAIKU_BUILD_B_PRIo16		"o"
#define HAIKU_BUILD_B_PRIx16		"x"
#define HAIKU_BUILD_B_PRIX16		"X"
#define HAIKU_BUILD_B_PRIu32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "u"
#define HAIKU_BUILD_B_PRIo32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "o"
#define HAIKU_BUILD_B_PRIx32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "x"
#define HAIKU_BUILD_B_PRIX32		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "X"
#define HAIKU_BUILD_B_PRIu64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "u"
#define HAIKU_BUILD_B_PRIo64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "o"
#define HAIKU_BUILD_B_PRIx64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "x"
#define HAIKU_BUILD_B_PRIX64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "X"

#define HAIKU_BUILD_B_SCNd8 		"hhd"
#define HAIKU_BUILD_B_SCNi8 		"hhi"
#define HAIKU_BUILD_B_SCNd16		"hd"
#define HAIKU_BUILD_B_SCNi16	 	"hi"
#define HAIKU_BUILD_B_SCNd32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "d"
#define HAIKU_BUILD_B_SCNi32	 	__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "i"
#define HAIKU_BUILD_B_SCNd64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "d"
#define HAIKU_BUILD_B_SCNi64 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "i"
#define HAIKU_BUILD_B_SCNu8 		"hhu"
#define HAIKU_BUILD_B_SCNo8 		"hho"
#define HAIKU_BUILD_B_SCNx8 		"hhx"
#define HAIKU_BUILD_B_SCNu16		"hu"
#define HAIKU_BUILD_B_SCNo16		"ho"
#define HAIKU_BUILD_B_SCNx16		"hx"
#define HAIKU_BUILD_B_SCNu32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "u"
#define HAIKU_BUILD_B_SCNo32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "o"
#define HAIKU_BUILD_B_SCNx32 		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32 "x"
#define HAIKU_BUILD_B_SCNu64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "u"
#define HAIKU_BUILD_B_SCNo64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "o"
#define HAIKU_BUILD_B_SCNx64		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64 "x"

/* printf() format strings for some standard types */
/* size_t */
#define HAIKU_BUILD_B_PRIuSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "u"
#define HAIKU_BUILD_B_PRIoSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "o"
#define HAIKU_BUILD_B_PRIxSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "x"
#define HAIKU_BUILD_B_PRIXSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "X"
/* ssize_t */
#define HAIKU_BUILD_B_PRIdSSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "d"
#define HAIKU_BUILD_B_PRIiSSIZE		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "i"
/* addr_t */
#define HAIKU_BUILD_B_PRIuADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "u"
#define HAIKU_BUILD_B_PRIoADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "o"
#define HAIKU_BUILD_B_PRIxADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "x"
#define HAIKU_BUILD_B_PRIXADDR		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "X"
/* phys_addr_t */
#define HAIKU_BUILD_B_PRIuPHYSADDR	__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "u"
#define HAIKU_BUILD_B_PRIoPHYSADDR	__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "o"
#define HAIKU_BUILD_B_PRIxPHYSADDR	__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "x"
#define HAIKU_BUILD_B_PRIXPHYSADDR	__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR "X"
/* generic_addr_t */
#define HAIKU_BUILD_B_PRIuGENADDR	\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "u"
#define HAIKU_BUILD_B_PRIoGENADDR	\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "o"
#define HAIKU_BUILD_B_PRIxGENADDR	\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "x"
#define HAIKU_BUILD_B_PRIXGENADDR	\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR "X"
/* off_t */
#define HAIKU_BUILD_B_PRIdOFF		HAIKU_BUILD_B_PRId64
#define HAIKU_BUILD_B_PRIiOFF		HAIKU_BUILD_B_PRIi64
/* dev_t */
#define HAIKU_BUILD_B_PRIdDEV		HAIKU_BUILD_B_PRId32
#define HAIKU_BUILD_B_PRIiDEV		HAIKU_BUILD_B_PRIi32
/* ino_t */
#define HAIKU_BUILD_B_PRIdINO		HAIKU_BUILD_B_PRId64
#define HAIKU_BUILD_B_PRIiINO		HAIKU_BUILD_B_PRIi64
/* time_t */
#define HAIKU_BUILD_B_PRIdTIME		HAIKU_BUILD_B_PRId32
#define HAIKU_BUILD_B_PRIiTIME		HAIKU_BUILD_B_PRIi32


/* Empty string ("") */
#ifdef __cplusplus
extern const char *HAIKU_BUILD_B_EMPTY_STRING;
#endif


/* min and max comparisons */
#ifndef __cplusplus
#	ifndef haiku_build_min
#		define haiku_build_min(a,b) ((a)>(b)?(b):(a))
#	endif
#	ifndef haiku_build_max
#		define haiku_build_max(a,b) ((a)>(b)?(a):(b))
#	endif
#endif

/* min() and max() are functions in C++ */
#define haiku_build_min_c(a,b) ((a)>(b)?(b):(a))
#define haiku_build_max_c(a,b) ((a)>(b)?(a):(b))


/* Grandfathering */
#ifndef __cplusplus
#	include <stdbool.h>
#endif

/*
#ifndef HAIKU_BUILD_NULL
#	define HAIKU_BUILD_NULL (0)
#endif
*/


#ifdef __cplusplus
extern "C" {
#endif

/* Atomic functions; previous value is returned */
extern haiku_build_int32	haiku_build_atomic_set(haiku_build_vint32 *value,
								haiku_build_int32 newValue);
extern haiku_build_int32	haiku_build_atomic_test_and_set(
								haiku_build_vint32 *value,
								haiku_build_int32 newValue,
								haiku_build_int32 testAgainst);
extern haiku_build_int32	haiku_build_atomic_add(haiku_build_vint32 *value,
								haiku_build_int32 addValue);
extern haiku_build_int32	haiku_build_atomic_and(haiku_build_vint32 *value,
								haiku_build_int32 andValue);
extern haiku_build_int32	haiku_build_atomic_or(haiku_build_vint32 *value,
								haiku_build_int32 orValue);
extern haiku_build_int32	haiku_build_atomic_get(haiku_build_vint32 *value);

extern haiku_build_int64	haiku_build_atomic_set64(haiku_build_vint64 *value,
								haiku_build_int64 newValue);
extern haiku_build_int64	haiku_build_atomic_test_and_set64(
								haiku_build_vint64 *value,
								haiku_build_int64 newValue,
								haiku_build_int64 testAgainst);
extern haiku_build_int64	haiku_build_atomic_add64(haiku_build_vint64 *value,
								haiku_build_int64 addValue);
extern haiku_build_int64	haiku_build_atomic_and64(haiku_build_vint64 *value,
								haiku_build_int64 andValue);
extern haiku_build_int64	haiku_build_atomic_or64(haiku_build_vint64 *value,
								haiku_build_int64 orValue);
extern haiku_build_int64	haiku_build_atomic_get64(haiku_build_vint64 *value);

/* Other stuff */
extern void*	haiku_build_get_stack_frame(void);

#ifdef __cplusplus
}
#endif

/* Obsolete or discouraged API */

/* use 'true' and 'false' */
#ifndef FALSE
#	define FALSE	0
#endif
#ifndef TRUE
#	define TRUE		1
#endif


/* Use the built-in atomic functions, if requested and available. */

#if defined(HAIKU_BUILD_B_USE_BUILTIN_ATOMIC_FUNCTIONS) && __GNUC__ >= 4

#define haiku_build_atomic_test_and_set(valuePointer, newValue, testAgainst) \
	__sync_val_compare_and_swap(valuePointer, testAgainst, newValue)
#define haiku_build_atomic_add(valuePointer, addValue)	\
	__sync_fetch_and_add(valuePointer, addValue)
#define haiku_build_atomic_and(valuePointer, andValue)	\
	__sync_fetch_and_and(valuePointer, andValue)
#define haiku_build_atomic_or(valuePointer, orValue)	\
	__sync_fetch_and_or(valuePointer, orValue)
#define haiku_build_atomic_get(valuePointer)	\
	__sync_fetch_and_or(valuePointer, 0)
	// No equivalent to atomic_get(). We simulate it via atomic or. On most
	// (all?) 32+ bit architectures aligned 32 bit reads will be atomic anyway,
	// though.

// Note: No equivalent for atomic_set(). It could be simulated by a
// get + atomic test and set loop, but calling the atomic_set() implementation
// might be faster.

#endif	// HAIKU_BUILD_B_USE_BUILTIN_ATOMIC_FUNCTIONS && __GNUC__ >= 4


#endif	/* _HAIKU_BUILD_SUPPORT_DEFS_H */
