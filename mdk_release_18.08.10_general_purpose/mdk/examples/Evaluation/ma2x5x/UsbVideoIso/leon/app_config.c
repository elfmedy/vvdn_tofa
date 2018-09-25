///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Key application system settings
///
///
///

// 1: Includes
// ----------------------------------------------------------------------------
#include "DrvDdr.h"
#include "DrvShaveL2Cache.h"
#include "OsDrvTimer.h"
#include "OsDrvCpr.h"
#include "app_config.h"

// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------

#define L2CACHE_CFG                (SHAVE_L2CACHE_NORMAL_MODE)
#define PARTITION_0                (0)
#define SHAVES_USED                (12)


// 3: Global Data (Only if absolutely necessary)
// ----------------------------------------------------------------------------
// Sections decoration is require here for downstream tools

// 4: Static Local Data
// ----------------------------------------------------------------------------

static tyAuxClkDividerCfg auxClk[] =
{
      {
          .auxClockEnableMask     = AUX_CLK_MASK_MEDIA,         // SIPP Clock
          .auxClockSource         = CLK_SRC_SYS_CLK_DIV2 ,      //
          .auxClockDivNumerator   = 1,                          //
          .auxClockDivDenominator = 1,                          //
      },
      {
          .auxClockEnableMask     = (AUX_CLK_MASK_CIF0 | AUX_CLK_MASK_CIF1),  // CIFs Clock
          .auxClockSource         = CLK_SRC_SYS_CLK,       //
          .auxClockDivNumerator   = 1,                          //
          .auxClockDivDenominator = 1,                          //
      },
      {
          .auxClockEnableMask     = CLOCKS_MIPICFG,             // MIPI CFG + ECFG Clock
          .auxClockSource         = CLK_SRC_SYS_CLK     ,       //
          .auxClockDivNumerator   = 1,                          //
          .auxClockDivDenominator = 24,                         //  the MIPI cfg clock should be <= 20 Mhz !
      },
      {
          .auxClockEnableMask     = AUX_CLK_MASK_USB_CTRL_SUSPEND_CLK,
          .auxClockSource         = CLK_SRC_PLL0,
          .auxClockDivNumerator   = 1,
          .auxClockDivDenominator = 24
      },
      {0, 0, 0, 0}, // Null Terminated List
    };

// 5: Static Function Prototypes
// ----------------------------------------------------------------------------
// 6: Functions Implementation
// ----------------------------------------------------------------------------

int32_t initClocksAndMemory(void)
{
    int32_t i;
    int32_t sc;
    // Configure the system
    sc = OsDrvCprInit();
    if(sc)
        return sc;
    sc = OsDrvCprOpen();
    if(sc)
        return sc;
    sc = OsDrvCprAuxClockArrayConfig(auxClk);
    if(sc)
        return sc;

    DrvCprSysDeviceAction(SIPP_DOMAIN, ASSERT_RESET, DEV_SIPP_MIPI);
    DrvCprSysDeviceAction(UPA_DOMAIN, ASSERT_RESET,  APP_UPA_CLOCKS);
    DrvCprSysDeviceAction(MSS_DOMAIN, DEASSERT_RESET, -1);
    DrvCprSysDeviceAction(CSS_DOMAIN,  DEASSERT_RESET, -1);
    DrvCprSysDeviceAction(SIPP_DOMAIN, DEASSERT_RESET, -1);
    DrvCprSysDeviceAction(UPA_DOMAIN,  DEASSERT_RESET, -1);

    sc = OsDrvTimerInit();
    if(sc)
        return sc;
    DrvDdrInitialise(NULL);

    // Set the shave L2 Cache mode
    sc = DrvShaveL2CacheSetMode(L2CACHE_CFG);
    if(sc)
        return sc;

    //Set Shave L2 cache partitions
    DrvShaveL2CacheSetupPartition(SHAVEPART256KB);

    //Allocate Shave L2 cache set partitions
    sc = DrvShaveL2CacheAllocateSetPartitions();
    if(sc)
        return sc;

    //Assign the one partition defined to all shaves
    for (i = 0; i < SHAVES_USED; i++)
    {
        DrvShaveL2CacheSetLSUPartId(i, PARTITION_0);
    }

    DrvShaveL2CachePartitionFlushAndInvalidate(PARTITION_0);

    return 0;
}
