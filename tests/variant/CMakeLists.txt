add_executable(tst_variant
    tst_variant.cpp
)
target_link_libraries(tst_variant
    PRIVATE
    StdCompatibilityLayer
)

add_test(
    NAME tst_variant
    COMMAND tst_variant
)
