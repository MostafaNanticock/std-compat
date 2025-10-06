set(TEST_DEPENDENCIES
    StdCompat_variant
)

pm_skip_if_targets_dont_exist(${TEST_DEPENDENCIES})

add_executable(tst_variant
    tst_variant.cpp
)
target_link_libraries(tst_variant
    PRIVATE
        ${TEST_DEPENDENCIES}
)

add_test(
    NAME tst_variant
    COMMAND tst_variant
)
