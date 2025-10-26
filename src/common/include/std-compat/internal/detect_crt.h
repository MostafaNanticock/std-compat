#pragma once

#include "detect_compiler.h"

/* =========================
   Step 1: Normalize detection
   ========================= */

#if defined(PM_CC_MSVC)
#    define __STDC_INCLUDE_CRT_MSVC__
#else
/* Probe and include headers that define CRT-identifying macros */
#    if defined(__has_include)
#        if __has_include(<version>)
#            include <version>
#        endif
#        if __has_include(<bits/c++config.h>)
#            include <bits/c++config.h> /* libstdc++ macro __GLIBCXX__ */
#        endif
#        if __has_include(<libc++/version.hpp>)
#            include <libc++/version.hpp> /* libc++ macro _LIBCPP_VERSION */
#        endif
#        if __has_include(<ciso646>)
#            include <ciso646> /* may define _LIBCPP_VERSION in libc++ */
#        endif
#    endif

/* Prefer platform-specific CRTs first */
#    if defined(__APPLE__)
#        if defined(_LIBCPP_VERSION)
#            define __STDC_INCLUDE_CRT_APPLE__ /* Apple libc++ */
#        else
#            define __STDC_INCLUDE_CRT_LIBSTDCXX__ /* Rare: Apple toolchain using libstdc++ */
#        endif

#    elif defined(__ANDROID__) || defined(__BIONIC__)
#        define __STDC_INCLUDE_CRT_BIONIC__ /* Android bionic (usually with libc++) */

/* Then decide based on CRT macros */
#    elif defined(_LIBCPP_VERSION)
#        define __STDC_INCLUDE_CRT_LIBCXX__ /* libc++ (Clang or GCC targeting libc++) */

#    elif defined(__GLIBCXX__)
#        if defined(__MINGW32__)
#            define __STDC_INCLUDE_CRT_MINGW__
#        elif defined(__NEWLIB__)
#            define __STDC_INCLUDE_CRT_NEWLIB__
#        elif defined(__MUSL__)
#            define __STDC_INCLUDE_CRT_MUSL__
#        else
#            define __STDC_INCLUDE_CRT_LIBSTDCXX__ /* GNU libstdc++ */
#        endif

/* Fallbacks if CRT macros aren’t available (IDE parsing, atypical setups) */
#    elif defined(__MINGW32__)
#        define __STDC_INCLUDE_CRT_MINGW__
#    elif defined(__NEWLIB__)
#        define __STDC_INCLUDE_CRT_NEWLIB__
#    elif defined(__MUSL__)
#        define __STDC_INCLUDE_CRT_MUSL__
#    elif defined(__GNUC__) && !defined(__clang__)
#        define __STDC_INCLUDE_CRT_LIBSTDCXX__
#    elif defined(__clang__)
#        define __STDC_INCLUDE_CRT_LIBCXX__

#    else
#        error "Unsupported compiler or CRT"
#    endif
#endif

/* =========================
   Step 2: Linear include chain
   ========================= */

#if defined(__STDC_INCLUDE_CRT_MSVC__)
#    include "crt_msvc.h"
#elif defined(__STDC_INCLUDE_CRT_APPLE__)
#    include "crt_apple.h"
#elif defined(__STDC_INCLUDE_CRT_BIONIC__)
#    include "crt_bionic.h"
#elif defined(__STDC_INCLUDE_CRT_LIBCXX__)
#    include "crt_libcxx.h"
#elif defined(__STDC_INCLUDE_CRT_MINGW__)
#    include "crt_mingw.h"
#elif defined(__STDC_INCLUDE_CRT_NEWLIB__)
#    include "crt_newlib.h"
#elif defined(__STDC_INCLUDE_CRT_MUSL__)
#    include "crt_musl.h"
#elif defined(__STDC_INCLUDE_CRT_LIBSTDCXX__)
#    include "crt_libstdcxx.h"
#else
#    error "Unsupported compiler or CRT (no internal CRT define set)"
#endif

#include "crt_patches/patches.h"

#include <string>

namespace PM
{
namespace internal
{
    inline std::string crtVersionString()
    {
        // clang-format off
        static std::string result = std::to_string(STDC_CRT_VERSION_MAJOR) + "." +
                                    std::to_string(STDC_CRT_VERSION_MINOR) + "." +
                                    std::to_string(STDC_CRT_VERSION_BUILD) + "." +
                                    std::to_string(STDC_CRT_VERSION_REVISION);
        // clang-format on

        return result;
    }
} // namespace internal
} // namespace PM
