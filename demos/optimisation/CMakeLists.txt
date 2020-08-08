cmake_minimum_required( VERSION 2.8 )
project( optimisation )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( optimiser
        src/demo_optimiser.cpp
	${CPP_INCLUDE_DIR}/cvpp/algorithms/optimiser/optimiser_nlopt.cpp
)


