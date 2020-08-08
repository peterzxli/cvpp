cmake_minimum_required( VERSION 2.8 )
project( doubly_stochastic )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( doubly_2D
        src/demo_doubly_2D.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/doubly_stochastic/dsgd_original.cpp
)

add_executable( doubly_3D
        src/demo_doubly_3D.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/doubly_stochastic/dsgd_original.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)
