#include "track.h"

namespace cvpp
{

// Constructor

Track::Track( const String& file ,
              const float& scale )
{
    image.load( file );
    this->scale = scale;

    dims.reset( 2 , 2 );
    dims.row(0) << 0.0 , 0.0 ;
    dims.row(1) << ( image.r() - 1 ) * scale ,
                   ( image.c() - 1 ) * scale ;
}

// Get track dimensions

const Matd&
Track::getDims() const
{
    return dims;
}

// Get value of a cell

float
Track::getVal( Pt2d pos ) const
{
    pos /= scale;
    pos.x = std::floor( pos.x );
    pos.y = image.r() - std::floor( pos.y ) - 1;

    return image.at( pos.y , pos.x );
}

float
Track::getVal( const float& x , const float& y ) const
{
    return getVal( Pt2d( x , y ) );
}

// Is inside a wall?

bool
Track::isWall( Pt2d pos ) const
{
    return getVal( pos ) == 0;
}

bool
Track::isWall( const float& x , const float& y ) const
{
    return isWall( Pt2d( x , y ) );
}

bool
Track::isWall( Pt2d pos1 , const Pt2d& pos2 , const int& div ) const
{
    Pt2d dif = ( pos2 - pos1 ) / div;

    forLOOPi( div + 1 )
        if( isWall( pos1 += dif ) ) return true;

    return false;
}

}
