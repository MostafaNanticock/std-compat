set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_filesystem INTERFACE)

target_sources(StdCompat_filesystem
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/filesystem
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/filesystem.hpp
)

target_link_libraries(StdCompat_filesystem
INTERFACE
    StdCompat_common
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompat_filesystem
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)

target_compile_definitions(StdCompat_filesystem
    INTERFACE
        filesystem_CONFIG_SELECT_FILESYSTEM=1
)
