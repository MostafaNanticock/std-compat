set(TEST_DEPENDENCIES
    StdCompat::filesystem
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(error_handling)
add_subdirectory(iteration)
add_subdirectory(operations)
add_subdirectory(path)
add_subdirectory(status)
