set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_optional INTERFACE)
add_library(StdCompat::optional ALIAS StdCompat_optional)

target_sources(StdCompat_optional
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/optional
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/optional.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/optional-fun.hpp
)

target_link_libraries(StdCompat_optional
INTERFACE
    StdCompat_common
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompat_optional
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)

target_compile_definitions(StdCompat_optional
    INTERFACE
        optional_CONFIG_SELECT_OPTIONAL=1
)
