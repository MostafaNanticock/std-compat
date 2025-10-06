set(TEST_DEPENDENCIES
    StdCompat_any
)

pm_skip_if_targets_dont_exist(${TEST_DEPENDENCIES})

add_executable(tst_any
    tst_any.cpp
)
target_link_libraries(tst_any
    PRIVATE
        ${TEST_DEPENDENCIES}
)

add_test(
    NAME tst_any
    COMMAND tst_any
)
