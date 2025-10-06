set(TEST_DEPENDENCIES
    StdCompat::optional
)

std_compat_add_test(tst_optional
    ${TEST_DEPENDENCIES}
    tst_optional.cpp
)
