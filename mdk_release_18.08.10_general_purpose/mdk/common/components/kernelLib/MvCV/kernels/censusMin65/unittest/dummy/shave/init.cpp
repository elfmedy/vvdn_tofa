///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
///

#include "censusMin65.h"
#include <stdio.h> 
#include "svuCommonShave.h"
#include "mv_types.h"

#define DISPARITIES 65
#define PADDING 32
#define TEST_FRAME_WIDTH (1920 )


unsigned char __attribute__ ((aligned (16))) input1[TEST_FRAME_WIDTH * DISPARITIES] ;

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
unsigned char __attribute__((section(".kept.data"))) output[TEST_FRAME_WIDTH + PADDING] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));


unsigned char *in1;
unsigned char *out;
unsigned int width;

int main( void )
{
    in1 = (unsigned char *)input1;
	out = (unsigned char *)output + PADDING/2;
	
	//printf("%x %x %x \n", in1,in2,out);
	#ifdef UNIT_TEST_USE_C_VERSION
		mvcvCensusMin65(in1,out,width);
	#else
		mvcvCensusMin65_asm(in1,out,width);
	#endif
	
	SHAVE_HALT; 
    return 0;
}