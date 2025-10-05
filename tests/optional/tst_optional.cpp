#include <../common/testing.h>

#include <optional>

// Optional feature toggles (if we need c++23 compatibility [Off by default]):
//   - STD_OPTIONAL_HAS_MONADIC_OPERATIONS

bool test_optional()
{
    // 1. Default construction (empty)
    std::optional<int> o1;
    if (o1.has_value())
        return false;

    // 2. Construction with value
    std::optional<int> o2(42);
    if (!o2.has_value() || *o2 != 42)
        return false;

    // 3. Copy constructor
    std::optional<int> o3 = o2;
    if (!o3.has_value() || *o3 != 42)
        return false;

    // 4. Move constructor
    std::optional<int> o4 = std::move(o3);
    if (!o4.has_value() || *o4 != 42)
        return false;

    // 5. Copy assignment
    o4 = o1;
    if (o4.has_value())
        return false;

    // 6. Move assignment
    o4 = std::optional<int>(99);
    if (!o4.has_value() || *o4 != 99)
        return false;

    // 7. operator-> and operator*
    struct Box
    {
        int v;
        int get() const
        {
            return v;
        }
    };
    std::optional<Box> ob(Box{7});
    if (!ob.has_value())
        return false;
    if (ob->get() != 7)
        return false;
    if ((*ob).get() != 7)
        return false;

    // 8. value()
    if (ob.value().get() != 7)
        return false;

    // 9. value_or()
    if (o1.value_or(123) != 123)
        return false;
    if (o2.value_or(123) != 42)
        return false;

    // 10. reset()
    o2.reset();
    if (o2.has_value())
        return false;

    // 11. emplace()
    o2.emplace(55);
    if (!o2.has_value() || *o2 != 55)
        return false;

    // 12. swap (member)
    std::optional<int> o5(11);
    o2.swap(o5);
    if (*o2 != 11 || *o5 != 55)
        return false;

    // 13. swap (non-member)
    std::swap(o2, o5);
    if (*o2 != 55 || *o5 != 11)
        return false;

#ifdef STD_OPTIONAL_HAS_MONADIC_OPERATIONS
    // 14. Monadic and_then()
    bool and_then_called = false;
    o2.and_then(
        [&](int v)
        {
            and_then_called = (v == 55);
            return std::optional<int>(v + 1);
        });
    if (!and_then_called)
        return false;

    // 15. Monadic transform()
    auto o6 = o2.transform([](int v) { return v * 2; });
    if (!o6.has_value() || *o6 != 110)
        return false;

    // 16. Monadic or_else()
    auto o7 = o2.or_else([]() { return std::optional<int>(999); });
    if (!o7.has_value() || *o7 != 55)
        return false;
#endif

    auto o8 = std::optional<int>();

#ifdef STD_OPTIONAL_HAS_MONADIC_OPERATIONS
    auto o9 = o8.or_else([]() { return std::optional<int>(999); });
    if (!o9.has_value() || *o9 != 999)
        return false;
#endif

    // 17. bad_optional_access
    {
        bool threw = false;
        try
        {
            PM_UNUSED(o8.value()); // should throw
        }
        catch (const std::bad_optional_access &)
        {
            threw = true;
        }
        if (!threw)
            return false;
    }

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_optional);
}
