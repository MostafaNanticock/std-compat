#pragma once

#include <sstream>

#ifdef __MINGW32_MAJOR_VERSION // Classic MinGW CRT (32-bit) is always affected
#    define _PM_MINGW_IMPLEMENT_TO_STRING_WORKAROUND 1
#else // Workaround needed for MinGW-w64 < 3.11
#    if (PM_CRT_VERSION_MAJOR < 3) || (PM_CRT_VERSION_MAJOR == 3 && PM_CRT_VERSION_MINOR < 11)
#        define _PM_MINGW_IMPLEMENT_TO_STRING_WORKAROUND 1
#    endif
#endif

#ifdef _PM_MINGW_IMPLEMENT_TO_STRING_WORKAROUND
namespace std
{
template <typename T>
std::string to_string(T value)
{
    std::ostringstream oss;
    oss << value;

    return oss.str();
}
} // namespace std
#endif
