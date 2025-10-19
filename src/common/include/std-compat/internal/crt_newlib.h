#pragma once

#include <_newlib_version.h>

#ifdef _NEWLIB_VERSION
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR ((_NEWLIB_VERSION / 10000) % 100)
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR ((_NEWLIB_VERSION / 100) % 100)
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD (_NEWLIB_VERSION % 100)
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
#    define STDC_CRT_NAME "Newlib CRT"
#endif

#ifndef STDC_CRT_NEWLIB
#    define STDC_CRT_NEWLIB ((STDC_CRT_VERSION_MAJOR * 1000000) + (STDC_CRT_VERSION_MINOR * 10000) + (STDC_CRT_VERSION_BUILD * 100) + STDC_CRT_VERSION_REVISION)
#endif
