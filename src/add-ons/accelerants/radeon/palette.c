/*
	Copyright (c) 2002/03, Thomas Kurschel
	

	Part of Radeon accelerant
		
	Palette handling. Though it's very often referred to as 
	being part of the DAC, this is not really true as palette
	lookup is part of the CRTC unit (else it wouldn't work for
	digital output like DVI)
*/


#include "GlobalData.h"
#include "dac_regs.h"
#include "CP.h"


// Radeon's DACs share same public registers, this function
// selects the DAC you'll talk to
#define selectPalette( head ) \
	WRITE_IB_REG( RADEON_DAC_CNTL2, \
		((head)->is_crtc2 ? RADEON_DAC2_PALETTE_ACC_CTL : 0) | \
		(ai->si->dac_cntl2 & ~RADEON_DAC2_PALETTE_ACC_CTL) );


// set standard colour palette (needed for non-palette modes)
void Radeon_InitPalette( accelerator_info *ai, physical_head *head )
{
	int i;
	
	START_IB();
	
	selectPalette( head );
	
	WRITE_IB_REG( RADEON_PALETTE_INDEX, 0 );
	
	for( i = 0; i < 256; ++i )
		WRITE_IB_REG( RADEON_PALETTE_DATA, (i << 16) | (i << 8) | i );
		
	SUBMIT_IB();
}

static void setPalette( accelerator_info *ai, physical_head *head, 
	uint count, uint8 first, uint8 *color_data );

// public function: set colour palette
void SET_INDEXED_COLORS(uint count, uint8 first, uint8 *color_data, uint32 flags) 
{
	virtual_card *vc = ai->vc;
	shared_info *si = ai->si;
	
	(void)flags;

	SHOW_FLOW( 3, "first=%d, count=%d", first, count );
	
	if( vc->mode.space != B_CMAP8 ) {
		SHOW_ERROR0( 2, "Tried to set palette in non-palette mode" );
		return;
	} 
	
	setPalette( ai, &si->heads[vc->heads[0].physical_head], count, first, color_data );
	
	if( vc->independant_heads > 1 )
		setPalette( ai, &si->heads[vc->heads[1].physical_head], count, first, color_data );
}


// set palette of one DAC
static void setPalette( accelerator_info *ai, physical_head *head, 
	uint count, uint8 first, uint8 *color_data )
{
	uint i;
	
	START_IB();
	
	selectPalette( head );
	
	WRITE_IB_REG( RADEON_PALETTE_INDEX, first );
	
	for( i = 0; i < count; ++i, color_data += 3 )
		WRITE_IB_REG( RADEON_PALETTE_DATA, 
			((uint32)color_data[0] << 16) | 
			((uint32)color_data[1] << 8) | 
			 color_data[2] );
			 
	SUBMIT_IB();
}
