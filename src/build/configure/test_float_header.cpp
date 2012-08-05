/*
 * Copyright 2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */


#include <float.h>
#include <stdio.h>


#define TO_STRING(x) #x
#define PRINT_MACRO(x) \
	printf("#define _HAIKU_BUILD_FEATURE_" #x " %s\n", TO_STRING(x))


int
main()
{
	printf("/* float.h */\n");
	PRINT_MACRO(__LDBL_UNION__);
	PRINT_MACRO(DBL_DECIMAL_DIG);
	PRINT_MACRO(DBL_DIG);
	PRINT_MACRO(DBL_EPSILON);
	PRINT_MACRO(DBL_HAS_SUBNORM);
	PRINT_MACRO(DBL_MANT_DIG);
	PRINT_MACRO(DBL_MAX_10_EXP);
	PRINT_MACRO(DBL_MAX_EXP);
	PRINT_MACRO(DBL_MAX);
	PRINT_MACRO(DBL_MIN_10_EXP);
	PRINT_MACRO(DBL_MIN_EXP);
	PRINT_MACRO(DBL_MIN);
	PRINT_MACRO(DBL_TRUE_MIN);
	PRINT_MACRO(DEC_EVAL_METHOD);
	PRINT_MACRO(DEC128_EPSILON);
	PRINT_MACRO(DEC128_MANT_DIG);
	PRINT_MACRO(DEC128_MAX_EXP);
	PRINT_MACRO(DEC128_MAX);
	PRINT_MACRO(DEC128_MIN_EXP);
	PRINT_MACRO(DEC128_MIN);
	PRINT_MACRO(DEC128_SUBNORMAL_MIN);
	PRINT_MACRO(DEC32_EPSILON);
	PRINT_MACRO(DEC32_MANT_DIG);
	PRINT_MACRO(DEC32_MAX_EXP);
	PRINT_MACRO(DEC32_MAX);
	PRINT_MACRO(DEC32_MIN_EXP);
	PRINT_MACRO(DEC32_MIN);
	PRINT_MACRO(DEC32_SUBNORMAL_MIN);
	PRINT_MACRO(DEC64_EPSILON);
	PRINT_MACRO(DEC64_MANT_DIG);
	PRINT_MACRO(DEC64_MAX_EXP);
	PRINT_MACRO(DEC64_MAX);
	PRINT_MACRO(DEC64_MIN_EXP);
	PRINT_MACRO(DEC64_MIN);
	PRINT_MACRO(DEC64_SUBNORMAL_MIN);
	PRINT_MACRO(DECIMAL_DIG);
	PRINT_MACRO(FLT_DECIMAL_DIG);
	PRINT_MACRO(FLT_DIG);
	PRINT_MACRO(FLT_EPSILON);
	PRINT_MACRO(FLT_EVAL_METHOD);
	PRINT_MACRO(FLT_HAS_SUBNORM);
	PRINT_MACRO(FLT_MANT_DIG);
	PRINT_MACRO(FLT_MAX_10_EXP);
	PRINT_MACRO(FLT_MAX_EXP);
	PRINT_MACRO(FLT_MAX);
	PRINT_MACRO(FLT_MIN_10_EXP);
	PRINT_MACRO(FLT_MIN_EXP);
	PRINT_MACRO(FLT_MIN);
	PRINT_MACRO(FLT_RADIX);
	PRINT_MACRO(FLT_ROUNDS);
	PRINT_MACRO(FLT_TRUE_MIN);
	PRINT_MACRO(LDBL_DECIMAL_DIG);
	PRINT_MACRO(LDBL_DIG);
	PRINT_MACRO(LDBL_EPSILON);
	PRINT_MACRO(LDBL_HAS_SUBNORM);
	PRINT_MACRO(LDBL_MANT_DIG);
	PRINT_MACRO(LDBL_MAX_10_EXP);
	PRINT_MACRO(LDBL_MAX_EXP);
	PRINT_MACRO(LDBL_MAX);
	PRINT_MACRO(LDBL_MIN_10_EXP);
	PRINT_MACRO(LDBL_MIN_EXP);
	PRINT_MACRO(LDBL_MIN);
	PRINT_MACRO(LDBL_TRUE_MIN);
	printf("\n");

	return 0;
}
