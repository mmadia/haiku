/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _STDLIB_H_
#define _STDLIB_H_


#include <target_alloca.h>
#include <target_div_t.h>
#include <target_limits.h>
#include <sys/target_types.h>
#include <target_wchar_t.h>

#define _HAIKU_BUILD_RAND_MAX		0x7fffffff
#define _HAIKU_BUILD_MB_CUR_MAX		(__ctype_get_mb_cur_max())

#define _HAIKU_BUILD_EXIT_SUCCESS	0
#define _HAIKU_BUILD_EXIT_FAILURE	1

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define RAND_MAX					_HAIKU_BUILD_RAND_MAX
#	define MB_CUR_MAX				_HAIKU_BUILD_MB_CUR_MAX

#	define EXIT_SUCCESS				_HAIKU_BUILD_EXIT_SUCCESS
#	define EXIT_FAILURE				_HAIKU_BUILD_EXIT_FAILURE
#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

/* random data structures (for thread-safe random numbers) */
struct _HAIKU_BUILD_IDENTIFIER(random_data) {
	int *fptr;
	int *rptr;
	int *state;
	int rand_type;
	int rand_deg;
	int rand_sep;
	int *end_ptr;
};

struct _HAIKU_BUILD_IDENTIFIER(drand48_data) {
	unsigned short int x[3];
	unsigned short int a[3];
	unsigned short int c;
	unsigned short int old_x[3];
	int init;
};


#ifdef __cplusplus
extern "C" {
#endif

/* memory allocation (see malloc.h for additional defines & prototypes) */
_HAIKU_BUILD_DECLARE_FUNCTION(void*, calloc,
	(size_t numElements, size_t size))
_HAIKU_BUILD_DECLARE_FUNCTION(void, free, (void *pointer))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, malloc, (size_t size))
_HAIKU_BUILD_DECLARE_FUNCTION(int, posix_memalign, (void **_pointer,
	size_t alignment, size_t size))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, realloc, (void *oldPointer,
	size_t newSize))

/* process termination */
_HAIKU_BUILD_DECLARE_FUNCTION(void, abort, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, atexit, (void (*func)(void)))
_HAIKU_BUILD_DECLARE_FUNCTION(int, atfork, (void (*func)(void)))
_HAIKU_BUILD_DECLARE_FUNCTION(void, exit, (int))
_HAIKU_BUILD_DECLARE_FUNCTION(void, _Exit, (int))

/* misc functions */
_HAIKU_BUILD_DECLARE_FUNCTION(char*, realpath,
	(const char *path, char *resolved))

_HAIKU_BUILD_DECLARE_FUNCTION(int, system, (const char *command))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, mktemp, (char *name))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, mkdtemp, (char *templat))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mkstemp, (char *templat))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, ecvt, (double value, int digits,
	int *_decimalPoint, int *_sign))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, fcvt, (double value, int precision,
	int *_decimalPoint, int *_sign))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, gcvt, (double value, int digits,
	char *buffer))

/* environment variables */
_HAIKU_BUILD_DECLARE_VARIABLE(char**, environ)
_HAIKU_BUILD_DECLARE_FUNCTION(int, clearenv, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, getenv, (const char *name))
_HAIKU_BUILD_DECLARE_FUNCTION(int, putenv, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setenv, (char const *name,
	char const *value, int rewrite))
_HAIKU_BUILD_DECLARE_FUNCTION(int, unsetenv, (const char *name))

/* ASCII string to number conversion */
_HAIKU_BUILD_DECLARE_FUNCTION(double, atof, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(int, atoi, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(long, atol, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(long long int, atoll, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned int, atoui, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned long, atoul, (const char *string))

_HAIKU_BUILD_DECLARE_FUNCTION(double, strtod, (const char *string, char **end))
_HAIKU_BUILD_DECLARE_FUNCTION(long double, strtold, (const char *string,
	char **end))
_HAIKU_BUILD_DECLARE_FUNCTION(float, strtof, (const char *string, char **end))
_HAIKU_BUILD_DECLARE_FUNCTION(long, strtol, (const char *string, char **end,
	int base))
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned long, strtoul, (const char *string,
	char **end, int base))
_HAIKU_BUILD_DECLARE_FUNCTION(long long, strtoll, (const char *string, char
	**end, int base))
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned long long, strtoull,
	(const char *string, char **end, int base))

/* random number generation */
_HAIKU_BUILD_DECLARE_FUNCTION(void, srand, (unsigned int seed))
_HAIKU_BUILD_DECLARE_FUNCTION(int, rand, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, random, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(void, srandom, (unsigned int seed))
_HAIKU_BUILD_DECLARE_FUNCTION(int, rand_r, (unsigned int *seed))
_HAIKU_BUILD_DECLARE_FUNCTION(int, random_r,
	(struct _HAIKU_BUILD_IDENTIFIER(random_data) *data, int *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, srandom_r,
	(unsigned int seed, struct _HAIKU_BUILD_IDENTIFIER(random_data) *data))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, initstate,
	(unsigned int seed, char *state, size_t size))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, setstate, (char *state))
_HAIKU_BUILD_DECLARE_FUNCTION(int, initstate_r,
	(unsigned int seed, void *stateBuffer, size_t stateLength,
			struct _HAIKU_BUILD_IDENTIFIER(random_data) *data))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setstate_r,
	(void *stateBuffer, struct _HAIKU_BUILD_IDENTIFIER(random_data) *data))

