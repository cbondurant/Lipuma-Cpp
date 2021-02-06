cmake_minimum_required(VERSION 3.18.0)

project(lipuma VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERISON VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
include_directories(${Qt5Gui_INCLUDE_DIRS}, {Qt5Widgets_INCLUDE_DIRS})
include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)


add_executable(lipuma
	src/main.cpp
)
target_link_libraries(lipuma Qt5::Gui Qt5::Widgets widget drawable tool)