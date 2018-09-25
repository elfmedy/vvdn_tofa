///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     scale05BilinHVFp16 kernel function call for unitary test
///

#include "scale05BilinHVFp16.h"
#include <stdio.h> 
#include "svuCommonShave.h"
#include "mv_types.h"

#define TEST_FRAME_WIDTH 1920
#define TEST_FRAME_HEIGHT 2

half input[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH];

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
half __attribute__((section(".kept.data"))) output[1][TEST_FRAME_WIDTH] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));


u32 width __attribute__ ((aligned (16)));
half* inLine[TEST_FRAME_HEIGHT];
half* outLine[1];
half** inLines;
half** outLines;



int main( void )
{
	for(int i = 0; i < TEST_FRAME_HEIGHT; i++)
	{
		inLine[i] = (half*)input[i];
	}
	
	outLine[0] = (half*)output[0];
	
	inLines = (half**)inLine;
	outLines = (half**)outLine;
	
	#ifdef UNIT_TEST_USE_C_VERSION
	mvispScale05BilinHVFp16(inLines, outLines, width);
	#else
	mvispScale05BilinHVFp16_asm(inLines, outLines, width);
	#endif
	
	SHAVE_HALT; 
    return 0;
}
