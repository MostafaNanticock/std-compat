set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_span INTERFACE)

target_sources(StdCompat_span
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/span
    ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/span.hpp
)

target_link_libraries(StdCompat_span
INTERFACE
    StdCompat_common
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompat_span
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)

target_compile_definitions(StdCompat_span
    INTERFACE
        span_CONFIG_SELECT_SPAN=1
)
