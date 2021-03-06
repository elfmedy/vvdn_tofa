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

#ifndef __MONOPIPE_H__
#define __MONOPIPE_H__

#include <sipp.h>
#include <sippTestCommon.h>

#include "isp_params.h"


//The full-frame buffers
extern UInt16 DDR_DATA MonoPipe_dmaIn0_buffer[ MONO_PIPE_INPUT_BUFFER_WIDTH * MONO_PIPE_INPUT_BUFFER_HEIGHT * 1 ]ALIGNED(8);
extern UInt8 DDR_DATA MonoPipe_dmaOut0_buffer[ MONO_PIPE_INPUT_BUFFER_WIDTH * MONO_PIPE_INPUT_BUFFER_HEIGHT * 1 ]ALIGNED(8);
	
///

typedef struct MonoPipe
{
	//Filter references for human readable shape
	SippPipeline *pl;

	//Declare references to all filters in the pipeline
	SippFilter *dmaIn0;
	SippFilter *sigmaDnsMa2x5x0;
	SippFilter *lscMa2x5x0;
	SippFilter *rawMa2x5x0;
	SippFilter *lutMa2x5x0;
	SippFilter *dmaOut0;
	SippFilter *sharpenMa2x5x0;
	SippFilter *ydnsMa2x5x0;

} MonoPipe;

void readMonoPipeInput(MonoPipe *pPl);
void writeMonoPipeOutput(MonoPipe *pPl);

void buildMonoPipe(MonoPipe *pPl);
void configMonoPipe(MonoPipe *pPl);


#endif