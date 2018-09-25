///
/// @file
/// @copyright All code copyright Movidius Ltd 2014, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     This file contains the declaration of the @ref lut10to8 SIPP filter API.
///    

#ifndef __SIPP_LUT10TO8_H__
#define __SIPP_LUT10TO8_H__ 

#include <sipp.h>

/// @sf_definition lut10to8  LUT 10 to 8
/// @sf_description  This filter performs a look-up table transform of a line. Destination line is filled with values from the look-up table. Indices of the entries are taken from the source line.
/// @sf_group ISP
/// @sf_preserve numPlanes, imgSize, dataType
/// @sf_outdatatype UInt8
/// @sf_inputs
/// 	- datatypes: UInt16; kernels: 1x1
/// @sf_extasm $(MV_COMMON_BASE)/components/kernelLib/MvCV/kernels/lookupTable10to8/arch/$(MV_SOC_REV_DIR)/shave/src/lookupTable10to8.asm
/// @{

/// @brief Parameter structure of the @ref lut10to8 filter.
typedef struct
{
    /// @sf_desc  Look-up table of 1024 elements; should have the same depth as the input line.
	UInt8 lutValue[1024];
}
Lut10to8Param;

/// @brief Shave function of the @ref lut10to8 filter.
void SVU_SYM(svuLut10to8)(SippFilter *fptr);
SHAVE_SYM_EXPORT(svuLut10to8);

/// @}

#endif //__SIPP_LUT10TO8_H__
