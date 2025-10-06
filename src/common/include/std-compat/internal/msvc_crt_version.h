#ifndef PM_STD_COMPAT_LAYER_COMMON_MSVC_CRT_DETECTION
#define PM_STD_COMPAT_LAYER_COMMON_MSVC_CRT_DETECTION

#ifndef _MSC_VER
#    error "This header requires MSVC."
#endif

#include <crtversion.h>
#include <string>

// ---------------- Compiler version ----------------

// Extract major/minor from _MSC_VER
#define PM_MSVC_VER_MAJOR (_MSC_VER / 100)
#define PM_MSVC_VER_MINOR (_MSC_VER % 100)

// Extract build from _MSC_FULL_VER
#if _MSC_FULL_VER >= 1000000000
// 10 digits: MMNNBBBBBB
#    define PM_MSVC_VER_BUILD ((_MSC_FULL_VER / 100000) % 100000)
#else
// 9 digits: MMNNBBBBB
#    define PM_MSVC_VER_BUILD ((_MSC_FULL_VER / 10000) % 100000)
#endif

// Revision
#define PM_MSVC_VER_REVISION _MSC_BUILD

// ---------------- UCRT version ----------------

#define PM_UCRT_VER_MAJOR _VC_CRT_MAJOR_VERSION
#define PM_UCRT_VER_MINOR _VC_CRT_MINOR_VERSION
#define PM_UCRT_VER_BUILD _VC_CRT_BUILD_VERSION
#define PM_UCRT_VER_REVISION _VC_CRT_RBUILD_VERSION

// Composite version for easier comparison
#define PM_UCRT_VER (PM_UCRT_VER_MAJOR * 10000000 + PM_UCRT_VER_MINOR * 100000 + PM_UCRT_VER_BUILD)

// Known UCRT version constants for major Visual Studio releases
// Based on when std::variant and related components were introduced
#define PM_UCRT_VER_VS2017_15_0 140000000  // Visual Studio 2017 15.0 - First version with std::variant support

namespace PM
{
namespace internal
{
    inline std::string msvcVersionString()
    {
        // clang-format off
        static std::string result = std::to_string(PM_MSVC_VER_MAJOR) + "." +
                                    std::to_string(PM_MSVC_VER_MINOR) + "." +
                                    std::to_string(PM_MSVC_VER_BUILD) + "." +
                                    std::to_string(PM_MSVC_VER_REVISION);
        // clang-format on

        return result;
    }

    inline std::string ucrtVersionString()
    {
        // clang-format off
        static std::string result = std::to_string(PM_UCRT_VER_MAJOR) + "." +
                                    std::to_string(PM_UCRT_VER_MINOR) + "." +
                                    std::to_string(PM_UCRT_VER_BUILD) + "." +
                                    std::to_string(PM_UCRT_VER_REVISION);
        // clang-format on

        return result;
    }
} // namespace internal
} // namespace PM

#endif // PM_STD_COMPAT_LAYER_COMMON_MSVC_CRT_DETECTION
