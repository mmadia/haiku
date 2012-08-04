/*
 * Copyright 2003-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _STDINT_H_
#define _STDINT_H_


#include <config_target/target_types.h>


/* Exact-width integer types */
typedef __haiku_build_haiku_std_int8	_haiku_build_int8_t;
typedef __haiku_build_haiku_std_uint8	_haiku_build_uint8_t;

typedef __haiku_build_haiku_std_int16	_haiku_build_int16_t;
typedef __haiku_build_haiku_std_uint16	_haiku_build_uint16_t;

typedef __haiku_build_haiku_std_int32	_haiku_build_int32_t;
typedef __haiku_build_haiku_std_uint32	_haiku_build_uint32_t;

typedef __haiku_build_haiku_std_int64	_haiku_build_int64_t;
typedef __haiku_build_haiku_std_uint64	_haiku_build_uint64_t;

/* Minimum-width integer types */
typedef __haiku_build_int8_t			_haiku_build_int_least8_t;
typedef __haiku_build_uint8_t			_haiku_build_uint_least8_t;

typedef __haiku_build_int16_t			_haiku_build_int_least16_t;
typedef __haiku_build_uint16_t			_haiku_build_uint_least16_t;

typedef __haiku_build_int32_t			_haiku_build_int_least32_t;
typedef __haiku_build_uint32_t			_haiku_build_uint_least32_t;

typedef __haiku_build_int64_t			_haiku_build_int_least64_t;
typedef __haiku_build_uint64_t			_haiku_build_uint_least64_t;

/* Fastest minimum-width integer types */
typedef __haiku_build_int32_t			_haiku_build_int_fast8_t;
typedef __haiku_build_uint32_t			_haiku_build_uint_fast8_t;

typedef __haiku_build_int32_t			_haiku_build_int_fast16_t;
typedef __haiku_build_uint32_t			_haiku_build_uint_fast16_t;

typedef __haiku_build_int32_t			_haiku_build_int_fast32_t;
typedef __haiku_build_uint32_t			_haiku_build_uint_fast32_t;

typedef __haiku_build_int64_t			_haiku_build_int_fast64_t;
typedef __haiku_build_uint64_t			_haiku_build_uint_fast64_t;

/* Integer types capable of holding object pointers */
typedef __haiku_build_haiku_saddr_t		_haiku_build_intptr_t;
typedef __haiku_build_haiku_addr_t		_haiku_build_uintptr_t;

/* Greatest-width integer types */
typedef __haiku_build_int64_t			_haiku_build_intmax_t;
typedef __haiku_build_uint64_t			_haiku_build_uintmax_t;

/* Limits of exact-width integer types */
#define _HAIKU_BUILD_INT8_MIN			(-128)
#define _HAIKU_BUILD_INT8_MAX			(127)
#define _HAIKU_BUILD_UINT8_MAX			(255U)

#define _HAIKU_BUILD_INT16_MIN			(-32768)
#define _HAIKU_BUILD_INT16_MAX			(32767)
#define _HAIKU_BUILD_UINT16_MAX			(65535U)

#define _HAIKU_BUILD_INT32_MAX			(2147483647)
#define _HAIKU_BUILD_INT32_MIN			(-INT32_MAX-1)
#define _HAIKU_BUILD_UINT32_MAX			(4294967295U)

#define _HAIKU_BUILD_INT64_MAX			(9223372036854775807LL)
#define _HAIKU_BUILD_INT64_MIN			(-INT64_MAX-1)
#define _HAIKU_BUILD_UINT64_MAX			(18446744073709551615ULL)

/* Limits of minimum-width integer types */
#define _HAIKU_BUILD_INT_LEAST8_MIN		INT8_MIN
#define _HAIKU_BUILD_INT_LEAST8_MAX		INT8_MAX
#define _HAIKU_BUILD_UINT_LEAST8_MAX	UINT8_MAX

#define _HAIKU_BUILD_INT_LEAST16_MIN	INT16_MIN
#define _HAIKU_BUILD_INT_LEAST16_MAX	INT16_MAX
#define _HAIKU_BUILD_UINT_LEAST16_MAX	UINT16_MAX

