///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     AccumulateWeighted kernel function call for unitary test
///

#include "accumulateWeighted.h"
#include <stdio.h> 
#include "svuCommonShave.h"
#include "mv_types.h"


#define TEST_FRAME_WIDTH 1920
#define TEST_FRAME_HEIGHT 4

u8 input[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH] __attribute__ ((aligned (16)));
u8 mask[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH] __attribute__ ((aligned (16)));

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
u8 __attribute__((section(".kept.data"))) output[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH * 4] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));


u32 width;
fp32 alpha;
u8* inLine[TEST_FRAME_HEIGHT];
u8* inMask[TEST_FRAME_HEIGHT];
fp32* outLine[TEST_FRAME_HEIGHT];
u8** inLines;
u8** inMasks;
fp32** outLines;


int main( void )
{
//	AccumulateWeighted(u8** srcAddr, u8** maskAddr, fp32** destAddr,u32 width, fp32 alpha)

	for(int i = 0; i < TEST_FRAME_HEIGHT; i++)
	{
		inLine[i] = (u8*)input[i];
		inMask[i] = (u8*)mask[i];
		outLine[i] = (fp32*)output[i];
	}

	inLines = (u8**)inLine;
	inMasks = (u8**)inMask;
	outLines = (fp32**)outLine;

	#ifdef UNIT_TEST_USE_C_VERSION
	mvcvAccumulateWeighted(inLines, inMasks, outLines, width, alpha);
	#else
	mvcvAccumulateWeighted_asm(inLines, inMasks, outLines, width, alpha);
	#endif

	SHAVE_HALT; 
    return 0;
}