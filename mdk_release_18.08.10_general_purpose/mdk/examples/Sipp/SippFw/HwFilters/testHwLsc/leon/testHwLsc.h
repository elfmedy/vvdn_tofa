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

#ifndef __TESTHWLSC_H__
#define __TESTHWLSC_H__

#include <sipp.h>
#include <sippTestCommon.h>

#include "testData.h"


//The full-frame buffers
extern UInt16 DDR_DATA TestHwLsc_dmaIn0_buffer[ SIPP_HW_LSC_BUFFER_WIDTH * SIPP_HW_LSC_BUFFER_HEIGHT * SIPP_HW_LSC_BUFFER_NUM_PLANES ]ALIGNED(8);
extern UInt16 DDR_DATA TestHwLsc_dmaOut0_buffer[ SIPP_HW_LSC_BUFFER_WIDTH * SIPP_HW_LSC_BUFFER_HEIGHT * SIPP_HW_LSC_BUFFER_NUM_PLANES ]ALIGNED(8);
	
///

typedef struct TestHwLsc
{
	//Filter references for human readable shape
	SippPipeline *pl;

	//Declare references to all filters in the pipeline
	SippFilter *dmaIn0;
	SippFilter *dmaOut0;
	SippFilter *lscMa2x5x0;

} TestHwLsc;

void readTestHwLscInput(TestHwLsc *pPl);
void writeTestHwLscOutput(TestHwLsc *pPl);

void buildTestHwLsc(TestHwLsc *pPl);
void configTestHwLsc(TestHwLsc *pPl);


#endif