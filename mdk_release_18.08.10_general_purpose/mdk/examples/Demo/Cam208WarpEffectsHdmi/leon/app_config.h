///  
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved 
///            For License Warranty see: common/license.txt   
///
/// @brief     Application configuration Leon header 
/// 
/// 
/// 
/// 
/// 

#ifndef APP_CONFIG_H
#define APP_CONFIG_H 

// 1: Includes
// ----------------------------------------------------------------------------
#include "mv_types.h"

// 2:  Source Specific #defines and types  (typedef,enum,struct)
// ----------------------------------------------------------------------------

// Shave L2 Cache Partition
#define PARTITION_0    (0)

// 3:  Exported Global Data (generally better to avoid)
// ----------------------------------------------------------------------------

// 4:  Exported Functions (non-inline)
// ----------------------------------------------------------------------------

/// Setup all the clock configurations needed by this application and also the ddr
///
/// @return    0 on success, non-zero otherwise  
int initClocksAndMemory(void);

#endif // APP_CONFIG_H
