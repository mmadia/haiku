/*
** Copyright 2003-2004, Axel Dörfler, axeld@pinc-software.de. All rights reserved.
** Distributed under the terms of the OpenBeOS License.
*/


#include "console.h"
#include "mmu.h"

#include <SupportDefs.h>
#include <boot/platform.h>
#include <boot/heap.h>
#include <boot/stage2.h>

#include <string.h>


#define HEAP_SIZE 32768

// GCC defined globals
extern void (*__ctor_list)(void);
extern void (*__ctor_end)(void);
extern uint8 __bss_start;
extern uint8 _end;

extern int main(stage2_args *args);
void _start(void);


static void
clear_bss(void)
{
	memset(&__bss_start, 0, &_end - &__bss_start);
}


static void
call_ctors(void)
{ 
	void (**f)(void);

	for (f = &__ctor_list; f < &__ctor_end; f++) {		
		(**f)();
	}
}


bool
platform_user_menu_requested(void)
{
	return false;
}


void
platform_start_kernel(void)
{
	mmu_init_for_kernel();
	printf("kernel entry at %lx\n", gKernelEntry);

	asm("movl	%0, %%eax;	"			// move stack out of way
		"movl	%%eax, %%esp; "
		: : "m" (gKernelArgs.cpu_kstack[0].start + gKernelArgs.cpu_kstack[0].size));
	asm("pushl  $0x0; "					// we're the BSP cpu (0)
		"pushl 	%0;	"					// kernel args
		"pushl 	$0x0;"					// dummy retval for call to main
		"pushl 	%1;	"					// this is the start address
		"ret;		"					// jump.
		: : "g" (&gKernelArgs), "g" (gKernelEntry));
}


void
_start(void)
{
	stage2_args args;

	asm("cld");			// Ain't nothing but a GCC thang.
	asm("fninit");		// initialize floating point unit

	clear_bss();

	call_ctors();
		// call C++ constructors before doing anything else

	args.heap_size = HEAP_SIZE;

	console_init();
	mmu_init();

	main(&args);
}

