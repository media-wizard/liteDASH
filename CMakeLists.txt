project (DASH)
cmake_minimum_required (VERSION 3.10)


find_package(EXPAT REQUIRED)

include_directories(include)
include_directories(manifest)

file(GLOB LIBSOURCES "parser/*.cpp" "mpd/*.cpp")
add_library(ltDash STATIC ${LIBSOURCES})
target_link_libraries(ltDash PRIVATE ${EXPAT_LIBRARIES})
target_include_directories (ltDash PRIVATE ${EXPAT_INCLUDE_DIRS})

set_target_properties(ltDash PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS TRUE
)

target_compile_options(ltDash PRIVATE
    -fPIC
)

file(GLOB SOURCES "test/*.cpp")

set(test DashTest )
add_executable(test ${SOURCES})
target_link_libraries(test ltDash)

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS TRUE
)
