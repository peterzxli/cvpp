
#include <cvpp/auxiliar/macros.h>
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

    double r = 0.05;

    // LOAD DATA

    Matd pts("../data/virtual_pts_01");
    Matd scan("../data/virtual_scan_01");

    // CALCULATE CLUSTERS

    Matd ctr; Mati lbl;
    pts.kmeans( m , ctr , lbl );

    // CALCULATE CLUSTER INFORMATION

    SeqMatd clouds,means,covs;
    pts.mcovRows( lbl , clouds , means , covs );

    // CREATE HILBERT MAP

    HMlard hm( new HMfeatSqExp( k ) ,
               new HMregrLogistic( 0.9 ) );

    // CREATE DATASET

    Matd Xtr , Ytr;
    hm.makeDataset( scan , Xtr , Ytr );

    // TRAIN HILBERT MAP

    hm.add( ctr , covs ); hm.train( Xtr , Ytr );

    // QUERY HILBERT MAP

    Matd Xte = MatGrid3d( pts.limRows( 0.1 ) , r );
    Matd Yte = hm.query( Xte );

    // SANITY CHECK

    disp( "Sanity Check" , hm.weights().sum() , 4971.45 );
    disp( "Sanity Check" , Yte.sum() , 143783 );

    // CREATE ISOSURFACE

    Matd srf = marching3D( Xte , Yte , 0.5 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window");
    draw.useScreen(0).set3Dworld().setViewer( -2.06671 , -3.15117 , 7.59169 ,
                                              -1.74380 , -2.61846 , 6.80942 );

    // CREATE BUFFERS

    unsigned buf_occ = draw.addBuffer3D( Xtr.sr( Ytr == 1 ) );
    unsigned buf_fre = draw.addBuffer3D( Xtr.sr( Ytr == 0 ) );

    unsigned buf_ctr = draw.addBuffer3D( ctr );
    unsigned buf_srf = draw.addBuffer3D( srf );

    // DRAW

    int show = 0;
    while( draw.input() )
    {
        draw[0].clear();

        switch( show )
        {
        case 0: // ISOSURFACE

            draw.color(BLU).wsurf3D( buf_srf );

            break;

        case 1: // DATASET

            draw.psc(1,RED).pts3D( buf_occ );
            draw.psc(1,GRE).pts3D( buf_fre );

            break;

        case 2: // CLUSTERS

            draw.psc(6,MAG).pts3D( buf_ctr );

            break;
        }

        draw.updateWindow(30);

        if( draw.keys.enter )
            show = ++show / 3 , halt(100);
    }

    return 0;
}
