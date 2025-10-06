add_executable(tst_expected
    tst_expected.cpp
)
target_link_libraries(tst_expected
    PRIVATE
    StdCompat_expected
)

add_test(
    NAME tst_expected
    COMMAND tst_expected
)
