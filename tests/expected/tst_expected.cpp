#include <../common/testing.h>

#include <expected>
#include <expected_compatibility>

struct Box
{
    int v;
    int get() const
    {
        return v;
    }
};

bool test_expected()
{
    // 1. Default construction with value
    std::expected<int, std::string> e1(42);
    if (!e1.has_value())
        return false;
    if (*e1 != 42)
        return false;

           // 2. Construction with unexpected
    std::expected<int, std::string> e2(std_compatibility::unexpected<std::string>("error"));
    if (e2.has_value())
        return false;
    if (e2.error() != "error")
        return false;

           // 3. Copy constructor
    std::expected<int, std::string> e3 = e1;
    if (!e3.has_value() || *e3 != 42)
        return false;

           // 4. Move constructor
    std::expected<int, std::string> e4 = std::move(e3);
    if (!e4.has_value() || *e4 != 42)
        return false;

           // 5. Copy assignment
    e4 = e2;
    if (e4.has_value())
        return false;
    if (e4.error() != "error")
        return false;

           // 6. Move assignment
    e4 = std::expected<int, std::string>(99);
    if (!e4.has_value() || *e4 != 99)
        return false;

           // 7. operator-> and operator*
    std::expected<Box, std::string> bx(Box{7});
    if (!bx.has_value())
        return false;
    if (bx->get() != 7)
        return false; // operator-> path
    if ((*bx).get() != 7)
        return false; // operator* path

           // 8. value() and error()
    if (e4.value() != 99)
        return false;
    e4 = std_compatibility::unexpected<std::string>("oops");
    if (e4.has_value())
        return false;
    if (e4.error() != "oops")
        return false;

           // 9. value_or()
    if (e4.value_or(123) != 123)
        return false;
    e4 = 77;
    if (e4.value_or(123) != 77)
        return false;

           // 10. error_or() (C++23, but tl::expected provides it)
    e4 = 55;
    if (e4.error_or(std::string("fallback")) != "fallback")
        return false;
    e4 = std_compatibility::unexpected<std::string>("bad");
    if (e4.error_or(std::string("fallback")) != "bad")
        return false;

           // 11. emplace()
    e4.emplace(88);
    if (!e4.has_value() || *e4 != 88)
        return false;

           // 12. swap (member)
    std::expected<int, std::string> e5(11);
    e4.swap(e5);
    if (*e4 != 11 || *e5 != 88)
        return false;

           // 13. swap (non-member)
    std::swap(e4, e5);
    if (*e4 != 88 || *e5 != 11)
        return false;

           // 14. Monadic and_then()
    bool and_then_called = false;
    PM_UNUSED(e4.and_then(
        [&](int v)
        {
            and_then_called = (v == 88);
            return std::expected<int, std::string>(v + 1);
        }));
    if (!and_then_called)
        return false;

           // 15. Monadic transform()
    auto e6 = e4.transform([](int v) { return v * 2; });
    if (!e6.has_value() || *e6 != 176)
        return false;

           // 16. Monadic or_else()
    auto e7 = e4.or_else([](const std::string &) { return std::expected<int, std::string>(999); });
    if (!e7.has_value() || *e7 != 88)
        return false;

    std::expected<int, std::string> e8 = std_compatibility::unexpected<std::string>("err");
    auto e9 = e8.or_else([](const std::string &) { return std::expected<int, std::string>(999); });
    if (!e9.has_value() || *e9 != 999)
        return false;

           // 17. Monadic transform_error()
    auto e10 = e8.transform_error([](const std::string &s) { return s + "!"; });
    if (e10.error() != "err!")
        return false;

           // 18. bad_expected_access
    {
        bool threw = false;
        try
        {
            PM_UNUSED(e8.value()); // should throw
        }
        catch (const std::bad_expected_access<std::string> &ex)
        {
            if (ex.error() != "err")
                return false;
            threw = true;
        }
        if (!threw)
            return false;
    }

    return true;
}

int main()
{
    PM_EXECUTE_TEST(test_expected);
}
