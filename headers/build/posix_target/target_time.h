/*
 * Copyright 2005-2012, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _HAIKU_BUILD_TIME_H_
#define _HAIKU_BUILD_TIME_H_


#include <sys/target_types.h>


struct _HAIKU_BUILD_IDENTIFIER(sigevent);	/* defined in <signal.h> */


typedef __haiku_build_haiku_int32	_haiku_build_clock_t;
typedef __haiku_build_haiku_int32 	_haiku_build_time_t;
typedef __haiku_build_haiku_int32 	_haiku_build_suseconds_t;
typedef __haiku_build_haiku_int32 	_haiku_build_useconds_t;


#define _HAIKU_BUILD_CLOCKS_PER_SEC				1000000
#define _HAIKU_BUILD_CLK_TCK					CLOCKS_PER_SEC

#define _HAIKU_BUILD_MAX_TIMESTR				70
	/* maximum length of a string returned by asctime(), and ctime() */

#define _HAIKU_BUILD_CLOCK_MONOTONIC			((_haiku_build_clockid_t)0)
	/* system-wide monotonic clock (aka system time) */
#define _HAIKU_BUILD_CLOCK_REALTIME				((_haiku_build_clockid_t)-1)
	/* system-wide real time clock */
#define _HAIKU_BUILD_CLOCK_PROCESS_CPUTIME_ID	((_haiku_build_clockid_t)-2)
	/* clock measuring the used CPU time of the current process */
#define _HAIKU_BUILD_CLOCK_THREAD_CPUTIME_ID	((_haiku_build_clockid_t)-3)
	/* clock measuring the used CPU time of the current thread */

#define _HAIKU_BUILD_TIMER_ABSTIME				1	/* absolute timer flag */


struct _HAIKU_BUILD_IDENTIFIER(timespec) {
	_haiku_build_time_t		tv_sec;		/* seconds */
	long					tv_nsec;	/* and nanoseconds */
};

struct _HAIKU_BUILD_IDENTIFIER(itimerspec) {
	struct _HAIKU_BUILD_IDENTIFIER(timespec) it_interval;
	struct _HAIKU_BUILD_IDENTIFIER(timespec) it_value;
};

struct _HAIKU_BUILD_IDENTIFIER(tm) {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;	/* day of month (1 to 31) */
	int	tm_mon;		/* months since January (0 to 11) */
	int	tm_year;	/* years since 1900 */
	int	tm_wday;	/* days since Sunday (0 to 6, Sunday = 0, ...) */
	int	tm_yday;	/* days since January 1 (0 to 365) */
	int	tm_isdst;	/* daylight savings time (0 == no, >0 == yes, <0 == has to be calculated */
	int tm_gmtoff;	/* timezone offset to GMT */
	char *tm_zone;	/* timezone name */
};


/* special timezone support */
extern char *_haiku_build_tzname[2];
extern int 	_haiku_build_daylight;
extern long	_haiku_build_timezone;


#ifdef __cplusplus
extern "C" {
#endif

_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_clock_t, clock, (void))
_HAIKU_BUILD_DECLARE_FUNCTION(double, difftime, (_haiku_build_time_t time1,
	_haiku_build_time_t time2))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_time_t, mktime,
	(struct _HAIKU_BUILD_IDENTIFIER(tm) *tm))
_HAIKU_BUILD_DECLARE_FUNCTION(_haiku_build_time_t, time,
	(_haiku_build_time_t *timer))
_HAIKU_BUILD_DECLARE_FUNCTION(char *, asctime,
	(const struct _HAIKU_BUILD_IDENTIFIER(tm) *tm))
_HAIKU_BUILD_DECLARE_FUNCTION(char *, asctime_r,
	(const struct _HAIKU_BUILD_IDENTIFIER(tm) *timep, char *buffer))
_HAIKU_BUILD_DECLARE_FUNCTION(char *, ctime,
	(const _haiku_build_time_t *timer))
_HAIKU_BUILD_DECLARE_FUNCTION(char *, ctime_r,
	(const _haiku_build_time_t *timer, char *buffer))
_HAIKU_BUILD_DECLARE_FUNCTION(struct _HAIKU_BUILD_IDENTIFIER(tm) *, gmtime,
	(const _haiku_build_time_t *timer))
_HAIKU_BUILD_DECLARE_FUNCTION(struct _HAIKU_BUILD_IDENTIFIER(tm) *, gmtime_r,
	(const _haiku_build_time_t *timer, struct _HAIKU_BUILD_IDENTIFIER(tm) *tm))
_HAIKU_BUILD_DECLARE_FUNCTION(struct _HAIKU_BUILD_IDENTIFIER(tm) *, localtime,
	(const _haiku_build_time_t *timer))
_HAIKU_BUILD_DECLARE_FUNCTION(struct _HAIKU_BUILD_IDENTIFIER(tm) *,
	localtime_r, (const _haiku_build_time_t *timer,
		struct _HAIKU_BUILD_IDENTIFIER(tm) *tm))
