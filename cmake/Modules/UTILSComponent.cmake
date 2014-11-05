if (DEFINED __INCLUDED_UTILS_COMPONENT_CMAKE)
    return()
endif()
set(__INCLUDED_UTILS_COMPONENT_CMAKE TRUE)

set(_utils_enabled_components "" CACHE INTERNAL "" FORCE)
set(_utils_disabled_components "" CACHE INTERNAL "" FORCE)

########################################################################
# Register a component into the system
#  - name the component string name
#  - var the global enable variable
#  - enb the default enable setting
#  - deps a list of dependencies
#  - dis the default disable setting
########################################################################
MACRO(UTILS_REGISTER_COMPONENT name var)
    message(STATUS "")
    message(STATUS "Configuring ${name} support...")
    foreach(dep ${ARGN})
        message(STATUS "    Dependency ${dep} = ${${dep}}")
    endforeach()
    
    unset(comp_deps)
    foreach(dep ${ARGN})
        list(FIND _utils_enabled_components ${dep} dep_enb_index)
        list(FIND _utils_disabled_components ${dep} dep_dis_index)
        if (${dep_enb_index} EQUAL -1 AND ${dep_dis_index} EQUAL -1)
            list(APPEND comp_deps ${dep})
        else()
            list(APPEND comp_deps ${dep}_cached)
        endif()
    endforeach()
    
    include(CMakeDependentOption)
    cmake_dependent_option(${var} "enable ${name} support" ON "${comp_deps}" OFF)
    
    if (${var})
        message(STATUS "   Enabling ${name} support")
        list(APPEND _utils_enabled_components ${name})
    else()
        message(STATUS "   Disabling ${name} support")
        list(APPEND _utils_disabled_components ${name})
    endif()
    
    set(_utils_enabled_components ${_utils_enabled_components} CACHE INTERNAL "" FORCE)
    set(_utils_disabled_components ${_utils_disabled_components} CACHE INTERNAL "" FORCE)
ENDMACRO(UTILS_REGISTER_COMPONENT)


########################################################################
# Print the registered component summary
########################################################################
FUNCTION(UTILS_PRINT_COMPONENT_SUMMARY)
    MESSAGE(STATUS "")
    MESSAGE(STATUS "######################################################")
    MESSAGE(STATUS "# UTILS enabled components                            ")
    MESSAGE(STATUS "######################################################")
    FOREACH(comp ${_utils_enabled_components})
        MESSAGE(STATUS "  * ${comp}")
    ENDFOREACH(comp)

    MESSAGE(STATUS "")
    MESSAGE(STATUS "######################################################")
    MESSAGE(STATUS "# UTILS disabled components                           ")
    MESSAGE(STATUS "######################################################")
    FOREACH(comp ${_utils_disabled_components})
        MESSAGE(STATUS "  * ${comp}")
    ENDFOREACH(comp)

    MESSAGE(STATUS "")
ENDFUNCTION(UTILS_PRINT_COMPONENT_SUMMARY)
