/*
 * Copyright 2002-2012, Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _INTTYPES_H_
#define _INTTYPES_H_


#include <target_stdint.h>

typedef struct {
	_haiku_build_intmax_t quot;	/* quotient */
	_haiku_build_intmax_t rem;	/* remainder */
} _HAIKU_BUILD_IDENTIFIER(imaxdiv_t);

// NOTE: #8730 does __STDC_FORMAT_MACROS need to be _HAIKU_BUILD_ prefixed?
#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)
/* fprintf() macros for signed integers */
#	define _HAIKU_BUILD_PRId8			"d"
#	define _HAIKU_BUILD_PRIdLEAST8		"d"
#	define _HAIKU_BUILD_PRIdFAST8		"d"
#	define _HAIKU_BUILD_PRIi8			"i"
#	define _HAIKU_BUILD_PRIiLEAST8		"i"
#	define _HAIKU_BUILD_PRIiFAST8		"i"

#	define _HAIKU_BUILD_PRId16			"d"
#	define _HAIKU_BUILD_PRIdLEAST16		"d"
#	define _HAIKU_BUILD_PRIdFAST16		"d"
#	define _HAIKU_BUILD_PRIi16			"i"
#	define _HAIKU_BUILD_PRIiLEAST16		"i"
#	define _HAIKU_BUILD_PRIiFAST16		"i"

#	define _HAIKU_BUILD_PRId32			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "d"
#	define _HAIKU_BUILD_PRIdLEAST32		_HAIKU_BUILD_PRId32
#	define _HAIKU_BUILD_PRIdFAST32		_HAIKU_BUILD_PRId32
#	define _HAIKU_BUILD_PRIi32			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "i"
#	define _HAIKU_BUILD_PRIiLEAST32		_HAIKU_BUILD_PRIi32
#	define _HAIKU_BUILD_PRIiFAST32		_HAIKU_BUILD_PRIi32

#	define _HAIKU_BUILD_PRId64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "d"
#	define _HAIKU_BUILD_PRIdLEAST64		_HAIKU_BUILD_PRId64
#	define _HAIKU_BUILD_PRIdFAST64		_HAIKU_BUILD_PRId64
#	define _HAIKU_BUILD_PRIi64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "i"
#	define _HAIKU_BUILD_PRIiLEAST64		_HAIKU_BUILD_PRIi64
#	define _HAIKU_BUILD_PRIiFAST64		_HAIKU_BUILD_PRIi64

#	define _HAIKU_BUILD_PRIdMAX			_HAIKU_BUILD_PRId64
#	define _HAIKU_BUILD_PRIdPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "d"
#	define _HAIKU_BUILD_PRIiMAX			_HAIKU_BUILD_PRIi64
#	define _HAIKU_BUILD_PRIiPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "i"

/* fprintf() macros for unsigned integers */
#	define _HAIKU_BUILD_PRIu8			"u"
#	define _HAIKU_BUILD_PRIuLEAST8		"u"
#	define _HAIKU_BUILD_PRIuFAST8		"u"
#	define _HAIKU_BUILD_PRIo8			"o"
#	define _HAIKU_BUILD_PRIoLEAST8		"o"
#	define _HAIKU_BUILD_PRIoFAST8		"o"
#	define _HAIKU_BUILD_PRIx8			"x"
#	define _HAIKU_BUILD_PRIxLEAST8		"x"
#	define _HAIKU_BUILD_PRIxFAST8		"x"
#	define _HAIKU_BUILD_PRIX8			"X"
#	define _HAIKU_BUILD_PRIXLEAST8		"X"
#	define _HAIKU_BUILD_PRIXFAST8		"X"

