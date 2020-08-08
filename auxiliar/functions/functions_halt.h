#ifndef FUNCTIONS_HALT_H
#define FUNCTIONS_HALT_H

#include <iostream>
#include <unistd.h>

namespace cvpp
{

inline void halt() { std::cin.get(); }
inline void halt( const int& t ) { usleep( 1000 * t ); }

}

#endif
