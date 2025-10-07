#ifndef PM_STD_COMPAT_LAYER_MONOSTATE
#define PM_STD_COMPAT_LAYER_MONOSTATE

#if defined(_MSC_VER) && defined(_MSVC_LANG)
#    define _PM_LANG_VER _MSVC_LANG
#    include <xutility>
#    if _PM_LANG_VER >= 201703L && _MSC_VER >= 1910  // VS2017 15.0+
#        include <variant>
#    endif
#else
#    define _PM_LANG_VER __cplusplus
#endif

namespace PM
{
namespace internal
{
    struct monostate
#if defined(_MSC_VER) && _PM_LANG_VER >= 201703L && _MSC_VER >= 1910  // VS2017 15.0+
        : public std::monostate
#endif
    {
        friend constexpr bool operator==(monostate, monostate) noexcept
        {
            return true;
        }
        friend constexpr bool operator!=(monostate, monostate) noexcept
        {
            return false;
        }
        friend constexpr bool operator<(monostate, monostate) noexcept
        {
            return false;
        }
        friend constexpr bool operator>(monostate, monostate) noexcept
        {
            return false;
        }
        friend constexpr bool operator<=(monostate, monostate) noexcept
        {
            return true;
        }
        friend constexpr bool operator>=(monostate, monostate) noexcept
        {
            return true;
        }
    };

} // namespace internal
} // namespace PM

// Just a work-around for MSVC when using std >= C++17
#if defined(_MSC_VER) && _PM_LANG_VER >= 201703L && _MSC_VER >= 1910  // VS2017 15.0+
namespace std
{
inline constexpr bool operator==(monostate, monostate) noexcept
{
    return true;
}

inline constexpr bool operator!=(monostate, monostate) noexcept
{
    return false;
}
} // namespace std
#endif

#endif // PM_STD_COMPAT_LAYER_MONOSTATE
