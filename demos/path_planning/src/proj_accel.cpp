
#include "./track.h"
#include "./model.h"

using namespace cvpp;

int main()
{
    Vec5f data( "states" );
    Pts2f traj = data.mat().cl(2);

    Track track;

    Model vehicle( traj , track ); vehicle.vectorise();
    Vec5f org_states = vehicle.states.clone();

    CPPlot draw("Window");
    draw[0].set2Dplot().setAxes( vehicle.traj() , 0.1 , 0.4 );

    int n = 1;
    int m = 5;

    while( draw.input() )
    {
        draw[0].clear().axes();

        track.plot( draw );
        vehicle.drawTrack( draw , org_states , BLA , BLU , 8 );
        vehicle.drawTrack( draw , vehicle.states , GRE , RED , 5 );
        draw.psc(7,RED).pts2D( vehicle.traj().r(n) );

        draw.updateWindow(30);

        if( draw.keys.enter )
        {
            vehicle.minimize( m++ , "DIST" );
            if( m > 15 ) m = 5;
            vehicle.vectorise();

            org_states.resize( vehicle.n() );
            vehicle.recreate( org_states );
            halt(100);
        }

        if( draw.keys.up   ) { if( n < vehicle.n() - 2 ) n++; halt(100); }
        if( draw.keys.down ) { if( n > 0               ) n--; halt(100); }

    }

    return 0;
}






