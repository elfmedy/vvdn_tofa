#include "censusMatching16.h"

void mvcvCensusMatching16(u32 *in1, u32 *in2, u8 *out, u32 width)
{
    u32 resultXOR, disparities = 16;
    u8 bitCount;

    for (u32 positionL = 0; positionL < width; positionL++)
    { // for each pixels

        for (u32 indexR = 0; indexR < disparities; indexR++)
        { // for all disparities

            resultXOR = *(in1 + positionL) ^ *(in2 + positionL - indexR);

            for(bitCount = 0; resultXOR; resultXOR >>= 1)
            {
                bitCount += resultXOR & 1;
            }

            out[positionL * disparities + indexR] = bitCount;
        } // Finish all disparities of one pixel

    } // Finish all pixels
}