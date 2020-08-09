cmake_minimum_required( VERSION 3.12 )
project( device )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( device
        src/demo_device.cpp
)


