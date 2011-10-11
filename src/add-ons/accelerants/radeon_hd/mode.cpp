/*
 * Copyright 2006-2011, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Support for i915 chipset and up based on the X driver,
 * Copyright 2006-2007 Intel Corporation.
 *
 * Authors:
 *		Axel Dörfler, axeld@pinc-software.de
 *		Alexander von Gluck, kallisti5@unixzen.com
 */


#include "accelerant_protos.h"
#include "accelerant.h"
#include "bios.h"
#include "utility.h"
#include "mode.h"
#include "display.h"
#include "pll.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <create_display_modes.h>


#define TRACE_MODE
#ifdef TRACE_MODE
extern "C" void _sPrintf(const char *format, ...);
#	define TRACE(x...) _sPrintf("radeon_hd: " x)
#else
#	define TRACE(x...) ;
#endif


status_t
create_mode_list(void)
{
	// TODO : multi-monitor?  for now we use VESA and not gDisplay edid

	const color_space kRadeonHDSpaces[] = {B_RGB32_LITTLE, B_RGB24_LITTLE,
		B_RGB16_LITTLE, B_RGB15_LITTLE, B_CMAP8};

	gInfo->mode_list_area = create_display_modes("radeon HD modes",
		gInfo->shared_info->has_edid ? &gInfo->shared_info->edid_info : NULL,
		NULL, 0, kRadeonHDSpaces,
		sizeof(kRadeonHDSpaces) / sizeof(kRadeonHDSpaces[0]),
		is_mode_supported, &gInfo->mode_list, &gInfo->shared_info->mode_count);
	if (gInfo->mode_list_area < B_OK)
		return gInfo->mode_list_area;

	gInfo->shared_info->mode_list_area = gInfo->mode_list_area;

	return B_OK;
}


//	#pragma mark -


uint32
radeon_accelerant_mode_count(void)
{
	TRACE("%s\n", __func__);

	return gInfo->shared_info->mode_count;
}


status_t
radeon_get_mode_list(display_mode *modeList)
{
	TRACE("%s\n", __func__);
	memcpy(modeList, gInfo->mode_list,
		gInfo->shared_info->mode_count * sizeof(display_mode));
	return B_OK;
}


status_t
radeon_get_edid_info(void* info, size_t size, uint32* edid_version)
{
	// TODO : multi-monitor?  for now we use VESA and not gDisplay edid

	TRACE("%s\n", __func__);
	if (!gInfo->shared_info->has_edid)
		return B_ERROR;
	if (size < sizeof(struct edid1_info))
		return B_BUFFER_OVERFLOW;

	memcpy(info, &gInfo->shared_info->edid_info, sizeof(struct edid1_info));
	*edid_version = EDID_VERSION_1;

	return B_OK;
}


void
radeon_dpms_set(int mode)
{
	switch(mode) {
		case B_DPMS_ON:
			TRACE("%s: ON\n", __func__);
			for (uint8 id = 0; id < MAX_DISPLAY; id++) {
				if (gDisplay[id]->active == false)
					continue;
				display_crtc_lock(id, ATOM_ENABLE);
				display_crtc_power(id, ATOM_ENABLE);
				display_crtc_memreq(id, ATOM_ENABLE);
				display_crtc_blank(id, ATOM_DISABLE);
				display_crtc_lock(id, ATOM_DISABLE);
			}
			break;
		case B_DPMS_STAND_BY:
		case B_DPMS_SUSPEND:
		case B_DPMS_OFF:
			TRACE("%s: OFF\n", __func__);
			for (uint8 id = 0; id < MAX_DISPLAY; id++) {
				if (gDisplay[id]->active == false)
					continue;
				display_crtc_lock(id, ATOM_ENABLE);
				display_crtc_blank(id, ATOM_ENABLE);
				display_crtc_memreq(id, ATOM_DISABLE);
				display_crtc_power(id, ATOM_DISABLE);
				display_crtc_lock(id, ATOM_DISABLE);
			}
			break;
	}
}


