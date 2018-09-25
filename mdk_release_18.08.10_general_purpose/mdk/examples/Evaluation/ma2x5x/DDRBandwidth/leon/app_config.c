///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Application configuration Leon file
///

// 1: Includes
// ----------------------------------------------------------------------------
#include <DrvCpr.h>
#include <DrvShaveL2Cache.h>
#include "app_config.h"
#include <DrvLeonL2C.h>
#include "DrvDdr.h"
// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------

#define L2CACHE_CFG     (SHAVE_L2CACHE_NORMAL_MODE)

// 3: Global Data (Only if absolutely necessary)
// ----------------------------------------------------------------------------
// Sections decoration is required here for downstream tools

// 4: Static Local Data
// ----------------------------------------------------------------------------
// 5: Static Function Prototypes
// ----------------------------------------------------------------------------

// 6: Functions Implementation
// ----------------------------------------------------------------------------

int initClocksAndMemory(void)
{
    tyAuxClkDividerCfg auxClkAllOn[] =
    {
        {AUX_CLK_MASK_UART, CLK_SRC_REFCLK0, 96, 625},   // Give the UART an SCLK that allows it to generate an output baud rate of of 115200 Hz (the uart divides by 16)
        {0,0,0,0}, // Null Terminated List
    };

    tySocClockConfig clocksConfig =
    {
        .refClk0InputKhz         = 12000,           // Default 12Mhz input clock
        .refClk1InputKhz         = 0,               // Assume no secondary oscillator for now
        .targetPll0FreqKhz       = 600000,
        .targetPll1FreqKhz       = 0,               // set in DDR driver
        .clkSrcPll1              = CLK_SRC_REFCLK0, // Supply both PLLS from REFCLK0
        .masterClkDivNumerator   = 1,
        .masterClkDivDenominator = 1,
        .cssDssClockEnableMask   = DEFAULT_CORE_CSS_DSS_CLOCKS,
        .mssClockEnableMask      = 0,                            // Not enabling any MSS clocks for now
        .upaClockEnableMask      = UPA_SHAVE_L2,
        .pAuxClkCfg              = auxClkAllOn,
    };

    DrvCprInit();
    DrvCprSetupClocks(&clocksConfig);

    return 0;
}