#	define _HAIKU_BUILD_PRIu16			"u"
#	define _HAIKU_BUILD_PRIuLEAST16		"u"
#	define _HAIKU_BUILD_PRIuFAST16		"u"
#	define _HAIKU_BUILD_PRIo16			"o"
#	define _HAIKU_BUILD_PRIoLEAST16		"o"
#	define _HAIKU_BUILD_PRIoFAST16		"o"
#	define _HAIKU_BUILD_PRIx16			"x"
#	define _HAIKU_BUILD_PRIxLEAST16		"x"
#	define _HAIKU_BUILD_PRIxFAST16		"x"
#	define _HAIKU_BUILD_PRIX16			"X"
#	define _HAIKU_BUILD_PRIXLEAST16		"X"
#	define _HAIKU_BUILD_PRIXFAST16		"X"

#	define _HAIKU_BUILD_PRIu32			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "u"
#	define _HAIKU_BUILD_PRIuLEAST32		_HAIKU_BUILD_PRIu32
#	define _HAIKU_BUILD_PRIuFAST32		_HAIKU_BUILD_PRIu32
#	define _HAIKU_BUILD_PRIo32			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "o"
#	define _HAIKU_BUILD_PRIoLEAST32		_HAIKU_BUILD_PRIo32
#	define _HAIKU_BUILD_PRIoFAST32		_HAIKU_BUILD_PRIo32
#	define _HAIKU_BUILD_PRIx32			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "x"
#	define _HAIKU_BUILD_PRIxLEAST32		_HAIKU_BUILD_PRIx32
#	define _HAIKU_BUILD_PRIxFAST32		_HAIKU_BUILD_PRIx32
#	define _HAIKU_BUILD_PRIX32			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "X"
#	define _HAIKU_BUILD_PRIXLEAST32		_HAIKU_BUILD_PRIX32
#	define _HAIKU_BUILD_PRIXFAST32		_HAIKU_BUILD_PRIX32

#	define _HAIKU_BUILD_PRIu64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "u"
#	define _HAIKU_BUILD_PRIuLEAST64		_HAIKU_BUILD_PRIu64
#	define _HAIKU_BUILD_PRIuFAST64		_HAIKU_BUILD_PRIu64
#	define _HAIKU_BUILD_PRIo64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "o"
#	define _HAIKU_BUILD_PRIoLEAST64		_HAIKU_BUILD_PRIo64
#	define _HAIKU_BUILD_PRIoFAST64		_HAIKU_BUILD_PRIo64
#	define _HAIKU_BUILD_PRIx64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "x"
#	define _HAIKU_BUILD_PRIxLEAST64		_HAIKU_BUILD_PRIx64
#	define _HAIKU_BUILD_PRIxFAST64		_HAIKU_BUILD_PRIx64
#	define _HAIKU_BUILD_PRIX64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "X"
#	define _HAIKU_BUILD_PRIXLEAST64		_HAIKU_BUILD_PRIX64
#	define _HAIKU_BUILD_PRIXFAST64		_HAIKU_BUILD_PRIX64

#	define _HAIKU_BUILD_PRIuMAX			_HAIKU_BUILD_PRIu64
#	define _HAIKU_BUILD_PRIuPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "u"
#	define _HAIKU_BUILD_PRIoMAX			_HAIKU_BUILD_PRIo64
#	define _HAIKU_BUILD_PRIoPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "o"
#	define _HAIKU_BUILD_PRIxMAX			_HAIKU_BUILD_PRIx64
#	define _HAIKU_BUILD_PRIxPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "x"
#	define _HAIKU_BUILD_PRIXMAX			_HAIKU_BUILD_PRIX64
#	define _HAIKU_BUILD_PRIXPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "X"

/* fscanf() macros for signed integers */
#	define _HAIKU_BUILD_SCNd8 			"hhd"
#	define _HAIKU_BUILD_SCNdLEAST8 		"hhd"
#	define _HAIKU_BUILD_SCNdFAST8 		"d"
#	define _HAIKU_BUILD_SCNi8 			"hhi"
#	define _HAIKU_BUILD_SCNiLEAST8 		"hhi"
#	define _HAIKU_BUILD_SCNiFAST8 		"i"

