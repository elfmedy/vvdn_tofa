///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Application configuration Leon header
///

#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_


// 1: Includes
// ----------------------------------------------------------------------------
#include <mv_types.h>

// 2:  Source Specific #defines and types  (typedef, enum, struct)
// ----------------------------------------------------------------------------
#define APP_UPA_CLOCKS              (DEV_UPA_SH0      | \
                                     DEV_UPA_SHAVE_L2 | \
                                     DEV_UPA_CDMA     | \
                                     DEV_UPA_CTRL      )
#define SHAVE_NUMBER     (0)
#define SHAVES_USED      (1)
//L2Cache partitions
#define PARTITION_0      (0)
// 3: Static Local Data
// ----------------------------------------------------------------------------

// 4:  Exported Functions (non-inline)
// ----------------------------------------------------------------------------
/// Setup all the clock configurations needed by this application and also the ddr
///
/// @return    0 on success, non-zero otherwise
/// Setup all the clock configurations needed by this application and also the ddr
///
/// @return    0 on success, non-zero otherwise  
int initClocksAndMemory(void);

#endif

