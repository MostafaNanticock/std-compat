#ifndef PM_STD_COMPAT_LAYER_COMMON_TESTING
#define PM_STD_COMPAT_LAYER_COMMON_TESTING

#include <iostream>

#ifndef PM_UNUSED
#    define PM_UNUSED(x) static_cast<void>(x)
#endif

// clang-format off
#define PM_EXECUTE_TEST(TestFunctionName)                                                       \
std::cout << "=== Testing " << #TestFunctionName << " ===" << std::endl;                    \
    if (!TestFunctionName())                                                                    \
{                                                                                           \
        std::cerr << "Test function :" << #TestFunctionName << "() failed" << std::endl;        \
        return -1;                                                                               \
}                                                                                           \
    else                                                                                        \
{                                                                                           \
        std::cout << "=== " << #TestFunctionName << ": All tests passed ===\n" << std::endl;    \
}
// clang-format on

#endif
