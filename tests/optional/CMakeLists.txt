set(TEST_DEPENDENCIES
    StdCompat_optional
)

pm_skip_if_targets_dont_exist(${TEST_DEPENDENCIES})

add_executable(tst_optional
    tst_optional.cpp
)
target_link_libraries(tst_optional
    PRIVATE
        ${TEST_DEPENDENCIES}
)

add_test(
    NAME tst_optional
    COMMAND tst_optional
)
