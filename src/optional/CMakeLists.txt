std_compat_add_module(optional
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/optional
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/optional.hpp

    DEPENDS
        StdCompat::common
)