#define _HAIKU_BUILD_INT_LEAST32_MIN	INT32_MIN
#define _HAIKU_BUILD_INT_LEAST32_MAX	INT32_MAX
#define _HAIKU_BUILD_UINT_LEAST32_MAX	UINT32_MAX

#define _HAIKU_BUILD_INT_LEAST64_MIN	INT64_MIN
#define _HAIKU_BUILD_INT_LEAST64_MAX	INT64_MAX
#define _HAIKU_BUILD_UINT_LEAST64_MAX	UINT64_MAX

/* Limits of fastest minimum-width integer types */
#define _HAIKU_BUILD_INT_FAST8_MIN 		INT8_MIN
#define _HAIKU_BUILD_INT_FAST8_MAX 		INT8_MAX
#define _HAIKU_BUILD_UINT_FAST8_MAX		UINT8_MAX

#define _HAIKU_BUILD_INT_FAST16_MIN		INT16_MIN
#define _HAIKU_BUILD_INT_FAST16_MAX		INT16_MAX
#define _HAIKU_BUILD_UINT_FAST16_MAX	UINT16_MAX

#define _HAIKU_BUILD_INT_FAST32_MIN		INT32_MIN
#define _HAIKU_BUILD_INT_FAST32_MAX		INT32_MAX
#define _HAIKU_BUILD_UINT_FAST32_MAX	UINT32_MAX

#define _HAIKU_BUILD_INT_FAST64_MIN		INT64_MIN
#define _HAIKU_BUILD_INT_FAST64_MAX		INT64_MAX
#define _HAIKU_BUILD_UINT_FAST64_MAX	UINT64_MAX

/* Limits of Integer types capable of holding object pointers */
#define _HAIKU_BUILD_INTPTR_MIN			__HAIKU_SADDR_MIN
#define _HAIKU_BUILD_INTPTR_MAX			__HAIKU_SADDR_MAX
#define _HAIKU_BUILD_UINTPTR_MAX		__HAIKU_ADDR_MAX

/* Limits of Greatest-width integer types */
#define _HAIKU_BUILD_INTMAX_MIN			INT64_MIN
#define _HAIKU_BUILD_INTMAX_MAX			INT64_MAX
#define _HAIKU_BUILD_UINTMAX_MAX		UINT64_MAX

/* Limits of other integer types */
#define _HAIKU_BUILD_PTDIFF_MIN			__HAIKU_SADDR_MIN
#define _HAIKU_BUILD_PTDIFF_MAX			__HAIKU_SADDR_MAX

#define _HAIKU_BUILD_SIG_ATOMIC_MIN		INT32_MIN
#define _HAIKU_BUILD_SIG_ATOMIC_MAX		INT32_MAX

#define _HAIKU_BUILD_SIZE_MAX			__HAIKU_ADDR_MAX

#define _HAIKU_BUILD_WINT_MIN			0
#define _HAIKU_BUILD_WINT_MAX			((wint_t)-1)


#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)

/* Macros of Integer Constant Expressions */
#define _HAIKU_BUILD_INT8_C(value)		value
#define _HAIKU_BUILD_INT16_C(value)		value
#define _HAIKU_BUILD_INT32_C(value)		value
#define _HAIKU_BUILD_INT64_C(value)		value ## LL

#define _HAIKU_BUILD_UINT8_C(value)		value ## U
#define _HAIKU_BUILD_UINT16_C(value)	value ## U
#define _HAIKU_BUILD_UINT32_C(value)	value ## U
#define _HAIKU_BUILD_UINT64_C(value)	value ## ULL

/* Macros for greatest-width integer constant expressions */
#define _HAIKU_BUILD_INTMAX_C(value)	value ## LL
#define _HAIKU_BUILD_UINTMAX_C(value)	value ## ULL

#endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */


