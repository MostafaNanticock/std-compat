std_compat_add_module(common
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/crt_patches.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_patches/patches.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_patches/patches_mingw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_patches/mingw_4.8_std_to_string.h

        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/detect_compiler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/compiler_clang.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/compiler_gcc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/compiler_msvc.h

        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/detect_crt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_apple.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_bionic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_libcxx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_libstdcxx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_mingw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_msvc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_musl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/crt_newlib.h
)
