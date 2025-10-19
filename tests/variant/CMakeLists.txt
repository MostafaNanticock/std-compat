set(TEST_DEPENDENCIES
    StdCompat::variant
)

stdc_add_test(tst_variant
    ${TEST_DEPENDENCIES}
    tst_variant.cpp
)
