#ifndef _CONVOLUTION3X3S2XHHX_ASM_TEST_H_
#define _CONVOLUTION3X3S2XHHX_ASM_TEST_H_

#include "half.h"

extern unsigned int convolution3x3s2xhhxCycleCount;
void Convolution3x3s2xhhx_asm_test(unsigned char** in, unsigned char** out, half conv[9], unsigned int width);

#endif //_CONVOLUTION3X3XHHX_ASM_TEST_H_
