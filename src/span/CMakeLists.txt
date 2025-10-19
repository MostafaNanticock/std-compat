stdc_add_module(span
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/span
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/span.hpp

    DEPENDS
        StdCompat::common

    COMPILE_DEFINITIONS
        span_CONFIG_SELECT_SPAN=1
)
