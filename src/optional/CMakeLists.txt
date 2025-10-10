std_compat_add_module(optional
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/optional
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/optional.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/optional-fun.hpp

    DEPENDS
        StdCompat::common

    COMPILE_DEFINITIONS
        optional_CONFIG_SELECT_OPTIONAL=1
)
