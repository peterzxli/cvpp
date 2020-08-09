
################################################################
########## COMPILE FLAGS

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y" )

################################################################

message( "******************************************** CHECKING FOR DEPENDENCIES ..." )

################################################################
########## OPENMP

find_package( OpenMP QUIET )

if( OPENMP_FOUND )

    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )

    message( "############################# OpenMP FOUND!" )
    if( ${VERBOSE} )
        message( "***** FLAGS: " ${OpenMP_CXX_FLAGS} )
    endif()
else()
    message( "############################# OpenMP **NOT** FOUND!" )
endif()

################################################################
########## EIGEN

find_package( Eigen3 REQUIRED QUIET )

if( EIGEN3_FOUND )
add_definitions( -DEIGEN_FOUND)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DEIGEN_NO_DEBUG -mavx -mfma" )

    include_directories(
        ${EIGEN3_INCLUDE_DIR}
    )

    message( "############################# Eigen3 FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${EIGEN3_INCLUDE_DIR} )
    endif()
else()
    message( "############################# Eigen3 **NOT** FOUND!" )
endif()

################################################################
########## BOOST

find_package( Boost REQUIRED COMPONENTS system thread chrono filesystem QUIET )

if( Boost_FOUND )
add_definitions( -DBOOST_FOUND )

    link_directories(
        ${Boost_LIBRARY_DIRS}
    )

    link_libraries(
        ${Boost_LIBRARIES}
    )

    message( "############################# Boost FOUND!" )
    if( ${VERBOSE} )
        message( "***** LIBRARY_DIRS: " ${Boost_LIBRARY_DIRS} )
        message( "***** LIBRARIES: " ${Boost_LIBRARIES} )
    endif()
else()
    message( "############################# Boost **NOT** FOUND!" )
endif()

################################################################
########## OPENCV

find_package( OpenCV 3 QUIET )

if( OpenCV_FOUND )
add_definitions( -DOPENCV_FOUND )

    include_directories(
        ${OpenCV_INCLUDE_DIRS}
    )

    link_libraries(
        ${OpenCV_LIBRARIES}
    )

    message( "############################# OpenCV FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${OpenCV_INCLUDE_DIRS} )
        message( "***** LIBRARIES: " ${OpenCV_LIBRARIES} )
    endif()
else()
    message( "############################# OpenCV **NOT** FOUND!" )
endif()

################################################################
########## MKL

find_package( MKL QUIET )

if( MKL_FOUND )
add_definitions( -DMKL_FOUND )

    include_directories(
        ${MKL_INCLUDE_DIR}
    )

    link_directories(
        ${MKL_LIB_DIR}
    )

    # Run MKL link advisor to determine correct flags:
    # https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor

    link_libraries(
        mkl_intel_lp64
        mkl_intel_thread
        mkl_core iomp5 pthread m dl
    )

    message( "############################# MKL FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${MKL_INCLUDE_DIR} )
        message( "***** LIBRARIES: " ${MKL_LIBRARIES} )
    endif()
else()
    message( "############################# MKL **NOT** FOUND!" )
endif()

################################################################
########## OPENGL

find_package( SDL2 QUIET )
find_package( GLUT QUIET )
find_package( OpenGL QUIET )

if( SDL2_FOUND AND GLUT_FOUND AND OPENGL_FOUND )
add_definitions( -DOPENGL_FOUND )

	if (FALSE)
		set( OPENGL_INCLUDE_DIR "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/Headers" )
		set ( OPENGL_LIBRARIES "/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib" )
	endif ()

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
    )

    link_libraries(
        SDL2
        ${GLUT_LIBRARIES}
        ${OPENGL_LIBRARIES}
    )

    message( "############################# OpenGL FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${SDL2_INCLUDE_DIRS} " " ${OPENGL_INCLUDE_DIR} )
        message( "***** LIBRARIES: " SDL2 " " ${GLUT_LIBRARIES} " OpenGL" ${OPENGL_LIBRARIES} )
    endif()
else()
    message( "############################# OpenGL **NOT** FOUND!" )
endif()

################################################################
########## ARRAYFIRE

find_package( ArrayFire QUIET )

if( ArrayFire_FOUND )
add_definitions( -DARRAYFIRE_FOUND )

    include_directories(
        ${ArrayFire_INCLUDE_DIRS}
    )

    link_libraries(
        ${ArrayFire_LIBRARIES}
    )

    message( "############################# ArrayFire FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${ArrayFire_INCLUDE_DIRS} )
        message( "***** LIBRARIES: " ${ArrayFire_LIBRARIES} )
    endif()
else()
    message( "############################# ArrayFire **NOT** FOUND!" )
endif()

################################################################
########## NLOPT

find_package( NLOPT QUIET )

if( NLOPT_FOUND )
add_definitions( -DNLOPT_FOUND )

    include_directories(
        ${NLOPT_INCLUDE_DIRS}
    )

    link_libraries(
        ${NLOPT_LIBRARIES}
    )

    message( "############################# NLOPT FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${NLOPT_INCLUDE_DIRS} )
        message( "***** LIBRARIES: " ${NLOPT_LIBRARIES} )
    endif()
else()
    message( "############################# NLOPT **NOT** FOUND!" )
endif()

################################################################
########## CUDA

find_package( CUDA QUIET )

if( CUDA_FOUND )
add_definitions( -DCUDA_FOUND )

    include_directories(
        ${CUDA_INCLUDE_DIRS}
    )

    link_libraries(
        ${CUDA_LIBRARIES}
    )

    message( "############################# CUDA FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${CUDA_INCLUDE_DIRS} )
        message( "***** LIBRARIES: " ${CUDA_LIBRARIES} )
    endif()
else()
    message( "############################# CUDA **NOT** FOUND!" )
endif()

################################################################
########## CURL

find_package( CURL QUIET )

if( CURL_FOUND )
add_definitions( -DCURL_FOUND )

    include_directories(
        ${CURL_INCLUDE_DIRS}
    )

    link_libraries(
        ${CURL_LIBRARIES}
    )

    message( "############################# CURL FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${CURL_INCLUDE_DIRS} )
        message( "***** LIBRARIES: " ${CURL_LIBRARIES} )
    endif()
else()
    message( "############################# CURL **NOT** FOUND!" )
endif()

################################################################
########## VLFEAT

find_package( VLFEAT QUIET )

if( VLFEAT_FOUND )
add_definitions( -DVLFEAT_FOUND )

    include_directories(
        ${VLFEAT_INCLUDE_DIR}
    )

    link_libraries(
        ${VLFEAT_LIBRARIES}
    )

    message( "############################# VLFeat FOUND!" )
    if( ${VERBOSE} )
        message( "***** INCLUDE_DIRS: " ${VLFEAT_INCLUDE_DIR} )
        message( "***** LIBRARIES: " ${VLFEAT_LIBRARIES} )
    endif()
else()
    message( "############################# VLFeat **NOT** FOUND!" )
endif()

################################################################
if (APPLE)
	message(STATUS "Finding LZ4 libraries")
	find_library(LZ4_LIBRARIES NAMES liblz4.dylib HINTS "/usr/local/Cellar/lz4/1.9.2/lib/")
	if(LZ4_LIBRARIES)
		message(STATUS "Found: ${LZ4_LIBRARIES}")
	else()
		message(STATUS "Not found: ${LZ4_LIBRARIES}")
		message(FATAL_ERROR "Cannot find required LZ4 libraries")
	endif()
	
	macro (add_executable _name)
	    # invoke built-in add_executable
	    _add_executable(${ARGV})
	    if (TARGET ${_name})
	        target_link_libraries(${_name} ${LZ4_LIBRARIES})
	    endif()
	endmacro()
endif ()

################################################################
message( "******************************************** CHECKING FOR DEPENDENCIES ... DONE!" )
