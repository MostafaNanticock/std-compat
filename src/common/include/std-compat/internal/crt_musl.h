#pragma once

#include <features.h>

#ifdef __MUSL__
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR 1
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR 2
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD 0
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
#    define PM_CRT_NAME "Musl libc"
#endif

#ifndef PM_CRT_MUSL
#    define PM_CRT_MUSL ((PM_CRT_VERSION_MAJOR * 1000000) + (PM_CRT_VERSION_MINOR * 10000) + (PM_CRT_VERSION_BUILD * 100) + PM_CRT_VERSION_REVISION)
#endif
