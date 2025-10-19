#pragma once

#include <_mingw.h>

#ifdef __MINGW64_VERSION_MAJOR
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR __MINGW64_VERSION_MAJOR
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR __MINGW64_VERSION_MINOR
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD 0
#    endif

#    ifndef STDC_CRT_VERSION_REVISION
#        define STDC_CRT_VERSION_REVISION 0
#    endif

#    ifndef STDC_CRT_NAME
#        define STDC_CRT_NAME "MinGW-w64 CRT"
#    endif
#elif defined(__MINGW32_MAJOR_VERSION)
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR __MINGW32_MAJOR_VERSION
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR __MINGW32_MINOR_VERSION
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD 0
#    endif

#    ifndef STDC_CRT_VERSION_REVISION
#        define STDC_CRT_VERSION_REVISION 0
#    endif

#    ifndef STDC_CRT_NAME
#        define STDC_CRT_NAME "MinGW CRT"
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

#    ifndef STDC_CRT_VERSION_REVISION
#        define STDC_CRT_VERSION_REVISION 0
#    endif

#    ifndef STDC_CRT_NAME
#        define STDC_CRT_NAME "Unknown MinGW CRT"
#    endif
#endif

#ifndef STDC_CRT_MINGW
#    define STDC_CRT_MINGW ((STDC_CRT_VERSION_MAJOR * 1000000) + (STDC_CRT_VERSION_MINOR * 10000) + (STDC_CRT_VERSION_BUILD * 100) + STDC_CRT_VERSION_REVISION)
#endif
