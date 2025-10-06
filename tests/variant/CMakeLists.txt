add_executable(tst_variant
    tst_variant.cpp
)
target_link_libraries(tst_variant
    PRIVATE
    StdCompat_variant
)

add_test(
    NAME tst_variant
    COMMAND tst_variant
)
