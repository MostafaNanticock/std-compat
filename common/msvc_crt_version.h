#ifndef PM_STD_COMPAT_LAYER_COMMON_MSVC_CRT_DETECTION
#define PM_STD_COMPAT_LAYER_COMMON_MSVC_CRT_DETECTION

// Detect MSVC toolset and map to CRT family
#if !defined(_MSC_VER)
#    error "This header requires MSVC."
#endif

// VS2015 (v140)
#if _MSC_VER == 1900
#    define MSVC_TOOLSET 140
#    define MSVC_VERSION_STR "Visual Studio 2015 (v140)"
#    define MSVC_CRT_FAMILY "VC++ 2015 CRT (vcruntime140.dll)"

// VS2017 (v141)
#elif _MSC_VER >= 1910 && _MSC_VER <= 1916
#    define MSVC_TOOLSET 141
#    define MSVC_VERSION_STR "Visual Studio 2017 (v141)"
#    define MSVC_CRT_FAMILY "VC++ 2017 CRT (vcruntime140.dll)"

// VS2019 (v142)
#elif _MSC_VER >= 1920 && _MSC_VER <= 1929
#    define MSVC_TOOLSET 142
#    define MSVC_VERSION_STR "Visual Studio 2019 (v142)"
#    define MSVC_CRT_FAMILY "VC++ 2019 CRT (vcruntime140.dll)"

// VS2022 (v143+)
#elif _MSC_VER >= 1930
#    define MSVC_TOOLSET 143
#    define MSVC_VERSION_STR "Visual Studio 2022+ (v143)"
#    define MSVC_CRT_FAMILY "VC++ 2022 CRT (vcruntime140.dll)"

// Unknown future version
#else
#    define MSVC_TOOLSET 0
#    define MSVC_VERSION_STR "Unknown future MSVC"
#    define MSVC_CRT_FAMILY "Unknown CRT family"
#endif

#endif
