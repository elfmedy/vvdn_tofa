////// @file gtmFp16ToFp16.cpp/// @copyright All code copyright Movidius Ltd 2012, all rights reserved///            For License Warranty see: common/license.txt////// @brief ///#include "gtmFp16ToFp16.h"#include <math.h>#include <stdlib.h>#include <stdio.h>//                             i18          i17         i16          i15         i14void mvispGtmFp16ToFp16(half* iline, half* output, u32 width, half* scurve, int nPoints){   int index;   u32 i;   for (i = 0; i < width; i++)   {      index = (int)((float)iline[i] * (nPoints - 1));      output[i] = scurve[index];      }}