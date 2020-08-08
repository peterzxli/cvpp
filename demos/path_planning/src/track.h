#ifndef TRACK_H
#define TRACK_H

#include <cvpp/interfaces/cpplot.h>

namespace cvpp
{

class Track
{

protected:

    SPts2d pts;
    Matd ctrs;

public:

    Track()
    {
        pts.resize( 3 );

        pts[0].push( Pt2d( -05.0 , +10.0 ) )
              .push( Pt2d( +15.0 , +10.0 ) )
              .push( Pt2d( +15.0 , +04.0 ) )
              .push( Pt2d( +40.0 , +04.0 ) )
              .push( Pt2d( +40.0 , -10.0 ) )
              .push( Pt2d( -05.0 , -10.0 ) );

        pts[1].push( Pt2d( +02.0 , +5.0 ) )
              .push( Pt2d( +08.0 , +5.0 ) )
              .push( Pt2d( +08.0 , -2.0 ) )
              .push( Pt2d( +35.0 , -2.0 ) )
              .push( Pt2d( +35.0 , -7.0 ) )
              .push( Pt2d( +02.0 , -7.0 ) );

        pts[2].push( Pt2d( +18.0 , +2.0 ) )
              .push( Pt2d( +30.0 , +2.0 ) )
              .push( Pt2d( +30.0 , +0.0 ) )
              .push( Pt2d( +18.0 , +0.0 ) );

        ctrs = pts[0].mat() | pts[1].mat() | pts[2].mat();
    }

    ~Track()
    {

    }

    Pts2d grid( const double& s ) const
    {
        return MatGrid2d( pts[0].mat() , s , 0.1 , 0.1 );
    }

    bool hit( const double& x , const double& y ) const
    {
        return hit( Pt2d( x , y ) );
    }

    bool hit( const Pt2d& pos ) const
    {
        if( pos.x < pts[0][0].x || pos.y > pts[0][0].y ||
            pos.x > pts[0][4].x || pos.y < pts[0][4].y ) return true;
        if( pos.x > pts[0][2].x && pos.y > pts[0][2].y ) return true;
        if( pos.x > pts[1][0].x && pos.y < pts[1][0].y &&
            pos.x < pts[1][1].x && pos.y > pts[1][5].y ) return true;
        if( pos.x > pts[1][2].x && pos.y < pts[1][2].y &&
            pos.x < pts[1][4].x && pos.y > pts[1][5].y ) return true;
        if( pos.x > pts[2][0].x && pos.y < pts[2][0].y &&
            pos.x < pts[2][2].x && pos.y > pts[2][2].y ) return true;
        return false;
    }

    void plot( CPPlot& draw )
    {
        draw.setAxes( pts[0] , 0.1 , 0.1 );
        draw.lwc(3,BLA).loop2D( pts[0] ).loop2D( pts[1] ).loop2D( pts[2] );
        draw.psc(6,MAG).pts2D( ctrs );
    }

};

}

#endif
