#ifndef __INTERPOLATEPIXELBILINEAR_H__
#define __INTERPOLATEPIXELBILINEAR_H__

#include <mv_types.h>
#include <mvcv_macro.h>

//!@{
/// Bilinear interpolation of four pixels
/// @param[in]  Line1 	- First input line
/// @param[in]  Line2 	- Second input line
/// @param[in]  x 		- The x coordinate of the pixel.
/// @param[in]  y 		- The y coordinate of the pixel. Because we work with two lines only, only the fractional part of the number matters.
/// @return     The value of the interpolated pixel.
MVCV_FUNC(half, mvcvInterpolatePixelBilinear, half* line1,
          half* line2, fp32 x, fp32 y);

#endif //__INTERPOLATEPIXELBILINEAR_H__
