#pragma once

#include <Availability.h>

#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR (__MAC_OS_X_VERSION_MIN_REQUIRED / 10000)
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR ((__MAC_OS_X_VERSION_MIN_REQUIRED / 100) % 100)
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD (__MAC_OS_X_VERSION_MIN_REQUIRED % 100)
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
#    define PM_CRT_NAME "Apple CRT (libSystem)"
#endif

#ifndef PM_CRT_APPLE
#    define PM_CRT_APPLE ((PM_CRT_VERSION_MAJOR * 1000000) + (PM_CRT_VERSION_MINOR * 10000) + (PM_CRT_VERSION_BUILD * 100) + PM_CRT_VERSION_REVISION)
#endif
