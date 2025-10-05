#include <../common/testing.h>

#include <variant>

bool test_variant()
{
    // 1. Constructors
    std::variant<int, std::string> v1; // default constructs first alternative
    if (!std::holds_alternative<int>(v1) || v1.index() != 0)
        return false;
    if (std::get<int>(v1) != 0)
        return false;

    std::variant<int, std::string> v2(42);
    if (!std::holds_alternative<int>(v2) || std::get<int>(v2) != 42)
        return false;

    std::variant<int, std::string> v3(std::string("hello"));
    if (!std::holds_alternative<std::string>(v3) || std::get<std::string>(v3) != "hello")
        return false;

    // 2. Copy constructor
    std::variant<int, std::string> v4(v2);
    if (!std::holds_alternative<int>(v4) || std::get<int>(v4) != 42)
        return false;

    // 3. Move constructor
    std::variant<int, std::string> v5(std::move(v4));
    if (!std::holds_alternative<int>(v5) || std::get<int>(v5) != 42)
        return false;

    // 4. Copy assignment
    v5 = v3;
    if (!std::holds_alternative<std::string>(v5) || std::get<std::string>(v5) != "hello")
        return false;

    // 5. Move assignment
    v5 = std::variant<int, std::string>(99);
    if (!std::holds_alternative<int>(v5) || std::get<int>(v5) != 99)
        return false;

    // 6. Observers: index, valueless_by_exception
    if (v5.index() != 0)
        return false;
    if (v5.valueless_by_exception())
        return false;

    // 7. Modifiers: emplace
    v5.emplace<std::string>("world");
    if (!std::holds_alternative<std::string>(v5) || std::get<std::string>(v5) != "world")
        return false;

    // 8. swap (member)
    std::variant<int, std::string> v6(123);
    v5.swap(v6);
    if (!std::holds_alternative<int>(v5) || std::get<int>(v5) != 123)
        return false;
    if (!std::holds_alternative<std::string>(v6) || std::get<std::string>(v6) != "world")
        return false;

    // 9. swap (non-member)
    std::swap(v5, v6);
    if (!std::holds_alternative<std::string>(v5) || std::get<std::string>(v5) != "world")
        return false;
    if (!std::holds_alternative<int>(v6) || std::get<int>(v6) != 123)
        return false;

    // 10. Non-member visit
    bool visited = false;
    std::visit(
        [&](std::variant<int, std::string> &&arg)
        {
            visited = true;
            PM_UNUSED(arg);
        },
        v5);
    if (!visited)
        return false;

    // 11. get / get_if by type
    if (*std::get_if<std::string>(&v5) != "world")
        return false;
    if (std::get_if<int>(&v5) != nullptr)
        return false;

    // 12. get / get_if by index
    if (*std::get_if<1>(&v5) != "world")
        return false;
    if (std::get_if<0>(&v5) != nullptr)
        return false;

    // 13. holds_alternative
    if (!std::holds_alternative<std::string>(v5))
        return false;
    if (std::holds_alternative<int>(v5))
        return false;

    // 14. bad_variant_access
    {
        bool threw = false;
        try
        {
            PM_UNUSED(std::get<int>(v5)); // wrong type
        }
        catch (const std::bad_variant_access &)
        {
            threw = true;
        }

        if (!threw)
            return false;
    }

    // 15. monostate
    std::variant<std::monostate, int> v7;
    if (!std::holds_alternative<std::monostate>(v7))
        return false;
    if (!(v7 == std::variant<std::monostate, int>(std::monostate{})))
        return false;

    // 16. variant_size / variant_alternative
    if (std::variant_size<decltype(v1)>::value != 2)
        return false;
    typedef std::variant_alternative<0, decltype(v1)>::type first_type;
    if (!std::is_same<first_type, int>::value)
        return false;

    // 17. variant_npos
    if (std::variant_npos != static_cast<std::size_t>(-1))
        return false;

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_variant);
}