/* BSD compatibility */
typedef __haiku_build_uint8_t	u_int8_t;
typedef __haiku_build_uint16_t	u_int16_t;
typedef __haiku_build_uint32_t	u_int32_t;
typedef __haiku_build_uint64_t	u_int64_t;

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
/* Exact-width integer types */
	typedef _haiku_build_int8_t				int8_t;
	typedef _haiku_build_uint8_t			uint8_t;

	typedef _haiku_build_int16_t			int16_t;
	typedef _haiku_build_uint16_t			uint16_t;

	typedef _haiku_build_int32_t			int32_t;
	typedef _haiku_build_uint32_t			uint32_t;

	typedef _haiku_build_int64_t			int64_t;
	typedef _haiku_build_uint64_t			uint64_t;

/* Minimum-width integer types */
	typedef _haiku_build_int_least8_t		int_least8_t;
	typedef _haiku_build_uint_least8_t		uint_least8_t;

	typedef _haiku_build_int_least16_t		int_least16_t;
	typedef _haiku_build_uint_least16_t		uint_least16_t;

	typedef _haiku_build_int_least32_t		int_least32_t;
	typedef _haiku_build_uint_least32_t		uint_least32_t;

	typedef _haiku_build_int_least64_t		int_least64_t;
	typedef _haiku_build_uint_least64_t		uint_least64_t;

/* Fastest minimum-width integer types */
	typedef _haiku_build_int_fast8_t		int_fast8_t;
	typedef _haiku_build_uint_fast8_t		uint_fast8_t;

	typedef _haiku_build_int_fast16_t		int_fast16_t;
	typedef _haiku_build_uint_fast16_t		uint_fast16_t;

	typedef _haiku_build_int_fast32_t		int_fast32_t;
	typedef _haiku_build_uint_fast32_t		uint_fast32_t;

	typedef _haiku_build_int_fast64_t		int_fast64_t;
	typedef _haiku_build_uint_fast64_t		uint_fast64_t;

/* Integer types capable of holding object pointers */
	typedef _haiku_build_intptr_t			intptr_t;
	typedef _haiku_build_uintptr_t			uintptr_t;

/* Greatest-width integer types */
	typedef _haiku_build_intmax_t			intmax_t;
	typedef _haiku_build_uintmax_t			uintmax_t;

/* Limits of exact-width integer types */
#	define INT8_MIN				_HAIKU_BUILD_INT8_MIN
#	define INT8_MAX				_HAIKU_BUILD_INT8_MAX
#	define UINT8_MAX			_HAIKU_BUILD_UINT8_MAX

#	define INT16_MIN			_HAIKU_BUILD_INT16_MIN
#	define INT16_MAX			_HAIKU_BUILD_INT16_MAX
#	define UINT16_MAX			_HAIKU_BUILD_UINT16_MAX

#	define INT32_MAX			_HAIKU_BUILD_INT32_MAX
#	define INT32_MIN			_HAIKU_BUILD_INT32_MIN
#	define UINT32_MAX			_HAIKU_BUILD_UINT32_MAX

#	define INT64_MAX			_HAIKU_BUILD_INT64_MAX
#	define INT64_MIN			_HAIKU_BUILD_INT64_MIN
#	define UINT64_MAX			_HAIKU_BUILD_UINT64_MAX

/* Limits of minimum-width integer types */
#	define INT_LEAST8_MIN		_HAIKU_BUILD_INT_LEAST8_MIN
#	define INT_LEAST8_MAX		_HAIKU_BUILD_INT_LEAST8_MAX
#	define UINT_LEAST8_MAX		_HAIKU_BUILD_UINT_LEAST8_MAX

#	define INT_LEAST16_MIN		_HAIKU_BUILD_INT_LEAST16_MIN
#	define INT_LEAST16_MAX		_HAIKU_BUILD_INT_LEAST16_MAX
#	define UINT_LEAST16_MAX		_HAIKU_BUILD_UINT_LEAST16_MAX

#	define INT_LEAST32_MIN		_HAIKU_BUILD_INT_LEAST32_MIN
#	define INT_LEAST32_MAX		_HAIKU_BUILD_INT_LEAST32_MAX
#	define UINT_LEAST32_MAX		_HAIKU_BUILD_UINT_LEAST32_MAX

