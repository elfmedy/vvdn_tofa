#include <sipp.h>
#include <sippShaveMacros.h>
#include <filters/dilate5x5/dilate5x5.h>

/// Dilate5x5 kernel
/// @param[in]  src      - array of pointers to input lines of the input image
/// @param[out] dst      - array of pointers to output lines
/// @param[in]  kernel   - array of pointers to input kernel
/// @param[in]  width    - width  of the input line

#ifdef SIPP_USE_MVCV
void mvcvDilate5x5_asm(UInt8** src, UInt8** dst, UInt8** kernel, UInt32 width);
#else
void Dilate5x5        (UInt8** src, UInt8** dst, UInt8** kernel, UInt32 width)
{
    int j,i1,j1;
    UInt8 max = 0;
    UInt8* row[5];

    for(j = 0;j < 5; j++)
        row[j] = src[j];

    // Determine the anchor positions which must be replaces by a maximum value
    for ( j = 0; j < width; j++)
    {
        max = 0;
        // Determine the maximum number into a k*k square
        for(i1 = 0; i1 < 5; i1++ )
        {
            for (j1 = 0; j1 < 5; j1++)
            {
                if(kernel[i1][j1]==1)
                {
                    if(max < row[i1][j1 + j - 2]){

                        max = row[i1][j1 + j - 2];
                    }
                }
            }
        }
        dst[0][j] = max;
    }
}
#endif

void svuDilate5x5(SippFilter *fptr)
{
    UInt8 *output;
    UInt8 *iline[5];
    Dilate5x5Param *param = (Dilate5x5Param*)fptr->params;

    UInt32 numLinesThisIter = sippFilterGetLinesThisIter (fptr);
    UInt32 iterNum;

    for (iterNum = 0; iterNum < numLinesThisIter; iterNum++)
    {
        //the 5 input lines
        iline[0]=(UInt8 *)getInPtr(fptr, 0, iterNum, 0, 0);
        iline[1]=(UInt8 *)getInPtr(fptr, 0, iterNum, 1, 0);
        iline[2]=(UInt8 *)getInPtr(fptr, 0, iterNum, 2, 0);
        iline[3]=(UInt8 *)getInPtr(fptr, 0, iterNum, 3, 0);
        iline[4]=(UInt8 *)getInPtr(fptr, 0, iterNum, 4, 0);
        //the output line
        output = (UInt8 *)getOutPtr(fptr, iterNum, 0);

    #ifdef SIPP_USE_MVCV
        mvcvDilate5x5_asm(iline, &output, (UInt8**)(param->dMat), fptr->sliceWidth);
    #else
        Dilate5x5(iline, &output, (UInt8**)(param->dMat), fptr->sliceWidth);
    #endif
    }
}
