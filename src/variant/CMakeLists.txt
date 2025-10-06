set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_variant INTERFACE)
add_library(StdCompat::variant ALIAS StdCompat_variant)

target_sources(StdCompat_variant
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/variant
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/variant.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/monostate_compat.h
)

target_link_libraries(StdCompat_variant
INTERFACE
    StdCompat_common
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompat_variant
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)

target_compile_definitions(StdCompat_variant
    INTERFACE
        variant_CONFIG_SELECT_VARIANT=1
)
