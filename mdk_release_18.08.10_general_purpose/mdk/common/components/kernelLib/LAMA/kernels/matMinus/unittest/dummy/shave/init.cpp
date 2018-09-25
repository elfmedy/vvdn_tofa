///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     ///matrix sub

#include "matMinus.h"
#include <stdio.h>
#include "svuCommonShave.h"
#include "mv_types.h"
#include <moviVectorTypes.h>

#define TEST_MATRIX_HEIGHT 64
#define TEST_MATRIX_WIDTH 64
#define EDGE 16

float input1[TEST_MATRIX_HEIGHT * TEST_MATRIX_WIDTH] __attribute__ ((aligned (16)));
float input2[TEST_MATRIX_HEIGHT * TEST_MATRIX_WIDTH] __attribute__ ((aligned (16)));

/*output pre pad marker*/
uint32_t  __attribute__((section(".kept.data"))) output_u32prePad[4] __attribute__ ((aligned (16)));
/*output data marker*/
float __attribute__((section(".kept.data"))) output[TEST_MATRIX_HEIGHT * TEST_MATRIX_WIDTH + EDGE] __attribute__ ((aligned (16)));
/*output post pad marker*/
uint32_t __attribute__((section(".kept.data"))) output_u32postPad[4] __attribute__ ((aligned (16)));

unsigned int width __attribute__ ((aligned (16)));
unsigned int height __attribute__ ((aligned (16)));

MAT *A;
MAT *B;
MAT *C;
MAT *out;

float matA[30]; ;//28 is size of mat structure
float matB[30]; ;//28 is size of mat structure
float matC[30]; ;//28 is size of mat structure
float matOut[30]; ;//28 is size of mat structure

int main(void)
{
	A   = (MAT *)(&matA[0]); 
	B   = (MAT *)(&matB[0]); 
	C   = (MAT *)(&matC[0]); 
	out = (MAT *)(&matOut[0]); 
	
	A->m    = height;         B->m    = height;           out->m    = height;
	A->n    = width;          B->n    = width;            out->n    = width;

	A->base = (float*)input1; B->base = (float*)input2;   out->base = (float*)output;
	

#ifdef UNIT_TEST_USE_C_VERSION
    C = mvcvMatMinus(A, B, out);
#else
    C = mvcvMatMinus_asm(A, B, out);
#endif

    SHAVE_HALT;
    return 0;
}