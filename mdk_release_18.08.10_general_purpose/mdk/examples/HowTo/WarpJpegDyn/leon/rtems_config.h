///
/// @file
/// @copyright All code copyright Movidius Ltd 2016, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     RTEMS configuration Leon header
///
#ifndef _RTEMS_CONFIG_H_
#define _RTEMS_CONFIG_H_

// 1: Includes
// ----------------------------------------------------------------------------
#include "app_config.h"
#include "fatalExtension.h"

#if defined(__RTEMS__)

#if !defined (__CONFIG__)
#define __CONFIG__

// 2: Defines
// ----------------------------------------------------------------------------

/* ask the system to generate a configuration table */
#define CONFIGURE_INIT

#ifndef RTEMS_POSIX_API
#define RTEMS_POSIX_API
#endif

#define CONFIGURE_MICROSECONDS_PER_TICK         1000    /* 1 millisecond */

#define CONFIGURE_TICKS_PER_TIMESLICE           50      /* 50 milliseconds */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define  CONFIGURE_MINIMUM_TASK_STACK_SIZE      (8192)

#define CONFIGURE_MAXIMUM_TASKS                 20

#define CONFIGURE_MAXIMUM_POSIX_THREADS         5

#define CONFIGURE_MAXIMUM_POSIX_MUTEXES         8

#define CONFIGURE_MAXIMUM_POSIX_KEYS            8

#define CONFIGURE_MAXIMUM_POSIX_SEMAPHORES      8

#define CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES  8

#define CONFIGURE_MAXIMUM_POSIX_TIMERS          4

#define CONFIGURE_MAXIMUM_TIMERS                4

#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM

#define CONFIGURE_FILESYSTEM_DOSFS

#define CONFIGURE_MAXIMUM_DRIVERS 10

// Add dynamic semaphore allocation
#define CONFIGURE_MAXIMUM_SEMAPHORES rtems_resource_unlimited(5)

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 30

#define CONFIGURE_APPLICATION_NEEDS_LIBBLOCK

#define CONFIGURE_POSIX_INIT_TASKS_TABLE

#define CONFIGURE_BDBUF_MAX_READ_AHEAD_BLOCKS  	(16)

#define CONFIGURE_BDBUF_MAX_WRITE_BLOCKS       	(64)

#define CONFIGURE_BDBUF_BUFFER_MIN_SIZE 		(512)

#define CONFIGURE_BDBUF_BUFFER_MAX_SIZE 		(32 * 1024)

#define CONFIGURE_BDBUF_CACHE_MEMORY_SIZE (4 * 1024 * 1024)


#define CONFIGURE_MAXIMUM_USER_EXTENSIONS    1
#define CONFIGURE_INITIAL_EXTENSIONS         { .fatal = Fatal_extension }

// 3:  Exported Global Data (generally better to avoid)
// ----------------------------------------------------------------------------
// 4:  Functions (non-inline)
// ----------------------------------------------------------------------------

void *POSIX_Init (void *args);

#include <rtems/confdefs.h>

#endif // __CONFIG__

#endif // __RTEMS__

// Program the booting clocks
// Programme the system clocks at Startup
BSP_SET_CLOCK(SYS_CLK_KHZ, PLL_DESIRED_FREQ_KHZ, 1, 1, DEFAULT_CORE_CSS_DSS_CLOCKS | DEV_CSS_SDIO, APP_MSS_CLOCKS, APP_UPA_CLOCKS, APP_SIPP_CLOCKS, 0);

// Programme the  L2C at startup
BSP_SET_L2C_CONFIG(0, L2C_REPL_LRU, 0, L2C_MODE_COPY_BACK, 0, NULL);


#endif // _RTEMS_CONFIG_H_
