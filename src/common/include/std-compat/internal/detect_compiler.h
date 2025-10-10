#pragma once

#if defined(_MSC_VER)
#    include "compiler_msvc.h"
#elif defined(__clang__)
#    include "compiler_clang.h"
#elif defined(__GNUC__)
#    include "compiler_gcc.h"
#else
#    define PM_COMPILER_IS_MSVC 0
#    define PM_COMPILER_IS_CLANG 0
#    define PM_COMPILER_IS_GCC 0

#    define PM_COMPILER_VERSION_MAJOR 0
#    define PM_COMPILER_VERSION_MINOR 0
#    define PM_COMPILER_VERSION_BUILD 0
#    define PM_COMPILER_VERSION_REVISION 0
#endif

#ifdef _MSVC_LANG
#    define PM_CPP_VERSION _MSVC_LANG
#elif defined(__cplusplus)
#    define PM_CPP_VERSION __cplusplus
#else
#    define PM_CPP_VERSION 0
#endif

#include "crt_patches/patches.h"

#include <string>

namespace PM
{
namespace internal
{
    inline std::string compilerVersionString()
    {
        // clang-format off
        static std::string result = std::string(PM_COMPILER_NAME) + " " +
                                    std::to_string(PM_COMPILER_VERSION_MAJOR) + "." +
                                    std::to_string(PM_COMPILER_VERSION_MINOR) + "." +
                                    std::to_string(PM_COMPILER_VERSION_BUILD) + "." +
                                    std::to_string(PM_COMPILER_VERSION_REVISION);
        // clang-format on

        return result;
    }
} // namespace internal
} // namespace PM
