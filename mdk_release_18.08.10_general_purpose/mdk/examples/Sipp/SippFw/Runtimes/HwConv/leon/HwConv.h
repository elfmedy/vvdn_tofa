///
/// @file
/// @copyright All code copyright Movidius Ltd 2014, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     This file contains the source code of the SIPP pipeline
///            generated by the SIPP Graph Designer.
///
///
///  ************************ DO NOT EDIT, THIS IS A GENERATED FILE!!!! ************************
/// 

#ifndef __HWCONV_H__
#define __HWCONV_H__

#include <sipp.h>
#include <sippTestCommon.h>

#include "HwConvSetup.h"


//The full-frame buffers
extern UInt8 DDR_DATA HwConv_dmaIn0_buffer[ SIPP_HW_CONV_BUFFER_WIDTH * SIPP_HW_CONV_BUFFER_HEIGHT * SIPP_HW_CONV_BUFFER_NUM_PLANES ]ALIGNED(8);
extern UInt8 DDR_DATA HwConv_dmaOut0_buffer[ SIPP_HW_CONV_BUFFER_WIDTH * SIPP_HW_CONV_BUFFER_HEIGHT * SIPP_HW_CONV_BUFFER_NUM_PLANES ]ALIGNED(8);
	
///

typedef struct HwConv
{
	//Filter references for human readable shape
	SippPipeline *pl;

	//Declare references to all filters in the pipeline
	SippFilter *dmaIn0;
	SippFilter *dmaOut0;
	SippFilter *convolutionMa2x5x0;

} HwConv;

void readHwConvInput(HwConv *pPl);
void writeHwConvOutput(HwConv *pPl);

void buildHwConv(HwConv *pPl);
void configHwConv(HwConv *pPl);


#endif