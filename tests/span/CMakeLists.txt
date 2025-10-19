set(TEST_DEPENDENCIES
    StdCompat::span
)

stdc_add_test(tst_span
    ${TEST_DEPENDENCIES}
    tst_span.cpp
)
