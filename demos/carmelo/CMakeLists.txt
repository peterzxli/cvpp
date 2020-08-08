cmake_minimum_required( VERSION 2.8 )
project( carmelo )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( template
        src/demo_template.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)

