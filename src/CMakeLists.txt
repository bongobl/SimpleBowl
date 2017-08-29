cmake_minimum_required(VERSION 2.8.3)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set( SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../include/Contract.hpp 
          ${CMAKE_CURRENT_SOURCE_DIR}/../include/Game.hpp 
          ${CMAKE_CURRENT_SOURCE_DIR}/../include/Round.hpp 
          ${CMAKE_CURRENT_SOURCE_DIR}/../include/SimpleBowlException.hpp 
          Contract.cpp 
          Game.cpp 
          Round.cpp )

option(BUILD_STATIC_LIBS "check to build static libs" OFF)

if(BUILD_STATIC_LIBS)
	set( LIB_TYPE STATIC )
else()
	set( LIB_TYPE SHARED )
endif()

add_library( simple-bowl ${LIB_TYPE} ${SRCS} )