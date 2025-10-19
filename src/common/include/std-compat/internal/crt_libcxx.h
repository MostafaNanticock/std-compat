#pragma once

#include <__config>

#ifdef _LIBCPP_VERSION
#    ifndef STDC_CRT_VERSION_MAJOR
#        define STDC_CRT_VERSION_MAJOR ((_LIBCPP_VERSION / 1000) % 1000)
#    endif

#    ifndef STDC_CRT_VERSION_MINOR
#        define STDC_CRT_VERSION_MINOR ((_LIBCPP_VERSION / 10) % 100)
#    endif

#    ifndef STDC_CRT_VERSION_BUILD
#        define STDC_CRT_VERSION_BUILD (_LIBCPP_VERSION % 10)
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
#    define STDC_CRT_NAME "Clang libc++"
#endif

#ifndef STDC_CRT_LIBCXX
#    define STDC_CRT_LIBCXX ((STDC_CRT_VERSION_MAJOR * 1000000) + (STDC_CRT_VERSION_MINOR * 10000) + (STDC_CRT_VERSION_BUILD * 100) + STDC_CRT_VERSION_REVISION)
#endif
