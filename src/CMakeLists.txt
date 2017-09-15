cmake_minimum_required(VERSION 2.8.3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

#define all source files
set( SRCS SimpleBowlException.cpp Contract.cpp Game.cpp Round.cpp )

# cache variable for build type
if(DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "choose build type")
else() 
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "choose build type")
endif()


# cache variable for library type
option(BUILD_STATIC_LIBS "check to build static libs" OFF)

if(BUILD_STATIC_LIBS)
	add_library( simple-bowl-static STATIC ${SRCS} )
else()
	add_library( simple-bowl SHARED ${SRCS} )
endif()




