cmake_minimum_required( VERSION 2.8 )
project( bundle_adjustment )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

include_directories(
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/include
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/include/sparse_bundle_adjustment
)

add_library( sba
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/sba.cpp
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/spa.cpp
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/spa2d.cpp
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/csparse.cpp
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/proj.cpp
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/node.cpp
    ${CPP_INCLUDE_DIR}/cvpp/auxiliar/third_party/sba/src/sba_file_io.cpp
)

link_libraries( sba blas lapack cholmod cxsparse )

add_executable( generate
        src/proj_generate.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/objects/object.cpp
)

add_executable( optimize
        src/proj_optimize.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/objects/object.cpp
)

add_executable( triangulation
        src/proj_triangulation.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/modules/cvis.cpp
)

add_executable( real_bundle
        src/proj_real_bundle.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/objects/object.cpp
)

add_executable( 5imgs
        src/proj_5imgs.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/modules/cvis.cpp
)

