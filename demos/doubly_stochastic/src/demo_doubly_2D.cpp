
#include <iostream>
#include <fstream>
#include <random>

#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/doubly_stochastic/dsgd_original.h>
#include <cvpp/algorithms/random_kitchen_sinks/feats/rks_feat_gaussian.h>

using namespace cvpp;

int main()
{
    // LOAD DATA

    Matd pts( "../data/rings_X" );
    Matd lbl( "../data/rings_Y" );

    Mati ridx( pts.r() ); ridx.setIncrease().ShuffleRows();
    pts.SampleRows( ridx ); lbl.SampleRows( ridx );

    Matd Xtr = pts.sampleRows( 0 , 2 ) , Xte = pts.sampleRows( 1 , 2 );
    Matd Ytr = lbl.sampleRows( 0 , 2 ) , Yte = lbl.sampleRows( 1 , 2 );

    // TRAIN DOUBLY STOCHASTIC CODE

    DSGDoriginal dblstoc( new RKSfeatGaussian );
    dblstoc.setData( pts , lbl );
    dblstoc.setParams( 10.0 , 1e-5 , 1.0 , 1e-4 , pow( 2 , 12 ) , pow( 2 , 6 ) , 250 );
    dblstoc.train();

    // QUERY DOUBLY STOCHASTIC CODE

    Matd Xgr = MatGrid2d( pts.limRows( 0.5 ) , 0.05 );
    Matd Ygr = dblstoc.query( Xgr );

    Matd clr = Ygr.c(0).clone();
    clr.Floor(-1).Ceil(+1).mlt(-1.0);

    // SANITY CHECK

    disp( "Sanity Check" , dblstoc.weights().absum() , 6978.61 );
    disp( "Sanity Check" , Ygr.absum() , 65840.9 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window");
    draw[0].set2Dplot().setAxes( Xgr ).setTitle( "Doubly Stochastic Binary Classification" );

    // CREATE BUFFERS

    unsigned buf_Xtr = draw.addBuffer2D( Xtr );
    unsigned buf_Ytr = draw.addBufferRGBlbl( Ytr + 4 );

    unsigned buf_Xte = draw.addBuffer2D( Xte );
    unsigned buf_Yte = draw.addBufferRGBlbl( Yte + 4 );

    unsigned buf_Xgr = draw.addBuffer2D( Xgr );
    unsigned buf_Igr = draw.addBufferIDXgrid( Xgr );
    unsigned buf_Ygr = draw.addBufferRGBjet( clr );

    // DRAW

    while( draw.input() )
    {
        draw[0].clear().axes();

        draw.grid2D( buf_Xgr , buf_Igr , buf_Ygr );
        draw.ps(4).pts2D( buf_Xtr , buf_Ytr );
        draw.ps(4).pts2D( buf_Xte , buf_Yte );

        draw.updateWindow();
    }

    return 0;
}
