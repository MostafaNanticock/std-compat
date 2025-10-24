cmake_minimum_required(VERSION 3.16)

project(StdCompat LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(StdCompatAPI)

# Create a header-only interface library
add_library(StdCompat INTERFACE)
add_subdirectory(src)

option(STDC_BUILD_TOOLS "Build the std-compat tools" ON)

if(STDC_BUILD_TOOLS)
    add_subdirectory(tools)
endif()

option(STDC_BUILD_TESTS "Build the std-compat tests" ON)

if(STDC_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