#	define INT_LEAST64_MIN		_HAIKU_BUILD_INT_LEAST64_MIN
#	define INT_LEAST64_MAX		_HAIKU_BUILD_INT_LEAST64_MAX
#	define UINT_LEAST64_MAX		_HAIKU_BUILD_UINT_LEAST64_MAX

/* Limits of fastest minimum-width integer types */
#	define INT_FAST8_MIN		_HAIKU_BUILD_INT_FAST8_MIN
#	define INT_FAST8_MAX		_HAIKU_BUILD_INT_FAST8_MAX
#	define UINT_FAST8_MAX		_HAIKU_BUILD_UINT_FAST8_MAX

#	define INT_FAST16_MIN		_HAIKU_BUILD_INT_FAST16_MIN
#	define INT_FAST16_MAX		_HAIKU_BUILD_INT_FAST16_MAX
#	define UINT_FAST16_MAX		_HAIKU_BUILD_UINT_FAST16_MAX

#	define INT_FAST32_MIN		_HAIKU_BUILD_INT_FAST32_MIN
#	define INT_FAST32_MAX		_HAIKU_BUILD_INT_FAST32_MAX
#	define UINT_FAST32_MAX		_HAIKU_BUILD_UINT_FAST32_MAX

#	define INT_FAST64_MIN		_HAIKU_BUILD_INT_FAST64_MIN
#	define INT_FAST64_MAX		_HAIKU_BUILD_INT_FAST64_MAX
#	define UINT_FAST64_MAX		_HAIKU_BUILD_UINT_FAST64_MAX

/* Limits of Integer types capable of holding object pointers */
#	define INTPTR_MIN			_HAIKU_BUILD_INTPTR_MIN
#	define INTPTR_MAX			_HAIKU_BUILD_INTPTR_MAX
#	define UINTPTR_MAX			_HAIKU_BUILD_UINTPTR_MAX

/* Limits of Greatest-width integer types */
#	define INTMAX_MIN			_HAIKU_BUILD_INTMAX_MIN
#	define INTMAX_MAX			_HAIKU_BUILD_INTMAX_MAX
#	define UINTMAX_MAX			_HAIKU_BUILD_UINTMAX_MAX

/* Limits of other integer types */
#	define PTDIFF_MIN			_HAIKU_BUILD_PTDIFF_MIN
#	define PTDIFF_MAX			_HAIKU_BUILD_PTDIFF_MAX

#	define SIG_ATOMIC_MIN		_HAIKU_BUILD_SIG_ATOMIC_MIN
#	define SIG_ATOMIC_MAX		_HAIKU_BUILD_SIG_ATOMIC_MAX

#	define SIZE_MAX				_HAIKU_BUILD_SIZE_MAX

#	define WINT_MIN				_HAIKU_BUILD_WINT_MIN
#	define WINT_MAX				_HAIKU_BUILD_WINT_MAX


#	if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)

/* Macros of Integer Constant Expressions */
#		define INT8_C(value)	_HAIKU_BUILD_INT8_C(value)
#		define INT16_C(value)	_HAIKU_BUILD_INT16_C(value)
#		define INT32_C(value)	_HAIKU_BUILD_INT32_C(value)
#		define INT64_C(value)	_HAIKU_BUILD_INT64_C(value)

#		define UINT8_C(value)	_HAIKU_BUILD_UINT8_C(value)
#		define UINT16_C(value)	_HAIKU_BUILD_UINT16_C(value)
#		define UINT32_C(value)	_HAIKU_BUILD_UINT32_C(value)
#		define UINT64_C(value)	_HAIKU_BUILD_UINT64_C(value)

/* Macros for greatest-width integer constant expressions */
#		define INTMAX_C(value)	_HAIKU_BUILD_INTMAX_C(value)
#		define UINTMAX_C(value)	_HAIKU_BUILD_UINTMAX_C(value)

#	endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */


/* BSD compatibility */
	typedef uint8_t__haiku_build_uint8_t;
	typedef uint16_t	__haiku_build_uint16_t;
	typedef uint32_t	__haiku_build_uint32_t;
	typedef uint64_t	__haiku_build_uint64_t;

#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */


#endif	/* _STDINT_H_ */
