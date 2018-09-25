#ifndef __MEDIANFILTER11x11_H__
#define __MEDIANFILTER11x11_H__

#include <mv_types.h>
#include <mvcv_macro.h>

//!@{
/// This kernel applies median blur filter with 11x11 size, histogram based method for median calculation
/// @param[in] widthLine - Width of input line
/// @param[out] outLine  - Output line
/// @param[in] inLine    - Input lines

MVCV_FUNC(void, mvcvMedianFilter11x11, u32 widthLine, u8 **outLine, u8 ** inLine)
//!@}

#endif //__MEDIANFILTER11x11_H__