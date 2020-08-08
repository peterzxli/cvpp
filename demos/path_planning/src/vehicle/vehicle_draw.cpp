#include "vehicle.h"

namespace cvpp
{

// Draw states

void
Vehicle::drawStates( CPPlot& draw , const Vec5d& states ,
                     const Scalar& clr1 , const Scalar& clr2 , const int& siz ) const
{
    Matd traj = states.mat().cl(2).clone();
    draw.lwc( 2 , clr1 ).line2D( traj ).psc( siz , clr1 ).pts2D( traj );

    forLOOPi( states.n() )
    {
        Pt2d pi( states[i][0] , states[i][1] );
        Pt2d pf( states[i][0] + states[i][3] * cos( states[i][2] ) ,
                 states[i][1] + states[i][3] * sin( states[i][2] ) );
        draw.lwc( 1 , clr2 ).line2D( pi , pf );
    }
}

void
Vehicle::drawStates( CPPlot& draw ,
                     const Scalar& clr1 , const Scalar& clr2 , const int& siz ) const
{
    drawStates( draw , states , clr1 , clr2 , siz );
}

}
