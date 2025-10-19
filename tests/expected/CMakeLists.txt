set(TEST_DEPENDENCIES
    StdCompat::expected
)

stdc_add_test(tst_expected
    ${TEST_DEPENDENCIES}
    tst_expected.cpp
)
