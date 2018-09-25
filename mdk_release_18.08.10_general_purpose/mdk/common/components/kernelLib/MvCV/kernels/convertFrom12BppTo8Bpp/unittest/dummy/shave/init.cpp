///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     cvtColor kernel function call for unitary test
///

#include <convertFrom12BppTo8Bpp.h>
#include <stdio.h> 
#include "svuCommonShave.h"
#include "mv_types.h"

#define TEST_FRAME_WIDTH 1920
#define TEST_FRAME_HEIGHT 2

u8 input[TEST_FRAME_HEIGHT*TEST_FRAME_WIDTH*2] __attribute__ ((aligned (16)));

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
u8 __attribute__((section(".kept.data"))) output[TEST_FRAME_HEIGHT*TEST_FRAME_WIDTH] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));


u32 width;

int main( void )
{
	#ifdef UNIT_TEST_USE_C_VERSION
	mvcvConvert12BppTo8Bpp(output, input, width);
	#else
	#ifdef MOVICOMPILE_OPTIMIZED
		mvcvConvert12BppTo8Bpp_opt(output, input, width);
		#else
		mvcvConvert12BppTo8Bpp_asm(output, input, width);
		#endif
	#endif
	SHAVE_HALT; 
    return 0;
}
