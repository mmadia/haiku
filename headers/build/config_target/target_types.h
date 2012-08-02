/*
 * Copyright 2009-2011, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _CONFIG_TYPES_H
#define _CONFIG_TYPES_H


#include <HaikuBuild.h>

#include <config_target/target_HaikuConfig.h>


/* fixed-width types -- the __haiku_std_[u]int* types correspond to the POSIX
   [u]int*_t types, the _haiku_[u]int* types to the BeOS [u]int* types. If
   __HAIKU_BEOS_COMPATIBLE_TYPES is not defined both sets are identical. Once
   we drop compatibility for good, we can consolidate the types.
*/
typedef _HAIKU_BUILD_FEATURE_int8	__haiku_build_haiku_std_int8;
typedef _HAIKU_BUILD_FEATURE_uint8	__haiku_build_haiku_std_uint8;
typedef _HAIKU_BUILD_FEATURE_int16	__haiku_build_haiku_std_int16;
typedef _HAIKU_BUILD_FEATURE_uint16	__haiku_build_haiku_std_uint16;
typedef _HAIKU_BUILD_FEATURE_int32	__haiku_build_haiku_std_int32;
typedef _HAIKU_BUILD_FEATURE_uint32	__haiku_build_haiku_std_uint32;
typedef _HAIKU_BUILD_FEATURE_int64	__haiku_build_haiku_std_int64;
typedef _HAIKU_BUILD_FEATURE_uint64	__haiku_build_haiku_std_uint64;

typedef __haiku_build_haiku_std_int8	__haiku_build_haiku_int8;
typedef __haiku_build_haiku_std_uint8	__haiku_build_haiku_uint8;
typedef __haiku_build_haiku_std_int16	__haiku_build_haiku_int16;
typedef __haiku_build_haiku_std_uint16	__haiku_build_haiku_uint16;
typedef __haiku_build_haiku_std_int32	__haiku_build_haiku_int32;
typedef __haiku_build_haiku_std_uint32	__haiku_build_haiku_uint32;
typedef __haiku_build_haiku_std_int64	__haiku_build_haiku_int64;
typedef __haiku_build_haiku_std_uint64	__haiku_build_haiku_uint64;

/* address types */
#ifdef __HAIKU_BUILD_HAIKU_ARCH_64_BIT
	typedef	__haiku_build_haiku_int64	__haiku_build_haiku_saddr_t;
	typedef	__haiku_build_haiku_uint64	__haiku_build_haiku_addr_t;
#else
	typedef	__haiku_build_haiku_int32	__haiku_build_haiku_saddr_t;
	typedef	__haiku_build_haiku_uint32	__haiku_build_haiku_addr_t;
#endif

#ifdef __HAIKU_BUILD_HAIKU_ARCH_PHYSICAL_64_BIT
	typedef	__haiku_build_haiku_int64	__haiku_build_haiku_phys_saddr_t;
	typedef	__haiku_build_haiku_uint64	__haiku_build_haiku_phys_addr_t;
#else
	typedef	__haiku_build_haiku_int32	__haiku_build_haiku_phys_saddr_t;
	typedef	__haiku_build_haiku_uint32	__haiku_build_haiku_phys_addr_t;
#endif

/* address type limits */
#ifdef __HAIKU_BUILD_HAIKU_ARCH_64_BIT
#	define __HAIKU_BUILD_HAIKU_SADDR_MAX		(9223372036854775807LL)
#	define __HAIKU_BUILD_HAIKU_ADDR_MAX			(18446744073709551615ULL)
#else
#	define __HAIKU_BUILD_HAIKU_SADDR_MAX		(2147483647)
#	define __HAIKU_BUILD_HAIKU_ADDR_MAX			(4294967295U)
#endif
#define __HAIKU_BUILD_HAIKU_SADDR_MIN		(-__HAIKU_BUILD_HAIKU_SADDR_MAX-1)

