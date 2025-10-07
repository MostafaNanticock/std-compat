cmake_minimum_required(VERSION 3.16)

project(StdCompat LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(StdCompatAPI)

# Check and display UCRT version during configuration
message(STATUS "Checking UCRT version...")
try_run(UCRT_CHECK_RUN_RESULT UCRT_CHECK_COMPILE_RESULT
    ${CMAKE_CURRENT_BINARY_DIR}/ucrt_check
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_ucrt_version/main.cpp
    COMPILE_OUTPUT_VARIABLE UCRT_CHECK_COMPILE_OUTPUT
    RUN_OUTPUT_VARIABLE UCRT_VERSION_OUTPUT
)

if(UCRT_CHECK_COMPILE_RESULT AND UCRT_CHECK_RUN_RESULT EQUAL 0)
    message(STATUS "UCRT Version: ${UCRT_VERSION_OUTPUT}")
else()
    message(WARNING "Failed to determine UCRT version")
    if(NOT UCRT_CHECK_COMPILE_RESULT)
        message(STATUS "Compile error: ${UCRT_CHECK_COMPILE_OUTPUT}")
    endif()
endif()

# Create a header-only interface library
add_library(StdCompat INTERFACE)

add_subdirectory(tools)
add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
