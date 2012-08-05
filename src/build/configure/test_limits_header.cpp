/*
 * Copyright 2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#include <limits.h>
#include <stdio.h>


#define TO_STRING(x) #x
#define PRINT_MACRO(x) \
	printf("#define _HAIKU_BUILD_FEATURE_" #x " %s\n", TO_STRING(x))


int
main()
{
	// NOTE: #8730 -- these are the combined definitions from
	// /boot/develop/abi/x86/gcc2/tools/gcc-2.95.3-haiku-111122/lib/gcc-lib/\
	//		i586-pc-haiku/2.95.3-haiku-111122/include/limits.h
	// /boot/develop/abi/x86/gcc4/tools/gcc-4.6.2-haiku-120121/lib/gcc/\
	//		i586-pc-haiku/4.6.2/install-tools/include/limits.h
	// sed -n -e '/\define[^d]/p' limits.h  | sed -e 's/\#//' \
	//		| awk '{ print "\tPRINT_MACRO\("$2"\);"}' | sort -u > defs.cpp
	PRINT_MACRO(__INT_MAX__);
	PRINT_MACRO(__LONG_LONG_MAX__);
	PRINT_MACRO(__LONG_MAX__);
	PRINT_MACRO(_LIMITS_H___);
	PRINT_MACRO(_MACH_MACHLIMITS_H_);
	PRINT_MACRO(CHAR_BIT);
	PRINT_MACRO(CHAR_MAX);
	PRINT_MACRO(CHAR_MIN);
	PRINT_MACRO(INT_MAX);
	PRINT_MACRO(INT_MIN);
	PRINT_MACRO(LLONG_MAX);
	PRINT_MACRO(LLONG_MIN);
	PRINT_MACRO(LONG_LONG_MAX);
	PRINT_MACRO(LONG_LONG_MIN);
	PRINT_MACRO(LONG_MAX);
	PRINT_MACRO(LONG_MIN);
	PRINT_MACRO(MB_LEN_MAX);
	PRINT_MACRO(SCHAR_MAX);
	PRINT_MACRO(SCHAR_MIN);
	PRINT_MACRO(SHRT_MAX);
	PRINT_MACRO(SHRT_MIN);
	PRINT_MACRO(UCHAR_MAX);
	PRINT_MACRO(UINT_MAX);
	PRINT_MACRO(ULLONG_MAX);
	PRINT_MACRO(ULONG_LONG_MAX);
	PRINT_MACRO(ULONG_MAX);
	PRINT_MACRO(USHRT_MAX);

	return 0;
}
