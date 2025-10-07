#include <testing.h>

#define PM_HAS_STD_BAD_VARIANT_ACCESS _PM_CC_SUPPORTS_CXX17

#if PM_HAS_STD_BAD_VARIANT_ACCESS
#    include <variant>
#endif
#include <exception>

// #include "../../variant/include/std-compat/internal/monostate_compat.h"

bool test_variant()
{
    // #ifdef _PM_CC_SUPPORTS_CXX17
    //     std::monostate ms1;
    //     std::cout << &ms1 << std::endl;
    // #endif

#ifdef PM_HAS_STD_BAD_VARIANT_ACCESS
    std::bad_variant_access bva;
    std::cout << &bva << std::endl;
#endif

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_variant);
}
