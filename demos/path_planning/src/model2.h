#ifndef MODEL_H
#define MODEL_H

#include <cvpp/interfaces/cpplot.h>
#include "./track2.h"

namespace cvpp
{

class Model
{

public:

    Arr5f start;
    Vec5f states;
    Vec3f actions;

    Track* track;
    CPPlot* draw;

    bool use_path;
    String type;

public:

////// CONSTRUCTOR

    Model( const Pts2f& traj , Track& track )
    {
        initialise( traj );
        parametrise( traj );

        this->track = &track;

        this->type = "DIST";
        this->use_path = false;
    }

////// AUXILIAR

    int n() const { return states.n(); }
    Matf traj() const { return states.mat().cl(2); }

    void setDraw(       CPPlot& draw ) { this->draw = &draw; }
    void setType( const String& type ) { this->type = type;  }

    float cost() { return cost( 0 , n() - 2 ); }
    float cost( const int& i , const int& n )
    {
        if( type == "DIST"  ) return cost_dist(  i , n );
        if( type == "ACCEL" ) return cost_accel( i , n );
        if( type == "VELOC" ) return cost_veloc( i , n );
    }

////// START

    void initialise( const Pts2f& traj )
    {
        start[0] = traj[0].x;
        start[1] = traj[0].y;
        start[2] = orient( traj[0] , traj[1] );
        start[3] = 0.0;
        start[4] = 0.0;
    }

////// PARAMETRISE

    void parametrise( const Pts2f& traj )
    {
        states.reset().push( start );
        forLOOPii( 1 , traj.n() )
        {
            Arr5f nstate;

            nstate[0] = traj[i].x;
            nstate[1] = traj[i].y;
            nstate[2] = orient( traj[i-1] , traj[i] );
            nstate[3] = dist( traj[i-1] , traj[i] );
            nstate[4] = normAngle( nstate[2] - states[-1][2] );

            states.push( nstate );
        }

        actions.reset();
        forLOOPi( states.n() - 1 )
        {
            Arr3f naction;

            naction[0] = 1.0;
            naction[1] =          ( states[i+1][3] - states[i][3] );
            naction[2] = normAngle( states[i+1][4] - states[i][4] );

            actions.push( naction );
        }
    }

////// PROPAGATE

    void propagate( Vec5f& states , const int& i )
    {
        states[i][3] = states[i-1][3] + actions[i-1][1];
        states[i][4] = states[i-1][4] + actions[i-1][2];

        states[i][2] = normAngle( states[i-1][2] + states[i][4] );
        states[i][0] =            states[i-1][0] + actions[i-1][0] * states[i][3] * cos( states[i][2] );
        states[i][1] =            states[i-1][1] + actions[i-1][0] * states[i][3] * sin( states[i][2] );
    }

////// RECREATE

    void recreate( Vec5f& states ) { recreate( states , 0 , actions.n() ); }
    void recreate( Vec5f& states , const int& st , const int& nn )
    {
        forLOOPii( st , std::min( (int)actions.n() , st + nn ) )
            propagate( states , i + 1 );
    }

////// LIMITS

    bool withinLimits()
    {
        Matf lim = actions.cr(2).limRows();
        if( lim(0,0) < -0.4f || lim(1,0) > +0.4f ||
            lim(0,1) < -0.2f || lim(1,1) > +0.2f ) return false;
        return true;
    }

    bool withinBounds()
    {
        forLOOPi( states.n() )
        {
            if( track->hit( states[i][0] , states[i][1] ) )
                return false;
        }
        return true;
    }

////// VECTORISE

    void vectorise()
    {
        Vec5f tmp_states;
        Vec3f tmp_actions;

        forLOOPj( states.n() - 1 )
        {
            tmp_states = states;
            tmp_actions = actions;

            Pt2f pt0 = Pt2f( states[j  ][0] , states[j  ][1] );
            Pt2f pt1 = Pt2f( states[j+1][0] , states[j+1][1] );
            float d = dist( pt0 , pt1 );

            if( d < 0.20 ) merge( j );
            if( d > 1.00 ) split( j , 4 );

            if( !withinLimits() || !withinBounds() )
            {
                states = tmp_states;
                actions = tmp_actions;
            }
        }
    }

////// SPLIT

