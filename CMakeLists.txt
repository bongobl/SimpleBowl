cmake_minimum_required(VERSION 2.8.3)
PROJECT(simple-bowl-build)

add_subdirectory(src lib)

# option to build example
option(BUILD_EXAMPLE_TEST "check to build example" OFF)

if(BUILD_EXAMPLE_TEST)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
	add_executable(testSimpleBowl main.cpp)
	if(BUILD_STATIC_LIBS)
		target_link_libraries(testSimpleBowl simple-bowl-static )
		ADD_DEPENDENCIES(testSimpleBowl simple-bowl-static)
	else()
		target_link_libraries(testSimpleBowl simple-bowl)
		ADD_DEPENDENCIES(testSimpleBowl simple-bowl)
	endif()
endif()