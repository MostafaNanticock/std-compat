#pragma once
#include <crtversion.h>

#ifndef PM_CRT_VERSION_MAJOR
#    define PM_CRT_VERSION_MAJOR _VC_CRT_MAJOR_VERSION
#endif

#ifndef PM_CRT_VERSION_MINOR
#    define PM_CRT_VERSION_MINOR _VC_CRT_MINOR_VERSION
#endif

#ifndef PM_CRT_VERSION_BUILD
#    define PM_CRT_VERSION_BUILD _VC_CRT_BUILD_VERSION
#endif

#ifndef PM_CRT_VERSION_REVISION
#    define PM_CRT_VERSION_REVISION _VC_CRT_RBUILD_VERSION
#endif

#ifndef PM_CRT_NAME
#    define PM_CRT_NAME "MSVC Universal CRT"
#endif
