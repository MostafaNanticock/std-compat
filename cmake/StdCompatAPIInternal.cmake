# Detect which C++ standard values are supported by the current compiler.
# On import, it sets PM_AVAILABLE_CXX_STANDARDS in the including scope.
#
function(_pm_detect_cxx_standards)
    include(CheckCXXCompilerFlag)

    set(_standards 11 14 17 20 23 26)
    set(_available "")

    foreach(std IN LISTS _standards)
        # Try the canonical flag for this standard
        check_cxx_compiler_flag("-std=c++${std}" HAS_CXX${std})
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