_HAIKU_BUILD_DECLARE_FUNCTION(int, nanosleep, (const
	_HAIKU_BUILD_IDENTIFIER(timespec) *, _HAIKU_BUILD_IDENTIFIER(timespec) *))
_HAIKU_BUILD_DECLARE_FUNCTION(size_t, strftime, (char *buffer, size_t maxSize,
	 const char *format, const struct _HAIKU_BUILD_IDENTIFIER(tm) *tm))
_HAIKU_BUILD_DECLARE_FUNCTION(char *, strptime, (const char *buf,
	const char *format, struct _HAIKU_BUILD_IDENTIFIER(tm) *tm))

/* clock functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, clock_getres,
	(_haiku_build_clockid_t clockID,
		_HAIKU_BUILD_IDENTIFIER(timespec)* resolution))
_HAIKU_BUILD_DECLARE_FUNCTION(int, clock_gettime,
	(_haiku_build_clockid_t clockID, _HAIKU_BUILD_IDENTIFIER(timespec)* _time))
_HAIKU_BUILD_DECLARE_FUNCTION(int, clock_settime,
	(_haiku_build_clockid_t clockID,
		const _HAIKU_BUILD_IDENTIFIER(timespec)* _time))
_HAIKU_BUILD_DECLARE_FUNCTION(int, clock_nanosleep,
	(_haiku_build_clockid_t clockID, int flags,
		const _HAIKU_BUILD_IDENTIFIER(timespec)* _time,
			_HAIKU_BUILD_IDENTIFIER(timespec)* remainingTime))
_HAIKU_BUILD_DECLARE_FUNCTION(int, clock_getcpuclockid,
	(_haiku_build_pid_t pid, _haiku_build_clockid_t* _clockID))

/* timer functions */
_HAIKU_BUILD_DECLARE_FUNCTION(int, timer_create,
	(_haiku_build_clockid_t clockID,
		struct _HAIKU_BUILD_IDENTIFIER(sigevent)* event,
			_HAIKU_BUILD_IDENTIFIER(timer_t)* timerID))
_HAIKU_BUILD_DECLARE_FUNCTION(int, timer_delete,
	(_HAIKU_BUILD_IDENTIFIER(timer_t) timerID))
_HAIKU_BUILD_DECLARE_FUNCTION(int, timer_gettime,
	(_HAIKU_BUILD_IDENTIFIER(timer_t) timerID, struct itimerspec* value))
_HAIKU_BUILD_DECLARE_FUNCTION(int, timer_settime,
	(_HAIKU_BUILD_IDENTIFIER(timer_t) timerID, int flags,
		const struct itimerspec* value, struct itimerspec* oldValue))
_HAIKU_BUILD_DECLARE_FUNCTION(int, timer_getoverrun,
	(_HAIKU_BUILD_IDENTIFIER(timer_t) timerID))

/* special timezone support */
_HAIKU_BUILD_DECLARE_FUNCTION(void, tzset, (void))

/* non-POSIX */
_HAIKU_BUILD_DECLARE_FUNCTION(int, stime, (const _haiku_build_time_t *t))

#ifdef __cplusplus
}
#endif

#ifndef _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER
	typedef _haiku_build_clock_t			clock_t;
	typedef _haiku_build_time_t				time_t;
	typedef _haiku_build_suseconds_t		suseconds_t;
	typedef _haiku_build_useconds_t			useconds_t;

#	define CLOCKS_PER_SEC				_HAIKU_BUILD_CLOCKS_PER_SEC
#	define CLK_TCK						_HAIKU_BUILD_CLK_TCK

#	define MAX_TIMESTR					_HAIKU_BUILD_MAX_TIMESTR
		/* maximum length of a string returned by asctime(), and ctime() */

#	define CLOCK_MONOTONIC				_HAIKU_BUILD_CLOCK_MONOTONIC
		/* system-wide monotonic clock (aka system time) */
#	define CLOCK_REALTIME				_HAIKU_BUILD_CLOCK_REALTIME
		/* system-wide real time clock */
#	define CLOCK_PROCESS_CPUTIME_ID		_HAIKU_BUILD_CLOCK_PROCESS_CPUTIME_ID
		/* clock measuring the used CPU time of the current process */
#	define CLOCK_THREAD_CPUTIME_ID		_HAIKU_BUILD_CLOCK_THREAD_CPUTIME_ID
		/* clock measuring the used CPU time of the current thread */

#	define TIMER_ABSTIME				_HAIKU_BUILD_TIMER_ABSTIME	/* absolute timer flag */


	/* special timezone support */
	extern _haiku_build_tzname 			*tzname[2];
	extern _haiku_build_daylight 		daylight;
	extern _haiku_build_timezone		timezone;

#	endif	/* _HAIKU_BUILD_LIBROOT_FUNCTION_WRAPPER */

#endif	/* _TIME_H_ */
