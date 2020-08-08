cmake_minimum_required( VERSION 2.8 )
project( gaussian_processes )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( full
        src/demo_full.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_full.cpp
)

add_executable( local_indep
        src/demo_local_indep.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_full.cpp
)

add_executable( local_sum
        src/demo_local_sum.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_full.cpp
)

add_executable( sparse
        src/demo_sparse.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_sparse.cpp
)

add_executable( varlearn
        src/demo_varlearn.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_varlearn.cpp
)

add_executable( varhetero
        src/demo_varhetero.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_varhetero.cpp
)

add_executable( bigdata
        src/demo_bigdata.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_base.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/gaussian_processes/models/gp_bigdata.cpp
)
