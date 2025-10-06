#ifndef PM_STD_COMPAT_LAYER_MONOSTATE
#define PM_STD_COMPAT_LAYER_MONOSTATE

#if defined(_MSC_VER) && defined(_MSVC_LANG)
#    define _PM_LANG_VER _MSVC_LANG
#    include <std-compat/internal/msvc_crt_version.h>
#    include <xutility>
#else
#    define _PM_LANG_VER __cplusplus
#endif

namespace PM
{
namespace internal
{
    struct monostate
#if defined(_MSC_VER) && _PM_LANG_VER >= 201703L && PM_UCRT_VER >= PM_UCRT_VER_VS2017_15_0
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
#if defined(_MSC_VER) && _PM_LANG_VER >= 201703L && PM_UCRT_VER >= PM_UCRT_VER_VS2017_15_0
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
