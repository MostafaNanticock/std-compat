set(TEST_DEPENDENCIES
    StdCompat::optional
)

stdc_add_test(tst_optional
    ${TEST_DEPENDENCIES}
    tst_optional.cpp
)
