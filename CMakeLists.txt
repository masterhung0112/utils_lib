cmake_minimum_required(VERSION 2.8)
project(UTILS C)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(UTILSComponent) # enable components

SET(INCLUDE_DIR include)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/mpr/include)

UTILS_REGISTER_COMPONENT("mpr" ENABLE_MPR)

if(${ENABLE_MPR})
    add_subdirectory(mpr)
endif()

add_executable(utils_app main.c)
target_link_libraries(utils_app mpr)

UTILS_PRINT_COMPONENT_SUMMARY()