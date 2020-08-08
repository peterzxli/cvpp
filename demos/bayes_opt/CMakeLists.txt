cmake_minimum_required( VERSION 2.8 )
project( camera )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( bo2D
        src/demo_bo2D.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_full.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/bayes_opt/bayes_opt.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/optimiser/optimiser_nlopt.cpp
)

add_executable( bo3D
        src/demo_bo3D.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_full.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/bayes_opt/bayes_opt.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/optimiser/optimiser_nlopt.cpp
)

