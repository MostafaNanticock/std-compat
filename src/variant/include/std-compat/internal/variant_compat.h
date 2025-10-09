#pragma once

#include <std-compat/internal/detect_compiler.h>

#ifdef PM_CC_MSVC
#    include "variant_compat_msvc.h"
#endif

#if PM_HAS_STD_BAD_VARIANT_ACCESS_OUTSIDE_VARIANT_HEADER
#    include <exception>
#else
namespace std
{
class bad_variant_access : public exception
{
public:
    bad_variant_access() noexcept = default;

    const char *what() const noexcept override
    {
        return "bad variant access";
    }
};
} // namespace std
#endif

#if PM_HAS_STD_MONOSTATE_OUTSIDE_VARIANT_HEADER
#    include <xutility>
#else
namespace std
{
struct monostate
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
} // namespace std
#endif
