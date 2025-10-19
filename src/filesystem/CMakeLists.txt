std_compat_add_module(filesystem
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/filesystem
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/filesystem.hpp

    DEPENDS
        StdCompat::common

    COMPILE_DEFINITIONS
        filesystem_CONFIG_SELECT_FILESYSTEM=1
)
