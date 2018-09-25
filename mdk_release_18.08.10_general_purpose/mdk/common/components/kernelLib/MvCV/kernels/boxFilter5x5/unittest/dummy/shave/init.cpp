///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     boxfilter5x5 kernel function call for unitary test
///

#include "boxFilter5x5.h"
#include <stdio.h> 
#include "svuCommonShave.h"
#include "mv_types.h"

#define TEST_FRAME_WIDTH 1920 + 16
#define TEST_FRAME_HEIGHT 16

u8 __attribute__ ((aligned (16))) input[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH];
u8 __attribute__ ((aligned (16))) output[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH];
u32 normalize;
u32 width;
u8* inLine[TEST_FRAME_HEIGHT];
u8* outLine[TEST_FRAME_HEIGHT];
u8** inLines;
u8** outLines;


int main( void )
{
	for(int i = 0; i < TEST_FRAME_HEIGHT; i++)
	{
		inLine[i] = (u8*)input[i] + 8;
		outLine[i] = (u8*)output[i];
	}

	inLines = (u8**)inLine;
	outLines = (u8**)outLine;

	#ifdef UNIT_TEST_USE_C_VERSION
	mvcvBoxfilter5x5(inLines, outLines, normalize, width);
	#else
		#ifdef MOVICOMPILE_OPTIMIZED
		mvcvBoxfilter5x5_opt(inLines, outLines, normalize, width);
		#else 
		mvcvBoxfilter5x5_asm(inLines, outLines, normalize, width);
		#endif
	#endif
	
	

	SHAVE_HALT; 
    return 0;
}
