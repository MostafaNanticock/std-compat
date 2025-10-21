stdc_add_module(expected
    DISABLE_BY_DEFAULT  # WIP

    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/expected
        ${CMAKE_CURRENT_SOURCE_DIR}/include/expected_compatibility
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/expected.hpp

    DEPENDS
        StdCompat::common

    COMPILE_DEFINITIONS
        nsel_CONFIG_SELECT_EXPECTED=1
)
