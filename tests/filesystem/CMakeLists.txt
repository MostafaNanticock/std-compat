add_executable(tst_filesystem
    tst_filesystem.cpp
)
target_link_libraries(tst_filesystem
    PRIVATE
    StdCompatibilityLayer
)

add_test(
    NAME tst_filesystem
    COMMAND tst_filesystem
)
