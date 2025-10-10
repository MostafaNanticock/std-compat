#pragma once

#include <bits/c++config.h>

#ifdef __GLIBCXX__
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR ((__GLIBCXX__ / 10000) % 100)
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR ((__GLIBCXX__ / 100) % 100)
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD (__GLIBCXX__ % 100)
#    endif
#else
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR 0
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR 0
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD 0
#    endif
#endif

#ifndef PM_CRT_VERSION_REVISION
#    define PM_CRT_VERSION_REVISION 0
#endif

#ifndef PM_CRT_NAME
#    define PM_CRT_NAME "GCC libstdc++"
#endif

#ifndef PM_CRT_LIBSTDCXX
#    define PM_CRT_LIBSTDCXX ((PM_CRT_VERSION_MAJOR * 1000000) + (PM_CRT_VERSION_MINOR * 10000) + (PM_CRT_VERSION_BUILD * 100) + PM_CRT_VERSION_REVISION)
#endif
