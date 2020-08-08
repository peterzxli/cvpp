
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/hilbert_maps/dsgd/hm_dsgd.h>
#include <cvpp/algorithms/hilbert_maps/dsgd/regrs/hm_dsgd_regr_doubly.h>
#include <cvpp/algorithms/random_kitchen_sinks/feats/rks_feat_gaussian.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    Matd pts( "../data/rings_X" );
    Matd lbl( "../data/rings_Y" );

    Mati ridx( pts.r() ); ridx.setIncrease().ShuffleRows();
    pts.SampleRows( ridx ); lbl.SampleRows( ridx );

    Matd Xtr = pts.sampleRows( 0 , 2 ) , Xte = pts.sampleRows( 1 , 2 );
    Matd Ytr = lbl.sampleRows( 0 , 2 ) , Yte = lbl.sampleRows( 1 , 2 );

    HMdsgd dsgd( new HMregrDoubly , new RKSfeatGaussian );
    dsgd.setData( pts , lbl );

    dsgd.setParams( 10.0 , 1e-5 , 1.0 , 1e-4 , 300 , 300 , 100 );

    dsgd.train();

    Matd Xgr = MatGrid2d( pts.limRows( 0.5 ) , 0.05 );
    Matd Ygr = dsgd.query( Xgr );

    disp( "Sanity Check" , dsgd.weights().absum() , 3761.53 );
    disp( "Sanity Check" , Ygr.absum() , 56494.9 );

    Matd clr = Ygr.c(0).clone();
    clr.Floor(-1).Ceil(+1).mlt(-1.0);

    CPPlot draw("Window");
    draw[0].set2Dplot().setAxes( Xgr ).setTitle( "DSGD Binary Classification" );

    unsigned buf_Xtr = draw.addBuffer2D( Xtr );
    unsigned buf_Ytr = draw.addBufferRGBlbl( Ytr + 4 );

    unsigned buf_Xte = draw.addBuffer2D( Xte );
    unsigned buf_Yte = draw.addBufferRGBlbl( Yte + 4 );

    unsigned buf_Xgr = draw.addBuffer2D( Xgr );
    unsigned buf_Igr = draw.addBufferIDXgrid( Xgr );
    unsigned buf_Ygr = draw.addBufferRGBjet( clr );

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


