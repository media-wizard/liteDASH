project (DASH)
cmake_minimum_required (VERSION 3.5)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++17 -g")

include_directories(include)
include_directories(manifest)

file(GLOB LIBSOURCES "parser/*.cpp" "mpd/*.cpp")
add_library(ltDash STATIC ${LIBSOURCES})

file(GLOB SOURCES "test/*.cpp")

set(test DashTest )
add_executable(test ${SOURCES})
target_link_libraries(test ltDash "-lexpat")
