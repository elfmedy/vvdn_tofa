#ifndef _CONVOLUTION9x9S4HHHH_ASM_TEST_H_
#define _CONVOLUTION9x9S4HHHH_ASM_TEST_H_

#include "half.h"

extern unsigned int convolution9x9s4hhhhCycleCount;
void Convolution9x9s4hhhh_asm_test(half** in, half** out, half conv[81], unsigned int width);

#endif //_CONVOLUTION9x9S4HHHH_ASM_TEST_H_