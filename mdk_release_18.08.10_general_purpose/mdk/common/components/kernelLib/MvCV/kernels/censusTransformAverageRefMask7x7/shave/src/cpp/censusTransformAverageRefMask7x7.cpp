#include <censusTransformAverageRefMask7x7.h>
#include <stdio.h>
/*
COLUMNS MASK - only the elements marked with 1 in the below mask, are compared with the reference value
1 0 1 0 1 0 1
1 0 1 0 1 0 1
1 0 1 0 1 0 1
1 0 1 0 1 0 1
1 0 1 0 1 0 1
1 0 1 0 1 0 1
1 0 1 0 1 0 1
*/

void mvcvCensusTransformAverageRefMask7x7(u8 **in, u32 *out, u32 width)
{
    int threshold = 1;
    int referenceValue;
    half referenceValue_half;
    int windowHeight = 7;

    for (unsigned int i = 0; i < width; i++)
    {
        out[i] = 0;
        referenceValue = 0;

        for (int line = 0; line < windowHeight; line++)
        {
            for (int col = -3; col <= 3; col++)
            {
                referenceValue += *(in[line] + i + col);
            }
        }
        referenceValue_half = ((half)referenceValue * (half)(0.02040816326530612244897959183673)); // this is actualy value divided by 49 (window size 7x7)
          referenceValue = (int)referenceValue_half;
        for (int line = 0; line < windowHeight; line++)
        {
            for (int col = -3; col <= 3; col+=2)
            {
                out[i] *= 2;
                if (*(in[line] + i + col) + threshold < referenceValue)
                {
                    out[i] += 1;
                }
            }
        }
    }
}
