///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief    	scale05BilinHV_U16ToU16 kernel function call for unitary test
///

#include <scale05BilinHV_U16ToU16.h>
#include <stdio.h> 
#include <svuCommonShave.h>
#include <mv_types.h>


#define OUT_PADDING 16
#define TEST_FRAME_WIDTH 1920
#define TEST_FRAME_HEIGHT 2

u16 input[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH * 2] __attribute__ ((aligned (16)));

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
u16 __attribute__((section(".kept.data"))) output[TEST_FRAME_WIDTH + 2 * OUT_PADDING] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));

u32 width __attribute__ ((aligned (16)));
u16 *inLine[TEST_FRAME_HEIGHT];
u16 **inLines;

int main( void )
{

	for(int i = 0; i < TEST_FRAME_HEIGHT; i++)
	{
		inLine[i] = (u16*)input[i];
	}
	inLines = (u16**)inLine;
	
	#ifdef UNIT_TEST_USE_C_VERSION
	mvispScale05BilinHV_U16ToU16(inLines, &output[OUT_PADDING], width);
	#else
	mvispScale05BilinHV_U16ToU16_asm(inLines, &output[OUT_PADDING], width);
	#endif
		
	SHAVE_HALT; 
    return 0;
}
