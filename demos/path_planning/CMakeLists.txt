cmake_minimum_required( VERSION 2.8 )
project( cvpp )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( track
        src/proj_track.cpp
        src/track/track.cpp
        src/vehicle/vehicle.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)


