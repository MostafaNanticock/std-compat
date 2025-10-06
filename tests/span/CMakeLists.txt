set(TEST_DEPENDENCIES
    StdCompat_span
)

pm_skip_if_targets_dont_exist(${TEST_DEPENDENCIES})

add_executable(tst_span
    tst_span.cpp
)
target_link_libraries(tst_span
    PRIVATE
        ${TEST_DEPENDENCIES}
)

add_test(
    NAME tst_span
    COMMAND tst_span
)
