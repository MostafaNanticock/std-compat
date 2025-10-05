#ifndef PM_STD_COMPAT_LAYER_COMMON_TESTING
#define PM_STD_COMPAT_LAYER_COMMON_TESTING

#include <msvc_crt_version.h>

#include <iostream>

#ifndef PM_UNUSED
#    define PM_UNUSED(x) static_cast<void>(x)
#endif

// clang-format off
#define PM_EXECUTE_TEST(TestFunctionName)                                                       \
std::cout << "=== Testing " << #TestFunctionName << " ===" << std::endl;                        \
    if (!TestFunctionName())                                                                    \
    {                                                                                           \
        std::cerr << "Test function :" << #TestFunctionName << "() failed" << std::endl;        \
        return -1;                                                                              \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        std::cout << "=== " << #TestFunctionName << ": All tests passed ===\n" << std::endl;    \
    }

#define PM_PRINT_COMPILE_INFO                                                                   \
    std::cout << "MSVC compiler version: " << PM_MSVC_VERSION_STRING << std::endl;                 \
    std::cout << "UCRT version: " << PM_UCRT_VERSION_STRING << std::endl;
// clang-format on

#endif
