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

#include "sippTutD2Model.h"

#include <include/sippHwDefs.h>
#include <filters/cvtColorRGBtoLuma/cvtColorRGBtoLuma.h>


//The full-frame buffers
UInt8      DDR_DATA SippTutD2Model_dmaIn0_buffer[512      * 512     * 3  ]ALIGNED(8);
UInt8      DDR_DATA SippTutD2Model_dmaOut1_buffer[512      * 512     * 1  ]ALIGNED(8);
	
///
void readSippTutD2ModelInput(SippTutD2Model *pPl)
{
   sippRdFileU8((UInt8*)SippTutD2Model_dmaIn0_buffer,512        * 512     * 3 * sizeof(UInt8),"../../../../../../../resources/lena_512x512_RGB.raw");
   //Ensure parameter is used to avoid compiler warning
   (void)(pPl);
	
}

void writeSippTutD2ModelOutput(SippTutD2Model *pPl)
{
   sippWrFileU8((UInt8*)SippTutD2Model_dmaOut1_buffer,512        * 512     * 1 * sizeof(UInt8),"output.raw");
   //Ensure parameter is used to avoid compiler warning
   (void)(pPl);

}
   
void buildSippTutD2Model(SippTutD2Model *pPl)
{
   // create new pipeline
   pPl->pl               = sippCreatePipeline(0, 7, SIPP_MBIN(mbinImgSipp));

   // create filters
   pPl->dmaIn0          =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(3),  SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
   pPl->cvtColorRGBtoLuma2 =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), 0,                  SVU_SYM(svuCvtColorRGBtoLuma), 0);
   pPl->dmaOut1         =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
	
   // link filters
   sippLinkFilter(pPl->cvtColorRGBtoLuma2, pPl->dmaIn0,        1,1                 );
   sippLinkFilter(pPl->dmaOut1,       pPl->cvtColorRGBtoLuma2, 1,1                 );
	
}

  
void configSippTutD2Model(SippTutD2Model *pPl)
{
   DmaParam            *dmaIn0Cfg          = (DmaParam         *)pPl->dmaIn0->params;
   DmaParam            *dmaOut1Cfg         = (DmaParam         *)pPl->dmaOut1->params;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // here go through all the filter instances and assign the value for all parameter
  // fields as defined in the filter property window
   dmaIn0Cfg->ddrAddr   = (UInt32)&SippTutD2Model_dmaIn0_buffer;
   dmaOut1Cfg->ddrAddr  = (UInt32)&SippTutD2Model_dmaOut1_buffer;
  
  
}