#	define _HAIKU_BUILD_SCNd16			"hd"
#	define _HAIKU_BUILD_SCNdLEAST16		"hd"
#	define _HAIKU_BUILD_SCNdFAST16		"d"
#	define _HAIKU_BUILD_SCNi16 			"hi"
#	define _HAIKU_BUILD_SCNiLEAST16		"hi"
#	define _HAIKU_BUILD_SCNiFAST16		"i"

#	define _HAIKU_BUILD_SCNd32 			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "d"
#	define _HAIKU_BUILD_SCNdLEAST32		_HAIKU_BUILD_SCNd32
#	define _HAIKU_BUILD_SCNdFAST32		_HAIKU_BUILD_SCNd32
#	define _HAIKU_BUILD_SCNi32 			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "i"
#	define _HAIKU_BUILD_SCNiLEAST32		_HAIKU_BUILD_SCNi32
#	define _HAIKU_BUILD_SCNiFAST32		_HAIKU_BUILD_SCNi32

#	define _HAIKU_BUILD_SCNd64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "d"
#	define _HAIKU_BUILD_SCNdLEAST64		_HAIKU_BUILD_SCNd64
#	define _HAIKU_BUILD_SCNdFAST64		_HAIKU_BUILD_SCNd64
#	define _HAIKU_BUILD_SCNi64 			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "i"
#	define _HAIKU_BUILD_SCNiLEAST64		_HAIKU_BUILD_SCNi64
#	define _HAIKU_BUILD_SCNiFAST64 		_HAIKU_BUILD_SCNi64

#	define _HAIKU_BUILD_SCNdMAX			_HAIKU_BUILD_SCNd64
#	define _HAIKU_BUILD_SCNdPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "d"
#	define _HAIKU_BUILD_SCNiMAX			_HAIKU_BUILD_SCNi64
#	define _HAIKU_BUILD_SCNiPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "i"

/* fscanf() macros for unsigned integers */
#	define _HAIKU_BUILD_SCNu8 			"hhu"
#	define _HAIKU_BUILD_SCNuLEAST8 		"hhu"
#	define _HAIKU_BUILD_SCNuFAST8 		"u"
#	define _HAIKU_BUILD_SCNo8 			"hho"
#	define _HAIKU_BUILD_SCNoLEAST8 		"hho"
#	define _HAIKU_BUILD_SCNoFAST8 		"o"
#	define _HAIKU_BUILD_SCNx8 			"hhx"
#	define _HAIKU_BUILD_SCNxLEAST8 		"hhx"
#	define _HAIKU_BUILD_SCNxFAST8 		"x"

#	define _HAIKU_BUILD_SCNu16			"hu"
#	define _HAIKU_BUILD_SCNuLEAST16		"hu"
#	define _HAIKU_BUILD_SCNuFAST16		"u"
#	define _HAIKU_BUILD_SCNo16			"ho"
#	define _HAIKU_BUILD_SCNoLEAST16		"ho"
#	define _HAIKU_BUILD_SCNoFAST16		"o"
#	define _HAIKU_BUILD_SCNx16			"hx"
#	define _HAIKU_BUILD_SCNxLEAST16		"hx"
#	define _HAIKU_BUILD_SCNxFAST16		"x"

#	define _HAIKU_BUILD_SCNu32 			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "u"
#	define _HAIKU_BUILD_SCNuLEAST32		_HAIKU_BUILD_SCNu32
#	define _HAIKU_BUILD_SCNuFAST32		_HAIKU_BUILD_SCNu32
#	define _HAIKU_BUILD_SCNo32 			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "o"
#	define _HAIKU_BUILD_SCNoLEAST32		_HAIKU_BUILD_SCNo32
#	define _HAIKU_BUILD_SCNoFAST32		_HAIKU_BUILD_SCNo32
#	define _HAIKU_BUILD_SCNx32 			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32 "x"
#	define _HAIKU_BUILD_SCNxLEAST32		_HAIKU_BUILD_SCNx32
#	define _HAIKU_BUILD_SCNxFAST32		_HAIKU_BUILD_SCNx32

