/*
 * Copyright 2002-2012 Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _ARCH_SIGNAL_H_
#define _ARCH_SIGNAL_H_


/*
 * Architecture-specific structure passed to signal handlers
 */

#if __INTEL__

typedef struct _HAIKU_BUILD_IDENTIFIER(packed_fp_stack) {
	unsigned char	st0[10];
	unsigned char	st1[10];
	unsigned char	st2[10];
	unsigned char	st3[10];
	unsigned char	st4[10];
	unsigned char	st5[10];
	unsigned char	st6[10];
	unsigned char	st7[10];
} _HAIKU_BUILD_IDENTIFIER(packed_fp_stack);

typedef struct _HAIKU_BUILD_IDENTIFIER(packed_mmx_regs) {
	unsigned char	mm0[10];
	unsigned char	mm1[10];
	unsigned char	mm2[10];
	unsigned char	mm3[10];
	unsigned char	mm4[10];
	unsigned char	mm5[10];
	unsigned char	mm6[10];
	unsigned char	mm7[10];
} _HAIKU_BUILD_IDENTIFIER(packed_mmx_regs);

typedef struct _HAIKU_BUILD_IDENTIFIER(old_extended_regs) {
	unsigned short	fp_control;
	unsigned short	_reserved1;
	unsigned short	fp_status;
	unsigned short	_reserved2;
	unsigned short	fp_tag;
	unsigned short	_reserved3;
	unsigned long	fp_eip;
	unsigned short	fp_cs;
	unsigned short	fp_opcode;
	unsigned long	fp_datap;
	unsigned short	fp_ds;
	unsigned short	_reserved4;
	union {
		_HAIKU_BUILD_IDENTIFIER(packed_fp_stack)	fp;
		_HAIKU_BUILD_IDENTIFIER(packed_mmx_regs)	mmx;
	} _HAIKU_BUILD_IDENTIFIER(fp_mmx);
} _HAIKU_BUILD_IDENTIFIER(old_extended_regs);

typedef struct _HAIKU_BUILD_IDENTIFIER(fp_stack) {
	unsigned char	st0[10];
	unsigned char	_reserved_42_47[6];
	unsigned char	st1[10];
	unsigned char	_reserved_58_63[6];
	unsigned char	st2[10];
	unsigned char	_reserved_74_79[6];
	unsigned char	st3[10];
	unsigned char	_reserved_90_95[6];
	unsigned char	st4[10];
	unsigned char	_reserved_106_111[6];
	unsigned char	st5[10];
	unsigned char	_reserved_122_127[6];
	unsigned char	st6[10];
	unsigned char	_reserved_138_143[6];
	unsigned char	st7[10];
	unsigned char	_reserved_154_159[6];
} _HAIKU_BUILD_IDENTIFIER(fp_stack);

typedef struct _HAIKU_BUILD_IDENTIFIER(mmx_regs) {
	unsigned char	mm0[10];
	unsigned char	_reserved_42_47[6];
	unsigned char	mm1[10];
	unsigned char	_reserved_58_63[6];
	unsigned char	mm2[10];
	unsigned char	_reserved_74_79[6];
	unsigned char	mm3[10];
	unsigned char	_reserved_90_95[6];
	unsigned char	mm4[10];
	unsigned char	_reserved_106_111[6];
	unsigned char	mm5[10];
	unsigned char	_reserved_122_127[6];
	unsigned char	mm6[10];
	unsigned char	_reserved_138_143[6];
	unsigned char	mm7[10];
	unsigned char	_reserved_154_159[6];
} _HAIKU_BUILD_IDENTIFIER(mmx_regs);

typedef struct _HAIKU_BUILD_IDENTIFIER(xmmx_regs) {
	unsigned char	xmm0[16];
	unsigned char	xmm1[16];
	unsigned char	xmm2[16];
	unsigned char	xmm3[16];
	unsigned char	xmm4[16];
	unsigned char	xmm5[16];
	unsigned char	xmm6[16];
	unsigned char	xmm7[16];
} _HAIKU_BUILD_IDENTIFIER(xmmx_regs);

typedef struct _HAIKU_BUILD_IDENTIFIER(new_extended_regs) {
	unsigned short	fp_control;
	unsigned short	fp_status;
	unsigned short	fp_tag;
	unsigned short	fp_opcode;
	unsigned long	fp_eip;
	unsigned short	fp_cs;
	unsigned short	res_14_15;
	unsigned long	fp_datap;
	unsigned short	fp_ds;
	unsigned short	_reserved_22_23;
	unsigned long	mxcsr;
	unsigned long	_reserved_28_31;
	union {
		_HAIKU_BUILD_IDENTIFIER(fp_stack) fp;
		_HAIKU_BUILD_IDENTIFIER(mmx_regs) mmx;
	} _HAIKU_BUILD_IDENTIFIER(fp_mmx);
	_HAIKU_BUILD_IDENTIFIER(xmmx_regs) xmmx;
	unsigned char	_reserved_288_511[224];
} _HAIKU_BUILD_IDENTIFIER(new_extended_regs);

typedef struct _HAIKU_BUILD_IDENTIFIER(extended_regs) {
	union {
		_HAIKU_BUILD_IDENTIFIER(old_extended_regs)	old_format;
		_HAIKU_BUILD_IDENTIFIER(new_extended_regs)	new_format;
	} _HAIKU_BUILD_IDENTIFIER(state);
	unsigned long	format;
} _HAIKU_BUILD_IDENTIFIER(extended_regs);

struct _HAIKU_BUILD_IDENTIFIER(vregs) {
	unsigned long							eip;
	unsigned long							eflags;
	unsigned long							eax;
	unsigned long							ecx;
	unsigned long							edx;
	unsigned long							esp;
	unsigned long							ebp;
	unsigned long							_reserved_1;
	_HAIKU_BUILD_IDENTIFIER(extended_regs)	xregs;
	unsigned long							edi;
	unsigned long							esi;
	unsigned long							ebx;
};

#endif /* __INTEL__ */

#endif /* _ARCH_SIGNAL_H_ */
