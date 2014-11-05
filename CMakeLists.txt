cmake_minimum_required(VERSION 2.8)
project(UTILS C)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(UTILSComponent) # enable components

UTILS_REGISTER_COMPONENT("mpr" ENABLE_MPR)

if(${ENABLE_MPR})
    add_subdirectory(mpr)
endif()

UTILS_PRINT_COMPONENT_SUMMARY()