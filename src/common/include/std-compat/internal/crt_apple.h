#pragma once

#include <Availability.h>

#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR (__MAC_OS_X_VERSION_MIN_REQUIRED / 10000)
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR ((__MAC_OS_X_VERSION_MIN_REQUIRED / 100) % 100)
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD (__MAC_OS_X_VERSION_MIN_REQUIRED % 100)
#    endif
#else
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR 0
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR 0
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD 0
#    endif
#endif

#ifndef STDC_CRT_VERSION_REVISION
#    define STDC_CRT_VERSION_REVISION 0
#endif

#ifndef STDC_CRT_NAME
#    define STDC_CRT_NAME "Apple CRT (libSystem)"
#endif

#ifndef STDC_CRT_APPLE
#    define STDC_CRT_APPLE ((STDC_CRT_VERSION_MAJOR * 1000000) + (STDC_CRT_VERSION_MINOR * 10000) + (STDC_CRT_VERSION_BUILD * 100) + STDC_CRT_VERSION_REVISION)
#endif
