add_executable(tst_span
    tst_span.cpp
)
target_link_libraries(tst_span
    PRIVATE
    StdCompatibilityLayer
)

add_test(
    NAME tst_span
    COMMAND tst_span
)
