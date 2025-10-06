set(TEST_DEPENDENCIES
    StdCompat_expected
)

pm_skip_if_targets_dont_exist(${TEST_DEPENDENCIES})

add_executable(tst_expected
    tst_expected.cpp
)
target_link_libraries(tst_expected
    PRIVATE
        ${TEST_DEPENDENCIES}
)

add_test(
    NAME tst_expected
    COMMAND tst_expected
)
