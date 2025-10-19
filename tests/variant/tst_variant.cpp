#include <testing.h>

#include <variant>

// constexpr bool operator==(std::monostate, std::monostate) noexcept
// {
//     return true;
// }

// constexpr bool operator!=(std::monostate, std::monostate) noexcept
// {
//     return true;
// }

#ifdef PM_STD_VARIANT
namespace PM
{
template <class _Storage, class _Fn>
constexpr std::_Variant_raw_visit_t<_Fn, _Storage> _Variant_raw_visit(size_t _Idx, _Storage &&_Obj,
                                                                      _Fn &&_Func) noexcept(std::_Variant_raw_visit_dispatch<_Fn, _Storage>)
{
    // Call _Func with _Storage if _Idx is variant_npos, and otherwise the _Idx-th element in _Storage.
    // pre: _Idx + 1 <= remove_reference_t<_Storage>::_Size
    constexpr size_t _Size = std::remove_reference_t<_Storage>::_Size;
    constexpr int _Strategy = _Size <= 4 ? 1 : _Size <= 16 ? 2 : _Size <= 64 ? 3 : _Size <= 256 ? 4 : -1;
    ++_Idx; // bias index by +1 to map {variant_npos} U [0, _Size) to the contiguous range [0, _Size]
    return std::_Variant_raw_visit1<_Strategy>::_Visit(_Idx, static_cast<_Fn &&>(_Func), static_cast<_Storage &&>(_Obj));
}

template <class _Ty, size_t _Tag>
struct _Tagged
{ // aggregate a runtime value and a compile-time tag value
    static constexpr size_t _Idx = _Tag;
    _Ty _Val;
};

template <class _Op, class _Result, class... _Types>
struct _Variant_relop_visitor2
{ // evaluate _Op with the contained value of two variants that hold the same alternative
    const std::_Variant_storage<_Types...> &_Left;

    template <class _Ty, size_t _Idx>
    constexpr _Result operator()(PM::_Tagged<const _Ty &, _Idx> _Right) const noexcept(
        std::disjunction_v<std::bool_constant<_Idx == std::variant_npos>, std::is_nothrow_invocable_r<_Result, _Op, const _Ty &, const _Ty &>>)
    {
        // determine the relationship between the stored values of _Left and _Right
        // pre: _Left.index() == _Idx && _Right.index() == _Idx
        if constexpr (_Idx != std::variant_npos)
            return _Op{}(std::_Variant_raw_get<_Idx>(_Left), _Right._Val);
        else
            // return whatever _Op returns for equal values
            return _Op{}(0, 0);
    }
};

template <class... _Types>
constexpr bool operator==(const std::variant<_Types...> &_Left, const std::variant<_Types...> &_Right) noexcept(
    std::conjunction_v<std::is_nothrow_invocable_r<bool, std::equal_to<>, const _Types &, const _Types &>...>) /* strengthened */
{
    // determine if the arguments are both valueless or contain equal values
    using _Visitor = PM::_Variant_relop_visitor2<std::equal_to<>, bool, _Types...>;
    const size_t _Right_index = _Right.index();
    return _Left.index() == _Right_index && PM::_Variant_raw_visit(_Right_index, _Right._Storage(), _Visitor{_Left._Storage()});
}
} // namespace PM
#endif

using monostate_int_variant = std::variant<std::monostate, int>;

template <typename T>
struct Comparator
{
    static bool equal(T const &v, T const &w)
    {
        switch (v.index())
        {
        case 0:
            return std::get<0>(v) == std::get<0>(w);
        case 1:
            return std::get<1>(v) == std::get<1>(w);
        case 2:
            return std::get<2>(v) == std::get<2>(w);
        case 3:
            return std::get<3>(v) == std::get<3>(w);
        case 4:
            return std::get<4>(v) == std::get<4>(w);
        case 5:
            return std::get<5>(v) == std::get<5>(w);
        case 6:
            return std::get<6>(v) == std::get<6>(w);
        case 7:
            return std::get<7>(v) == std::get<7>(w);
        case 8:
            return std::get<8>(v) == std::get<8>(w);
        case 9:
            return std::get<9>(v) == std::get<9>(w);
        case 10:
            return std::get<10>(v) == std::get<10>(w);
        case 11:
            return std::get<11>(v) == std::get<11>(w);
        case 12:
            return std::get<12>(v) == std::get<12>(w);
        case 13:
            return std::get<13>(v) == std::get<13>(w);
        case 14:
            return std::get<14>(v) == std::get<14>(w);
        case 15:
            return std::get<15>(v) == std::get<15>(w);

        default:
            return false;
        }
    }
};

namespace PM
{
struct A
{
};

constexpr bool operator==(A, A)
{
    return true;
}

constexpr bool operator!=(A, A)
{
    return false;
}
} // namespace PM

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

    // // 15. monostate
    std::variant<std::monostate, int> v7;
    if (!std::holds_alternative<std::monostate>(v7))
        return false;
    if (!(v7 == std::variant<std::monostate, int>(std::monostate{})))
        return false;

    std::variant<PM::A, int> v7_;
    if (!std::holds_alternative<PM::A>(v7_))
        return false;
    if (!(v7_ == std::variant<PM::A, int>(PM::A{})))
        return false;

    // nonstd::detail::Comparator<monostate_int_variant>::equal(v7, monostate_int_variant(std::monostate{}));
    // Comparator<monostate_int_variant>::equal(v7, monostate_int_variant(std::monostate{}));

    std::monostate a, b;
    if (!(a == b))
        return false;
    if (a != b)
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
