set(TEST_DEPENDENCIES
    StdCompat::variant
    # StdCompat_common
)

std_compat_add_test(tst_variant
    ${TEST_DEPENDENCIES}
    tst_variant.cpp
)

# add_executable(tst_variant tst_variant.cpp)
# target_link_libraries(tst_variant
#     PRIVATE
#         ${TEST_DEPENDENCIES}
# )
# set_target_properties(tst_variant PROPERTIES
#     CXX_STANDARD 17
#     CXX_STANDARD_REQUIRED YES
#     CXX_EXTENSIONS NO
# )

# add_test(
#     NAME tst_variant
#     COMMAND tst_variant
# )
