include(StdCompatAPIInternal)

_pm_detect_cxx_standards()

# Usage:
#   std_compat_add_test(
#       <BASE_NAME>
#       <DEPENDS>
#       <Sources...>
#   )
#
# Example:
#   set(TEST_DEPENDS MyLib Qt6::Test)
#   std_compat_add_test(tst_any "${TEST_DEPENDS}" tst_any.cpp)
#
# This will generate executables/tests:
#   tst_any_cxx11, tst_any_cxx14, tst_any_cxx17, ...
#
macro(std_compat_add_test BASE_NAME DEPENDS)
    set(_deps "${DEPENDS}")
    set(_sources ${ARGN})

    pm_skip_if_targets_dont_exist(${_deps})

    foreach(_std IN LISTS PM_AVAILABLE_CXX_STANDARDS)
        set(_tgt "${BASE_NAME}_cxx${_std}")

        add_executable(${_tgt} ${_sources})
        target_link_libraries(${_tgt}
            PRIVATE
                ${_deps}
        )
        set_target_properties(${_tgt} PROPERTIES
            CXX_STANDARD ${_std}
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
        )

        add_test(
            NAME ${_tgt}
            COMMAND ${_tgt}
        )
    endforeach()
endmacro()
