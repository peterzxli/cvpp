#include "vehicle.h"

namespace cvpp
{

// Constructor ( Pts2d )

Vehicle::Vehicle( const Pts2d& traj , const double& maxLin , const double& maxAng )
{
    construct( traj , maxLin , maxAng );
}

// Constructor ( String )

Vehicle::Vehicle( const String& str , const double& maxLin , const double& maxAng )
{
    Pts2d traj( str );
    construct( traj , maxLin , maxAng );
}

// Shared constructor code

void
Vehicle::construct( const Pts2d& traj , const double& maxLin, const double& maxAng )
{
    maxAccel[0] = maxLin;
    maxAccel[1] = maxAng;

    initialise( traj );
    parametrise( traj );
}

// Initialise

void
Vehicle::initialise( const Pts2d& traj )
{
    start[0] = traj[0].x;
    start[1] = traj[0].y;
    start[2] = orient( traj[0] , traj[1] );
    start[3] = 0.0;
    start[4] = 0.0;
}

// Within limits

bool
Vehicle::withinLimits() const
{
    Matd lim = actions.cr(2).limRows();
    if( lim(0,0) < - maxAccel[0] || lim(1,0) > + maxAccel[0] ||
        lim(0,1) < - maxAccel[1] || lim(1,1) > + maxAccel[1] ) return false;
    return true;
}

// Within bounds

bool
Vehicle::withinBounds() const
{
    forLOOPi( states.n() - 1 )
    {
        if( track->isWall( Pt2f( states[i  ][0] , states[i  ][1] ) ,
                           Pt2f( states[i+1][0] , states[i+1][1] ) ) )
            return false;
    }

    return true;
}

// Is Valid

bool
Vehicle::isValid() const
{
    return withinLimits() && withinBounds();
}

// Parametrise

void
Vehicle::parametrise( const Pts2d& traj )
{
    states.reset().push( start );
    actions.reset();

    forLOOPii( 1 , traj.n() )
    {
        Arr5d nstate;
        Arr3d naction;

        nstate[0] = traj[i].x;
        nstate[1] = traj[i].y;
        nstate[2] = orient( traj[i-1] , traj[i] );

        naction[0] = 0.0;

        do {
            naction[0] += 1.0;
            update( states[-1] , nstate , naction );
        }
        while ( fabs( naction[1] ) > maxAccel[0] ||
                fabs( naction[2] ) > maxAccel[1] );

        states.push( nstate );
        actions.push( naction );
    }
}

// Recreate

void
Vehicle::recreate( Vec5d& states , const int& i )
{
    states[i][3] = states[i-1][3] + actions[i-1][0] * actions[i-1][1];
    states[i][4] = states[i-1][4] + actions[i-1][0] * actions[i-1][2];

    states[i][2] = normAngle( states[i-1][2] + actions[i-1][0] * states[i][4] );
    states[i][0] =            states[i-1][0] + actions[i-1][0] * states[i][3] * cos( states[i][2] );
    states[i][1] =            states[i-1][1] + actions[i-1][0] * states[i][3] * sin( states[i][2] );
}

void
Vehicle::recreate( Vec5d& states , const int& st , const int& nn )
{
    forLOOPii( st , std::min( (int)actions.n() , st + nn ) )
            recreate( states , i + 1 );
}

void
Vehicle::recreate( Vec5d& states )
{
    recreate( states , 0 , actions.n() );
}

// Update

void
Vehicle::update( Arr5d& prev , Arr5d& curr , Arr3d& act )
{
    curr[3] = dist( Pt2f( curr[0] , curr[1] ) ,
                    Pt2f( prev[0] , prev[1] ) ) / act[0];
    curr[4] = normAngle(  curr[2] - prev[2] )   / act[0];

    act[1] =          ( curr[3] - prev[3] ) / act[0];
    act[2] = normAngle( curr[4] - prev[4] ) / act[0];
}

// Shake

double
Vehicle::shake( const int& i , int n )
{
    n = std::min( (int)states.n() - i - 2 , n );
    recreate( states , i , n );

    forLOOPjj( 0 , states.n() - 1 )
    {
        states[j+1][2] = orient( Pt2f( states[j  ][0] , states[j  ][1] ) ,
                                 Pt2f( states[j+1][0] , states[j+1][1] ) );
        update( states[j] , states[j+1] , actions[j] );
    }

    return cost( i , n );
}

// Vectorise

void
Vehicle::vectorise()
{
    Vec5d tmp_states;
    Vec3d tmp_actions;

    forLOOPi( actions.n() - 1 )
    {
        double t = actions[i][0];
        double v = states[i][3];

        if( t < 0.5 )
        {
            tmp_states = states;
            tmp_actions = actions;

            merge( i );

            if( !isValid() )
            {
                states = tmp_states;
                actions = tmp_actions;
            }
        }
        else
        if( t > 2.0 || v * t > 3.0 )
        {
            tmp_states = states;
            tmp_actions = actions;

            split( i , 2 );

            if( !isValid() )
            {
                states = tmp_states;
                actions = tmp_actions;
            }
        }

    }
}

// Merge

void
Vehicle::merge( const int& i )
{
    float tstep = actions[i-1][0] + actions[i][0];

    states.erase( i ); actions.erase( i );
    actions[i-1][0] = tstep;

    forLOOPjj( i , std::min( (int)states.n() , i + 3 ) )
    {
        states[j][2] = orient( Pt2f( states[j-1][0] , states[j-1][1] ) ,
                               Pt2f( states[j  ][0] , states[j  ][1] ) );
        update( states[j-1] , states[j] , actions[j-1] );
    }
}

// Split

void
Vehicle::split( const int& i , const int& n )
{
    actions[i][0] /= double(n);
    forLOOPj( n - 1 )
    {
        states.push( Arr5d() , i + 1 );
        actions.push( actions[i] , i + 1 );
    }

    recreate( states , i , n );
    forLOOPjj( i , std::min( (int)states.n() , i + n + 4 ) )
    {
        states[j][2] = orient( Pt2f( states[j-1][0] , states[j-1][1] ) ,
                               Pt2f( states[j  ][0] , states[j  ][1] ) );
        update( states[j-1] , states[j] , actions[j-1] );
    }
}

// Minimise

void
Vehicle::minimise( const int& i , const int& n )
{
    if( i + n >= actions.n() ) return;
    double bval = cost( i , n );

    Vec5d tmp_states = states.clone();
    Vec3d tmp_actions = actions.clone();

    forLOOPk( 500 )
    {
        actions.mat().r( i , n ).AddRand( 0.02 );
        double cval = shake( i , n );

        if( cval < bval )
        {
            bval = cval;

            tmp_states = states;
            tmp_actions = actions;
        }
        else
        {
            states = tmp_states;
            actions = tmp_actions;
        }
    }
}

void
Vehicle::minimise( const int& n )
{
    forLOOPii( 0 , actions.n() )
            minimise( i , n );
    vectorise();
}

}

