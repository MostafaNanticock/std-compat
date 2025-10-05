add_executable(tst_optional
    tst_optional.cpp
)
target_link_libraries(tst_optional
    PRIVATE
    StdCompatibilityLayer
)

add_test(
    NAME tst_optional
    COMMAND tst_optional
)
