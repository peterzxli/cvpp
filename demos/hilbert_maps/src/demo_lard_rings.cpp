
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/hilbert_maps/lard/hm_lard.h>
#include <cvpp/algorithms/hilbert_maps/lard/feats/hm_lard_feat_sqexp.h>
#include <cvpp/algorithms/hilbert_maps/lard/regrs/hm_lard_regr_logistic.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    Matd Xtr( "../data/rings_X" );
    Matd Ytr( "../data/rings_Y" );

    Mati ridx( Xtr.r() ); ridx.setIncrease().ShuffleRows();
    Xtr.SampleRows( ridx ); Ytr.SampleRows( ridx );

    Matd Ztr = MatGrid2d( Xtr.limRows( 0.5 ) , 0.20 );
    Matd Xte = MatGrid2d( Xtr.limRows( 0.5 ) , 0.05 );

    SeqMatd Str( Ztr.r() );
    forLOOPi( Ztr.r() ) Str[i] = MatIDTYd( 2 , 0.005 );

    HMlard hm( new HMfeatSqExp( 5 ) ,
               new HMregrLogistic( 0.9 ) );

    hm.add( Ztr , Str ).train( Xtr , Ytr );
    Matd Yte = hm.query( Xte );

    disp( "Sanity Check" , hm.weights().sum() , -0.25691 );
    disp( "Sanity Check" , Yte.sum() , 1723.58 );

    CPPlot draw("Window");
    draw[0].set2Dplot().setAxes( Xte ).setTitle( "LARD-HM Binary Classification" );

    unsigned buf_pts = draw.addBuffer2D( Xtr );
    unsigned buf_lbl = draw.addBufferRGBlbl( Ytr + 4 );
    unsigned buf_ctr = draw.addBuffer2D( Ztr );

    unsigned buf_grd = draw.addBuffer2D( Xte );
    unsigned buf_idx = draw.addBufferIDXgrid( Xte );
    unsigned buf_clr = draw.addBufferRGBjet( Yte );

    int show = 0;
    while( draw.input() )
    {
        draw[0].clear().axes();

        draw.grid2D( buf_grd , buf_idx , buf_clr );

        switch( show )
        {
        case 0:

            draw.ps(4).pts2D( buf_pts , buf_lbl );

            break;

        case 1:

            draw.psc(6,MAG).pts2D( buf_ctr );
//            draw.clr(RED).ellipse2D( Ztr , Str );

            break;
        }

        draw.updateWindow(30);

        if( draw.keys.enter )
            show = ++show % 2 , halt(100);
    }

    return 0;
}


