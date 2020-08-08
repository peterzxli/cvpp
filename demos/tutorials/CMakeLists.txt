cmake_minimum_required( VERSION 3.12 )
project( tutorials )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( matrix
        src/main_matrix.cpp
)

