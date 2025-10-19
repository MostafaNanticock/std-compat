#pragma once

#include <features.h>

#ifdef __MUSL__
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR 1
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR 2
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD 0
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
#    define STDC_CRT_NAME "Musl libc"
#endif

#ifndef STDC_CRT_MUSL
#    define STDC_CRT_MUSL ((STDC_CRT_VERSION_MAJOR * 1000000) + (STDC_CRT_VERSION_MINOR * 10000) + (STDC_CRT_VERSION_BUILD * 100) + STDC_CRT_VERSION_REVISION)
#endif
