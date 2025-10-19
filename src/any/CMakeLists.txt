std_compat_add_module(any
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/any
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/any.hpp

    DEPENDS
        StdCompat::common

    COMPILE_DEFINITIONS
        any_CONFIG_SELECT_ANY=1
)
