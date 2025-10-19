stdc_add_module(optional
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/optional
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/optional.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/no_functional_patch.h

    DEPENDS
        StdCompat::common
)
