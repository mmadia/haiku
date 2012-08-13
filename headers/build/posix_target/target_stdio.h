/*
 * Copyright 2004-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _STDIO_H_
#define _STDIO_H_


#include <sys/target_types.h>
#include <target_null.h>
#include <target_stdarg.h>


/* Dodge gcc 2.95.3's fixincludes hack stdio_va_list by including this string:
 * __gnuc_va_list */


#define _HAIKU_BUILD_BUFSIZ			8192
#define _HAIKU_BUILD_IOFBF			0		/* fully buffered */
#define _HAIKU_BUILD_IOLBF			1		/* line buffered */
#define _HAIKU_BUILD_IONBF			2		/* not buffered */

/*
 * FOPEN_MAX is a minimum maximum, and should be the number of descriptors
 * that the kernel can provide without allocation of a resource that can
 * fail without the process sleeping.  Do not use this for anything
 */
#define _HAIKU_BUILD_FOPEN_MAX		128
#define _HAIKU_BUILD_STREAM_MAX		_HAIKU_BUILD_FOPEN_MAX
#define _HAIKU_BUILD_FILENAME_MAX	256
#define _HAIKU_BUILD_TMP_MAX		32768

#define _HAIKU_BUILD_L_ctermid  	32
#define _HAIKU_BUILD_L_cuserid  	32
#define _HAIKU_BUILD_L_tmpnam		512

#define _HAIKU_BUILD_P_tmpdir		"/tmp/"

#ifdef _HAIKU_BUILD_EOF
#	undef _HAIKU_BUILD_EOF
#endif
#define _HAIKU_BUILD_EOF			-1

#ifndef _HAIKU_BUILD_SEEK_SET
#	define _HAIKU_BUILD_SEEK_SET	0
#endif
#ifndef _HAIKU_BUILD_SEEK_CUR
#	define _HAIKU_BUILD_SEEK_CUR	1
#endif
#ifndef _HAIKU_BUILD_SEEK_END
#	define _HAIKU_BUILD_SEEK_END	2
#endif


typedef _haiku_build_off_t fpos_t;

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define BUFSIZ			_HAIKU_BUILD_BUFSIZ
#	define _IOFBF			_HAIKU_BUILD_IOFBF		/* fully buffered */
#	define _IOLBF			_HAIKU_BUILD_IOLBF		/* line buffered */
#	define _IONBF			_HAIKU_BUILD_IONBF		/* not buffered */

/*
 * FOPEN_MAX is a minimum maximum, and should be the number of descriptors
 * that the kernel can provide without allocation of a resource that can
 * fail without the process sleeping.  Do not use this for anything
 */
#	define FOPEN_MAX		_HAIKU_BUILD_FOPEN_MAX
#	define STREAM_MAX		_HAIKU_BUILD_STREAM_MAX
#	define FILENAME_MAX		_HAIKU_BUILD_FILENAME_MAX
#	define TMP_MAX			_HAIKU_BUILD_TMP_MAX

#	define L_ctermid  		_HAIKU_BUILD_L_ctermid
#	define L_cuserid  		_HAIKU_BUILD_L_cuserid
#	define L_tmpnam			_HAIKU_BUILD_L_tmpnam

#	define	P_tmpdir		_HAIKU_BUILD_P_tmpdir

#	ifdef EOF
#		undef EOF
#	endif
#	define EOF				_HAIKU_BUILD_EOF

#	ifndef SEEK_SET
#		define SEEK_SET		_HAIKU_BUILD_SEEK_SET
#	endif
#	ifndef SEEK_CUR
#		define SEEK_CUR		_HAIKU_BUILD_SEEK_CUR
#	endif
#	ifndef SEEK_END
#		define SEEK_END		_HAIKU_BUILD_SEEK_END
#	endif


typedef _haiku_build_off_t	fpos_t;
#	endif	/* _STDIO_H_ */

