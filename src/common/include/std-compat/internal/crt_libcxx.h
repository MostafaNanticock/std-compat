#pragma once

#include <__config>

#ifdef _LIBCPP_VERSION
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR ((_LIBCPP_VERSION / 1000) % 1000)
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR ((_LIBCPP_VERSION / 10) % 100)
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD (_LIBCPP_VERSION % 10)
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
#    define PM_CRT_NAME "Clang libc++"
#endif

#ifndef PM_CRT_LIBCXX
#    define PM_CRT_LIBCXX ((PM_CRT_VERSION_MAJOR * 1000000) + (PM_CRT_VERSION_MINOR * 10000) + (PM_CRT_VERSION_BUILD * 100) + PM_CRT_VERSION_REVISION)
#endif
