///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief    cvtColorRGBtoNV21 kernel function call for unitary test
///

#include <sLaplacian3x3Fp16ToFp16.h>
#include <mv_types.h>
#include <svuCommonShave.h>

#define TEST_FRAME_WIDTH 1920 + 16
#define TEST_FRAME_HEIGHT 3

half input[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH] __attribute__ ((aligned (16)));

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
half __attribute__((section(".kept.data"))) output[TEST_FRAME_HEIGHT][TEST_FRAME_WIDTH] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));

u32 width __attribute__ ((aligned (16)));

half* inLine[TEST_FRAME_HEIGHT];
half* outLine[TEST_FRAME_HEIGHT];

half** inLines;
half** outLines;
/* half  input[3][56] = {
	{(half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02}, 
	{(half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02}, 
	{(half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02, (half)0.02} 
};
 */

int main( void )
{
	for(int i = 0; i < TEST_FRAME_HEIGHT; i++)
	{
		inLine[i] = (half*)input[i] + 8;
		
	}
	outLine[0] = (half*)output[0];
	
	inLines = (half**)inLine;
	outLines = (half**)outLine;

	#ifdef UNIT_TEST_USE_C_VERSION
    mvcvSLaplacian3x3Fp16ToFp16(inLines, outLines, width);
	#else
	mvcvSLaplacian3x3Fp16ToFp16_asm(inLines, outLines, width);
	#endif
	
	SHAVE_HALT; 
    return 0;
}