/* TODO: #8730 -- stdio_pre.h, stdio_post.h, etc.
	The stdio_pre.h and stdio_post.h headers are implementation details. They
	are never included by client code. Their contents should be revised and
	merged into stdio.h.

	FILE should by defined as an opaque type, fgetc() and fputc() should be
	defined as function prototypes, not macros or inline functions.

	stdio_ext.h may not be needed either.
	Start with an empty file and only add something, if actually used.
*/
//#include <target_stdio_pre.h>
struct _HAIKU_BUILD_IDENTIFIER(_FILE);
typedef _HAIKU_BUILD_IDENTIFIER(_FILE) _HAIKU_BUILD_IDENTIFIER(FILE);

#define __HAIKU_BUILD_PRINTFLIKE(format, varargs) \
	__attribute__ ((__format__ (__printf__, format, varargs)))
#define __HAIKU_BUILD_SCANFLIKE(format, varargs) \
	__attribute__((__format__ (__scanf__, format, varargs)))
#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define __PRINTFLIKE(format, varargs) 	\
		__HAIKU_BUILD_PRINTFLIKE(format, varargs)
#	define __SCANFLIKE(format, varargs)		\
		__HAIKU_BUILD_SCANFLIKE(format, varargs)
#endif /* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */
// end of stdio_pre.h

_HAIKU_BUILD_DECLARE_VARIABLE(_HAIKU_BUILD_IDENTIFIER(FILE)*, stdin)
_HAIKU_BUILD_DECLARE_VARIABLE(_HAIKU_BUILD_IDENTIFIER(FILE)*, stdout)
_HAIKU_BUILD_DECLARE_VARIABLE(_HAIKU_BUILD_IDENTIFIER(FILE)*, stderr)


#ifdef __cplusplus
extern "C" {
#endif

/* file operations */
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, fopen,
	(const char *name, const char *mode))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, freopen,
	(const char *name, const char *mode, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, fdopen,
	(int fd, const char *mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fclose,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, fileno,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fileno_unlocked,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, ferror,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, ferror_unlocked,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(void, clearerr,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(void, clearerr_unlocked,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, feof,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, feof_unlocked,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(void, flockfile,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(void, funlockfile,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, ftrylockfile,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, remove, (const char *name))
_HAIKU_BUILD_DECLARE_FUNCTION(int, rename, (const char *from, const char *to))
_HAIKU_BUILD_DECLARE_FUNCTION(int, renameat,
	(int fromFD, const char *from, int toFD, const char *to))

/* pipes */
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, popen,
	(const char *command, const char *mode))
_HAIKU_BUILD_DECLARE_FUNCTION(int, pclose,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(void, perror, (const char *errorPrefix))

/* memory streams */
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, fmemopen,
	(void *buf, size_t size, const char *mode))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, open_memstream,
	(char **buf, size_t *size))

/* file I/O */
_HAIKU_BUILD_DECLARE_FUNCTION(int, fflush,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fflush_unlocked,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fpurge,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, fgetpos,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, fpos_t *position))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fsetpos,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, const fpos_t *position))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fseek,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, long offset, int seekType))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fseeko,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, off_t offset, int seekType))
_HAIKU_BUILD_DECLARE_FUNCTION(int, _fseek,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, fpos_t offset, int seekType))
_HAIKU_BUILD_DECLARE_FUNCTION(long, ftell,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_off_t, ftello,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_fpos_t, _ftell,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(void, rewind,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(void, setbuf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *file, char *buff))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setvbuf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *file, char *buff, int mode, size_t size))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setbuffer,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, char *buf, size_t size))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setlinebuf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(size_t, fwrite,
	(const void *buffer, size_t size, size_t numItems,
		_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(size_t, fread,
	(void *buffer, size_t size, size_t numItems,
		_HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, putc,
	(int c, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, putchar(int c))
_HAIKU_BUILD_DECLARE_FUNCTION(int, putchar_unlocked, (int c))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fputc,
	(int c, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fputc_unlocked,
	(int c, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, puts, (const char *string))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fputs,
	(const char *string, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(int, getc,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, ungetc,
	(int c, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(int, getchar, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, getchar_unlocked, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fgetc,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, gets, (char *buffer))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, fgets,
	(char *string, int stringLength, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))

_HAIKU_BUILD_DECLARE_FUNCTION(ssize_t, getdelim,
	(char **_line, size_t *_length, int delimiter,
		_HAIKU_BUILD_IDENTIFIER(FILE) *stream))
_HAIKU_BUILD_DECLARE_FUNCTION(ssize_t, getline,
	(char **_line, size_t *_length, _HAIKU_BUILD_IDENTIFIER(FILE) *stream))

/* formatted I/O */
/* TODO: #8730 */
_HAIKU_BUILD_DECLARE_FUNCTION_ETC(int, printf,
	(char const *format, ...), __PRINTFLIKE(1,2))
_HAIKU_BUILD_DECLARE_FUNCTION_ETC(int, fprintf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, char const *format, ...),
		__PRINTFLIKE(2,3))
_HAIKU_BUILD_DECLARE_FUNCTION_ETC(int, sprintf,
	(char *string, char const *format, ...), __PRINTFLIKE(2,3))
_HAIKU_BUILD_DECLARE_FUNCTION_ETC(int, snprintf,
	(char *string, size_t size, char const *format, ...), __PRINTFLIKE(3,4))
_HAIKU_BUILD_DECLARE_FUNCTION_ETC(int, asprintf,
	(char **ret, char const *format, ...), __PRINTFLIKE(2,3))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vprintf,
	(char const *format, va_list ap))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vfprintf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, char const *format, va_list ap))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vsprintf,
	(char *string, char const *format, va_list ap))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vsnprintf,
	(char *string, size_t size, char const *format, va_list ap))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vasprintf,
	(char **ret, char const *format, va_list ap))

