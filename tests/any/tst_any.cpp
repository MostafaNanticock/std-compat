#include <../common/testing.h>

#include <any>

struct MoveAware
{
    int value;
    int moves;
    int copies;

    explicit MoveAware(int v) : value(v), moves(0), copies(0)
    {
    }
    MoveAware(const MoveAware &other) : value(other.value), moves(other.moves), copies(other.copies + 1)
    {
    }
    MoveAware(MoveAware &&other) noexcept : value(other.value), moves(other.moves + 1), copies(other.copies)
    {
    }
    MoveAware &operator=(const MoveAware &other)
    {
        if (this != &other)
        {
            value = other.value;
            moves = other.moves;
            copies = other.copies + 1;
        }
        return *this;
    }
    MoveAware &operator=(MoveAware &&other) noexcept
    {
        if (this != &other)
        {
            value = other.value;
            moves = other.moves + 1;
            copies = other.copies;
        }
        return *this;
    }
};

bool test_any()
{
    // 1. Default constructor
    std::any a;
    if (a.has_value())
        return false;
    if (a.type() != typeid(void))
        return false;

    // 2. Emplace (C++11-friendly instead of in_place_type)
    std::any b;
    b.emplace<int>(42);
    if (!b.has_value())
        return false;
    if (b.type() != typeid(int))
        return false;
    if (std::any_cast<int>(b) != 42)
        return false;

    // 3. Copy constructor
    std::any c = b;
    if (!c.has_value())
        return false;
    if (std::any_cast<int>(c) != 42)
        return false;

    // 4. Move constructor
    std::any d = std::move(c);
    if (!d.has_value())
        return false;
    if (std::any_cast<int>(d) != 42)
        return false;

    // 5. Converting constructor
    std::string s = "hello";
    std::any e = s;
    if (std::any_cast<std::string>(e) != "hello")
        return false;

    // 6. Copy assignment
    e = b;
    if (std::any_cast<int>(e) != 42)
        return false;

    // 7. Move assignment
    e = std::string("world");
    if (std::any_cast<std::string>(e) != "world")
        return false;

    // 8. emplace
    e.emplace<int>(99);
    if (std::any_cast<int>(e) != 99)
        return false;

    // 9. reset
    e.reset();
    if (e.has_value())
        return false;

    // 10. swap
    std::any f(123);
    std::any g(std::string("abc"));
    swap(f, g);
    if (std::any_cast<std::string>(f) != "abc")
        return false;
    if (std::any_cast<int>(g) != 123)
        return false;

    // 11. any_cast pointer form
    std::any h(3.14);
    double *pd = std::any_cast<double>(&h);
    if (!pd || *pd != 3.14)
        return false;

    // 12. any_cast reference form
    *std::any_cast<double>(&h) = 2.71;
    if (std::any_cast<double>(h) != 2.71)
        return false;

    // 13. make_any
    std::any i = std::make_any<std::string>("xyz");
    if (std::any_cast<std::string>(i) != "xyz")
        return false;

    // 14. bad_any_cast exception
    {
        bool threw = false;
        try
        {
            PM_UNUSED(std::any_cast<int>(h)); // h holds double
        }
        catch (const std::bad_any_cast &)
        {
            threw = true;
        }

        if (!threw)
            return false;
    }

    // 15. Move semantics with a copyable, movable type
    std::any j;
    j.emplace<MoveAware>(7);
    MoveAware m = std::any_cast<MoveAware>(std::move(j)); // value-returning any_cast yields by value (move)
    if (m.value != 7)
        return false;
    if (m.moves == 0)
        return false; // ensure a move happened

    return true;
}

int main()
{
    PM_EXECUTE_TEST(test_any);
}