#	define _HAIKU_BUILD_SCNu64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "u"
#	define _HAIKU_BUILD_SCNuLEAST64		_HAIKU_BUILD_SCNu64
#	define _HAIKU_BUILD_SCNuFAST64		_HAIKU_BUILD_SCNu64
#	define _HAIKU_BUILD_SCNo64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "o"
#	define _HAIKU_BUILD_SCNoLEAST64		_HAIKU_BUILD_SCNo64
#	define _HAIKU_BUILD_SCNoFAST64		_HAIKU_BUILD_SCNo64
#	define _HAIKU_BUILD_SCNx64			_HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64 "x"
#	define _HAIKU_BUILD_SCNxLEAST64		_HAIKU_BUILD_SCNx64
#	define _HAIKU_BUILD_SCNxFAST64		_HAIKU_BUILD_SCNx64

#	define _HAIKU_BUILD_SCNuMAX			_HAIKU_BUILD_SCNu64
#	define _HAIKU_BUILD_SCNuPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "u"
#	define _HAIKU_BUILD_SCNoMAX			_HAIKU_BUILD_SCNo64
#	define _HAIKU_BUILD_SCNoPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "o"
#	define _HAIKU_BUILD_SCNxMAX			_HAIKU_BUILD_SCNx64
#	define _HAIKU_BUILD_SCNxPTR			_HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR "x"

#	ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
/* fprintf() macros for signed integers */
#		define PRId8					_HAIKU_BUILD_PRId8
#		define PRIdLEAST8				_HAIKU_BUILD_PRIdLEAST8
#		define PRIdFAST8				_HAIKU_BUILD_PRIdFAST8
#		define PRIi8					_HAIKU_BUILD_PRIi8
#		define PRIiLEAST8				_HAIKU_BUILD_PRIiLEAST8
#		define PRIiFAST8				_HAIKU_BUILD_PRIiFAST8

#		define PRId16					_HAIKU_BUILD_PRId16
#		define PRIdLEAST16				_HAIKU_BUILD_PRIdLEAST16
#		define PRIdFAST16				_HAIKU_BUILD_PRIdFAST16
#		define PRIi16					_HAIKU_BUILD_PRIi16
#		define PRIiLEAST16				_HAIKU_BUILD_PRIiLEAST16
#		define PRIiFAST16				_HAIKU_BUILD_PRIiFAST16

#		define PRId32					_HAIKU_BUILD_PRId32
#		define PRIdLEAST32				_HAIKU_BUILD_PRIdLEAST32
#		define PRIdFAST32				_HAIKU_BUILD_PRIdFAST32
#		define PRIi32					_HAIKU_BUILD_PRIi32
#		define PRIiLEAST32				_HAIKU_BUILD_PRIiLEAST32
#		define PRIiFAST32				_HAIKU_BUILD_PRIiFAST32

#		define PRId64					_HAIKU_BUILD_PRId64
#		define PRIdLEAST64				_HAIKU_BUILD_PRIdLEAST64
#		define PRIdFAST64				_HAIKU_BUILD_PRIdFAST64
#		define PRIi64					_HAIKU_BUILD_PRIi64
#		define PRIiLEAST64				_HAIKU_BUILD_PRIiLEAST64
#		define PRIiFAST64				_HAIKU_BUILD_PRIiFAST64

#		define PRIdMAX					_HAIKU_BUILD_PRIdMAX
#		define PRIdPTR					_HAIKU_BUILD_PRIdPTR
#		define PRIiMAX					_HAIKU_BUILD_PRIiMAX
#		define PRIiPTR					_HAIKU_BUILD_PRIiPTR

