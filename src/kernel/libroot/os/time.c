/* 
** Copyright 2002-2003, Axel Dörfler, axeld@pinc-software.de. All rights reserved.
** Distributed under the terms of the OpenBeOS License.
*/


#include <OS.h>
#include "syscalls.h"

static area_id	sCloneRtcArea;
static volatile bigtime_t *sBootTime = NULL;


status_t
setup_rtc_area()
{
	area_id rtcArea = find_area("rtc_region");
	if (rtcArea < 0) {
		printf("setup_rtc_area: error finding rtc_region %s\n",
			strerror(rtcArea));
	}
	sCloneRtcArea = clone_area("cloned_rtc_region", (void**)&sBootTime,
		B_ANY_ADDRESS, B_READ_AREA, rtcArea);
	if (sCloneRtcArea < 0) {
		printf("setup_rtc_area: error cloning rtc_region\n");
		return sCloneRtcArea;
	}
	
	return B_OK;	
}


uint32
real_time_clock(void)
{
	if (!sBootTime)
		setup_rtc_area();
	//return (*sBootTime + system_time()) / 1000000;
	return 0;
}


void
set_real_time_clock(uint32 secs)
{
	_kern_set_real_time_clock(secs);
}


bigtime_t
real_time_clock_usecs(void)
{
	if (!sBootTime)
		setup_rtc_area();
	//return *sBootTime + system_time();
	return 0;
}


status_t
set_timezone(char *timezone)
{
	// ToDo: set_timezone()
	return B_ERROR;
}


/*
// ToDo: currently defined in atomic.S - but should be in its own file time.S
bigtime_t
system_time(void)
{
	// time since booting in microseconds
	return sys_system_time();
}
*/


bigtime_t
set_alarm(bigtime_t when, uint32 flags)
{
	// ToDo: set_alarm()
	return B_ERROR;
}
