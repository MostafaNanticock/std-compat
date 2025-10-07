#pragma once

#if defined(_MSC_VER)
    #include "crt_msvc.h"
#elif defined(__clang__) && defined(__APPLE__)
    #include "crt_apple.h"
#elif defined(__clang__) && defined(__ANDROID__)
    #include "crt_bionic.h"
#elif defined(__clang__)
    #include "crt_libcxx.h"
#elif defined(__GNUC__) && defined(__MINGW32__)
    #include "crt_mingw.h"
#elif defined(__GNUC__) && defined(__NEWLIB__)
    #include "crt_newlib.h"
#elif defined(__GNUC__) && defined(__MUSL__)
    #include "crt_musl.h"
#elif defined(__GNUC__)
    #include "crt_libstdcxx.h"
#else
    #error "Unsupported compiler or CRT"
#endif
