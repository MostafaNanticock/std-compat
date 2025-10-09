set(TEST_DEPENDENCIES
    StdCompat::variant
)

std_compat_add_test(tst_variant
    ${TEST_DEPENDENCIES}
    tst_variant.cpp
)
