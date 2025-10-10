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

//
// WORKAROUND for the 4.8 bug with non-existing std::to_string() implementation
//
#include "mingw_4.8_std_to_string.h"
