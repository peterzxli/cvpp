cmake_minimum_required( VERSION 2.8 )
project( tutorials )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake )
include( CVPP )

include_directories( /home/vguizilini/Documents/code/cpp/dev )
link_directories( /home/vguizilini/Documents/code/cpp/dev/cvpp/build )
link_libraries( cvpp )

add_executable( tut src/test.cpp )

