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

#ifndef __MEMREGIONAPI_H__
#define __MEMREGIONAPI_H__

#include <sipp.h>
#include <sippTestCommon.h>

#include "MemRegionApiParams.h"


//The full-frame buffers
extern UInt16 DDR_DATA MemRegionApi_dmaIn0_buffer[ MEM_API_TEST_BAYER_WIDTH * MEM_API_TEST_BAYER_HEIGHT * 1 ]ALIGNED(8);
extern UInt8 DDR_DATA MemRegionApi_dmaOut0_buffer[ MEM_API_TEST_BAYER_WIDTH * MEM_API_TEST_BAYER_HEIGHT * 3 ]ALIGNED(8);
extern UInt16 DDR_DATA MemRegionApi_dmaOut1_buffer[ MEM_API_TEST_BAYER_WIDTH * MEM_API_TEST_BAYER_HEIGHT * 1 ]ALIGNED(8);
	
///

typedef struct MemRegionApi
{
	//Filter references for human readable shape
	SippPipeline *pl;

	//Declare references to all filters in the pipeline
	SippFilter *dmaIn0;
	SippFilter *dmaOut0;
	SippFilter *debayerMa2x5x0;
	SippFilter *dmaOut1;
	SippFilter *lscMa2x5x0;
	SippFilter *rawMa2x5x0;

} MemRegionApi;

void readMemRegionApiInput(MemRegionApi *pPl);
void writeMemRegionApiOutput(MemRegionApi *pPl);

void buildMemRegionApi(MemRegionApi *pPl);
void configMemRegionApi(MemRegionApi *pPl);


#endif