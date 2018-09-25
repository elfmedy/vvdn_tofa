#include <stdint.h>
#include "isp_params_wrap.h" //ALIGNED macro

//Dumped from:
// http://dub30/svn/TRUNK/fragrak_v2/data/fragrak/sipp/MODELS/sipp_hw/octave_compare/luttest/test.cpp
//fp16 channel mode LUT
uint16_t gammaLutFp16[512*4] ALIGNED(8) = 
{
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000,  0x0000,0x0000,0x0000,0x0000, 
     0x0000,0x0000,0x0000,0x0000,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00,  0x1d00,0x1d00,0x1d00,0x1d00, 
     0x1d00,0x1d00,0x1d00,0x1d00,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f, 
     0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f, 
     0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f, 
     0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f,  0x207f,0x207f,0x207f,0x207f, 
     0x207f,0x207f,0x207f,0x207f,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300, 
     0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300, 
     0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300, 
     0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300,  0x2300,0x2300,0x2300,0x2300, 
     0x2300,0x2300,0x2300,0x2300,  0x247f,0x247f,0x247f,0x247f,  0x247f,0x247f,0x247f,0x247f,  0x247f,0x247f,0x247f,0x247f, 
     0x247f,0x247f,0x247f,0x247f,  0x247f,0x247f,0x247f,0x247f,  0x247f,0x247f,0x247f,0x247f,  0x247f,0x247f,0x247f,0x247f, 
     0x247f,0x247f,0x247f,0x247f,  0x25c0,0x25c0,0x25c0,0x25c0,  0x25c0,0x25c0,0x25c0,0x25c0,  0x25c0,0x25c0,0x25c0,0x25c0, 
     0x25c0,0x25c0,0x25c0,0x25c0,  0x25c0,0x25c0,0x25c0,0x25c0,  0x25c0,0x25c0,0x25c0,0x25c0,  0x25c0,0x25c0,0x25c0,0x25c0, 
     0x25c0,0x25c0,0x25c0,0x25c0,  0x26bf,0x26bf,0x26bf,0x26bf,  0x26bf,0x26bf,0x26bf,0x26bf,  0x26bf,0x26bf,0x26bf,0x26bf, 
     0x26bf,0x26bf,0x26bf,0x26bf,  0x26bf,0x26bf,0x26bf,0x26bf,  0x26bf,0x26bf,0x26bf,0x26bf,  0x26bf,0x26bf,0x26bf,0x26bf, 
     0x26bf,0x26bf,0x26bf,0x26bf,  0x2800,0x2800,0x2800,0x2800,  0x2800,0x2800,0x2800,0x2800,  0x2800,0x2800,0x2800,0x2800, 
     0x2800,0x2800,0x2800,0x2800,  0x2800,0x2800,0x2800,0x2800,  0x2800,0x2800,0x2800,0x2800,  0x2800,0x2800,0x2800,0x2800, 
     0x2800,0x2800,0x2800,0x2800,  0x287f,0x287f,0x287f,0x287f,  0x287f,0x287f,0x287f,0x287f,  0x287f,0x287f,0x287f,0x287f, 
     0x287f,0x287f,0x287f,0x287f,  0x2940,0x2940,0x2940,0x2940,  0x2940,0x2940,0x2940,0x2940,  0x2940,0x2940,0x2940,0x2940, 
     0x2940,0x2940,0x2940,0x2940,  0x2a00,0x2a00,0x2a00,0x2a00,  0x2a00,0x2a00,0x2a00,0x2a00,  0x2a00,0x2a00,0x2a00,0x2a00, 
     0x2a00,0x2a00,0x2a00,0x2a00,  0x2abf,0x2abf,0x2abf,0x2abf,  0x2abf,0x2abf,0x2abf,0x2abf,  0x2abf,0x2abf,0x2abf,0x2abf, 
     0x2abf,0x2abf,0x2abf,0x2abf,  0x2b80,0x2b80,0x2b80,0x2b80,  0x2b80,0x2b80,0x2b80,0x2b80,  0x2b80,0x2b80,0x2b80,0x2b80, 
     0x2b80,0x2b80,0x2b80,0x2b80,  0x2c1f,0x2c1f,0x2c1f,0x2c1f,  0x2c1f,0x2c1f,0x2c1f,0x2c1f,  0x2c1f,0x2c1f,0x2c1f,0x2c1f, 
     0x2c1f,0x2c1f,0x2c1f,0x2c1f,  0x2c7f,0x2c7f,0x2c7f,0x2c7f,  0x2c7f,0x2c7f,0x2c7f,0x2c7f,  0x2c7f,0x2c7f,0x2c7f,0x2c7f, 
     0x2c7f,0x2c7f,0x2c7f,0x2c7f,  0x2ce0,0x2ce0,0x2ce0,0x2ce0,  0x2ce0,0x2ce0,0x2ce0,0x2ce0,  0x2ce0,0x2ce0,0x2ce0,0x2ce0, 
     0x2ce0,0x2ce0,0x2ce0,0x2ce0,  0x2d3f,0x2d3f,0x2d3f,0x2d3f,  0x2d3f,0x2d3f,0x2d3f,0x2d3f,  0x2da0,0x2da0,0x2da0,0x2da0, 
     0x2da0,0x2da0,0x2da0,0x2da0,  0x2e00,0x2e00,0x2e00,0x2e00,  0x2e00,0x2e00,0x2e00,0x2e00,  0x2e5f,0x2e5f,0x2e5f,0x2e5f, 
     0x2e5f,0x2e5f,0x2e5f,0x2e5f,  0x2ec0,0x2ec0,0x2ec0,0x2ec0,  0x2ec0,0x2ec0,0x2ec0,0x2ec0,  0x2f1f,0x2f1f,0x2f1f,0x2f1f, 
     0x2f1f,0x2f1f,0x2f1f,0x2f1f,  0x2f80,0x2f80,0x2f80,0x2f80,  0x2f80,0x2f80,0x2f80,0x2f80,  0x2fe0,0x2fe0,0x2fe0,0x2fe0, 
     0x2fe0,0x2fe0,0x2fe0,0x2fe0,  0x3028,0x3028,0x3028,0x3028,  0x3028,0x3028,0x3028,0x3028,  0x3050,0x3050,0x3050,0x3050, 
     0x3050,0x3050,0x3050,0x3050,  0x3080,0x3080,0x3080,0x3080,  0x3080,0x3080,0x3080,0x3080,  0x30a8,0x30a8,0x30a8,0x30a8, 
     0x30a8,0x30a8,0x30a8,0x30a8,  0x30d7,0x30d7,0x30d7,0x30d7,  0x30d7,0x30d7,0x30d7,0x30d7,  0x3100,0x3100,0x3100,0x3100, 
     0x3100,0x3100,0x3100,0x3100,  0x312f,0x312f,0x312f,0x312f,  0x312f,0x312f,0x312f,0x312f,  0x3157,0x3157,0x3157,0x3157, 
     0x3157,0x3157,0x3157,0x3157,  0x318a,0x318a,0x318a,0x318a,  0x31b3,0x31b3,0x31b3,0x31b3,  0x31e2,0x31e2,0x31e2,0x31e2, 
     0x320b,0x320b,0x320b,0x320b,  0x323a,0x323a,0x323a,0x323a,  0x3263,0x3263,0x3263,0x3263,  0x3292,0x3292,0x3292,0x3292, 
     0x32bb,0x32bb,0x32bb,0x32bb,  0x32ea,0x32ea,0x32ea,0x32ea,  0x330a,0x330a,0x330a,0x330a,  0x3332,0x3332,0x3332,0x3332, 
     0x3352,0x3352,0x3352,0x3352,  0x337a,0x337a,0x337a,0x337a,  0x339a,0x339a,0x339a,0x339a,  0x33c2,0x33c2,0x33c2,0x33c2, 
     0x33ea,0x33ea,0x33ea,0x33ea,  0x3405,0x3405,0x3405,0x3405,  0x3419,0x3419,0x3419,0x3419,  0x3429,0x3429,0x3429,0x3429, 
     0x343d,0x343d,0x343d,0x343d,  0x344d,0x344d,0x344d,0x344d,  0x3461,0x3461,0x3461,0x3461,  0x3471,0x3471,0x3471,0x3471, 
     0x3485,0x3485,0x3485,0x3485,  0x3495,0x3495,0x3495,0x3495,  0x34a9,0x34a9,0x34a9,0x34a9,  0x34b9,0x34b9,0x34b9,0x34b9, 
     0x34cd,0x34cd,0x34cd,0x34cd,  0x34dd,0x34dd,0x34dd,0x34dd,  0x34f1,0x34f1,0x34f1,0x34f1,  0x3501,0x3501,0x3501,0x3501, 
     0x3515,0x3515,0x3515,0x3515,  0x3536,0x3536,0x3536,0x3536,  0x3556,0x3556,0x3556,0x3556,  0x3576,0x3576,0x3576,0x3576, 
     0x3596,0x3596,0x3596,0x3596,  0x35b8,0x35b8,0x35b8,0x35b8,  0x35dc,0x35dc,0x35dc,0x35dc,  0x3600,0x3600,0x3600,0x3600, 
     0x3624,0x3624,0x3624,0x3624,  0x3648,0x3648,0x3648,0x3648,  0x366a,0x366a,0x366a,0x366a,  0x368a,0x368a,0x368a,0x368a, 
     0x36aa,0x36aa,0x36aa,0x36aa,  0x36ca,0x36ca,0x36ca,0x36ca,  0x36ea,0x36ea,0x36ea,0x36ea,  0x370a,0x370a,0x370a,0x370a, 
     0x372a,0x372a,0x372a,0x372a,  0x3749,0x3749,0x3749,0x3749,  0x3765,0x3765,0x3765,0x3765,  0x377e,0x377e,0x377e,0x377e, 
     0x3799,0x3799,0x3799,0x3799,  0x37b2,0x37b2,0x37b2,0x37b2,  0x37ca,0x37ca,0x37ca,0x37ca,  0x37e5,0x37e5,0x37e5,0x37e5, 
     0x37fe,0x37fe,0x37fe,0x37fe,  0x380b,0x380b,0x380b,0x380b,  0x3817,0x3817,0x3817,0x3817,  0x3823,0x3823,0x3823,0x3823, 
     0x382f,0x382f,0x382f,0x382f,  0x383b,0x383b,0x383b,0x383b,  0x3847,0x3847,0x3847,0x3847,  0x3853,0x3853,0x3853,0x3853, 
     0x385f,0x385f,0x385f,0x385f,  0x3876,0x3876,0x3876,0x3876,  0x388c,0x388c,0x388c,0x388c,  0x389d,0x389d,0x389d,0x389d, 
     0x38ad,0x38ad,0x38ad,0x38ad,  0x38bf,0x38bf,0x38bf,0x38bf,  0x38d1,0x38d1,0x38d1,0x38d1,  0x38e3,0x38e3,0x38e3,0x38e3, 
     0x38f5,0x38f5,0x38f5,0x38f5,  0x3908,0x3908,0x3908,0x3908,  0x391c,0x391c,0x391c,0x391c,  0x392f,0x392f,0x392f,0x392f, 
     0x393f,0x393f,0x393f,0x393f,  0x394f,0x394f,0x394f,0x394f,  0x395d,0x395d,0x395d,0x395d,  0x396d,0x396d,0x396d,0x396d, 
     0x397d,0x397d,0x397d,0x397d,  0x398c,0x398c,0x398c,0x398c,  0x399a,0x399a,0x399a,0x399a,  0x39a6,0x39a6,0x39a6,0x39a6, 
     0x39b4,0x39b4,0x39b4,0x39b4,  0x39c0,0x39c0,0x39c0,0x39c0,  0x39ca,0x39ca,0x39ca,0x39ca,  0x39d4,0x39d4,0x39d4,0x39d4, 
     0x39e0,0x39e0,0x39e0,0x39e0,  0x39ea,0x39ea,0x39ea,0x39ea,  0x39f6,0x39f6,0x39f6,0x39f6,  0x3a02,0x3a02,0x3a02,0x3a02, 
     0x3a0e,0x3a0e,0x3a0e,0x3a0e,  0x3a18,0x3a18,0x3a18,0x3a18,  0x3a22,0x3a22,0x3a22,0x3a22,  0x3a2c,0x3a2c,0x3a2c,0x3a2c, 
     0x3a36,0x3a36,0x3a36,0x3a36,  0x3a4b,0x3a4b,0x3a4b,0x3a4b,  0x3a5b,0x3a5b,0x3a5b,0x3a5b,  0x3a6d,0x3a6d,0x3a6d,0x3a6d, 
     0x3a7f,0x3a7f,0x3a7f,0x3a7f,  0x3a8f,0x3a8f,0x3a8f,0x3a8f,  0x3a9d,0x3a9d,0x3a9d,0x3a9d,  0x3aad,0x3aad,0x3aad,0x3aad, 
     0x3abf,0x3abf,0x3abf,0x3abf,  0x3ad1,0x3ad1,0x3ad1,0x3ad1,  0x3ae3,0x3ae3,0x3ae3,0x3ae3,  0x3af3,0x3af3,0x3af3,0x3af3, 
     0x3b05,0x3b05,0x3b05,0x3b05,  0x3b15,0x3b15,0x3b15,0x3b15,  0x3b23,0x3b23,0x3b23,0x3b23,  0x3b31,0x3b31,0x3b31,0x3b31, 
     0x3b3b,0x3b3b,0x3b3b,0x3b3b,  0x3b46,0x3b46,0x3b46,0x3b46,  0x3b4f,0x3b4f,0x3b4f,0x3b4f,  0x3b5c,0x3b5c,0x3b5c,0x3b5c, 
     0x3b67,0x3b67,0x3b67,0x3b67,  0x3b74,0x3b74,0x3b74,0x3b74,  0x3b80,0x3b80,0x3b80,0x3b80,  0x3b8a,0x3b8a,0x3b8a,0x3b8a, 
     0x3b94,0x3b94,0x3b94,0x3b94,  0x3b9c,0x3b9c,0x3b9c,0x3b9c,  0x3ba3,0x3ba3,0x3ba3,0x3ba3,  0x3bab,0x3bab,0x3bab,0x3bab, 
     0x3bb9,0x3bb9,0x3bb9,0x3bb9,  0x3bc7,0x3bc7,0x3bc7,0x3bc7,  0x3bd8,0x3bd8,0x3bd8,0x3bd8,  0x3be3,0x3be3,0x3be3,0x3be3, 
     0x3bee,0x3bee,0x3bee,0x3bee,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
     0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00,  0x3c00,0x3c00,0x3c00,0x3c00, 
};
