
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

    double r = 0.1;

    // LOAD DATA

    Matd scan("../data/rosest.dat"); scan.cr(3).AddRand( r );
    Matd pts = scan.cr(3).clone();

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

    hm.add( ctr , covs ).train( Xtr , Ytr );

    // QUERY HILBERT MAP

    Matd Xte = MatGrid3d( pts.limRows( 0.1 ) , r );
    Matd Yte = hm.query( Xte );

    // SANITY CHECK

    disp( "Sanity Check" , hm.weights().sum() , 5939.85 );
    disp( "Sanity Check" , Yte.sum() / 1e3 , 1958.03 );

    // CREATE ISOSURFACE

    Matd srf = marching3D( Xte , Yte , 0.5 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window");
    draw.useScreen(0).set3Dworld().setViewer( -13.0430 , 5.85078 , 6.76949 ,
                                              -12.2406 , 5.26825 , 6.64000 );

    // CREATE BUFFERS

    unsigned buf_pts = draw.addBuffer3D( pts );
    unsigned buf_ctr = draw.addBuffer3D( ctr );
    unsigned buf_srf = draw.addBuffer3D( srf );

    // DRAW

    bool show = true;
    while( draw.input() )
    {
        draw[0].clear();

        if( show ) // ISOSURFACE
        {
            draw.color(BLU).wsurf3D( buf_srf );
        }
        else // DATASET + CLUSTERS
        {
            draw.psc(2,WHI).pts3D( buf_pts );
            draw.psc(6,MAG).pts3D( buf_ctr );
        }

        draw.updateWindow(30);

        if( draw.keys.enter )
            show = !show , halt(100);
    }

    return 0;
}
