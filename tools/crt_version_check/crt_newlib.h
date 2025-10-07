#pragma once
#include <_newlib_version.h>

#ifdef _NEWLIB_VERSION
    #define PM_CRT_VERSION_MAJOR ((_NEWLIB_VERSION / 10000) % 100)
    #define PM_CRT_VERSION_MINOR ((_NEWLIB_VERSION / 100) % 100)
    #define PM_CRT_VERSION_BUILD (_NEWLIB_VERSION % 100)
#else
    #define PM_CRT_VERSION_MAJOR 0
    #define PM_CRT_VERSION_MINOR 0
    #define PM_CRT_VERSION_BUILD 0
#endif

#define PM_CRT_VERSION_REVISION 0
#define PM_CRT_NAME "Newlib CRT"
