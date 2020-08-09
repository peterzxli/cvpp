################################################################
########## CMAKE FLAGS

option(VERBOSE "VERBOSE" ON)

################################################################
########## CMAKE INFORMATION

message( "******************************************** CMAKE INFORMATION ..." )
message( "****** CMake Version : " ${CMAKE_VERSION} )
message( "****** CMake System  : " ${CMAKE_SYSTEM}  )
message( "****** GCC Version   : " ${CMAKE_CXX_COMPILER_VERSION} )

################################################################
########## CPP

# Change to the folder CVPP is installed
set( CPP_INCLUDE_DIR "~" )
include_directories(${CPP_INCLUDE_DIR})

################################################################
########## CVPP

include(CVPP_ALL)

################################################################





