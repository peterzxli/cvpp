
#include "./track/track.h"
#include "./vehicle/vehicle.h"

#include <cvpp/interfaces/cpplot.h>

using namespace cvpp;

int main()
{
    Track track( "../data/track.png" , 0.2 );
    Vehicle vehicle( "../data/traj.txt" , 0.4 , 0.2 );

    vehicle.setType( "TIME" );
    vehicle.setTrack( track );

    Vec5d org_states = vehicle.getStates().clone();
    vehicle.recreate( org_states );

    Matd grid = MatGrid2d( track.getDims() , 0.2 );

    Matd vals( grid.r() );
    forLOOPi( vals.r() )
        vals(i) = track.getVal( grid(i,0) , grid(i,1) );

    CPPlot draw( "Window" , ULHW( 2 * 400 , 3 * 600 ) , 2 , 3 );
    draw[0].set2Dplot().setAxes( grid );
    draw[1].set2Dplot().setTitle( "Linear acceleration during race" );
    draw[2].set2Dplot().setTitle( "Linear velocity during race" );
    draw[3].set2Dplot().setTitle( "Cost value over iterations" );
    draw[4].set2Dplot().setTitle( "Angular acceleration during race" );
    draw[5].set2Dplot().setTitle( "Angular velocity during race" );

    int buf_grd = draw.addBuffer2D( grid );
    int buf_idx = draw.addBufferIDXgrid( grid );
    int buf_val = draw.addBufferGRAYjet( vals );

    int m = 20;

    Pts2f costs;
    costs.push( Pt2f( 0 , vehicle.cost() ) );
    double prev = costs[-1].y;

    int cnt = 0;
    while( draw.input() )
    {
        draw[0].clear().axes();

        draw.grid2D( buf_grd , buf_idx , buf_val );

        vehicle.drawStates( draw , org_states , BLU , BLU , 8 );
        vehicle.drawStates( draw , GRE , RED , 6 );

        draw[3].clear();

        if( costs.n() > 1 )
        {
            draw.setAxes( costs ).axes();
            draw.lwc(3,BLA).line2D( costs );
        }

        Matd t = vehicle.getActions().c(0).cumsumRows();

        draw[1].clear();
        Matd alin( vehicle.getNumActions() , 2 );
        alin.c(0) = t; alin.c(1) = vehicle.getActions().c(1);
        draw.setAxes( alin ).axes().lwc(3,BLA).line2D( alin );

        draw[4].clear();
        Matd aang( vehicle.getNumActions() , 2 );
        aang.c(0) = t; aang.c(1) = vehicle.getActions().c(2);
        draw.setAxes( aang ).axes().lwc(3,BLA).line2D( aang );

        draw[2].clear();
        Matd vlin( vehicle.getNumStates() , 2 );
        vlin.c(0).setIncrease(); vlin.c(1) = vehicle.getStates().c(3);
        draw.setAxes( vlin ).axes().lwc(3,BLA).line2D( vlin );

        draw[5].clear();
        Matd vang( vehicle.getNumStates() , 2 );
        vang.c(0).setIncrease(); vang.c(1) = vehicle.getStates().c(4);
        draw.setAxes( vang ).axes().lwc(3,BLA).line2D( vang );

        draw.updateWindow(30);

        vehicle.minimise( m );
        org_states.resize( vehicle.getNumStates() );
        vehicle.recreate( org_states );

        costs.push( Pt2f( costs.n() , vehicle.cost() ) );
        disp( costs[-1].y , vehicle.getActions().n() , m );
        double curr = costs[-1].y;

        if( curr == prev ) { cnt++; }
        else { cnt = 0; prev = curr; }
        if( cnt == 10 ) { cnt = 0; m -= 2; }

        if( m == 0 )
        {
            m = 20;
//            disp( "DONE" );
//            vehicle.getStates().save( "states" );
//            vehicle.getActions().save( "actions" );
//            costs.save( "costs" );
//            halt();
        }

//        if( draw.keys.enter )
//        {
//            vehicle.minimise( m );
//            org_states.resize( vehicle.getNumStates() );
//            vehicle.recreate( org_states );

//            costs.push( Pt2f( costs.n() , vehicle.cost() ) );
//            disp( costs[-1].y , vehicle.getActions().n() );
//            halt(100);
//        }

        if( draw.keys.up   ) { disp( ++m ); halt(100); }
        if( draw.keys.down ) { disp( --m ); halt(100); }

        if( draw.keys.space )
        {
            vehicle.getStates().print();
            vehicle.getActions().print();
            halt(100);
        }
    }

    return 0;
}






