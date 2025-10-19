# Detect which C++ standard values are supported by the current compiler.
# On import, it sets PM_AVAILABLE_CXX_STANDARDS in the including scope.
#
function(_stdc_detect_cxx_standards)
    include(CheckCXXCompilerFlag)

    set(_standards 11 14 17 20 23 26)
    set(_available "")

    foreach(std IN LISTS _standards)
        # Try the appropriate flag for this standard based on compiler
        if(MSVC)
            # MSVC uses /std:c++XX format, but only supports 14, 17, 20, 23
            if(std GREATER_EQUAL 14)
                check_cxx_compiler_flag("/std:c++${std}" HAS_CXX${std})
            else()
                # MSVC doesn't have a specific flag for C++11, it's the default
                set(HAS_CXX${std} TRUE)
            endif()
        else()
            # GCC/Clang use -std=c++XX format
            check_cxx_compiler_flag("-std=c++${std}" HAS_CXX${std})
        endif()
        
        if(HAS_CXX${std})
            list(APPEND _available ${std})
        endif()
    endforeach()

    set(PM_AVAILABLE_CXX_STANDARDS "${_available}" PARENT_SCOPE)
endfunction()

# Usage:
#   _pm_target_exists(<target_name> <result_var>)
#
function(_pm_target_exists target_name result_var)
    if(TARGET "${target_name}")
        set(${result_var} TRUE PARENT_SCOPE)
    else()
        set(${result_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

# Usage:
#   _pm_targets_exist(<result_var> <target1> [<target2> ...])
#
function(_pm_targets_exist result_var)
    set(_all_exist TRUE)
    foreach(_tgt IN LISTS ARGN)
        _pm_target_exists("${_tgt}" _exists)
        if(NOT _exists)
            set(_all_exist FALSE)
        endif()
    endforeach()
    set(${result_var} ${_all_exist} PARENT_SCOPE)
endfunction()

# Usage:
#   pm_skip_if_targets_dont_exist(<target1> [<target2> ...])
#
macro(pm_skip_if_targets_dont_exist)
    _pm_targets_exist(_all_exist ${ARGV})
    if(NOT _all_exist)
        # just stop this file.
        return()
    endif()
endmacro()

# Usage:
#   _pm_add_supported_cxx_standards_definitions(<Target>)
#
macro(_pm_add_supported_cxx_standards_definitions target)
    foreach(_std IN LISTS PM_AVAILABLE_CXX_STANDARDS)
        target_compile_definitions(${target}
            INTERFACE
                _PM_CC_SUPPORTS_CXX${_std}
        )
    endforeach()
endmacro()

# Usage:
#   _stdc_check_crt_version()
#
# Detects and displays the CRT version during configuration.
#
# FIXME: We should find a better way that doesn't include running the compiled binary,
#        as this wouldn't work in cross-compilation scenarios.
#
function(_stdc_check_crt_version)
    if(DEFINED STDC_CRT_VERSION_CHECKED)
        return()
    endif()
    set(STDC_CRT_VERSION_CHECKED TRUE CACHE INTERNAL "CRT version has been checked")

    message(STATUS "Checking CRT version...")

    try_run(CRT_CHECK_RUN_RESULT CRT_CHECK_COMPILE_RESULT
        ${CMAKE_CURRENT_BINARY_DIR}/crt_version_check
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/crt_version_check/crt_version_check.cpp
        COMPILE_OUTPUT_VARIABLE CRT_CHECK_COMPILE_OUTPUT
        RUN_OUTPUT_VARIABLE CRT_VERSION_OUTPUT
    )

    if(CRT_CHECK_COMPILE_RESULT AND CRT_CHECK_RUN_RESULT EQUAL 0)
        string(REPLACE "\n" ";" CRT_VERSION_LINES "${CRT_VERSION_OUTPUT}")

        foreach(line IN LISTS CRT_VERSION_LINES)
            if(line MATCHES "^STDC_CRT_NAME=(.*)")
                string(STRIP "${CMAKE_MATCH_1}" _raw_crt_name)
                string(REGEX REPLACE "\n" "" _clean_crt_name "${_raw_crt_name}")
                set(STDC_CRT_NAME "${_clean_crt_name}" CACHE STRING "Detected CRT name")
            elseif(line MATCHES "^STDC_CRT_VERSION_STRING=(.*)")
                string(STRIP "${CMAKE_MATCH_1}" _version_string)
                set(STDC_CRT_VERSION_STRING "${_version_string}" CACHE STRING "Full CRT version string")
            elseif(line MATCHES "^STDC_CRT_VERSION_MAJOR=(.*)")
                set(STDC_CRT_VERSION_MAJOR "${CMAKE_MATCH_1}" CACHE STRING "CRT major version")
            elseif(line MATCHES "^STDC_CRT_VERSION_MINOR=(.*)")
                set(STDC_CRT_VERSION_MINOR "${CMAKE_MATCH_1}" CACHE STRING "CRT minor version")
            elseif(line MATCHES "^STDC_CRT_VERSION_BUILD=(.*)")
                set(STDC_CRT_VERSION_BUILD "${CMAKE_MATCH_1}" CACHE STRING "CRT build version")
            elseif(line MATCHES "^STDC_CRT_VERSION_REVISION=(.*)")
                set(STDC_CRT_VERSION_REVISION "${CMAKE_MATCH_1}" CACHE STRING "CRT revision version")
            endif()
        endforeach()

        message(STATUS "CRT Name    : ${STDC_CRT_NAME}")
        message(STATUS "CRT Version : ${STDC_CRT_VERSION_STRING}")
    else()
        message(WARNING "Failed to determine CRT version")
        if(NOT CRT_CHECK_COMPILE_RESULT)
            message(STATUS "Compile error:\n${CRT_CHECK_COMPILE_OUTPUT}")
        endif()
        set(STDC_CRT_NAME "unknown" CACHE STRING "Detected CRT name")
        set(STDC_CRT_VERSION_STRING "0.0.0.0" CACHE STRING "Full CRT version string")
        set(STDC_CRT_VERSION_MAJOR 0 CACHE STRING "CRT major version")
        set(STDC_CRT_VERSION_MINOR 0 CACHE STRING "CRT minor version")
        set(STDC_CRT_VERSION_BUILD 0 CACHE STRING "CRT build version")
        set(STDC_CRT_VERSION_REVISION 0 CACHE STRING "CRT revision version")
    endif()
endfunction()
