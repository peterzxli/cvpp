cmake_minimum_required( VERSION 2.8 )
project( cvpp )

set(CMAKE_BUILD_TYPE Release)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
include( CVPP )

file( GLOB_RECURSE INTERFACES
	interfaces/cpplot.cpp 
	interfaces/cppture.cpp 
	interfaces/cpprint.cpp )

file( GLOB_RECURSE OBJECTS
	objects/object.cpp )

add_library( cvpp SHARED 
		${INTERFACES} 
		${OBJECTS} )

