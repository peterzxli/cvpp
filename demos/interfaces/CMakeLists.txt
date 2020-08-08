cmake_minimum_required( VERSION 2.8 )
project( interfaces )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( process
        src/demo_process.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cppture.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpprint.cpp
)


