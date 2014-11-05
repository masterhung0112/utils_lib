macro(MPR_APPEND_SOURCES)
    list(APPEND mpr_sources ${ARGV})
endmacro(MPR_APPEND_SOURCES)

add_subdirectory(include)
add_subdirectory(src)

add_library(mpr SHARED ${mpr_sources})