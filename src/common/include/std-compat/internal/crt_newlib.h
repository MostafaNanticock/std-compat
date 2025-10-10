#pragma once

#include <_newlib_version.h>

#ifdef _NEWLIB_VERSION
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR ((_NEWLIB_VERSION / 10000) % 100)
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR ((_NEWLIB_VERSION / 100) % 100)
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD (_NEWLIB_VERSION % 100)
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
#    define PM_CRT_NAME "Newlib CRT"
#endif

#ifndef PM_CRT_NEWLIB
#    define PM_CRT_NEWLIB ((PM_CRT_VERSION_MAJOR * 1000000) + (PM_CRT_VERSION_MINOR * 10000) + (PM_CRT_VERSION_BUILD * 100) + PM_CRT_VERSION_REVISION)
#endif