status_t
radeon_set_display_mode(display_mode *mode)
{
	// TODO : multi-monitor?  for now we use VESA and not gDisplay edid
	// Set mode on each display
	for (uint8 id = 0; id < MAX_DISPLAY; id++) {
		if (gDisplay[id]->active == false)
			continue;

		uint16 connector_index = gDisplay[id]->connector_index;

		// *** encoder prep
		encoder_output_lock(true);
		encoder_dpms_set(id, gConnector[connector_index]->encoder.object_id,
			B_DPMS_OFF);
		encoder_assign_crtc(id);

		// *** CRT controler prep
		display_crtc_lock(id, ATOM_ENABLE);
		display_crtc_blank(id, ATOM_ENABLE);
		display_crtc_memreq(id, ATOM_DISABLE);
		display_crtc_power(id, ATOM_DISABLE);

		// *** CRT controler mode set
		// TODO : program SS
		pll_set(ATOM_PPLL1, mode->timing.pixel_clock, id);
			// TODO : check if ATOM_PPLL1 is used and use ATOM_PPLL2 if so
		display_crtc_set_dtd(id, mode);

		// TODO : vvvv : atombios_crtc_set_base
		display_crtc_fb_set_dce1(id, mode);
		// atombios_overscan_setup
		display_crtc_scale(id, mode);

		// *** encoder mode set
		encoder_mode_set(id, mode->timing.pixel_clock);

		// *** CRT controler commit
		display_crtc_blank(id, ATOM_DISABLE);
		display_crtc_memreq(id, ATOM_ENABLE);
		display_crtc_power(id, ATOM_ENABLE);
		display_crtc_lock(id, ATOM_DISABLE);

		// *** encoder commit
		encoder_dpms_set(id, gConnector[connector_index]->encoder.object_id,
			B_DPMS_ON);
		encoder_output_lock(false);
	}

	int32 crtstatus = Read32(CRT, D1CRTC_STATUS);
	TRACE("CRT0 Status: 0x%X\n", crtstatus);
	crtstatus = Read32(CRT, D2CRTC_STATUS);
	TRACE("CRT1 Status: 0x%X\n", crtstatus);

	return B_OK;
}


status_t
radeon_get_display_mode(display_mode *_currentMode)
{
	TRACE("%s\n", __func__);

	*_currentMode = gInfo->shared_info->current_mode;
	return B_OK;
}


status_t
radeon_get_frame_buffer_config(frame_buffer_config *config)
{
	TRACE("%s\n", __func__);

	config->frame_buffer = gInfo->shared_info->frame_buffer;
	config->frame_buffer_dma = (uint8 *)gInfo->shared_info->frame_buffer_phys;

	config->bytes_per_row = gInfo->shared_info->bytes_per_row;

	return B_OK;
}


status_t
radeon_get_pixel_clock_limits(display_mode *mode, uint32 *_low, uint32 *_high)
{
	TRACE("%s\n", __func__);

	if (_low != NULL) {
		// lower limit of about 48Hz vertical refresh
		uint32 totalClocks = (uint32)mode->timing.h_total
			*(uint32)mode->timing.v_total;
		uint32 low = (totalClocks * 48L) / 1000L;

		if (low < PLL_MIN_DEFAULT)
			low = PLL_MIN_DEFAULT;
		else if (low > PLL_MAX_DEFAULT)
			return B_ERROR;

		*_low = low;
	}

	if (_high != NULL)
		*_high = PLL_MAX_DEFAULT;

	//*_low = 48L;
	//*_high = 100 * 1000000L;
	return B_OK;
}


