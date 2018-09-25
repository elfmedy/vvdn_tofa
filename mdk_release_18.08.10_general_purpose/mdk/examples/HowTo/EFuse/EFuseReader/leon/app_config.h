///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     Application configuration Leon header
///

#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#include <mv_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Setup all the clock configurations needed by this application
///
/// @return    0 on success, non-zero otherwise  

//L2 cache partition
#define PARTITION_0    (0)

int initClocksAndMemory(void);

#ifdef __cplusplus
}
#endif

#endif
