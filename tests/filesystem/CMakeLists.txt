set(TEST_DEPENDENCIES
    StdCompat::filesystem
)

std_compat_add_test(tst_filesystem
    ${TEST_DEPENDENCIES}
    tst_filesystem.cpp
)
