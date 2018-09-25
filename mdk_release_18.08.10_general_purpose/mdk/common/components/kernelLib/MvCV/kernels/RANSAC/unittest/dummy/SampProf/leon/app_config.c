///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief    Application configuration Leon file
///

// 1: Includes
// ----------------------------------------------------------------------------

#include <OsDrvCpr.h>
#include <DrvShaveL2Cache.h>
#include "app_config.h"
#include <registersMyriad.h>
#include <swcLeonUtils.h>






// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------

#define L2CACHE_CFG     (SHAVE_L2CACHE_NORMAL_MODE)


// 3: Global Data (Only if absolutely necessary)
// ----------------------------------------------------------------------------

// 4: Static Local Data
// ----------------------------------------------------------------------------
// 5: Static Function Prototypes
// ----------------------------------------------------------------------------

// 6: Functions Implementation
// ----------------------------------------------------------------------------
// Setup all the clock configurations needed by this application and also the ddr
int initClocksAndMemory(void)
{

    tyAuxClkDividerCfg auxClkAllOn[] =
    {
        {AUX_CLK_MASK_UART, CLK_SRC_REFCLK0, 96, 625},   // Give the UART an SCLK that allows it to generate an output baud rate of of 115200 Hz (the uart divides by 16)
        {0,0,0,0}, // Null Terminated List
    };

    // Configure the system
    OsDrvCprInit();

    OsDrvCprOpen();
    OsDrvCprAuxClockArrayConfig(auxClkAllOn);

    DrvShaveL2CacheSetMode(L2CACHE_CFG);
    return 0;
}
