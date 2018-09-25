///
/// @file
/// @copyright All code copyright Movidius Ltd 2014, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Variation of "IpipePPTest09, IpipePPTest09_a
///            PP inputs 960x128 and outputs 480x64 RGB data for VideoSipp
///            LOS starts LRT which executes the PP test.
///

// 1: Includes
// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <DrvLeon.h>
#include <DrvCpr.h>
#include <DrvTimer.h>
#include <bsp.h>
#include "rtems_config.h"

// 2:  Source Specific #defines and types  (typedef, enum, struct)
// ----------------------------------------------------------------------------
// 3: Global Data (Only if absolutely necessary)
// ----------------------------------------------------------------------------
//Entry point of the leon_rt processor
extern u32      *lrt_start;
// 4: Static Local Data
// ----------------------------------------------------------------------------
// 5: Static Function Prototypes
// ----------------------------------------------------------------------------
// 6: Functions Implementation
// ----------------------------------------------------------------------------
void *POSIX_Init (void *args)
{
    (void) args;// "use" the variables to hush the compiler warning.

    s32 sc;

    printf("Init clocks..\n");
    sc = initClocksAndMemory();
    if(sc)
        exit(sc);

    printf("Starting LRT..\n");
    DrvLeonRTStartup((u32)&lrt_start);
    DrvLeonRTWaitExecution();

    exit(0);
}
