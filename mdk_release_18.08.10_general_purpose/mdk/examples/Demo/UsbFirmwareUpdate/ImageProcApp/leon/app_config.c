///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief    Application configuration Leon file
///

// 1: Includes
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <OsDrvCpr.h>
#include <DrvShaveL2Cache.h>
#include "app_config.h"

// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------            

//clock defines
#define CLOCKS_MIPICFG (AUX_CLK_MASK_MIPI_ECFG | AUX_CLK_MASK_MIPI_CFG)

//The Leon processors are both working in little endian same as the SHAVE processors.
#define BIGENDIANMODE       (0x01000786)

// 3: Global Data (Only if absolutely necessary)
// ----------------------------------------------------------------------------

// 4: Static Local Data
// ----------------------------------------------------------------------------
// Default clock used by the App
// System Clock configuration on start-up
BSP_SET_CLOCK(DEFAULT_OSC0_KHZ, PLL_DESIRED_FREQ_KHZ, 1, 1,
              (DEFAULT_RTEMS_CSS_LOS_CLOCKS | DEV_CSS_SPI0),
              DEFAULT_RTEMS_MSS_LRT_CLOCKS,
              0, 0, 0);

// Program the  L2C at startup
BSP_SET_L2C_CONFIG(1, L2C_REPL_LRU, 0, L2C_MODE_WRITE_THROUGH, 0, NULL);

// 5: Static Function Prototypes
// ----------------------------------------------------------------------------
inline void v_blocksResetSiliconSpecific(void);

// 6: Functions Implementation
// ----------------------------------------------------------------------------


/**********************************************************************
 * Function: int v_blocksResetSiliconSpecific(void)
 * Description: function called at init to enable disable CPU subsystems for the application
 *    This function needs to be updated depending on the CPU variant used. It purpose is to
 *    disable unused peripheral, thus saving power.
 *    The current configuration can be used for MA2100 and MA2x5x CPU's
 * Return Val:  - OS_MYR_DRV_SUCCESS (0) if all initialization functions executed correctly,
 *              - different then 0 if any init function failed.
 ***********************************************************************/
inline void v_blocksResetSiliconSpecific(void)
{
    // Disable not needed subsystems
    OsDrvCprSysDeviceAction(SIPP_DOMAIN, ASSERT_RESET, -1ULL);
    OsDrvCprSysDeviceAction(UPA_DOMAIN,  ASSERT_RESET, -1ULL);
    OsDrvCprSysDeviceAction(MSS_DOMAIN,  ASSERT_RESET, -1ULL);

    // Disable only CSS subsystems not needed.
    DrvCprSysDeviceAction(CSS_DOMAIN,  ASSERT_RESET, (unsigned long long)(-1ULL ^ DEFAULT_CORE_CSS_DSS_CLOCKS));

    // turn off power for unused subsystems
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_0);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_1);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_2);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_3);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_4);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_5);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_6);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_7);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_8);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_9);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_10);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_SHAVE_11);

#ifdef MA2100
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_MSS_ANALOG);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_MSS_DIGITAL);
#else
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_MSS_CPU);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_MSS_AMC);
    OsDrvCprPowerTurnOffIsland(POWER_ISLAND_MSS_SIPP);
#endif
}


/**********************************************************************
 * Function: int initClocksAndMemory(void)
 * Description: function called at init to init and configure system clocks.
 * Return Val:  - OS_MYR_DRV_SUCCESS (0) if all initialization functions executed correctly,
 *              - different then 0 if any init function failed.
 ***********************************************************************/
int i_initClocksAndMemory(void)
{
    // Array to hold all the clock configurations.
    // This array allows separate configuration of any clock sources.
    // Variable can be used localy, because it is accessed only once at init,
    // this impl. uses more stack but less RAM.
    const tyAuxClkDividerCfg auxClk[] =
    {
        {0,0,0,0}, // Null Terminated List
    };

    int ret_code = 0; // Variable to store fundtion return value

    // Init CPR Driver in order to be able to get sys clk
    if ((ret_code = (int)OsDrvCprInit()) != OS_MYR_DRV_SUCCESS)
    {
        printf("Error: OsDrvCprInit() FAILED, with error code: %d\n", ret_code);
        return ret_code;
    }

    // Open CPR Driver in order to be able to get sys clk
    if ((ret_code = (int)OsDrvCprOpen()) != OS_MYR_DRV_SUCCESS)
    {
        printf("Error: OsDrvCprOpen() FAILED, with error code: %d\n", ret_code);
        return ret_code;
    }

    // Setup Aux clocks
    if ((ret_code = (int)OsDrvCprAuxClockArrayConfig(auxClk)) != OS_MYR_DRV_SUCCESS)
    {
        printf("Error: OsDrvCprAuxClockArrayConfig() FAILED, with error code: %d\n", ret_code);
        return ret_code;
    }

    // Call board specific reset defined ./arch/ma2xxx/leon/in los_app_config_2xxx.c
    v_blocksResetSiliconSpecific();

    return (ret_code);
}

/* end of file */
