cmake_minimum_required(VERSION 3.16)

project(StdCompat LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(std-compatAPI)

# Create a header-only interface library
add_library(StdCompat INTERFACE)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
