#pragma once

// Helpers to stringify __LINE__
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

// Build "file(line): " prefix
#define LOCATION __FILE__ "(" STRINGIZE(__LINE__) ") : "

#if defined(_MSC_VER)
// MSVC: use __pragma(message(...))
#    define WARN(msg) __pragma(message(LOCATION msg))
#elif defined(__GNUC__) || defined(__clang__)
// GCC/Clang: use _Pragma with GCC warning
#    define DO_PRAGMA(x) _Pragma(#x)
#    define WARN(msg) DO_PRAGMA(GCC warning LOCATION msg)
#else
#    define WARN(msg)
#endif

// Example usage
WARN("Hi there")

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
