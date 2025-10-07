# message(STATUS "Supported C++ compile features:")
# foreach(feature IN LISTS CMAKE_CXX_COMPILE_FEATURES)
#     message(STATUS "  ${feature}")
# endforeach()

set(TEST_DEPENDENCIES
    StdCompat::variant
)

std_compat_add_test(tst_variant
    ${TEST_DEPENDENCIES}
    tst_variant.cpp
)
