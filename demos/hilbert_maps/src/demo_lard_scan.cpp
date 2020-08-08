
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/hilbert_maps/lard/hm_lard.h>
#include <cvpp/algorithms/hilbert_maps/lard/feats/hm_lard_feat_sqexp.h>
#include <cvpp/algorithms/hilbert_maps/lard/regrs/hm_lard_regr_logistic.h>

#include <cvpp/algorithms/marching_cubes/marching3D.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // NUMBER OF CLUSTERS AND NEIGHBOURS

    unsigned m = 1000 , k = 5 ;

    // QUERY RESOLUTION

    double r = 0.1;

    // LOAD DATA

    Matd scan( "../data/scan_input" );
    Matd pts = scan.cr(3).AddRand( 0.1 ).clone();

    // CALCULATE CLUSTERS

    Matd ctr; Mati lbl;
    pts.kmeans( 1500 , ctr , lbl );

    // CALCULATE CLUSTER INFORMATION

    SeqMatd clouds , means , covs ;
    pts.mcovRows( lbl , clouds , means , covs );

    // CREATE HILBERT MAP

    HMlard hm( new HMfeatSqExp( k ) ,
               new HMregrLogistic( 0.5 ) );

    // CREATE DATASET

    Matd Xtr , Ytr;
    scan.makeScanset( Xtr , Ytr , 3.0 , 0.1 , 2 , 0.8 );

    // TRAIN HILBERT MAP

    hm.add( ctr , covs ).train( Xtr , Ytr );

    // QUERY HILBERT MAP

    Matd Xte = MatGrid3d( pts.limRows( 0.1 ) , r );
    Matd Yte = hm.query( Xte );

    // SANITY CHECK

    disp( "Sanity Check" , hm.weights().sum() , 6512.82 );
    disp( "Sanity Check" , Yte.sum() , 251853 );

    // CREATE ISOSURFACE

    Matd srf = marching3D( Xte , Yte , 0.5 );

    // SET PLOT INTERFACE

    CPPlot draw("Window");
    draw[0].set3Dworld().setViewer( 9.25611 , -15.7120 , 10.4006 ,
                                    8.88789 , -14.9852 , 9.82077 );

    // CREATE BUFFERS

    unsigned buf_occ = draw.addBuffer( Xtr.sr( Ytr == 1 ) );
    unsigned buf_fre = draw.addBuffer( Xtr.sr( Ytr == 0 ) );

    unsigned buf_ctr = draw.addBuffer( ctr );
    unsigned buf_srf = draw.addBuffer( srf );

    // DRAW

    unsigned show = 0;
    while( draw.input() )
    {
        draw[0].clear();

        draw.pushMatrix();
        draw.rotateX( 90 );

        switch( show )
        {
        case 0: // DATASET

            draw.psc(1,RED).pts3D( buf_occ );
            draw.psc(1,GRE).pts3D( buf_fre );

            break;

        case 1: // CLUSTERS

            draw.psc(2,MAG).pts3D( buf_ctr );

            break;

        case 2: // ISOSURFACE

            draw.clr(BLU).wsurf3D( buf_srf );

            break;
        }

        draw.popMatrix();
        draw.updateWindow(30);

        if( draw.keys.enter )
            show = ++show % 3 , halt(100) ;
    }

    return 0;
}
