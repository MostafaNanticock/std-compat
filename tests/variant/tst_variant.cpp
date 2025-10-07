#include <testing.h>

#include <variant>

// #include "../../variant/include/std-compat/internal/monostate_compat.h"

bool test_variant()
{
// #ifdef _PM_CC_SUPPORTS_CXX17
//     std::monostate ms1;
//     std::cout << &ms1 << std::endl;
// #endif

#ifdef _PM_CC_SUPPORTS_CXX17
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
