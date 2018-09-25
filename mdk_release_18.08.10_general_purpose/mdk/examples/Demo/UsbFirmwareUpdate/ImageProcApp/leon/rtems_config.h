///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     RTEMS configuration Leon header
///
#ifndef RTEMS_CONFIG_H_
#define RTEMS_CONFIG_H_

// 1: Includes
// ----------------------------------------------------------------------------
#include "fatalExtension.h"


// 2: Defines
// ----------------------------------------------------------------------------
#if defined(__RTEMS__)

#if !defined (__CONFIG__)
#define __CONFIG__

/* ask the system to generate a configuration table */
#define CONFIGURE_INIT

#ifndef RTEMS_POSIX_API
#define RTEMS_POSIX_API
#endif

#define CONFIGURE_MICROSECONDS_PER_TICK         1000    /* 1 millisecond */

#define CONFIGURE_TICKS_PER_TIMESLICE           50      /* 50 milliseconds */

//#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

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

#define CONFIGURE_MAXIMUM_DEVICES 10

#define CONFIGURE_MAXIMUM_SEMAPHORES (4 * RTEMS_DOSFS_SEMAPHORES_PER_INSTANCE)

#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 30

#define CONFIGURE_APPLICATION_NEEDS_LIBBLOCK

#define CONFIGURE_POSIX_INIT_TASKS_TABLE

#define CONFIGURE_MAXIMUM_USER_EXTENSIONS    1

#define CONFIGURE_INITIAL_EXTENSIONS         { .fatal = Fatal_extension }

void *POSIX_Init (void *args);

#include <rtems/confdefs.h>

#endif // __CONFIG__

#endif // __RTEMS__

#endif // LEON_RTEMS_CONFIG_H_

/* end of file */