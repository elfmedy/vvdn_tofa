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

#include "testHwPolyPhaseFIR.h"

#include <include/sippHwDefs.h>
#include <arch/ma2x5x/include/sippHwDefs_ma2x5x.h>


//The full-frame buffers
UInt8      DDR_DATA TestHwPolyPhaseFIR_dmaIn0_buffer[SIPP_HW_POLY_FIR_INPUT_BUFFER_WIDTH* SIPP_HW_POLY_FIR_INPUT_BUFFER_HEIGHT* SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES]ALIGNED(8);
UInt8      DDR_DATA TestHwPolyPhaseFIR_dmaOut0_buffer[SIPP_HW_POLY_FIR_OUTPUT_BUFFER_WIDTH* SIPP_HW_POLY_FIR_OUTPUT_BUFFER_HEIGHT* SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES]ALIGNED(8);
	
///
void readTestHwPolyPhaseFIRInput(TestHwPolyPhaseFIR *pPl)
{
   sippRdFileU8((UInt8*)TestHwPolyPhaseFIR_dmaIn0_buffer,SIPP_HW_POLY_FIR_INPUT_BUFFER_WIDTH * SIPP_HW_POLY_FIR_INPUT_BUFFER_HEIGHT * SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES* sizeof(UInt8),"../../../../../../../resources/testIMG_1296x972_P400.rgb");
   //Ensure parameter is used to avoid compiler warning
   (void)(pPl);
	
}

void writeTestHwPolyPhaseFIROutput(TestHwPolyPhaseFIR *pPl)
{
   sippWrFileU8((UInt8*)TestHwPolyPhaseFIR_dmaOut0_buffer,SIPP_HW_POLY_FIR_OUTPUT_BUFFER_WIDTH * SIPP_HW_POLY_FIR_OUTPUT_BUFFER_HEIGHT * SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES* sizeof(UInt8),"output.raw");
   //Ensure parameter is used to avoid compiler warning
   (void)(pPl);

}
   
void buildTestHwPolyPhaseFIR(TestHwPolyPhaseFIR *pPl)
{
   // create new pipeline
   pPl->pl               = sippCreatePipeline(0, 0, SIPP_MBIN(mbinImgSipp));

   // create filters
   pPl->dmaIn0          =  sippCreateFilter(pPl->pl, 0x00,       SIPP_HW_POLY_FIR_INPUT_BUFFER_WIDTH, SIPP_HW_POLY_FIR_INPUT_BUFFER_HEIGHT, N_PL(SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES), SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
   pPl->polyphasefirMa2x5x0 =  sippCreateFilter(pPl->pl, SIPP_RESIZE, SIPP_HW_POLY_FIR_OUTPUT_BUFFER_WIDTH, SIPP_HW_POLY_FIR_OUTPUT_BUFFER_HEIGHT, N_PL(SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES), SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_UPFIRDN_ID,    0);
   pPl->dmaOut0         =  sippCreateFilter(pPl->pl, 0x00,       SIPP_HW_POLY_FIR_OUTPUT_BUFFER_WIDTH, SIPP_HW_POLY_FIR_OUTPUT_BUFFER_HEIGHT, N_PL(SIPP_HW_POLY_FIR_INPUT_BUFFER_NUM_PLANES), SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
	
   // link filters
   sippLinkFilter(pPl->polyphasefirMa2x5x0, pPl->dmaIn0,        3,3                 );
   sippLinkFilter(pPl->dmaOut0,       pPl->polyphasefirMa2x5x0, 1,1                 );
	
}

  
void configTestHwPolyPhaseFIR(TestHwPolyPhaseFIR *pPl)
{
   DmaParam            *dmaIn0Cfg          = (DmaParam         *)pPl->dmaIn0->params;
   PolyFirParam        *polyphasefirMa2x5x0Cfg= (PolyFirParam     *)pPl->polyphasefirMa2x5x0->params;
   DmaParam            *dmaOut0Cfg         = (DmaParam         *)pPl->dmaOut0->params;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // here go through all the filter instances and assign the value for all parameter
  // fields as defined in the filter property window
   polyphasefirMa2x5x0Cfg->clamp=OUTPUT_CLAMP;
   polyphasefirMa2x5x0Cfg->horzD=H_DEN;
   polyphasefirMa2x5x0Cfg->horzN=H_NUM;
   polyphasefirMa2x5x0Cfg->vertD=V_DEN;
   polyphasefirMa2x5x0Cfg->vertN=V_NUM;
   polyphasefirMa2x5x0Cfg->horzCoefs=(UInt8*)coefs;
   polyphasefirMa2x5x0Cfg->vertCoefs=(UInt8*)coefs;
   polyphasefirMa2x5x0Cfg->planeMode=POLY_PLANE_ALL;
   dmaIn0Cfg->ddrAddr   = (UInt32)&TestHwPolyPhaseFIR_dmaIn0_buffer;
   dmaOut0Cfg->ddrAddr  = (UInt32)&TestHwPolyPhaseFIR_dmaOut0_buffer;
  
  
}
