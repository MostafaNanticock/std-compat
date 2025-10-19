set(TEST_DEPENDENCIES
    StdCompat::filesystem
)

stdc_add_test(tst_filesystem
    ${TEST_DEPENDENCIES}
    tst_filesystem.cpp
)
