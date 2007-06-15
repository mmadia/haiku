/*
	Copyright 1999, Be Incorporated.   All Rights Reserved.
	This file may be used under the terms of the Be Sample Code License.

	Other authors:
	Gerald Zajac 2006-2007
*/

#include "GlobalData.h"
#include "AccelerantPrototypes.h"
#include <string.h>


#define	T_POSITIVE_SYNC	(B_POSITIVE_HSYNC | B_POSITIVE_VSYNC)
#define MODE_FLAGS (B_SCROLL | B_8_BIT_DAC | B_HARDWARE_CURSOR | B_PARALLEL_ACCESS)
#define MODE_COUNT (sizeof (mode_list) / sizeof (display_mode))

static const display_mode mode_list[] = {
	{ { 25175, 640, 656, 752, 800, 480, 490, 492, 525, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(640X480X8.Z1) */
	{ { 27500, 640, 672, 768, 864, 480, 488, 494, 530, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* 640X480X60Hz */
	{ { 30500, 640, 672, 768, 864, 480, 517, 523, 588, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* SVGA_640X480X60HzNI */
	{ { 31500, 640, 664, 704, 832, 480, 489, 492, 520, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70-72Hz_(640X480X8.Z1) */
	{ { 31500, 640, 656, 720, 840, 480, 481, 484, 500, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(640X480X8.Z1) */
	{ { 36000, 640, 696, 752, 832, 480, 481, 484, 509, 0}, B_CMAP8, 640, 480, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(640X480X8.Z1) */

	{ { 36000, 800, 824, 896, 1024, 600, 601, 603, 625, 0}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@56Hz_(800X600) */
	{ { 38100, 800, 832, 960, 1088, 600, 602, 606, 620, 0}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* SVGA_800X600X56HzNI */
	{ { 40000, 800, 840, 968, 1056, 600, 601, 605, 628, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(800X600X8.Z1) */
	{ { 49500, 800, 816, 896, 1056, 600, 601, 604, 625, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(800X600X8.Z1) */
	{ { 50000, 800, 856, 976, 1040, 600, 637, 643, 666, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70-72Hz_(800X600X8.Z1) */
	{ { 56250, 800, 832, 896, 1048, 600, 601, 604, 631, T_POSITIVE_SYNC}, B_CMAP8, 800, 600, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(800X600X8.Z1) */

	{ { 65000, 1024, 1048, 1184, 1344, 768, 771, 777, 806, 0}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1024X768X8.Z1) */
	{ { 75000, 1024, 1048, 1184, 1328, 768, 771, 777, 806, 0}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70-72Hz_(1024X768X8.Z1) */
	{ { 78750, 1024, 1040, 1136, 1312, 768, 769, 772, 800, T_POSITIVE_SYNC}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1024X768X8.Z1) */
	{ { 94500, 1024, 1072, 1168, 1376, 768, 769, 772, 808, T_POSITIVE_SYNC}, B_CMAP8, 1024, 768, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(1024X768X8.Z1) */

	{ { 94200, 1152, 1184, 1280, 1472, 864, 865, 868, 914, T_POSITIVE_SYNC}, B_CMAP8, 1152, 864, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70Hz_(1152X864X8.Z1) */
	{ { 97800, 1152, 1216, 1344, 1552, 864, 865, 868, 900, T_POSITIVE_SYNC}, B_CMAP8, 1152, 864, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70Hz_(1152X864X8.Z1) */
	{ { 108000, 1152, 1216, 1344, 1600, 864, 865, 868, 900, T_POSITIVE_SYNC}, B_CMAP8, 1152, 864, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1152X864X8.Z1) */
	{ { 121500, 1152, 1216, 1344, 1568, 864, 865, 868, 911, T_POSITIVE_SYNC}, B_CMAP8, 1152, 864, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(1152X864X8.Z1) */

	{ { 108000, 1280, 1328, 1440, 1688, 1024, 1025, 1028, 1066, T_POSITIVE_SYNC}, B_CMAP8, 1280, 1024, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1280X1024X8.Z1) */
	{ { 135000, 1280, 1296, 1440, 1688, 1024, 1025, 1028, 1066, T_POSITIVE_SYNC}, B_CMAP8, 1280, 1024, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1280X1024X8.Z1) */
	{ { 157500, 1280, 1344, 1504, 1728, 1024, 1025, 1028, 1072, T_POSITIVE_SYNC}, B_CMAP8, 1280, 1024, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(1280X1024X8.Z1) */

	{ { 122600, 1400, 1488, 1640, 1880, 1050, 1051, 1054, 1087, T_POSITIVE_SYNC}, B_CMAP8, 1400, 1050, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1400X1050) */
	{ { 155800, 1400, 1464, 1784, 1912, 1050, 1052, 1064, 1090, T_POSITIVE_SYNC}, B_CMAP8, 1400, 1050, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1400X1050) */

	{ { 162000, 1600, 1664, 1856, 2160, 1200, 1201, 1204, 1250, T_POSITIVE_SYNC}, B_CMAP8, 1600, 1200, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1600X1200X8.Z1) */
	{ { 175500, 1600, 1664, 1856, 2160, 1200, 1201, 1204, 1250, T_POSITIVE_SYNC}, B_CMAP8, 1600, 1200, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@65Hz_(1600X1200X8.Z1) */
	{ { 189000, 1600, 1664, 1856, 2160, 1200, 1201, 1204, 1250, T_POSITIVE_SYNC}, B_CMAP8, 1600, 1200, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@70Hz_(1600X1200X8.Z1) */
	{ { 202500, 1600, 1664, 1856, 2160, 1200, 1201, 1204, 1250, T_POSITIVE_SYNC}, B_CMAP8, 1600, 1200, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1600X1200X8.Z1) */
	{ { 216000, 1600, 1664, 1856, 2160, 1200, 1201, 1204, 1250, T_POSITIVE_SYNC}, B_CMAP8, 1600, 1200, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@80Hz_(1600X1200X8.Z1) */
	{ { 229500, 1600, 1664, 1856, 2160, 1200, 1201, 1204, 1250, T_POSITIVE_SYNC}, B_CMAP8, 1600, 1200, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(1600X1200X8.Z1) */

	{ { 204750, 1792, 1920, 2120, 2448, 1344, 1345, 1348, 1394, B_POSITIVE_VSYNC}, B_CMAP8, 1792, 1344, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1792X1344) */
	{ { 261000, 1792, 1888, 2104, 2456, 1344, 1345, 1348, 1417, B_POSITIVE_VSYNC}, B_CMAP8, 1792, 1344, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1792X1344) */

	{ { 218250, 1856, 1952, 2176, 2528, 1392, 1393, 1396, 1439, B_POSITIVE_VSYNC}, B_CMAP8, 1856, 1392, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1856X1392) */
	{ { 288000, 1856, 1984, 2208, 2560, 1392, 1393, 1396, 1500, B_POSITIVE_VSYNC}, B_CMAP8, 1856, 1392, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1856X1392) */

	{ { 234000, 1920, 2048, 2256, 2600, 1440, 1441, 1444, 1500, B_POSITIVE_VSYNC}, B_CMAP8, 1920, 1440, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(1920X1440) */
	{ { 297000, 1920, 2064, 2288, 2640, 1440, 1441, 1444, 1500, B_POSITIVE_VSYNC}, B_CMAP8, 1920, 1440, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(1920X1440) */
	{ { 341350, 1920, 2072, 2288, 2656, 1440, 1441, 1444, 1512, B_POSITIVE_VSYNC}, B_CMAP8, 1920, 1440, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@85Hz_(1920X1440) */

	{ { 266950, 2048, 2200, 2424, 2800, 1536, 1537, 1540, 1589, B_POSITIVE_VSYNC}, B_CMAP8, 2048, 1536, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@60Hz_(2048x1536) */
	{ { 340480, 2048, 2216, 2440, 2832, 1536, 1537, 1540, 1603, B_POSITIVE_VSYNC}, B_CMAP8, 2048, 1536, 0, 0, MODE_FLAGS}, /* Vesa_Monitor_@75Hz_(2048x1536) */
	{ { 388040, 2048, 2216, 2440, 2832, 1536, 1537, 1540, 1612, B_POSITIVE_VSYNC}, B_CMAP8, 2048, 1536, 0, 0, MODE_FLAGS}  /* Vesa_Monitor_@85Hz_(2048x1536) */
};


/* create a mask of one "bits" bits wide */
#define MASKFROMWIDTH(bits) ((1 << bits) - 1)

/*
	Validate a target display mode is both
		a) a valid display mode for this device and
		b) falls between the contraints imposed by "low" and "high"

	Return values:
		B_ERROR - mode is not (or cannot) be made valid for this device.
		B_BAD_VALUE - valid mode can be constructed, but it is not within limits.
		B_OK - mode is both valid AND is within the limits.
*/
status_t 
PROPOSE_DISPLAY_MODE(display_mode *target, const display_mode *low, const display_mode *high)
{
	const uint16 h_sync_bits = MASKFROMWIDTH(5);
	const uint16 h_total_bits = MASKFROMWIDTH(9);
	const uint16 v_display_bits = MASKFROMWIDTH(11);
	const uint16 v_sync_bits = MASKFROMWIDTH(5);

	status_t result = B_OK;
	uint32 row_bytes, limit_clock;
	double target_refresh = ((double)target->timing.pixel_clock * 1000.0)
					  / ((double)target->timing.h_total
					  * (double)target->timing.v_total);
	bool want_same_width = (target->timing.h_display == target->virtual_width);
	bool want_same_height = (target->timing.v_display == target->virtual_height);

	/*
	  NOTE:
	  Different devices provide different levels of control over the
	  various CRTC values.  This code should be used as a *GUIDELINE ONLY*.
	  The device you're controling may have very different constraints,
	  and the code below may be insufficient to insure that a particular
	  display_mode is valid for your device.  You would do well to spend
	  quite a bit of time ensuring that you understand the limitations of
	  your device, as setting these values incorrectly can create a
	  display_mode that could turn your monitor into a useless slag of
	  molten components, burn up your card, lock up the PCI bus, cause
	  partialy or multiply repeating display images, or otherwise look
	  just plain wierd.  Honest.
	  */
	/*
	  NOTE:
	  This code doesn't explicitly support interlaced video modes.
	  */

//	TRACE(("ProposeDisplayMode;  clock = %d, width = %d, height = %d\n",
//		  target->timing.pixel_clock, target->virtual_width, target->virtual_height));

	/* validate horizontal timings */
	{
		/* for most devices, horizontal parameters must be multiples of 8 */
		uint16 h_display = target->timing.h_display >> 3;
		uint16 h_sync_start = target->timing.h_sync_start >> 3;
		uint16 h_sync_end = target->timing.h_sync_end >> 3;
		uint16 h_total = target->timing.h_total >> 3;

		/* ensure reasonable minimum display and sequential order of parms */
		if (h_display < (320 >> 3))
			h_display = 320 >> 3;
		if (h_display > (2048 >> 3))
			h_display = 2048 >> 3;
		if (h_sync_start < (h_display + 2))
			h_sync_start = h_display + 2;
		if (h_sync_end < (h_sync_start + 3))
			h_sync_end = h_sync_start + 3; /*(0x001f >> 2);*/
		if (h_total < (h_sync_end + 1))
			h_total = h_sync_end + 1;
		/* adjust for register limitations: */
		/* h_total is 9 bits */
		if (h_total > h_total_bits)
			h_total = h_total_bits;
		/* h_display is 8 bits - handled above */
		/* h_sync_start is 9 bits */
		/* h_sync_width is 5 bits */
		if ((h_sync_end - h_sync_start) > h_sync_bits)
			h_sync_end = h_sync_start + h_sync_bits;

		/* shift back to the full width values */
		target->timing.h_display = h_display << 3;
		target->timing.h_sync_start = h_sync_start << 3;
		target->timing.h_sync_end = h_sync_end << 3;
		target->timing.h_total = h_total << 3;
	}
	
	/* did we fall out of one of the limits? */
	if ((target->timing.h_display < low->timing.h_display)
		|| (target->timing.h_display > high->timing.h_display)
		|| (target->timing.h_sync_start < low->timing.h_sync_start)
		|| (target->timing.h_sync_start > high->timing.h_sync_start)
		|| (target->timing.h_sync_end < low->timing.h_sync_end)
		|| (target->timing.h_sync_end > high->timing.h_sync_end)
		|| (target->timing.h_total < low->timing.h_total)
		|| (target->timing.h_total > high->timing.h_total))
		result = B_BAD_VALUE;


	/* validate vertical timings */
	{
		uint16 v_display = target->timing.v_display;
		uint16 v_sync_start = target->timing.v_sync_start;
		uint16 v_sync_end = target->timing.v_sync_end;
		uint16 v_total = target->timing.v_total;

		/* ensure reasonable minium display and sequential order of parms */
		/* v_display is 11 bits */
		/* v_total is 11 bits */
		/* v_sync_start is 11 bits */
		/* v_sync_width is 5 bits */
		if (v_display < 200)
			v_display = 200;
		if (v_display > (v_display_bits - 5))
			v_display = (v_display_bits - 5); /* leave room for the sync pulse */
		if (v_sync_start < (v_display + 1))
			v_sync_start = v_display + 1;
		if (v_sync_end < v_sync_start)
			v_sync_end = v_sync_start + 3;
		if (v_total < (v_sync_end + 1))
			v_total = v_sync_end + 1;
		/* adjust for register limitations */
		if ((v_sync_end - v_sync_start) > v_sync_bits)
			v_sync_end = v_sync_start + v_sync_bits;

		target->timing.v_display = v_display;
		target->timing.v_sync_start = v_sync_start;
		target->timing.v_sync_end = v_sync_end;
		target->timing.v_total = v_total;
	}

	/* did we fall out of one of the limits? */
	if ((target->timing.v_display < low->timing.v_display)
		|| (target->timing.v_display > high->timing.v_display)
		|| (target->timing.v_sync_start < low->timing.v_sync_start)
		|| (target->timing.v_sync_start > high->timing.h_sync_start)
		|| (target->timing.v_sync_end < low->timing.v_sync_end)
		|| (target->timing.v_sync_end > high->timing.v_sync_end)
		|| (target->timing.v_total < low->timing.v_total)
		|| (target->timing.v_total > high->timing.v_total))
		result = B_BAD_VALUE;
	
	// If the video is connected directly to an LCD display (ie, notebook
	// computer), restrict the display mode to the resolution of the LCD
	// display.
	
	if (MT_LCD == si->displayType && si->panelX > 0 && si->panelY > 0 &&
		(target->timing.h_display != si->panelX
			|| target->timing.v_display != si->panelY)) {
		return B_ERROR;
	}

	/* adjust pixel clock for DAC limits and target refresh rate */
	/*
	  We're re-calcuating the pixel_clock here because we might have
	  changed the h/v totals above.  If we didn't change anything
	  the calculation is wasted, but it's no big deal.
	  */
	target->timing.pixel_clock = target_refresh
			  * ((double)target->timing.h_total)
			  * ((double)target->timing.v_total) / 1000.0;

	/*
	  Select the maximum pixel clock based on the color space.  Your
	  device may have other constraints.  In this sample driver, we
	  calculated the maximum pixel clock for this device in the
	  initialization code.
	  This is also a convienient place to determine the number of bytes
	  per pixel for a later display pitch calculation.
	  */
	switch (target->space & 0x0fff) {
	case B_CMAP8:
		limit_clock = si->pix_clk_max8;
		row_bytes = 1;
		break;
	//case B_RGB15:
	case B_RGB16:
		limit_clock = si->pix_clk_max16;
		row_bytes = 2;
		break;
	case B_RGB32:
		limit_clock = si->pix_clk_max32;
		row_bytes = 4;
		break;
	default:
		/* no amount of adjusting will fix not being able to support
			the pixel format */
		return B_ERROR;
	}
	/* make sure we don't generate more pixel bandwidth than the device
		can handle */
	if (target->timing.pixel_clock > limit_clock)
		target->timing.pixel_clock = limit_clock;
	/* we probably ought to check against too low of a pixel rate,
		but I'm lazy */

	/* note if we fell outside the limits */
	if ((target->timing.pixel_clock < low->timing.pixel_clock)
		|| (target->timing.pixel_clock > high->timing.pixel_clock))
		result = B_BAD_VALUE;

	/* validate display vs. virtual */
	if ((target->timing.h_display > target->virtual_width) || want_same_width)
		target->virtual_width = target->timing.h_display;
	if ((target->timing.v_display > target->virtual_height) || want_same_height)
		target->virtual_height = target->timing.v_display;
	if (target->virtual_width > 2048)
		target->virtual_width = 2048;

	/* adjust virtual width for engine limitations */
	target->virtual_width = (target->virtual_width + 7) & ~7;
	if ( (target->virtual_width < low->virtual_width)
		|| (target->virtual_width > high->virtual_width))
		result = B_BAD_VALUE;

	/* calculate rowbytes after we've nailed the virtual width */
	row_bytes *= target->virtual_width;

	/* memory requirement for frame buffer */
	if ((row_bytes * target->virtual_height) > si->maxFrameBufferSize)
		target->virtual_height = si->maxFrameBufferSize / row_bytes;

	if (target->virtual_height > 2048)
		target->virtual_height = 2048;

	if (target->virtual_height < target->timing.v_display)
		/* not enough frame buffer memory for the mode */
		return B_ERROR;
	else if ((target->virtual_height < low->virtual_height)
			 || (target->virtual_height > high->virtual_height))
		result = B_BAD_VALUE;

	return result;
}

/*
	Return the number of modes this device will return from GET_MODE_LIST().
*/
uint32 
ACCELERANT_MODE_COUNT(void)
{
	/* return the number of 'built-in' display modes */
	return si->modeCount;
}

/*
	Copy the list of guaranteed supported video modes to the location
	provided.
*/
status_t 
GET_MODE_LIST(display_mode *dm)
{
	/* copy them to the buffer pointed at by *dm */
	memcpy(dm, modeList, si->modeCount * sizeof(display_mode));
	return B_OK;
}


/*
	Create a list of display_modes to pass back to the caller.
*/
status_t 
create_mode_list(void)
{
	size_t max_size;
	uint32 i;
	uint32 pix_clk_range;
	const display_mode *src;
	display_mode *dst, low, high;

	/*
	  We prefer frame buffers to have the same endianness as the host
	  CPU, but it's not required.	You can even return both, although
	  there isn't a way for the current Screen preferences panel to
	  allow the user to choose which one to use.
	  */
#if defined(__INTEL__)
	color_space colorSpaces[] = { B_CMAP8, B_RGB16_LITTLE, B_RGB32_LITTLE };
#else
	color_space colorSpaces[] =  { B_CMAP8, B_RGB16_BIG, B_RGB32_BIG };
#endif

	int numColorSpaces = sizeof(colorSpaces) / sizeof(colorSpaces[0]);

	/* figure out how big the list could be, and adjust up to nearest
		multiple of B_PAGE_SIZE */
	max_size = ((MODE_COUNT * numColorSpaces * sizeof(display_mode))
				+ (B_PAGE_SIZE - 1)) & ~(B_PAGE_SIZE - 1);
	/* create an area to hold the info */
	si->modeArea = modeListArea = create_area("SAVAGE accelerant mode info",
			(void **) &modeList, B_ANY_ADDRESS, max_size, B_NO_LOCK, B_READ_AREA | B_WRITE_AREA);
	if (modeListArea < B_OK)
		return modeListArea;

	/* walk through our predefined list and see which modes fit this device */
	src = mode_list;
	dst = modeList;
	si->modeCount = 0;

	for (i = 0; i < MODE_COUNT; i++) {
		int j;

		/* set ranges for acceptable values */
		low = high = *src;
		/* Expand range of default clock by 3.1% on each end: arbitrarily picked */
		pix_clk_range = low.timing.pixel_clock >> 5;	// divide by 32 to get ~3.1%
		low.timing.pixel_clock -= pix_clk_range;
		high.timing.pixel_clock += pix_clk_range;

		/* do it once for each depth we want to support */
		for (j = 0; j < numColorSpaces; j++) {
			/* set target values */
			*dst = *src;
			/* poke the specific space */
			dst->space = low.space = high.space = colorSpaces[j];
			/* ask for a compatible mode */
			if (PROPOSE_DISPLAY_MODE(dst, &low, &high) == B_OK) {
				/* count it, and move on to next mode */
				dst++;
				si->modeCount++;
			}
		}
		/* advance to next mode */
		src++;
	}

	return B_OK;
}