/*	fprintf() macros for unsigned integers */
#		define PRIu8					_HAIKU_BUILD_PRIu8
#		define PRIuLEAST8				_HAIKU_BUILD_PRIuLEAST8
#		define PRIuFAST8				_HAIKU_BUILD_PRIuFAST8
#		define PRIo8					_HAIKU_BUILD_PRIo8
#		define PRIoLEAST8				_HAIKU_BUILD_PRIoLEAST8
#		define PRIoFAST8				_HAIKU_BUILD_PRIoFAST8
#		define PRIx8					_HAIKU_BUILD_PRIx8
#		define PRIxLEAST8				_HAIKU_BUILD_PRIxLEAST8
#		define PRIxFAST8				_HAIKU_BUILD_PRIxFAST8
#		define PRIX8					_HAIKU_BUILD_PRIX8
#		define PRIXLEAST8				_HAIKU_BUILD_PRIXLEAST8
#		define PRIXFAST8				_HAIKU_BUILD_PRIXFAST8

#		define PRIu16					_HAIKU_BUILD_PRIu16
#		define PRIuLEAST16				_HAIKU_BUILD_PRIuLEAST16
#		define PRIuFAST16				_HAIKU_BUILD_PRIuFAST16
#		define PRIo16					_HAIKU_BUILD_PRIo16
#		define PRIoLEAST16				_HAIKU_BUILD_PRIoLEAST16
#		define PRIoFAST16				_HAIKU_BUILD_PRIoFAST16
#		define PRIx16					_HAIKU_BUILD_PRIx16
#		define PRIxLEAST16				_HAIKU_BUILD_PRIxLEAST16
#		define PRIxFAST16				_HAIKU_BUILD_PRIxFAST16
#		define PRIX16					_HAIKU_BUILD_PRIX16
#		define PRIXLEAST16				_HAIKU_BUILD_PRIXLEAST16
#		define PRIXFAST16				_HAIKU_BUILD_PRIXFAST16

#		define PRIu32					_HAIKU_BUILD_PRIu32
#		define PRIuLEAST32				_HAIKU_BUILD_PRIuLEAST32s
#		define PRIuFAST32				_HAIKU_BUILD_PRIuFAST32
#		define PRIo32					_HAIKU_BUILD_PRIo32
#		define PRIoLEAST32				_HAIKU_BUILD_PRIoLEAST32
#		define PRIoFAST32				_HAIKU_BUILD_PRIoFAST32
#		define PRIx32					_HAIKU_BUILD_PRIx32
#		define PRIxLEAST32				_HAIKU_BUILD_PRIxLEAST32
#		define PRIxFAST32				_HAIKU_BUILD_PRIxFAST32
#		define PRIX32					_HAIKU_BUILD_PRIX32
#		define PRIXLEAST32				_HAIKU_BUILD_PRIXLEAST32
#		define PRIXFAST32				_HAIKU_BUILD_PRIXFAST32

#		define PRIu64					_HAIKU_BUILD_PRIu64
#		define PRIuLEAST64				_HAIKU_BUILD_PRIuLEAST64
#		define PRIuFAST64				_HAIKU_BUILD_PRIuFAST64
#		define PRIo64					_HAIKU_BUILD_PRIo64
#		define PRIoLEAST64				_HAIKU_BUILD_PRIoLEAST64
#		define PRIoFAST64				_HAIKU_BUILD_PRIoFAST64
#		define PRIx64					_HAIKU_BUILD_PRIx64
#		define PRIxLEAST64				_HAIKU_BUILD_PRIxLEAST64
#		define PRIxFAST64				_HAIKU_BUILD_PRIxFAST64
#		define PRIX64					_HAIKU_BUILD_PRIX64
#		define PRIXLEAST64				_HAIKU_BUILD_PRIXLEAST64
#		define PRIXFAST64				_HAIKU_BUILD_PRIXFAST64

