#ifndef VEHICLE_H
#define VEHICLE_H

#include <cvpp/auxiliar/macros.h>
#include <cvpp/interfaces/cpplot.h>

#include "../track/track.h"

namespace cvpp
{

class Vehicle
{

protected:

    Arr5d start;
    Vec5d states;

    Vec3d actions;
    Arr2d maxAccel;

    String type;
    Track* track;

public:

    Vehicle( const Pts2d& , const double& , const double& );
    Vehicle( const String& , const double& , const double& );

    void construct( const Pts2d& , const double& , const double& );

    void setType( const String& type ) { this->type  = type;   }
    void setTrack(      Track& track ) { this->track = &track; }

    const Vec5d& getStates() const { return states; }
    const Vec3d& getActions() const { return actions; }

    const int getNumStates() const { return states.n(); }
    const int getNumActions() const { return actions.n(); }

    void drawStates( CPPlot& , const Vec5d& , const Scalar& , const Scalar& , const int& = 3 ) const;
    void drawStates( CPPlot& , const Scalar& , const Scalar& , const int& = 3 ) const;

    bool withinLimits() const;
    bool withinBounds() const;
    bool isValid() const;

    void recreate( Vec5d& , const int& , const int& );
    void recreate( Vec5d& );

    double shake( const int& , int );

    void minimise( const int& , const int& );
    void minimise( const int& );

    double cost();

    void vectorise();
    void split( const int& , const int& );
    void merge( const int& );

protected:

    void initialise( const Pts2d& );
    void parametrise( const Pts2d& );

    void recreate( Vec5d& , const int& );
    void update( Arr5d& , Arr5d& , Arr3d& );

    double cost(        const int& , const int& );
    double cost_dist(   const int& , const int& );
    double cost_accel(  const int& , const int& );
    double cost_veloc(  const int& , const int& );
    double cost_time(   const int& , const int& );
    double cost_custom( const int& , const int& );

};

}

#endif
