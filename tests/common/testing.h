#ifndef PM_STD_COMPAT_LAYER_COMMON_TESTING
#define PM_STD_COMPAT_LAYER_COMMON_TESTING

// #include <std-compat/internal/msvc_crt_version.h>
#include <std-compat/internal/msvc_crt_version.h>

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
    std::cout << "MSVC version: " << PM::internal::msvcVersionString() << std::endl;            \
    std::cout << "UCRT version: " << PM::internal::ucrtVersionString() << std::endl;
// clang-format on

#endif
