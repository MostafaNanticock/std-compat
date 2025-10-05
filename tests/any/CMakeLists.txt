add_executable(tst_any
    tst_any.cpp
)
target_link_libraries(tst_any
    PRIVATE
    StdCompatibilityLayer
)

add_test(
    NAME tst_any
    COMMAND tst_any
)
