
#include "./model2.h"

using namespace cvpp;

int main()
{
    Vec5f data( "states" );
    Pts2f traj = data.mat().cl(2);

    Track track;

    Model vehicle( traj , track ); vehicle.vectorise();
    Vec5f org_states = vehicle.states.clone();

    CPPlot draw("Window",1,2);
    draw[0].set2Dplot().setAxes( vehicle.traj() , 0.1 , 0.4 );
    draw[1].set2Dplot();

    vehicle.setDraw( draw );
    vehicle.setType( "DIST" );
    vehicle.use_path = false;

    int m = 5;

    Pts2f costs;

    while( draw.input() )
    {
        draw[0].clear().axes();

        vehicle.drawTrack();
        vehicle.drawStates( org_states , BLA , BLU , 8 );
        vehicle.drawStates( vehicle.states , GRE , RED , 5 );

        draw[1].clear();

        if( costs.n() > 1 )
        {
            draw.setAxes( 0 , costs.n() , costs.mat().c(1).min()  , costs.mat().c(1).max() ).axes();
            draw.lwc(2,BLA).line2D( costs );
        }

        draw.updateWindow(30);

        if( draw.keys.enter )
        {
            vehicle.minimize( m );
            vehicle.vectorise();

            float cost = vehicle.cost();
            vehicle.actions.limRows().print( cost );
            costs.push( Pt2f( costs.n() , cost ) );

            org_states.resize( vehicle.n() );
            vehicle.recreate( org_states );
            halt(100);
        }

        if( draw.keys.up   ) { disp( ++m ); halt(100); }
        if( draw.keys.down ) { disp( --m ); halt(100); }
    }

    return 0;
}






