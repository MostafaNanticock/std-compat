#pragma once

#include <android/api-level.h>

#ifdef __ANDROID_API__
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR (__ANDROID_API__ / 100)
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR (__ANDROID_API__ % 100)
#    endif
#else
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR 0
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR 0
#    endif
#endif

#ifndef PM_CRT_VERSION_BUILD
#    define PM_CRT_VERSION_BUILD 0
#endif

#ifndef PM_CRT_VERSION_REVISION
#    define PM_CRT_VERSION_REVISION 0
#endif

#ifndef PM_CRT_NAME
#    define PM_CRT_NAME "Android Bionic libc"
#endif
