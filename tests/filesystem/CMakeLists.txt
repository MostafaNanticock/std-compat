set(TEST_DEPENDENCIES
    StdCompat_filesystem
)

pm_skip_if_targets_dont_exist(${TEST_DEPENDENCIES})

add_executable(tst_filesystem
    tst_filesystem.cpp
)
target_link_libraries(tst_filesystem
    PRIVATE
        ${TEST_DEPENDENCIES}
)

add_test(
    NAME tst_filesystem
    COMMAND tst_filesystem
)
