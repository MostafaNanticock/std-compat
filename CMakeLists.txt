cmake_minimum_required(VERSION 3.21)

project(StdCompatibilityLayer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Windows SDK version: $ENV{WindowsSDKVersion}")

# Create a header-only interface library
add_library(StdCompatibilityLayer INTERFACE)

# List of directories containing your custom std headers
set(STD_COMPAT_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/any
    ${CMAKE_CURRENT_SOURCE_DIR}/expected
    ${CMAKE_CURRENT_SOURCE_DIR}/filesystem
    ${CMAKE_CURRENT_SOURCE_DIR}/optional
    ${CMAKE_CURRENT_SOURCE_DIR}/span
    ${CMAKE_CURRENT_SOURCE_DIR}/variant
)

target_sources(StdCompatibilityLayer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/any/any
        ${CMAKE_CURRENT_SOURCE_DIR}/any/any.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/expected/expected
        ${CMAKE_CURRENT_SOURCE_DIR}/expected/expected.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/expected/expected_compatibility
        ${CMAKE_CURRENT_SOURCE_DIR}/filesystem/filesystem
        ${CMAKE_CURRENT_SOURCE_DIR}/filesystem/filesystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/optional/optional
        ${CMAKE_CURRENT_SOURCE_DIR}/optional/optional.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/span/span
        ${CMAKE_CURRENT_SOURCE_DIR}/span/span.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/variant/variant
        ${CMAKE_CURRENT_SOURCE_DIR}/variant/variant.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/variant/monostate_compat.h
)

# Add include directories to consumers, BEFORE system includes
target_include_directories(StdCompatibilityLayer
    INTERFACE
        $<BUILD_INTERFACE:${STD_COMPAT_INCLUDE_DIRS}>
)

# Ensure these directories are searched first
# The BEFORE keyword ensures they precede default CRT include paths
set_property(TARGET StdCompatibilityLayer PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES
    "$<BUILD_INTERFACE:${STD_COMPAT_INCLUDE_DIRS}>"
)

target_compile_definitions(StdCompatibilityLayer
    INTERFACE
        optional_CONFIG_SELECT_OPTIONAL=1
        any_CONFIG_SELECT_ANY=1
        nsel_CONFIG_SELECT_EXPECTED=1
        variant_CONFIG_SELECT_VARIANT=1
)

# Optionally, mark as system includes to suppress warnings from shim headers
# target_include_directories(StdCompatibilityLayer
#     INTERFACE
#         $<BUILD_INTERFACE:${STD_COMPAT_INCLUDE_DIRS}>
#         SYSTEM
# )

add_executable(tst_StdCompatibilityLayer
    tests/tst_StdCompatibilityLayer.cpp
)
target_link_libraries(tst_StdCompatibilityLayer
PRIVATE
    StdCompatibilityLayer
)
