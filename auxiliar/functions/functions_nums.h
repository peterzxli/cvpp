#ifndef FUNCTIONS_NUMS_H
#define FUNCTIONS_NUMS_H

#include <cvpp/auxiliar/definitions/definitions_standard.h>
#include <cvpp/auxiliar/definitions/definitions_loops.h>

namespace cvpp
{

TPL_T T
roundDec( const T& val , const int& n )
{
    T m = pow( 10.0 , n );
    return std::round( m * val ) / m;
}

inline int
numDigits( const double& n )
{
    if( n == 0 ) return 1;
    else if( n > 0 )
         return std::floor( log10( std::abs(round(n)) ) ) + 1;
    else return std::floor( log10( std::abs(round(n)) ) ) + 2;
}

inline int
splitSize( const int& n , const int& d )
{
    int r = n / d;
    if( n % d != 0 ) r++;
    return r;
}

TPL_T inline int
sign( const T& val )
{
    return ( val > 0 ) - ( val < 0 );
}

inline int
rbo( int d , int v )
{
    int r = 0 , s = log2(d);
    forLOOPi(s)
    {
        d /= 2;
        if( v % 2 ) r += d;
        v /= 2;
    }
    return r;
}

}

#endif
