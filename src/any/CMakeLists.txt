set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_any INTERFACE)
add_library(StdCompat::any ALIAS StdCompat_any)

target_sources(StdCompat_any
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/any
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/any.hpp
)

target_link_libraries(StdCompat_any
INTERFACE
    StdCompat_common
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompat_any
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)

target_compile_definitions(StdCompat_any
    INTERFACE
        any_CONFIG_SELECT_ANY=1
)
