include(StdCompatAPIInternal)

_stdc_detect_cxx_standards()
_stdc_check_crt_version()

# Usage:
#   stdc_add_module(TARGET_NAME
#       <SOURCES...>
#       <DEPENDS...>
#       <INCLUDE_DIRS...>
#       <COMPILE_DEFINITIONS...>
#   )
function(stdc_add_module TARGET_NAME)
    cmake_parse_arguments(STDCOMPAT
        "DISABLE_BY_DEFAULT"
        ""
        "INCLUDE_DIRS;SOURCES;DEPENDS;COMPILE_DEFINITIONS"
        ${ARGN})

    # Create the interface library
    add_library(${TARGET_NAME} INTERFACE)
    add_library(StdCompat::${TARGET_NAME} ALIAS ${TARGET_NAME})

    # Sources
    if(STDCOMPAT_SOURCES)
        target_sources(${TARGET_NAME}
            INTERFACE
                ${STDCOMPAT_SOURCES}
        )
    endif()

    # Dependencies
    if(STDCOMPAT_DEPENDS)
        target_link_libraries(${TARGET_NAME}
            INTERFACE
                ${STDCOMPAT_DEPENDS}
        )
    endif()

    # Include directories
    set(STDC_DEFAULT_INCLUDE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/include
    )
    target_include_directories(${TARGET_NAME}
        INTERFACE
            $<BUILD_INTERFACE:${STDC_DEFAULT_INCLUDE_DIRS}>
    )

    if(STDCOMPAT_INCLUDE_DIRS)
        target_include_directories(${TARGET_NAME}
            INTERFACE
                $<BUILD_INTERFACE:${STDCOMPAT_INCLUDE_DIRS}>
        )
    endif()

    # Add supported C++ standard definitions
    _pm_add_supported_cxx_standards_definitions(${TARGET_NAME})

    # Compile definitions
    if(STDCOMPAT_COMPILE_DEFINITIONS)
        target_compile_definitions(${TARGET_NAME}
            INTERFACE
                ${STDCOMPAT_COMPILE_DEFINITIONS}
        )
    endif()
endfunction()

# Usage:
#   stdc_add_test(
#       <BASE_NAME>
#       <DEPENDS>
#       <Sources...>
#   )
#
# Example:
#   set(TEST_DEPENDS MyLib Qt6::Test)
#   stdc_add_test(tst_any "${TEST_DEPENDS}" tst_any.cpp)
#
# This will generate executables/tests:
#   tst_any_cxx11, tst_any_cxx14, tst_any_cxx17, ...
#
macro(stdc_add_test BASE_NAME DEPENDS)
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