bool
is_mode_supported(display_mode *mode)
{
	TRACE("MODE: %d ; %d %d %d %d ; %d %d %d %d\n",
		mode->timing.pixel_clock, mode->timing.h_display,
		mode->timing.h_sync_start, mode->timing.h_sync_end,
		mode->timing.h_total, mode->timing.v_display,
		mode->timing.v_sync_start, mode->timing.v_sync_end,
		mode->timing.v_total);

	// Validate modeline is within a sane range
	if (is_mode_sane(mode) != B_OK)
		return false;

	// TODO : is_mode_supported on *which* display?
	uint32 crtid = 0;

	// if we have edid info, check frequency adginst crt reported valid ranges
	if (gInfo->shared_info->has_edid
		&& gDisplay[crtid]->found_ranges) {

		uint32 hfreq = mode->timing.pixel_clock / mode->timing.h_total;
		if (hfreq > gDisplay[crtid]->hfreq_max + 1
			|| hfreq < gDisplay[crtid]->hfreq_min - 1) {
			TRACE("!!! hfreq : %d , hfreq_min : %d, hfreq_max : %d\n",
				hfreq, gDisplay[crtid]->hfreq_min, gDisplay[crtid]->hfreq_max);
			TRACE("!!! %dx%d falls outside of CRT %d's valid "
				"horizontal range.\n", mode->timing.h_display,
				mode->timing.v_display, crtid);
			return false;
		}

		uint32 vfreq = mode->timing.pixel_clock / ((mode->timing.v_total
			* mode->timing.h_total) / 1000);

		if (vfreq > gDisplay[crtid]->vfreq_max + 1
			|| vfreq < gDisplay[crtid]->vfreq_min - 1) {
			TRACE("!!! vfreq : %d , vfreq_min : %d, vfreq_max : %d\n",
				vfreq, gDisplay[crtid]->vfreq_min, gDisplay[crtid]->vfreq_max);
			TRACE("!!! %dx%d falls outside of CRT %d's valid vertical range\n",
				mode->timing.h_display, mode->timing.v_display, crtid);
			return false;
		}
	}

	TRACE("%dx%d is within CRT %d's valid frequency range\n",
		mode->timing.h_display, mode->timing.v_display, crtid);

	return true;
}


/*
 * A quick sanity check of the provided display_mode
 */
status_t
is_mode_sane(display_mode *mode)
{
	// horizontal timing
	// validate h_sync_start is less then h_sync_end
	if (mode->timing.h_sync_start > mode->timing.h_sync_end) {
		TRACE("%s: ERROR: (%dx%d) "
			"received h_sync_start greater then h_sync_end!\n",
			__func__, mode->timing.h_display, mode->timing.v_display);
		return B_ERROR;
	}
	// validate h_total is greater then h_display
	if (mode->timing.h_total < mode->timing.h_display) {
		TRACE("%s: ERROR: (%dx%d) "
			"received h_total greater then h_display!\n",
			__func__, mode->timing.h_display, mode->timing.v_display);
		return B_ERROR;
	}

	// vertical timing
	// validate v_start is less then v_end
	if (mode->timing.v_sync_start > mode->timing.v_sync_end) {
		TRACE("%s: ERROR: (%dx%d) "
			"received v_sync_start greater then v_sync_end!\n",
			__func__, mode->timing.h_display, mode->timing.v_display);
		return B_ERROR;
	}
	// validate v_total is greater then v_display
	if (mode->timing.v_total < mode->timing.v_display) {
		TRACE("%s: ERROR: (%dx%d) "
			"received v_total greater then v_display!\n",
			__func__, mode->timing.h_display, mode->timing.v_display);
		return B_ERROR;
	}

	// calculate refresh rate for given timings to whole int (in Hz)
	int refresh = mode->timing.pixel_clock * 1000
		/ (mode->timing.h_total * mode->timing.v_total);

	if (refresh < 30 || refresh > 250) {
		TRACE("%s: ERROR: (%dx%d) "
			"refresh rate of %dHz is unlikely for any kind of monitor!\n",
			__func__, mode->timing.h_display, mode->timing.v_display, refresh);
		return B_ERROR;
	}

	return B_OK;
}


