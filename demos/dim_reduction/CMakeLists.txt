cmake_minimum_required( VERSION 2.8 )
project( dim_reduction )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( pca
        src/demo_pca.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/dim_reduction/linear_pca.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)

add_executable( kpca
        src/demo_kpca.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/dim_reduction/kernel_pca.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)

add_executable( isomap
        src/demo_isomap.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
)


