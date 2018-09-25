///
/// @file      mvispScale2xBilinHV025_U8ToU8.h
/// @copyright All code copyright Movidius Ltd 2013, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Down scale by half in each direction wil bilinear (sw) kernel.
///            U8 in and out
///

#ifndef __mvispScale2xBilinHV025_U8ToU8_H__
#define __mvispScale2xBilinHV025_U8ToU8_H__
#include <mv_types.h>
#include <mvcv_macro.h>

//!@{
/// mvispScale2xBilinHV025_U8ToU8 kernel
/// @param[in] in         - Input lines
/// @param[in] out        - Output line
/// @param[in] inWidth    - Width of input line

MVCV_FUNC(void, mvispScale2xBilinHV025_U8ToU8, u8** in, u8** out, u32 inWidth)

//!@}

#endif //__mvispScale2xBilinHV025_U8ToU8_H__