cmake_minimum_required( VERSION 2.8 )
project( camera )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( projection
        src/demo_projection.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cppture.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/objects/object.cpp
)

add_executable( depth
        src/demo_depth.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/objects/object.cpp
)

add_executable( epipolar
        src/demo_epipolar.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/modules/cvis.cpp
)

add_executable( poseest
        src/demo_poseest.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/modules/cvis.cpp
)

add_executable( essential
        src/demo_essential.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/modules/cvis.cpp
)
