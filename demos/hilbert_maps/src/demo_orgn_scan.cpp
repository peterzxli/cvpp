
#include <cvpp/auxiliar/macros.h>
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/hilbert_maps/orgn/hm_orgn.h>
#include <cvpp/algorithms/hilbert_maps/orgn/feats/hm_orgn_feat_triangle.h>
#include <cvpp/algorithms/hilbert_maps/orgn/regrs/hm_orgn_regr_logistic.h>

#include <cvpp/algorithms/marching_cubes/marching3D.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // LOAD DATASET

    Matd Xtr( "../data/scan_Xtr" );
    Mati Ytr( "../data/scan_Ytr" );
    Matd scan( "../data/scan_input" );

    Matd pts = scan.cr(3).clone();
    Matd lim = pts.limRows( 2.0 );

    // CREATE HILBERT MAP

    HMorgn hm( new HMfeatTriangle( lim , 1.0 , 0.5 , 0.2 ) ,
               new HMregrLogistic( 0.1 , 0.5 , 0.001 ) );

    // TRAIN HILBERT MAP

    hm.train( Xtr , Ytr );

    // QUERY HILBERT MAP

    Matd Xte( "../data/scan_Xev" );
    Matd Yte = hm.query( Xte );

    // SANITY CHECK

    disp( "Sanity Check" , hm.weights().sum() , 51.2361 );
    disp( "Sanity Check" , Yte.sum() , 101270 );

    // CREATE ISOSURFACE

    Matd srf = marching3D( Xte , Yte , 0.5 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window");
    draw[0].set3Dworld().setViewer( 9.25611 , -15.7120 , 10.4006 ,
                                    8.88789 , -14.9852 , 9.82077 );

    // CREATE BUFFERS

    unsigned buf_occ = draw.addBuffer3D( Xtr.sr( Ytr == 1 ) );
    unsigned buf_fre = draw.addBuffer3D( Xtr.sr( Ytr == 0 ) );

    unsigned buf_pts = draw.addBuffer3D( Xte.sr( Yte > 0.5 ) );
    unsigned buf_tex = draw.addBufferRGBjet( Yte.sr( Yte > 0.5 ) );

    unsigned buf_srf = draw.addBuffer3D( srf );

    // DRAW

    int show = 0;
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

        case 1: // CLASSIFIED POINTS

            draw.ps(2).pts3D( buf_pts , buf_tex );

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
