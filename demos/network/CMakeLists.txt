cmake_minimum_required( VERSION 2.8 )
project( network )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( email
        src/demo_email.cpp
)

add_executable( download
        src/demo_download.cpp
)

