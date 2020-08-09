cmake_minimum_required( VERSION 3.12 )
project( hilbert_maps )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake )
include( CVPP )

add_executable( orgn_scan
        src/demo_orgn_scan.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/orgn/hm_orgn.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)

add_executable( lard_rings
        src/demo_lard_rings.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/lard/hm_lard.cpp
)

add_executable( lard_scan
        src/demo_lard_scan.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/lard/hm_lard.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)

add_executable( lard_virtual
        src/demo_lard_virtual.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/lard/hm_lard.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)

add_executable( lard_riegl1
        src/demo_lard_riegl1.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/lard/hm_lard.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)

add_executable( lard_riegl2
        src/demo_lard_riegl2.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/lard/hm_lard.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)

add_executable( dsgd_rings
        src/demo_dsgd_rings.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/dsgd/hm_dsgd.cpp
)

add_executable( dsgd_virtual
        src/demo_dsgd_virtual.cpp
        ${CPP_INCLUDE_DIR}/cvpp/interfaces/cpplot.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/hilbert_maps/dsgd/hm_dsgd.cpp
        ${CPP_INCLUDE_DIR}/cvpp/algorithms/marching_cubes/marching3D.cpp
)
