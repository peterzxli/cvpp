#ifndef TRACK2_H
#define TRACK2_H

#include <cvpp/interfaces/cpplot.h>

namespace cvpp
{

class Track
{

protected:

    SPts2d pts,trk;

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

        trk.resize(4);

        trk[0].push( Pt2d( -3.0 , -9.0 ) )
              .push( Pt2d( +0.0 , -9.0 ) )
              .push( Pt2d( +0.0 , +8.0 ) )
              .push( Pt2d( -3.0 , +8.0 ) );

        trk[1].push( Pt2d(  +1.0 , +7.0 ) )
              .push( Pt2d(  +1.0 , +8.0 ) )
              .push( Pt2d( +12.0 , +8.0 ) )
              .push( Pt2d( +12.0 , +7.0 ) );

        trk[2].push( Pt2d(  +5.0 , -9.0 ) )
              .push( Pt2d( +30.0 , -9.0 ) )
              .push( Pt2d( +30.0 , -8.0 ) )
              .push( Pt2d(  +5.0 , -8.0 ) );

        trk[3].push( Pt2d( +11.0 , +0.0 ) )
              .push( Pt2d( +11.0 , +6.0 ) )
              .push( Pt2d( +13.0 , +6.0 ) )
              .push( Pt2d( +13.0 , +0.0 ) );
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

    bool path( const double& x , const double& y ) const
    {
        return path( Pt2d( x , y ) );
    }

    bool path( const Pt2d& pos ) const
    {
        if( pos.x > trk[0][0].x && pos.x < trk[0][1].x &&
            pos.y > trk[0][0].y && pos.y < trk[0][2].y ) return true;
        if( pos.x > trk[1][0].x && pos.x < trk[1][2].x &&
            pos.y > trk[1][0].y && pos.y < trk[1][1].y ) return true;
        if( pos.x > trk[2][0].x && pos.x < trk[2][1].x &&
            pos.y > trk[2][1].y && pos.y < trk[2][2].y ) return true;
        if( pos.x > trk[3][0].x && pos.x < trk[3][2].x &&
            pos.y > trk[3][0].y && pos.y < trk[3][1].y ) return true;
        return false;
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

    void plot( CPPlot& draw , const bool& use_path )
    {
        draw.setAxes( pts[0] , 0.1 , 0.1 );
        forLOOPi( pts.size() ) draw.lwc(3,BLA).loop2D( pts[i] );
        if( use_path ) forLOOPi( trk.size() ) draw.lwc(3,BLU).loop2D( trk[i] );
    }

};

}

#endif
