project (DASH)
cmake_minimum_required (VERSION 3.5)

include_directories(include)
include_directories(manifest)

file(GLOB LIBSOURCES "parser/*.cpp" "mpd/*.cpp")
add_library(ltDash STATIC ${LIBSOURCES})

set_target_properties(ltDash PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS TRUE
)



file(GLOB SOURCES "test/*.cpp")

set(test DashTest )
add_executable(test ${SOURCES})
target_link_libraries(test ltDash "-lexpat")

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS TRUE
)
