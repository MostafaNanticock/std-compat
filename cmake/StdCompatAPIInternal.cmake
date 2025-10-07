# Detect which C++ standard values are supported by the current compiler.
# On import, it sets PM_AVAILABLE_CXX_STANDARDS in the including scope.
#
function(_pm_detect_cxx_standards)
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
#   _pm_check_ucrt_version()
#
# Detects and displays the UCRT version during configuration.
# Only runs on MSVC/Windows platforms where UCRT is relevant.
#
function(_pm_check_ucrt_version)
    # Only check UCRT version on MSVC/Windows
    if(NOT MSVC)
        return()
    endif()

    # Avoid running the check multiple times
    if(DEFINED PM_UCRT_VERSION_CHECKED)
        return()
    endif()
    set(PM_UCRT_VERSION_CHECKED TRUE CACHE INTERNAL "UCRT version has been checked")

    message(STATUS "Checking UCRT version...")
    
    # Try to compile and run the UCRT version checker
    try_run(UCRT_CHECK_RUN_RESULT UCRT_CHECK_COMPILE_RESULT
        ${CMAKE_CURRENT_BINARY_DIR}/ucrt_check
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_ucrt_version/main.cpp
        COMPILE_OUTPUT_VARIABLE UCRT_CHECK_COMPILE_OUTPUT
        RUN_OUTPUT_VARIABLE UCRT_VERSION_OUTPUT
    )

    if(UCRT_CHECK_COMPILE_RESULT AND UCRT_CHECK_RUN_RESULT EQUAL 0)
        string(STRIP "${UCRT_VERSION_OUTPUT}" UCRT_VERSION_OUTPUT)
        message(STATUS "UCRT Version: ${UCRT_VERSION_OUTPUT}")
        set(PM_UCRT_VERSION "${UCRT_VERSION_OUTPUT}" CACHE STRING "Detected UCRT version")
    else()
        message(WARNING "Failed to determine UCRT version")
        if(NOT UCRT_CHECK_COMPILE_RESULT)
            message(STATUS "Compile error: ${UCRT_CHECK_COMPILE_OUTPUT}")
        endif()
        set(PM_UCRT_VERSION "unknown" CACHE STRING "Detected UCRT version")
    endif()
endfunction()

