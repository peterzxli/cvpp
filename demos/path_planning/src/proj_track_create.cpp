
#include "./track/track.h"
#include <cvpp/interfaces/cpplot.h>

using namespace cvpp;

int main()
{
    Track track( "track.png" , 0.2 );

    Matf grid = MatGrid2f( track.getDims() , 0.2 );

    Matf vals( grid.r() );
    forLOOPi( vals.r() )
        vals(i) = track.getVal( grid(i,0) , grid(i,1) );

    Pts2f traj;

    CPPlot draw( "Window" );
    draw[0].set2Dplot().setAxes( grid );

    int buf_grd = draw.addBuffer2D( grid );
    int buf_idx = draw.addBufferIDXgrid( grid );
    int buf_val = draw.addBufferGRAYjet( vals );

    bool store = false;

    while( draw.input() )
    {
        draw[0].clear();
        draw.grid2D( buf_grd , buf_idx , buf_val );
        draw.lwc( 2 , store ? RED : GRE ).line2D( traj );
        draw.axes();

        draw.updateWindow(30);

        if( draw.keys.space )
        {
            store = !store;
            if( !store ) traj.save( "traj" );
            halt(100);
        }

        if( store )
        {
            if( traj.empty() )
                traj.push( draw.mousePos() );
            else if( dist( draw.mousePos() , traj[-1] ) > 1.0 )
                traj.push( draw.mousePos() );
        }
    }

    return 0;
}






