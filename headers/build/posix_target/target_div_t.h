/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _DIV_T_H_
#define _DIV_T_H_


typedef struct {
	int	quot;
	int	rem;
} _HAIKU_BUILD_IDENTIFIER(div_t);

typedef struct {
	long quot;
	long rem;
} _HAIKU_BUILD_IDENTIFIER(ldiv_t);

typedef struct {
	long long quot;
	long long rem;
} _HAIKU_BUILD_IDENTIFIER(lldiv_t);

#endif /* _DIV_T_H_ */
