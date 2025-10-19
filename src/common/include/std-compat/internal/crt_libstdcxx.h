#pragma once

#include <bits/c++config.h>

#ifdef __GLIBCXX__
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR ((__GLIBCXX__ / 10000) % 100)
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR ((__GLIBCXX__ / 100) % 100)
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD (__GLIBCXX__ % 100)
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
#    define STDC_CRT_NAME "GCC libstdc++"
#endif

#ifndef STDC_CRT_LIBSTDCXX
#    define STDC_CRT_LIBSTDCXX ((STDC_CRT_VERSION_MAJOR * 1000000) + (STDC_CRT_VERSION_MINOR * 10000) + (STDC_CRT_VERSION_BUILD * 100) + STDC_CRT_VERSION_REVISION)
#endif
