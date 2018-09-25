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

#include "sippTutB1Model.h"

#include <include/sippHwDefs.h>
#include <filters/negative/negative.h>
#include <filters/avg/avg.h>


//The full-frame buffers
UInt8      DDR_DATA SippTutB1Model_dmaIn0_buffer[512      * 512     * 1  ]ALIGNED(8);
UInt8      DDR_DATA SippTutB1Model_dmaIn1_buffer[512      * 512     * 1  ]ALIGNED(8);
UInt8      DDR_DATA SippTutB1Model_dmaOut3_buffer[512      * 512     * 1  ]ALIGNED(8);
	
///
void readSippTutB1ModelInput(SippTutB1Model *pPl)
{
   sippRdFileU8((UInt8*)SippTutB1Model_dmaIn0_buffer,512        * 512     * 1 * sizeof(UInt8),"../../../../../../../resources/lena_512x512_luma.raw");
   sippRdFileU8((UInt8*)SippTutB1Model_dmaIn1_buffer,512        * 512     * 1 * sizeof(UInt8),"../../../../../../../resources/Baywatch_512x512_P422.yuv");
   //Ensure parameter is used to avoid compiler warning
   (void)(pPl);
	
}

void writeSippTutB1ModelOutput(SippTutB1Model *pPl)
{
   sippWrFileU8((UInt8*)SippTutB1Model_dmaOut3_buffer,512        * 512     * 1 * sizeof(UInt8),"output.raw");
   //Ensure parameter is used to avoid compiler warning
   (void)(pPl);

}
   
void buildSippTutB1Model(SippTutB1Model *pPl)
{
   // create new pipeline
   pPl->pl               = sippCreatePipeline(0, 7, SIPP_MBIN(mbinImgSipp));

   // create filters
   pPl->dmaIn0          =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
   pPl->dmaIn1          =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
   pPl->negative4       =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), 0,                  SVU_SYM(svuNegative),         0);
   pPl->avg2            =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), 0,                  SVU_SYM(svuAvg),              0);
   pPl->dmaOut3         =  sippCreateFilter(pPl->pl, 0x00,       512,    512,    N_PL(1),  SZ(UInt8), SIPP_AUTO,          (FnSvuRun)SIPP_DMA_ID,        0);
	
   // link filters
   sippLinkFilter(pPl->negative4,     pPl->dmaIn1,        1,1                 );
   sippLinkFilter(pPl->avg2,          pPl->dmaIn0,        1,1                 );
   sippLinkFilter(pPl->avg2,          pPl->negative4,     1,1                 );
   sippLinkFilter(pPl->dmaOut3,       pPl->avg2,          1,1                 );
	
}

  
void configSippTutB1Model(SippTutB1Model *pPl)
{
   DmaParam            *dmaIn0Cfg          = (DmaParam         *)pPl->dmaIn0->params;
   DmaParam            *dmaIn1Cfg          = (DmaParam         *)pPl->dmaIn1->params;
   DmaParam            *dmaOut3Cfg         = (DmaParam         *)pPl->dmaOut3->params;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // here go through all the filter instances and assign the value for all parameter
  // fields as defined in the filter property window
   dmaIn0Cfg->ddrAddr   = (UInt32)&SippTutB1Model_dmaIn0_buffer;
   dmaIn1Cfg->ddrAddr   = (UInt32)&SippTutB1Model_dmaIn1_buffer;
   dmaOut3Cfg->ddrAddr  = (UInt32)&SippTutB1Model_dmaOut3_buffer;
  
  
}
