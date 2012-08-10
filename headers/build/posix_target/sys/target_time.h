/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SYS_TIME_H
#define _SYS_TIME_H


#include <sys/target_types.h>


struct _HAIKU_BUILD_IDENTIFIER(timeval) {
	_HAIKU_BUILD_IDENTIFIER(time_t)			tv_sec;		/* seconds */
	_HAIKU_BUILD_IDENTIFIER(suseconds_t)	tv_usec;	/* microseconds */
};

#include <sys/target_select.h>
	/* circular dependency: fd_set needs to be defined and the
	 * select prototype exported by this file, but <sys/select.h>
	 * needs struct timeval.
	 */

struct _HAIKU_BUILD_IDENTIFIER(timezone) {
	int tz_minuteswest;
	int tz_dsttime;
};

struct _HAIKU_BUILD_IDENTIFIER(itimerval) {
	struct _HAIKU_BUILD_IDENTIFIER(timeval) it_interval;
	struct _HAIKU_BUILD_IDENTIFIER(timeval) it_value;
};

#define _HAIKU_BUILD_ITIMER_REAL		1	/* real time */
#define _HAIKU_BUILD_ITIMER_VIRTUAL		2	/* process virtual time */
#define _HAIKU_BUILD_ITIMER_PROF		3	/* both */


#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(int, getitimer, (int which,
	struct _HAIKU_BUILD_IDENTIFIER(timerval) *value))
_HAIKU_BUILD_DECLARE_FUNCTION(int, setitimer, (int which,
	const struct _HAIKU_BUILD_IDENTIFIER(itimerval) *value,
		struct _HAIKU_BUILD_IDENTIFIER(itimerval) *oldValue))
_HAIKU_BUILD_DECLARE_FUNCTION(int, gettimeofday,
	(struct _HAIKU_BUILD_IDENTIFIER(timeval) *tv, void *tz))

_HAIKU_BUILD_DECLARE_FUNCTION(int, utimes, (const char *name,
	const struct _HAIKU_BUILD_IDENTIFIER(timeval) times[2]))
	/* legacy */

#ifdef __cplusplus
}
#endif

/* BSDish macros operating on timeval structs */
#define _haiku_build_timeradd(a, b, res)				\
	do {												\
		(res)->tv_sec = (a)->tv_sec + (b)->tv_sec;		\
		(res)->tv_usec = (a)->tv_usec + (b)->tv_usec;	\
		if ((res)->tv_usec >= 1000000) {				\
			(res)->tv_usec -= 1000000;					\
			(res)->tv_sec++;							\
		}												\
	} while (0)
#define _haiku_build_timersub(a, b, res)				\
	do {												\
		(res)->tv_sec = (a)->tv_sec - (b)->tv_sec;		\
		(res)->tv_usec = (a)->tv_usec - (b)->tv_usec;	\
		if ((res)->tv_usec < 0) {						\
			(res)->tv_usec += 1000000;					\
			(res)->tv_sec--;							\
		}												\
	} while (0)
#define _haiku_build_timerclear(a)	((a)->tv_sec = (a)->tv_usec = 0)
#define _haiku_build_timerisset(a)	((a)->tv_sec != 0 || (a)->tv_usec != 0)
#define _haiku_build_timercmp(a, b, cmp)	((a)->tv_sec == (b)->tv_sec \
		? (a)->tv_usec cmp (b)->tv_usec : (a)->tv_sec cmp (b)->tv_sec)

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
#	define ITIMER_REAL		_HAIKU_BUILD_ITIMER_REAL	/* real time */
#	define ITIMER_VIRTUAL	_HAIKU_BUILD_ITIMER_VIRTUAL	/* process virtual time */
#	define ITIMER_PROF		_HAIKU_BUILD_ITIMER_PROF	/* both */

	/* BSDish macros operating on timeval structs */
#	define timeradd(a, b, res)	_haiku_build_timeradd(a, b, res)
#	define timersub(a, b, res)	_haiku_build_timersub(a, b, res)
#	define timerclear(a)		_haiku_build_timerclear(a)
#	define timerisset(a)		_haiku_build_timerisset(a)
#	define timercmp(a, b, cmp)	_haiku_build_timercmp(a, b, cmp)

#endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#endif	/* _SYS_TIME_H */
