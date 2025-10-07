#pragma once
#include <features.h>

#ifdef __MUSL__
    #define PM_CRT_VERSION_MAJOR 1
    #define PM_CRT_VERSION_MINOR 2
    #define PM_CRT_VERSION_BUILD 0
#else
    #define PM_CRT_VERSION_MAJOR 0
    #define PM_CRT_VERSION_MINOR 0
    #define PM_CRT_VERSION_BUILD 0
#endif

#define PM_CRT_VERSION_REVISION 0
#define PM_CRT_NAME "Musl libc"
