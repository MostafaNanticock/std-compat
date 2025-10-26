#pragma once

#include <cstring>
#include <string>

#ifndef STD_STRING_VIEW
#    if __cplusplus >= 201703L
#        define STD_STRING_VIEW 1
#    endif
#endif

#ifdef STD_STRING_VIEW
#    include <string_view>
#endif

namespace stdc
{
namespace tests
{
// char8_t is only a distinct type since C++20, but we can alias to unsigned char
#if defined(__cpp_char8_t)
    using u8string = std::u8string;

    // Accept both char8_t* and char* sources
    inline u8string make_u8(const char8_t *s)
    {
        return u8string(s);
    }

    inline u8string make_u8(const char *s)
    {
        // reinterpret the byte sequence as char8_t and copy with length
        return u8string(reinterpret_cast<const char8_t *>(s), reinterpret_cast<const char8_t *>(s) + std::strlen(s));
    }
#else
    using u8string = std::basic_string<unsigned char>;

    inline u8string make_u8(const char *s)
    {
        return u8string(reinterpret_cast<const unsigned char *>(s), std::strlen(s));
    }
#endif

#ifdef STD_STRING_VIEW
    using string_view = std::string_view;
#endif

} // namespace tests
} // namespace stdc
