#pragma once

#include <_mingw.h>

#ifdef __MINGW64_VERSION_MAJOR
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR __MINGW64_VERSION_MAJOR
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR __MINGW64_VERSION_MINOR
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD 0
#    endif

#    ifndef PM_CRT_VERSION_REVISION
#        define PM_CRT_VERSION_REVISION 0
#    endif

#    ifndef PM_CRT_NAME
#        define PM_CRT_NAME "MinGW-w64 CRT"
#    endif
#elif defined(__MINGW32_MAJOR_VERSION)
#    ifndef PM_CRT_VERSION_MAJOR
#        define PM_CRT_VERSION_MAJOR __MINGW32_MAJOR_VERSION
#    endif

#    ifndef PM_CRT_VERSION_MINOR
#        define PM_CRT_VERSION_MINOR __MINGW32_MINOR_VERSION
#    endif

#    ifndef PM_CRT_VERSION_BUILD
#        define PM_CRT_VERSION_BUILD 0
#    endif

#    ifndef PM_CRT_VERSION_REVISION
#        define PM_CRT_VERSION_REVISION 0
#    endif

#    ifndef PM_CRT_NAME
#        define PM_CRT_NAME "MinGW CRT"
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

#    ifndef PM_CRT_VERSION_REVISION
#        define PM_CRT_VERSION_REVISION 0
#    endif

#    ifndef PM_CRT_NAME
#        define PM_CRT_NAME "Unknown MinGW CRT"
#    endif
#endif

//
// WORKAROUND for the 4.8 bug with non-existing std::to_string() implementation
//
#include "mingw/4.8_std_to_string.h"
