#pragma once
#include <bits/c++config.h>

#ifdef __GLIBCXX__
    #define PM_CRT_VERSION_MAJOR ((__GLIBCXX__ / 10000) % 100)
    #define PM_CRT_VERSION_MINOR ((__GLIBCXX__ / 100) % 100)
    #define PM_CRT_VERSION_BUILD (__GLIBCXX__ % 100)
#else
    #define PM_CRT_VERSION_MAJOR 0
    #define PM_CRT_VERSION_MINOR 0
    #define PM_CRT_VERSION_BUILD 0
#endif

#define PM_CRT_VERSION_REVISION 0
#define PM_CRT_NAME "GCC libstdc++"
