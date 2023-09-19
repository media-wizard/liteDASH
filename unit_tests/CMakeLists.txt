project(unit-tests)

add_executable(dash_unit_test
    main.cpp
    dash_mpd_test.cpp
)

target_link_libraries (dash_unit_test LINK_PUBLIC
    ltDash
    Catch2::Catch2WithMain
)

set_target_properties(dash_unit_test PROPERTIES
CXX_STANDARD 17
CXX_EXTENSIONS TRUE
)