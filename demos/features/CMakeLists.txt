cmake_minimum_required( VERSION 2.8 )
project( feature )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( matcher
        src/demo_matcher.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)

add_executable( tracker
        src/demo_tracker.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cppture.cpp
)

add_executable( object
        src/demo_object.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cppture.cpp
)

add_executable( warp
        src/demo_warp.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)

add_executable( transform
        src/demo_transform.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/modules/cvis.cpp
)