#ifdef __HAIKU_BUILD_HAIKU_ARCH_PHYSICAL_64_BIT
#	define __HAIKU_BUILD_HAIKU_PHYS_SADDR_MAX	(9223372036854775807LL)
#	define __HAIKU_BUILD_HAIKU_PHYS_ADDR_MAX	(18446744073709551615ULL)
#else
#	define __HAIKU_BUILD_HAIKU_PHYS_SADDR_MAX	(2147483647)
#	define __HAIKU_BUILD_HAIKU_PHYS_ADDR_MAX	(4294967295U)
#endif
#define __HAIKU_BUILD_HAIKU_PHYS_SADDR_MIN	(-__HAIKU_BUILD_HAIKU_SADDR_MAX-1)


/* printf()/scanf() format prefixes */
#define	__HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32	\
	_HAIKU_BUILD_FEATURE_FORMAT_PREFIX_int32
#define __HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64	\
	_HAIKU_BUILD_FEATURE_FORMAT_PREFIX_int64

#define	__HAIKU_BUILD_HAIKU_PRI_PREFIX_32	\
	__HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32
#define	__HAIKU_BUILD_HAIKU_PRI_PREFIX_64	\
	__HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64

#ifdef __HAIKU_BUILD_HAIKU_ARCH_64_BIT
#	define __HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR	\
		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64
#else
#	define __HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR	\
		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32
#endif

#ifdef __HAIKU_BUILD_HAIKU_ARCH_PHYSICAL_64_BIT
#	define __HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR	\
		__HAIKU_BUILD_HAIKU_PRI_PREFIX_64
#else
#	define __HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR	\
		__HAIKU_BUILD_HAIKU_PRI_PREFIX_32
#endif


/* a generic address type wide enough for virtual and physical addresses */
#if __HAIKU_BUILD_HAIKU_ARCH_BITS >= __HAIKU_BUILD_HAIKU_ARCH_PHYSICAL_BITS
	typedef __haiku_build_haiku_addr_t		__haiku_build_haiku_generic_addr_t;
#	define __HAIKU_BUILD_HAIKU_GENERIC_ADDR_MAX			\
		__HAIKU_BUILD_HAIKU_ADDR_MAX
#	define __HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR	\
		__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR
#else
	typedef __haiku_build_haiku_phys_addr_t	__haiku_build_haiku_generic_addr_t;
#	define __HAIKU_BUILD_HAIKU_GENERIC_ADDR_MAX			\
		__HAIKU_BUILD_HAIKU_PHYS_ADDR_MAX
#	define __HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR	\
		__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR
#endif


/* map the macros/types, if not building the libroot mapper functions */

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER

#define __HAIKU_SADDR_MAX	__HAIKU_BUILD_HAIKU_SADDR_MAX
#define __HAIKU_ADDR_MAX	__HAIKU_BUILD_HAIKU_ADDR_MAX
#define __HAIKU_SADDR_MIN	__HAIKU_BUILD_HAIKU_SADDR_MIN

#define __HAIKU_PHYS_SADDR_MAX	__HAIKU_BUILD_HAIKU_PHYS_SADDR_MAX
#define __HAIKU_PHYS_ADDR_MAX	__HAIKU_BUILD_HAIKU_PHYS_ADDR_MAX
#define __HAIKU_PHYS_SADDR_MIN	__HAIKU_BUILD_HAIKU_PHYS_SADDR_MIN

#define	__HAIKU_STD_PRI_PREFIX_32	__HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_32
#define __HAIKU_STD_PRI_PREFIX_64	__HAIKU_BUILD_HAIKU_STD_PRI_PREFIX_64

#define	__HAIKU_PRI_PREFIX_32	__HAIKU_BUILD_HAIKU_PRI_PREFIX_32
#define	__HAIKU_PRI_PREFIX_64	__HAIKU_BUILD_HAIKU_PRI_PREFIX_64

#define __HAIKU_PRI_PREFIX_ADDR			__HAIKU_BUILD_HAIKU_PRI_PREFIX_ADDR
#define __HAIKU_PRI_PREFIX_PHYS_ADDR	__HAIKU_BUILD_HAIKU_PRI_PREFIX_PHYS_ADDR

#define __HAIKU_GENERIC_ADDR_MAX	__HAIKU_BUILD_HAIKU_GENERIC_ADDR_MAX
#define __HAIKU_PRI_PREFIX_GENERIC_ADDR		\
	__HAIKU_BUILD_HAIKU_PRI_PREFIX_GENERIC_ADDR

#endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#endif	/* _CONFIG_BUILD_TYPES_H */
