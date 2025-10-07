#pragma once
#include <__config>

#ifdef _LIBCPP_VERSION
    #define PM_CRT_VERSION_MAJOR ((_LIBCPP_VERSION / 1000) % 1000)
    #define PM_CRT_VERSION_MINOR ((_LIBCPP_VERSION / 10) % 100)
    #define PM_CRT_VERSION_BUILD (_LIBCPP_VERSION % 10)
#else
    #define PM_CRT_VERSION_MAJOR 0
    #define PM_CRT_VERSION_MINOR 0
    #define PM_CRT_VERSION_BUILD 0
#endif

#define PM_CRT_VERSION_REVISION 0
#define PM_CRT_NAME "Clang libc++"
