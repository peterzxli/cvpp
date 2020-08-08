
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/doubly_stochastic/dsgd_original.h>
#include <cvpp/algorithms/random_kitchen_sinks/feats/rks_feat_gaussian.h>
#include <cvpp/algorithms/marching_cubes/marching3D.h>

using namespace cvpp;

int main()
{
    // LOAD DATA

    Matd scan( "../data/virtual_scan_01" );

    // MAKE DATASET

    Matd X,Y;
    scan.makeSCANdataset( X , Y );

    Mati rnd( X.r() ); rnd.setIncrease().ShuffleRows();
    X.SampleRows( rnd ); Y.SampleRows( rnd );

    // TRAIN DOUBLY STOCHASTIC CODE

    DSGDoriginal dblstoc( new RKSfeatGaussian );
    dblstoc.setData( X , Y );
    dblstoc.setParams( 0.1 , 1e-5 , 1 , 1e-4 , pow( 2 , 13 ) , pow( 2 , 7 ) , 10000 );
    dblstoc.train();

    // QUERY DOUBLY STOCHASTIC CODE

    Matd grd = MatGrid3d( X.limRows( 0.3 ) , 0.1 );
    Matd qry = dblstoc.query( grd ).c(0).clone();

    // SANITY CHECK

    disp( "Sanity Check" , dblstoc.weights().sum() , -20.1605 );
    disp( "Sanity Check" , qry.sum() , -477818 );

    // CREATE ISOSURFACE

    Matd srf = marching3D( grd , qry , 0.0 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window");
    draw[0].set3Dworld().setViewer( -2.06671 , -3.15117 , 7.59169 ,
                                    -1.74380 , -2.61846 , 6.80942 );

    // CREATE BUFFERS

    unsigned buf_Xfr = draw.addBuffer3D( X.sr( Y == 0 ) );
    unsigned buf_Xoc = draw.addBuffer3D( X.sr( Y == 1 ) );
    unsigned buf_srf = draw.addBuffer3D( srf );

    // DRAW

    unsigned show = 0;
    while( draw.input() )
    {
        draw[0].clear();

        switch( show )
        {
        case 0: // ALL

            draw.psc(1,WHI).pts3D( buf_Xoc );
            draw.psc(1,GRE).pts3D( buf_Xfr );
            draw.clr(BLU).wsurf3D( buf_srf );

            break;

        case 1: // DATASET

            draw.psc(1,WHI).pts3D( buf_Xoc );
            draw.psc(1,GRE).pts3D( buf_Xfr );

            break;

        case 2: // ISOSURFACE

            draw.clr(BLU).wsurf3D( buf_srf );

            break;


        }

        if( draw.keys.enter )
            show = ++show % 3 , halt(100);

        draw.updateWindow(30);
    }

    return 0;
}
