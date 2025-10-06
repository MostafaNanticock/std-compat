set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(StdCompat_common INTERFACE)

target_sources(StdCompat_common
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/msvc_crt_version.h
)

target_include_directories(StdCompat_common
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
)
