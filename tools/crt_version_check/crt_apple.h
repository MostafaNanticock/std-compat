#pragma once
#include <Availability.h>

#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
    #define PM_CRT_VERSION_MAJOR (__MAC_OS_X_VERSION_MIN_REQUIRED / 10000)
    #define PM_CRT_VERSION_MINOR ((__MAC_OS_X_VERSION_MIN_REQUIRED / 100) % 100)
    #define PM_CRT_VERSION_BUILD (__MAC_OS_X_VERSION_MIN_REQUIRED % 100)
#else
    #define PM_CRT_VERSION_MAJOR 0
    #define PM_CRT_VERSION_MINOR 0
    #define PM_CRT_VERSION_BUILD 0
#endif

#define PM_CRT_VERSION_REVISION 0
#define PM_CRT_NAME "Apple CRT (libSystem)"