_HAIKU_BUILD_DECLARE_FUNCTION(double, drand48, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(double, erand48,(unsigned short int xsubi[3]))
_HAIKU_BUILD_DECLARE_FUNCTION(long, lrand48, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(long, nrand48, (unsigned short int xsubi[3]))
_HAIKU_BUILD_DECLARE_FUNCTION(long, mrand48, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(long, jrand48, (unsigned short int xsubi[3]))
_HAIKU_BUILD_DECLARE_FUNCTION(void, srand48, (long int seed))
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned short*, seed48, (unsigned short int seed16v[3]))
_HAIKU_BUILD_DECLARE_FUNCTION(void, lcong48, (unsigned short int param[7]))

_HAIKU_BUILD_DECLARE_FUNCTION(int, drand48_r,
	(struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data, double *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, erand48_r, (unsigned short int xsubi[3],
	struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data, double *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, lrand48_r,
	(struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data, long int *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, nrand48_r, (unsigned short int xsubi[3],
	struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data, long int *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mrand48_r,
	(struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data, long int *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, jrand48_r, (unsigned short int xsubi[3],
	struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data, long int *result))
_HAIKU_BUILD_DECLARE_FUNCTION(int, srand48_r, (long int seed,
	struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data))
_HAIKU_BUILD_DECLARE_FUNCTION(int, seed48_r, (unsigned short int seed16v[3],
	struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data))
_HAIKU_BUILD_DECLARE_FUNCTION(int, lcong48_r, (unsigned short int param[7],
	struct _HAIKU_BUILD_IDENTIFIER(drand48_data) *data))

/* search and sort functions */
typedef int (*_compare_function)(const void *, const void *);

_HAIKU_BUILD_DECLARE_FUNCTION(void*, bsearch, (const void *key,
	const void *base, size_t numElements, size_t sizeOfElement,
		_compare_function))
_HAIKU_BUILD_DECLARE_FUNCTION(int, heapsort, (void *base,
	size_t numElements, size_t sizeOfElement, _compare_function))
_HAIKU_BUILD_DECLARE_FUNCTION(int, mergesort, (void *base,
	size_t numElements, size_t sizeOfElement, _compare_function))
_HAIKU_BUILD_DECLARE_FUNCTION(void, qsort, (void *base,
	size_t numElements, size_t sizeOfElement, _compare_function))
_HAIKU_BUILD_DECLARE_FUNCTION(int, radixsort,
	(_haiku_build_u_char const **base, int numElements,
		_haiku_build_u_char const *table, _haiku_build_u_int endByte))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sradixsort,
	(_haiku_build_u_char const **base, int numElements,
		_haiku_build_u_char const *table, _haiku_build_u_int endByte))

/* misc math functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, abs, (int number))
_HAIKU_BUILD_DECLARE_FUNCTION(long, labs, (long number))
_HAIKU_BUILD_DECLARE_FUNCTION(long long, llabs, (long long number))

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(div_t), div,
	(int numerator, int denominator))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(ldiv_t), ldiv,
	(long numerator, long denominator))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(lldiv_t), lldiv,
	(long long numerator, long long denominator))

/* wide & multibyte string functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, mblen, (const char *string, size_t maxSize))
/* TODO: #8730 -- _HAIKU_BUILD_FEATURE_* for wchar_t
	You'll need to add a new one just like for the fixed width integer types,
	i.e. just add a "PRINT_TYPE_INFO(wchar);" in test_int_types.cpp. Unless, of
	course, <wchar_t.h> isn't wrapped by FreeBSD. Then you can include it and
	use wchar_t directly.
*/
_HAIKU_BUILD_DECLARE_FUNCTION(int, mbtowc, (wchar_t *pwc,
	const char *string, size_t maxSize))
_HAIKU_BUILD_DECLARE_FUNCTION(int, wctomb, (char *string, wchar_t wchar))
_HAIKU_BUILD_DECLARE_FUNCTION(size_t, mbstowcs,
	(wchar_t *pwcs, const char *string, size_t maxSize))
_HAIKU_BUILD_DECLARE_FUNCTION(size_t, wcstombs,
	(char *string, const wchar_t *pwcs, size_t maxSize))

/* crypt */
_HAIKU_BUILD_DECLARE_FUNCTION(void, setkey, (const char *key))

/* sub-option parsing */
_HAIKU_BUILD_DECLARE_FUNCTION(int, getsubopt, (char **optionp,
	char * const *keylistp,	char **valuep))

/* pty functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, posix_openpt, (int openFlags))
_HAIKU_BUILD_DECLARE_FUNCTION(int, grantpt, (int masterFD))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, ptsname, (int masterFD))
_HAIKU_BUILD_DECLARE_FUNCTION(int, unlockpt, (int masterFD))

/* internal accessor to value for MB_CUR_MAX */
_HAIKU_BUILD_DECLARE_FUNCTION(unsigned short, __ctype_get_mb_cur_max, (void))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _STDLIB_H_ */
