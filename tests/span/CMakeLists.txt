set(TEST_DEPENDENCIES
    StdCompat::span
)

std_compat_add_test(tst_span
    ${TEST_DEPENDENCIES}
    tst_span.cpp
)
