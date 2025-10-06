# Usage:
#   pm_target_exists(<target_name> <result_var>)
#
function(pm_target_exists target_name result_var)
    if(TARGET "${target_name}")
        set(${result_var} TRUE PARENT_SCOPE)
    else()
        set(${result_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

# Usage:
#   pm_targets_exist(<result_var> <target1> [<target2> ...])
#
function(pm_targets_exist result_var)
    set(_all_exist TRUE)
    foreach(_tgt IN LISTS ARGN)
        pm_target_exists("${_tgt}" _exists)
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
    pm_targets_exist(_all_exist ${ARGV})
    if(NOT _all_exist)
        # Exit gracefully: no message, no error, just stop this file.
        return()
    endif()
endmacro()
