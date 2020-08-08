#ifndef MACROS_H
#define MACROS_H

#include <cvpp/auxiliar/macros_base.h>

#include "functions/functions_border.h"
#include "functions/functions_alglin.h"

namespace cvpp
{

// MACRO

Matd inline
LIMITSd( const int& n )
{
    Matd lim( 2 , n );
    lim.r(0) = PINF; lim.r(1) = NINF;
    return lim;
}

// ROUND

}

#endif
