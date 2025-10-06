set(TEST_DEPENDENCIES
    StdCompat::expected
)

std_compat_add_test(tst_expected
    ${TEST_DEPENDENCIES}
    tst_expected.cpp
)
