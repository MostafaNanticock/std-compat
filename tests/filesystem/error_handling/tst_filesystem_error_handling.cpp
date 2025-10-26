#include <testing.h>

#include <filesystem>

bool test_error_handling()
{
    // FIXME: not implemented yet

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_error_handling);
}
