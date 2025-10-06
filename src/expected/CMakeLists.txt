set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_expected INTERFACE)

target_sources(StdCompat_expected
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/expected
    ${CMAKE_CURRENT_SOURCE_DIR}/include/expected_compatibility
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/expected.hpp
)

target_link_libraries(StdCompat_expected
INTERFACE
    StdCompat_common
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompat_expected
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)

target_compile_definitions(StdCompat_expected
    INTERFACE
        nsel_CONFIG_SELECT_EXPECTED=1
)
