macro(MPR_APPEND_SOURCES)
    list(APPEND mpr_sources ${ARGV})
endmacro(MPR_APPEND_SOURCES)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

install (FILES
    include/mpr.h
    DESTINATION $(INCLUDE_DIR)/
    COMPONENT headers
)

MPR_APPEND_SOURCES(src/mprMutex.c)
MPR_APPEND_SOURCES(src/mprThread.c)

if (UNIX)
    find_library(PTHREAD_LIB pthread)
    if (${PTHREAD_LIB_NOT_FOUND})
        message(error "pthread library is necessary to build mpr")
    endif()
endif(UNIX)

add_library(mpr SHARED ${mpr_sources})
target_link_libraries(mpr ${PTHREAD_LIB})