_HAIKU_BUILD_DECLARE_FUNCTION(int, scanf,
	(char const *format, ...))
_HAIKU_BUILD_DECLARE_FUNCTION(int, fscanf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, char const *format, ...))
_HAIKU_BUILD_DECLARE_FUNCTION(int, sscanf,
	(char const *str, char const *format, ...))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vscanf,
	(char const *format, va_list ap))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vsscanf,
	(char const *str, char const *format, va_list ap))
_HAIKU_BUILD_DECLARE_FUNCTION(int, vfscanf,
	(_HAIKU_BUILD_IDENTIFIER(FILE) *stream, char const *format, va_list ap))

/* misc */
_HAIKU_BUILD_DECLARE_FUNCTION(char*, ctermid, (char *controllingTerminal))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, cuserid, (char *s))

/* temporary files */
_HAIKU_BUILD_DECLARE_FUNCTION(char*, tempnam,
	(char const *path, char const *prefix))
_HAIKU_BUILD_DECLARE_FUNCTION(_HAIKU_BUILD_IDENTIFIER(FILE)*, tmpfile,(void))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, tmpnam,(char *nameBuffer))
_HAIKU_BUILD_DECLARE_FUNCTION(char*, tmpnam_r, (char *nameBuffer))

// #include <target_stdio_post.h>
/*	TODO: #8730 -- These should be defined as functions instead (check the
	POSIX specs for their signature).
*/
#define _haiku_build_getc(stream) \
	(_single_threaded ? _haiku_build_getc_unlocked(stream) : \
		_haiku_build_getc(stream))
#define _haiku_build_putc(c, stream) \
	(_single_threaded ? _haiku_build_putc_unlocked(c, stream) : \
		_haiku_build_putc(c, stream))

// end of stdio_post.h

#ifdef __cplusplus
}
#endif


#endif	/* _STDIO_H_ */
