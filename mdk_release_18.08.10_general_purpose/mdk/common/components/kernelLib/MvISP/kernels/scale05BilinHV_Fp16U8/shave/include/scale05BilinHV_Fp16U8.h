///
/// @file
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Downscale to half resolution in each direction with bilinear (sw) kernel; 
///            Fp16 in / U8 out
///

#ifndef __SCALE05BILINHV_Fp16U8_H__
#define __SCALE05BILINHV_Fp16U8_H__
#include <mv_types.h>
#include <mvcv_macro.h>


//!@{
/// scale05BilinHV_U16U8 kernel (custom size)
/// @param[in] in         - Input lines
/// @param[in] out        - Output line
/// @param[in] inWidth    - Width of input line

MVCV_FUNC(void, mvispScale05BilinHV_Fp16U8, half** in, u8** out, u32 inWidth)

//!@}

#endif //__SCALE05BILINHV_Fp16U8_H__