cmake_minimum_required( VERSION 2.8 )
project( gaussian_processes )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( compare
        src/demo_compare.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/random_kitchen_sinks/models/rks_original.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/random_kitchen_sinks/models/rks_fastfood.cpp
)


