/*
 * Copyright 2004-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _STRING_H_
#define _STRING_H_


#include <sys/target_types.h>


#ifdef __cplusplus
extern "C" {
#endif


/* memXXX() functions */
_HAIKU_BUILD_DECLARE_FUNCTION(void*, memchr, (const void *source, int value,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(int, memcmp, (const void *buffer1,
	const void *buffer2, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, memcpy, (void *dest, const void *source,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, memccpy, (void *dest, const void *source,
	int stopByte, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, memmove, (void *dest, const void *source,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(void*, memset, (void *dest, int value,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))

#ifdef __HAIKU_BUILD_USE_GNU
_HAIKU_BUILD_DECLARE_FUNCTION(void*, memrchr, (const void *source, int value,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
#endif

/* string functions */
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strcpy, (char *dest, const char *source))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strncpy, (char *dest, const char *source,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strcat, (char *dest, const char *source))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strncat, (char *dest, const char *source,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strlen,
	(const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(int, strcmp, (const char *string1,
	const char *string2))
_HAIKU_BUILD_DECLARE_FUNCTION(int, strncmp, (const char *string1,
	const char *string2, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, strchr, (const char *string,
	int character))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strrchr, (const char *string,
	int character))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strstr, (const char *string,
	const char *searchString))

#ifdef __HAIKU_BUILD_USE_GNU
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strchrnul, (const char *string,
	int character))
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(char*, strpbrk, (const char *string,
	const char *set))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strtok, (char *string, const char *set))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strtok_r, (char *string, const char *set,
	char **savePointer))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strspn,
	(const char *string, const char *set))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strcspn,
	(const char *string, const char *set))

_HAIKU_BUILD_DECLARE_FUNCTION(int, strcoll, (const char *string1,
	const char *string2))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strxfrm,
	(char *string1, const char *string2,
		_HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, strerror, (int errorCode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, strerror_r, (int errorCode, char *buffer,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ bufferSize))

/* non-standard string functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, strcasecmp, (const char *string1,
	const char *string2))
_HAIKU_BUILD_DECLARE_FUNCTION(int, strncasecmp, (const char *string1,
	const char *string2, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, strcasestr, (const char *string,
	const char *searchString))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, strdup, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strndup, (const char* string,
	_HAIKU_BUILD_FEATURE___SIZE_TYPE__ size))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, stpcpy, ( char *dest, const char *source))

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strlcat,
	(char *dest, const char *source, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strlcpy,
	(char *dest, const char *source, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ length))

_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_FEATURE___SIZE_TYPE__, strnlen,
	(const char *string, _HAIKU_BUILD_FEATURE___SIZE_TYPE__ count))

_HAIKU_BUILD_DECLARE_FUNCTION(char*, strlwr, (char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, strupr, (char *string))

/* _HAIKU_BUILD_DECLARE_FUNCTION(char*, strsep(char **stringPointer, const char *delimiter); */

_HAIKU_BUILD_DECLARE_FUNCTION(const char*, strsignal, (int signal))

/* legacy compatibility -- might be removed one day */
#define _haiku_build_bcmp(a, b, length) memcmp((a), (b), (length))
#define _haiku_build_bcopy(source, dest, length) memmove((dest), (source), (length))
#define _haiku_build_bzero(buffer, length) memset((buffer), 0, (length))

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define bcmp(a, b, length)			_haiku_build_bcmp(a, b, length)
#	define bcopy(source, dest, length)	_haiku_build_bcopy(source, dest, length)
#	define bzero(buffer, length)		_haiku_build_bzero(buffer, length)
#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

_HAIKU_BUILD_DECLARE_FUNCTION(int, ffs, (int i))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, index, (const char *s, int c))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, rindex, (char const *s, int c))

#ifdef __cplusplus
}
#endif

#endif  /* _STRING_H_ */