#		define PRIuMAX					_HAIKU_BUILD_PRIuMAX
#		define PRIuPTR					_HAIKU_BUILD_PRIuPTR
#		define PRIoMAX					_HAIKU_BUILD_PRIoMAX
#		define PRIoPTR					_HAIKU_BUILD_PRIoPTR
#		define PRIxMAX					_HAIKU_BUILD_PRIxMAX
#		define PRIxPTR					_HAIKU_BUILD_PRIxPTR
#		define PRIXMAX					_HAIKU_BUILD_PRIXMAX
#		define PRIXPTR					_HAIKU_BUILD_PRIXPTR

/*	fscanf() macros for signed integers */
#		define SCNd8					_HAIKU_BUILD_SCNd8
#		define SCNdLEAST8				_HAIKU_BUILD_SCNdLEAST8
#		define SCNdFAST8				_HAIKU_BUILD_SCNdFAST8
#		define SCNi8					_HAIKU_BUILD_SCNi8
#		define SCNiLEAST8				_HAIKU_BUILD_SCNiLEAST8
#		define SCNiFAST8				_HAIKU_BUILD_SCNiFAST8

#		define SCNd16					_HAIKU_BUILD_SCNd16
#		define SCNdLEAST16				_HAIKU_BUILD_SCNdLEAST16
#		define SCNdFAST16				_HAIKU_BUILD_SCNdFAST16
#		define SCNi16					_HAIKU_BUILD_SCNi16
#		define SCNiLEAST16				_HAIKU_BUILD_SCNiLEAST16
#		define SCNiFAST16				_HAIKU_BUILD_SCNiFAST16

#		define SCNd32					_HAIKU_BUILD_SCNd32
#		define SCNdLEAST32				_HAIKU_BUILD_SCNdLEAST32
#		define SCNdFAST32				_HAIKU_BUILD_SCNdFAST32
#		define SCNi32					_HAIKU_BUILD_SCNi32
#		define SCNiLEAST32				_HAIKU_BUILD_SCNiLEAST32
#		define SCNiFAST32				_HAIKU_BUILD_SCNiFAST32

#		define SCNd64					_HAIKU_BUILD_SCNd64
#		define SCNdLEAST64				_HAIKU_BUILD_SCNdLEAST64
#		define SCNdFAST64				_HAIKU_BUILD_SCNdFAST64
#		define SCNi64					_HAIKU_BUILD_SCNi64
#		define SCNiLEAST64				_HAIKU_BUILD_SCNiLEAST64
#		define SCNiFAST64				_HAIKU_BUILD_SCNiFAST64

#		define SCNdMAX					_HAIKU_BUILD_SCNdMAX
#		define SCNdPTR					_HAIKU_BUILD_SCNdPTR
#		define SCNiMAX					_HAIKU_BUILD_SCNiMAX
#		define SCNiPTR					_HAIKU_BUILD_SCNiPTR

/* fscanf() macros for unsigned integers */
#		define SCNu8					_HAIKU_BUILD_SCNu8
#		define SCNuLEAST8				_HAIKU_BUILD_SCNuLEAST8
#		define SCNuFAST8				_HAIKU_BUILD_SCNuFAST8
#		define SCNo8					_HAIKU_BUILD_SCNo8
#		define SCNoLEAST8				_HAIKU_BUILD_SCNoLEAST8
#		define SCNoFAST8				_HAIKU_BUILD_SCNoFAST8
#		define SCNx8					_HAIKU_BUILD_SCNx8
#		define SCNxLEAST8				_HAIKU_BUILD_SCNxLEAST8
#		define SCNxFAST8				_HAIKU_BUILD_SCNxFAST8

