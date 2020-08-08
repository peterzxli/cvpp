#ifndef FUNCTIONS_COLOR_H
#define FUNCTIONS_COLOR_H
#ifdef OPENCV_FOUND

#include <cvpp/auxiliar/definitions/definitions_cpplot.h>
#include <cvpp/auxiliar/definitions/definitions_standard.h>
#include <cvpp/auxiliar/definitions/definitions_opencv.h>

namespace cvpp
{

// COLOR

inline void
RGBlsd( const float& v , float& r , float& g , float& b )
{
    r = ( 0 - v ) * 255.0; if( r < 0 ) r = -r;
    g = ( 1 - v ) * 255.0; if( g < 0 ) g = -g;
    b = ( 2 - v ) * 255.0; if( b < 0 ) b = -b;

    r = r < 0 ? 0 : ( r > 255 ? 255 : r );
    g = g < 0 ? 0 : ( g > 255 ? 255 : g );
    b = b < 0 ? 0 : ( b > 255 ? 255 : b );
}

inline Scalar
RGBstr( const String& str )
{
    if( str == "BLA" ) return BLA;
    if( str == "WHI" ) return WHI;
    if( str == "RED" ) return RED;
    if( str == "GRE" ) return GRE;
    if( str == "BLU" ) return BLU;
    if( str == "YEL" ) return YEL;
    if( str == "CYA" ) return CYA;
    if( str == "MAG" ) return MAG;
    if( str == "PUR" ) return PUR;
    if( str == "BRO" ) return BRO;
    if( str == "NAV" ) return NAV;
}

inline Scalar
RGBint( const int& i )
{
    if( i == -1 )
        return Scalar( 0.0 , 0.0 , 0.0 );
    if( i == -2 )
        return Scalar( 1.0 , 1.0 , 1.0 );

    switch( i % 12 )
    {
        case  0: return Scalar( 0.0 , 0.0 , 1.0 );
        case  1: return Scalar( 1.0 , 0.0 , 0.0 );
        case  2: return Scalar( 0.0 , 1.0 , 0.0 );
        case  3: return Scalar( 1.0 , 1.0 , 0.0 );
        case  4: return Scalar( 0.0 , 1.0 , 1.0 );
        case  5: return Scalar( 1.0 , 0.0 , 1.0 );
        case  6: return Scalar( 0.5 , 0.0 , 0.0 );
        case  7: return Scalar( 0.0 , 0.0 , 0.5 );
        case  8: return Scalar( 0.0 , 0.5 , 0.0 );
        case  9: return Scalar( 0.5 , 0.5 , 0.0 );
        case 10: return Scalar( 0.5 , 0.0 , 0.5 );
        case 11: return Scalar( 0.0 , 0.5 , 0.5 );
    }
}

}

#endif
#endif
