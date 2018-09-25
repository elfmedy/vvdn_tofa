///
/// @file
/// @copyright All code copyright Movidius Ltd 2014, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     USB mass storage class example
///

// 1: Includes
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <rtems.h>
#include <rtems/bspIo.h>
#include <bsp.h>

#include <mv_types.h>
#include "app_config.h"
#include "OsDrvUsbPhy.h"
#include "OsDrvCpr.h"
#include "DrvDdr.h"


#include "usbpumpdebug.h"
#include "usbpump_application_rtems_api.h"

// 2:  Source Specific #defines and types  (typedef, enum, struct)
// ----------------------------------------------------------------------------

// Default clock used by the App
// System Clock configuration on start-up
BSP_SET_CLOCK(DEFAULT_OSC0_KHZ, PLL_DESIRED_FREQ_KHZ, 1, 1, DEFAULT_RTEMS_CSS_LOS_CLOCKS, DEFAULT_RTEMS_MSS_LRT_CLOCKS,0,0,0);
// Program L2 cache behaviour
BSP_SET_L2C_CONFIG(1,DEFAULT_RTEMS_L2C_REPLACEMENT_POLICY, DEFAULT_RTEMS_L2C_LOCKED_WAYS,DEFAULT_RTEMS_L2C_MODE, 0, 0);

// 4: Static Local Data
// ----------------------------------------------------------------------------
/* Sections decoration is require here for downstream tools */

#ifndef DISABLE_LEON_DCACHE
# define USBPUMP_MDK_CACHE_ENABLE       1
#else
# define USBPUMP_MDK_CACHE_ENABLE       0
#endif

static USBPUMP_APPLICATION_RTEMS_CONFIGURATION sg_DataPump_AppConfig =
USBPUMP_APPLICATION_RTEMS_CONFIGURATION_INIT_V1(
    /* nEventQueue */            64,
    /* pMemoryPool */            NULL,
    /* nMemoryPool */            0,
    /* DataPumpTaskPriority */   100,
    /* DebugTaskPriority */      200,
    /* UsbInterruptPriority */   10,
    /* pDeviceSerialNumber */    NULL,
    /* pUseBusPowerFn */         NULL,
    /* fCacheEnabled */          USBPUMP_MDK_CACHE_ENABLE,
    /* DebugMask */              UDMASK_ANY | UDMASK_ERRORS
    );

// 5: Static Function Prototypes
// ----------------------------------------------------------------------------

// 6: Functions Implementation
// ----------------------------------------------------------------------------

void *POSIX_Init (void *args)
{
    (void) args;// "use" the variables to hush the compiler warning.

    s32 sc;
    osDrvUsbPhyParam_t initParam =
    {
        .enableOtgBlock    = USB_PHY_OTG_DISABLED,
        .useExternalClock  = USB_PHY_USE_EXT_CLK,
        .fSel              = USB_REFCLK_20MHZ,
        .refClkSel0        = USB_SUPER_SPEED_CLK_CONFIG,
        .forceHsOnly       = USB_PHY_HS_ONLY_OFF
    };

    sc = initClocksAndMemory();
    if(sc)
        exit(sc);

    OsDrvUsbPhyInit(&initParam);
    if (UsbPump_Rtems_DataPump_Startup(&sg_DataPump_AppConfig) != NULL)
    {
        printf("USB Mass Storage Class demo started\n\n");
    }
    else
    {
        printf("\n\nUsbPump_Rtems_DataPump_Startup() failed!\n\n\n");
        exit(1);
    }
    return NULL;
}