    void split( const int& i , const int& n )
    {
        float off = states[i+1][4];
        float tstep = actions[i][0] / float(n);

        forLOOPj( n - 1 )
        {
            states.push( Arr5f() , i + 1 );
            actions.push( Arr3f( tstep , 0.0 , 0.0 ) , i + 1 );
        }

        actions[i][0] = tstep;
        actions[i+1][2] -= off;
        if( i + n < actions.n() )
            actions[i+n][2] += off;

        recreate( states , i , n );
    }

////// MERGE

    void merge( const int& i )
    {
        float tstep = actions[i-1][0] + actions[i][0];

        states.erase( i ); actions.erase( i );
        actions[i-1][0] = tstep;

        forLOOPjj( i , std::min( (int)states.n() , i + 3 ) )
        {
            Pt2f pt0 = Pt2f( states[j-1][0] , states[j-1][1] );
            Pt2f pt1 = Pt2f( states[j  ][0] , states[j  ][1] );

            states[j][2] = orient( pt0 , pt1 );
            states[j][3] = dist( pt0 , pt1 ) / actions[j-1][0];
            states[j][4] = normAngle( states[j][2] - states[j-1][2] );

            actions[j-1][1] =          ( states[j][3] - states[j-1][3] );
            actions[j-1][2] = normAngle( states[j][4] - states[j-1][4] );
        }
    }

////// SHAKE

    float shake( const int& i , int n )
    {
        n = std::min( (int)states.n() - i - 2 , n );
        recreate( states , i , n );

        forLOOPjj( i , std::min( (int)states.n() - 1 , i + n + 4 ) )
        {
            Pt2f pt0 = Pt2f( states[j  ][0] , states[j  ][1] );
            Pt2f pt1 = Pt2f( states[j+1][0] , states[j+1][1] );

            states[j+1][2] = orient( pt0 , pt1 );
            states[j+1][3] = dist( pt0 , pt1 ) / actions[j][0];
            states[j+1][4] = normAngle( states[j+1][2] - states[j][2] );

            actions[j][1] =          ( states[j+1][3] - states[j][3] );
            actions[j][2] = normAngle( states[j+1][4] - states[j][4] );
        }

        return cost( i , n );
    }

////// COST

    float cost_dist( const int& i , const int& n )
    {
        if( !withinLimits() || !withinBounds() )
            return 1e12;

        float d = 0;
        forLOOPjj( i , std::min( (int)states.n() , i + n + 1 ) )
        {
            double nd = dist( Pt2f( states[j  ][0] , states[j  ][1] ) ,
                              Pt2f( states[j+1][0] , states[j+1][1] ) );

            if( use_path && track->path( states[j+1][0] , states[j+1][1] ) )
                 d += nd / 100;
            else d += nd;
        }

        return d;
    }

    float cost_accel( const int& i , const int& n )
    {
        if( !withinLimits() )
            return 1e12;

        return actions.cr(2).sqsum();
    }

    float cost_veloc( const int& i , const int& n )
    {
        if( !withinLimits() )
            return 1e12;

        return ( - states.c(3).absum() ) / cost_distance( i , n );
    }

////// MINIMIZE

    void minimize( const int& i , const int& n )
    {
        if( i + n >= actions.n() ) return;
        Matf bmat = actions.mat().r(i,n).clone();
        float bval = shake( i , n );

        forLOOPk( 500 )
        {
            actions.mat().b(i,1,n,2).AddRand( 0.02 );
            float cval = shake( i , n );

            if( cval < bval )
            {
                bmat = actions.mat().r(i,n);
                bval = cval;
            }
            else
            {
                actions.mat().r(i,n) = bmat;
            }
        }

        shake( i , n );
    }

    void minimize( const int& n )
    {
        forLOOPii( 0 , actions.n() )
            minimize( i , n );
    }

////// DRAW

    void drawTrack()
    {
        track->plot( *draw , use_path );
    }

    void drawStates(const Vec5f& states , const Scalar& clr1 ,
                                          const Scalar& clr2 , const int& siz )
    {
        Matf traj = states.mat().cl(2).clone();
        draw->lwc(2,clr1).line2D( traj ).psc(siz,clr1).pts2D( traj );

        forLOOPi( states.n() )
        {
            Pt2f pi( states[i][0] , states[i][1] );
            Pt2f pf( states[i][0] + 0.5 * states[i][3] * cos( states[i][2] ) ,
                     states[i][1] + 0.5 * states[i][3] * sin( states[i][2] ) );
            draw->lwc(1,clr2).line2D( pi , pf );
        }
    }

};

}

#endif
