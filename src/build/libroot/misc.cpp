
//#include <BeOSBuildCompatibility.h>

#include <target_errno.h>
#include <target_stdio.h>
#include <target_stdlib.h>
#include <target_unistd.h>
#include <sys/target_stat.h>
#include <sys/target_time.h>

#include <target_Debug.h>
#include <target_image.h>
#include <target_OS.h>

mode_t __gUmask = 022;

// debugger
void
debugger(const char *message)
{
	fprintf(stderr, "debugger() called: %s\n", message);
	exit(1);
}

// _debuggerAssert
int
_debuggerAssert(const char *file, int line, const char *expression)
{
	char buffer[2048];
	snprintf(buffer, sizeof(buffer), "%s:%d: %s\n", file, line, expression);
	debugger(buffer);
	return 0;
}

// system_time
bigtime_t
system_time(void)
{
	struct timeval tm;
	gettimeofday(&tm, NULL);
	return (int64)tm.tv_sec * 1000000LL + (int64)tm.tv_usec;
}

// snooze
status_t
snooze(bigtime_t amount)
{
	if (amount <= 0)
		return B_OK;

	int64 secs = amount / 1000000LL;
	int64 usecs = amount % 1000000LL;
	if (secs > 0) {
		if (sleep((unsigned)secs) < 0)
			return errno;
	}

	if (usecs > 0) {
		if (usleep((useconds_t)usecs) < 0)
			return errno;
	}

	return B_OK;
}

// snooze_until
status_t
snooze_until(bigtime_t time, int timeBase)
{
	return snooze(time - system_time());
}
