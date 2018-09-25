// Low Level Correction contain black level correction and corect bad pixel
#include <sipp.h>
#include <sippShaveMacros.h>
#include <filters/lowLvlCorr/lowLvlCorr.h>

#define SUB_SATURATE(x,y) (x < y ? 0 : (x - y))
//#define MAX(x,y) (x < y ? y : x)
//#define MIN(x,y) (x < y ? x : y)
//##########################################################################################
void svuLowLvlCorr(SippFilter *fptr)
{
    UInt32 x;
    LowLvlCorrParam *param = (LowLvlCorrParam *)fptr->params;
    UInt16 blackLevel = param->blackLevel;
    float  alpha      = param->alphaBadPixel;

    //Input pointers
    UInt16  *in[3];

    UInt32 numLinesThisIter = sippFilterGetLinesThisIter (fptr);
    UInt32 iterNum;

    for (iterNum = 0; iterNum < numLinesThisIter; iterNum++)
    {

        in[0]= (UInt16 *)getInPtr(fptr, 0, iterNum, 0, 0);
        in[1]= (UInt16 *)getInPtr(fptr, 0, iterNum, 1, 0);
        in[2]= (UInt16 *)getInPtr(fptr, 0, iterNum, 2, 0);

        //Output pointers
        UInt16  *out = (UInt16 *)getOutPtr(fptr, iterNum, 0);

        for(x=0; x<fptr->sliceWidth; x++)
        {
            UInt16 maxim =
            MAX(
                MAX(
                    MAX(SUB_SATURATE(in[0][x-1],blackLevel),SUB_SATURATE(in[2][x-1],blackLevel)),
                    MAX(SUB_SATURATE(in[0][x-0],blackLevel),SUB_SATURATE(in[2][x-0],blackLevel))
                ),
                MAX(
                    MAX(SUB_SATURATE(in[0][x+1],blackLevel),SUB_SATURATE(in[2][x+1],blackLevel)),
                    MAX(SUB_SATURATE(in[1][x-1],blackLevel),SUB_SATURATE(in[1][x+1],blackLevel))
                )
            );

            UInt16 minim =
            MIN(
                MIN(
                    MIN(SUB_SATURATE(in[0][x-1],blackLevel),SUB_SATURATE(in[2][x-1],blackLevel)),
                    MIN(SUB_SATURATE(in[0][x-0],blackLevel),SUB_SATURATE(in[2][x-0],blackLevel))
                ),
                MIN(
                    MIN(SUB_SATURATE(in[0][x+1],blackLevel),SUB_SATURATE(in[2][x+1],blackLevel)),
                    MIN(SUB_SATURATE(in[1][x-1],blackLevel),SUB_SATURATE(in[1][x+1],blackLevel))
                )
            );

            float fp = (float)SUB_SATURATE(in[1][x+0],blackLevel);
            float mxf = (float)maxim;
            float mnf = (float)minim;
            if (fp > alpha * mxf)
            {
                out[x] = maxim;
            }
            else
            {
                if (fp < mnf/alpha )
                {
                    out[x] = minim;
                }
                else
                {
                    out[x] = SUB_SATURATE(in[1][x+0],blackLevel);
                }
            }
        }
    }
}
