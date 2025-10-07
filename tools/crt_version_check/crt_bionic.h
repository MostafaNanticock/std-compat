#pragma once
#include <android/api-level.h>

#ifdef __ANDROID_API__
    #define PM_CRT_VERSION_MAJOR (__ANDROID_API__ / 100)
    #define PM_CRT_VERSION_MINOR (__ANDROID_API__ % 100)
#else
    #define PM_CRT_VERSION_MAJOR 0
    #define PM_CRT_VERSION_MINOR 0
#endif

#define PM_CRT_VERSION_BUILD 0
#define PM_CRT_VERSION_REVISION 0
#define PM_CRT_NAME "Android Bionic libc"
