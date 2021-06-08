find_package(Catch2 REQUIRED)


add_executable(catch_tests
	catch_main.cpp
	test_math.cpp
)


target_include_directories(catch_tests PRIVATE .)
target_link_libraries(catch_tests Catch2::Catch2 Qt5::Gui Qt5::Widgets widget drawable tool math)

include(Catch)
catch_discover_tests(catch_tests)