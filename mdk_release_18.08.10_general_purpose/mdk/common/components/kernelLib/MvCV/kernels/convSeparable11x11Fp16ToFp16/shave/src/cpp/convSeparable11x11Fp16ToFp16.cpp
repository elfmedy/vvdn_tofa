#include "convSeparable11x11Fp16ToFp16.h"

void mvcvConvSeparable11x11Fp16ToFp16(half** out, half** in, half conv[6], u32 inWidth)
{
    int i;
    half* lines[11];
    float sum = 0.0f;

    //Initialize lines pointers
    lines[0]  = in[0];
    lines[1]  = in[1];
    lines[2]  = in[2];
    lines[3]  = in[3];
    lines[4]  = in[4];
    lines[5]  = in[5];
    lines[6]  = in[6];
    lines[7]  = in[7];
    lines[8]  = in[8];
    lines[9]  = in[9];
    lines[10] = in[10];

    //Go on the whole line
    for (i = 0; i < (int)inWidth; i++){
		sum = ((float)(lines[0][i-5] + lines[10][i-5]) * (float)conv[0] + (float)(lines[1][i-5] + lines[9][i-5]) * (float)conv[1] + (float)(lines[2][i-5] + lines[8][i-5]) * (float)conv[2] + (float)(lines[3][i-5] + lines[7][i-5]) * (float)conv[3] + (float)(lines[4][i-5] + lines[6][i-5]) * (float)conv[4] + (float)lines[5][i-5] * (float)conv[5] +
			   (float)(lines[0][i+5] + lines[10][i+5]) * (float)conv[0] + (float)(lines[1][i+5] + lines[9][i+5]) * (float)conv[1] + (float)(lines[2][i+5] + lines[8][i+5]) * (float)conv[2] + (float)(lines[3][i+5] + lines[7][i+5]) * (float)conv[3] + (float)(lines[4][i+5] + lines[6][i+5]) * (float)conv[4] + (float)lines[5][i+5] * (float)conv[5]) * (float)conv[0] +
              ((float)(lines[0][i-4] + lines[10][i-4]) * (float)conv[0] + (float)(lines[1][i-4] + lines[9][i-4]) * (float)conv[1] + (float)(lines[2][i-4] + lines[8][i-4]) * (float)conv[2] + (float)(lines[3][i-4] + lines[7][i-4]) * (float)conv[3] + (float)(lines[4][i-4] + lines[6][i-4]) * (float)conv[4] + (float)lines[5][i-4] * (float)conv[5] +
			   (float)(lines[0][i+4] + lines[10][i+4]) * (float)conv[0] + (float)(lines[1][i+4] + lines[9][i+4]) * (float)conv[1] + (float)(lines[2][i+4] + lines[8][i+4]) * (float)conv[2] + (float)(lines[3][i+4] + lines[7][i+4]) * (float)conv[3] + (float)(lines[4][i+4] + lines[6][i+4]) * (float)conv[4] + (float)lines[5][i+4] * (float)conv[5]) * (float)conv[1] +
              ((float)(lines[0][i-3] + lines[10][i-3]) * (float)conv[0] + (float)(lines[1][i-3] + lines[9][i-3]) * (float)conv[1] + (float)(lines[2][i-3] + lines[8][i-3]) * (float)conv[2] + (float)(lines[3][i-5] + lines[7][i-3]) * (float)conv[3] + (float)(lines[4][i-3] + lines[6][i-3]) * (float)conv[4] + (float)lines[5][i-3] * (float)conv[5] +
			   (float)(lines[0][i+3] + lines[10][i+3]) * (float)conv[0] + (float)(lines[1][i+3] + lines[9][i+3]) * (float)conv[1] + (float)(lines[2][i+3] + lines[8][i+3]) * (float)conv[2] + (float)(lines[3][i+5] + lines[7][i+3]) * (float)conv[3] + (float)(lines[4][i+3] + lines[6][i+3]) * (float)conv[4] + (float)lines[5][i+3] * (float)conv[5]) * (float)conv[2] +
              ((float)(lines[0][i-2] + lines[10][i-2]) * (float)conv[0] + (float)(lines[1][i-2] + lines[9][i-2]) * (float)conv[1] + (float)(lines[2][i-2] + lines[8][i-2]) * (float)conv[2] + (float)(lines[3][i-5] + lines[7][i-2]) * (float)conv[3] + (float)(lines[4][i-2] + lines[6][i-2]) * (float)conv[4] + (float)lines[5][i-2] * (float)conv[5] +
			   (float)(lines[0][i+2] + lines[10][i+2]) * (float)conv[0] + (float)(lines[1][i+2] + lines[9][i+2]) * (float)conv[1] + (float)(lines[2][i+2] + lines[8][i+2]) * (float)conv[2] + (float)(lines[3][i+5] + lines[7][i+2]) * (float)conv[3] + (float)(lines[4][i+2] + lines[6][i+2]) * (float)conv[4] + (float)lines[5][i+2] * (float)conv[5]) * (float)conv[3] +
			  ((float)(lines[0][i-1] + lines[10][i-1]) * (float)conv[0] + (float)(lines[1][i-1] + lines[9][i-1]) * (float)conv[1] + (float)(lines[2][i-1] + lines[8][i-1]) * (float)conv[2] + (float)(lines[3][i-1] + lines[7][i-1]) * (float)conv[3] + (float)(lines[4][i-1] + lines[6][i-1]) * (float)conv[4] + (float)lines[5][i-1] * (float)conv[5] +
			   (float)(lines[0][i+1] + lines[10][i+1]) * (float)conv[0] + (float)(lines[1][i+1] + lines[9][i+1]) * (float)conv[1] + (float)(lines[2][i+1] + lines[8][i+1]) * (float)conv[2] + (float)(lines[3][i+1] + lines[7][i+1]) * (float)conv[3] + (float)(lines[4][i+1] + lines[6][i+1]) * (float)conv[4] + (float)lines[5][i+1] * (float)conv[5]) * (float)conv[4] +
			  ((float)(lines[0][i  ] + lines[10][i  ]) * (float)conv[0] + (float)(lines[1][i  ] + lines[9][i  ]) * (float)conv[1] + (float)(lines[2][i  ] + lines[8][i  ]) * (float)conv[2] + (float)(lines[3][i  ] + lines[7][i  ]) * (float)conv[3] + (float)(lines[4][i  ] + lines[6][i  ]) * (float)conv[4] + (float)lines[5][i  ] * (float)conv[5]) * (float)conv[5];

        out[0][i] = (half)(sum);
    }
    return;
}