#		define SCNu16					_HAIKU_BUILD_SCNu16
#		define SCNuLEAST16				_HAIKU_BUILD_SCNuLEAST16
#		define SCNuFAST16				_HAIKU_BUILD_SCNuFAST16
#		define SCNo16					_HAIKU_BUILD_SCNo16
#		define SCNoLEAST16				_HAIKU_BUILD_SCNoLEAST16
#		define SCNoFAST16				_HAIKU_BUILD_SCNoFAST16
#		define SCNx16					_HAIKU_BUILD_SCNx16
#		define SCNxLEAST16				_HAIKU_BUILD_SCNxLEAST16
#		define SCNxFAST16				_HAIKU_BUILD_SCNxFAST16

#		define SCNu32					_HAIKU_BUILD_SCNu32
#		define SCNuLEAST32				_HAIKU_BUILD_SCNuLEAST32
#		define SCNuFAST32				_HAIKU_BUILD_SCNuFAST32
#		define SCNo32					_HAIKU_BUILD_SCNo32
#		define SCNoLEAST32				_HAIKU_BUILD_SCNoLEAST32
#		define SCNoFAST32				_HAIKU_BUILD_SCNoFAST32
#		define SCNx32					_HAIKU_BUILD_SCNx32
#		define SCNxLEAST32				_HAIKU_BUILD_SCNxLEAST32
#		define SCNxFAST32				_HAIKU_BUILD_SCNxFAST32

#		define SCNu64					_HAIKU_BUILD_SCNu64
#		define SCNuLEAST64				_HAIKU_BUILD_SCNuLEAST64
#		define SCNuFAST64				_HAIKU_BUILD_SCNuFAST64
#		define SCNo64					_HAIKU_BUILD_SCNo64
#		define SCNoLEAST64				_HAIKU_BUILD_SCNoLEAST64
#		define SCNoFAST64				_HAIKU_BUILD_SCNoFAST64
#		define SCNx64					_HAIKU_BUILD_SCNx64
#		define SCNxLEAST64				_HAIKU_BUILD_SCNxLEAST64
#		define SCNxFAST64				_HAIKU_BUILD_SCNxFAST64

#		define SCNuMAX					_HAIKU_BUILD_SCNuMAX
#		define SCNuPTR					_HAIKU_BUILD_SCNuPTR
#		define SCNoMAX					_HAIKU_BUILD_SCNoMAX
#		define SCNoPTR					_HAIKU_BUILD_SCNoPTR
#		define SCNxMAX					_HAIKU_BUILD_SCNxMAX
#		define SCNxPTR					_HAIKU_BUILD_SCNxPTR
#	endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */
#endif /* !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) */


#ifdef __cplusplus
extern "C" {
#endif

_haiku_build_intmax_t	_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_intmax_t, \
	imaxabs, (_haiku_build_intmax_t num))
_HAIKU_BUILD_IDENTIFIER(imaxdiv_t)	_HAIKU_BUILD_DECLARE_FUNCTION(\
	_HAIKU_BUILD_IDENTIFIER(imaxdiv_t), _haiku_build_imaxdiv, \
		(_haiku_build_intmax_t numer, _haiku_build_intmax_t denom))

_haiku_build_intmax_t	_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_intmax_t, \
	strtoimax, (const _haiku_build_char *string, _haiku_build_char **_end, \
		_haiku_build_int base))
_haiku_build_uintmax_t	_HAIKU_BUILD_DECLARE_FUNCTION(\
	_haiku_build_uintmax_t, strtoumax, (const _haiku_build_char *string, \
		_haiku_build_char **_end, _haiku_build_int base))
// NOTE: these commented functions may not be updated 100% correctly.
/* _haiku_build_intmax_t	_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_intmax_t, \
	wcstoimax, (const __wchar_t *, __wchar_t **, _haiku_build_int)) */
/* _haiku_build_uintmax_t	_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_uintmax_t, \
	wcstoumax, (const __wchar_t *, __wchar_t **, _haiku_build_int)) */


#ifdef __cplusplus
}
#endif


#endif	/* _INTTYPES_H_ */
