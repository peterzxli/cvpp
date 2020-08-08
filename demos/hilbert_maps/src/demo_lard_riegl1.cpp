
#include <cvpp/auxiliar/macros.h>
#include <cvpp/auxiliar/timer.h>

#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/hilbert_maps/lard/hm_lard.h>
#include <cvpp/algorithms/hilbert_maps/lard/feats/hm_lard_feat_sqexp.h>
#include <cvpp/algorithms/hilbert_maps/lard/regrs/hm_lard_regr_logistic.h>

#include <cvpp/algorithms/marching_cubes/marching3D.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // NUMBER OF CLUSTERS , NEIGHBOURS AND SAMPLING

    unsigned m = 1000 , k = 3 , s = 5 ;

    // QUERY RESOLUTION

    double r = 0.05;

    // LOAD DATA

    Matd pts( "../data/riegl1_pts" ); pts.SampleRows( s ).AddRand( 0.05 );
    Matd clr( "../data/riegl1_clr" ); clr.SampleRows( s );

    Matd scan = Mat13d( 0 , 0 , 0 ) & pts;

    // CALCULATE CLUSTERS

    Matd ctr; Mati lbl;
    pts.kmeans( m , ctr , lbl );

    // CALCULATE CLUSTER INFORMATION

    SeqMatd clouds,means,covs;
    pts.mcovRows( lbl , clouds , means , covs );

    // CREATE HILBERT MAP

    HMlard hm( new HMfeatSqExp( k ) ,
               new HMregrLogistic( 0.5 ) );

    // CREATE DATASET

    Matd Xtr , Ytr;
    hm.makeDataset( scan , Xtr , Ytr );

    // TRAIN HILBERT MAP

    hm.add( ctr , covs ).train( Xtr , Ytr );

    // QUERY HILBERT MAP

    Matd Xte = MatGrid3d( pts.limRows( 0.1 ) , r );
    Matd Yte = hm.query( Xte );

    // SANITY CHECK

    disp( "Sanity Check" , hm.weights().sum() , 7192.36 );
    disp( "Sanity Check" , Yte.sum() / 1e3 , 2507.24 );

    // CREATE ISOSURFACE

    Matd srf = marching3D( Xte , Yte , 0.5 );

    // CREATE PLOT INTERFACE

    CPPlot draw( "Window" );
    draw[0].set3Dworld().setViewer( -6.83803 , -11.9944 , 5.06121 ,
                                    -6.47722 , -11.0936 , 4.81936 );

    // CREATE BUFFERS

    unsigned buf_pts = draw.addBuffer3D( pts );
    unsigned buf_clr = draw.addBuffer3D( clr );
    unsigned buf_ctr = draw.addBuffer3D( ctr );

    unsigned buf_srf = draw.addBuffer3D( srf );
    unsigned buf_tex = draw.addBufferRGBknn( srf , pts , clr );

    // DRAW

    bool show = true;
    while( draw.input() )
    {
        draw[0].clear();

        if( show ) // ISOSURFACE
        {
            draw.wsurf3D( buf_srf , buf_tex );
        }
        else // DATASET + CLUSTERS
        {
            draw.ps(1).pts3D( buf_pts , buf_clr );
            draw.psc(8,MAG).pts3D( buf_ctr );
        }

        draw.updateWindow(30);

        if( draw.keys.space )
            show = !show , halt(100);
    }


    return 0;
}
