cmake_minimum_required( VERSION 2.8 )
project( hilbert_maps )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( dataset3d
        src/demo_dataset3d.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)
