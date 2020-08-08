#include "vehicle.h"

namespace cvpp
{

// Cost

double
Vehicle::cost( const int& i , const int& n )
{
    if( !isValid() ) return 1e12;

    if( type == "DIST"   ) return cost_dist(   i , n );
    if( type == "ACCEL"  ) return cost_accel(  i , n );
    if( type == "VELOC"  ) return cost_veloc(  i , n );
    if( type == "TIME"   ) return cost_time(   i , n );
    if( type == "CUSTOM" ) return cost_custom( i , n );
}

double
Vehicle::cost()
{
    return cost( 0 , states.n() - 2 );
}

// Cost Distance

double
Vehicle::cost_dist( const int& i , const int& n )
{
    double d = 0;
    forLOOPjj( i , std::min( (int)states.n() , i + n + 1 ) )
    {
        double nd = dist( Pt2d( states[j  ][0] , states[j  ][1] ) ,
                          Pt2d( states[j+1][0] , states[j+1][1] ) );
        d += nd;
    }

    return d;
}

// Cost Acceleration

double
Vehicle::cost_accel( const int& i , const int& n )
{
    return actions.cr(2).sqsum();
}

// Cost Velocity

double
Vehicle::cost_veloc( const int& i , const int& n )
{
    return ( - states.c(3).abmean() );
}

// Cost Time

double
Vehicle::cost_time( const int& i , const int& n )
{
    return actions.c(0).absum();
}

// Cost Custom

double
Vehicle::cost_custom( const int& i , const int& n )
{
    return cost_time( i , n ) * cost_dist( i , n );
}

}

