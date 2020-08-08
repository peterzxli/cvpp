
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/marching_cubes/marching3D.h>

#include <cvpp/algorithms/hilbert_maps/dsgd/hm_dsgd.h>
#include <cvpp/algorithms/hilbert_maps/dsgd/regrs/hm_dsgd_regr_doubly.h>
#include <cvpp/algorithms/random_kitchen_sinks/feats/rks_feat_gaussian.h>

using namespace cvpp;

int main()
{
    Matd scan( "../data/virtual_scan_01" );

    Matd Xtr,Ytr;
    scan.makeSCANdataset( Xtr , Ytr );

    Mati rnd( Xtr.r() ); rnd.setIncrease().ShuffleRows();
    Xtr.SampleRows( rnd ); Ytr.SampleRows( rnd );

    HMdsgd hm( new HMregrDoubly , new RKSfeatGaussian );
    hm.setData( Xtr , Ytr );

    hm.setParams( 0.1 , 0 , 1.0 , 1e-4 , 2000 , 500 , 10000 );

    hm.train();

    Matd Xte = MatGrid3d( Xtr.limRows( 0.3 ) , 0.1 );
    Matd Yte = hm.query( Xte ).c(0).clone();

    disp( "Sanity Check" , hm.weights().absum() , 30927.4 );
    disp( "Sanity Check" , Yte.sum() , -866379 );

    Matd srf = marching3D( Xte , Yte , 0.0 );

    CPPlot draw("Window");
    draw[0].set3Dworld().setViewer( -2.06671 , -3.15117 , 7.59169 ,
                                    -1.74380 , -2.61846 , 6.80942 );

    unsigned buf_Xfr = draw.addBuffer3D( Xtr.sr( Ytr == 0 ) );
    unsigned buf_Xoc = draw.addBuffer3D( Xtr.sr( Ytr == 1 ) );
    unsigned buf_srf = draw.addBuffer3D( srf );

    while( draw.input() )
    {
        draw[0].clear();

        draw.psc(1,WHI).pts3D( buf_Xoc );
        draw.psc(1,GRE).pts3D( buf_Xfr );
        draw.clr(BLU).wsurf3D( buf_srf );

        draw.updateWindow(30);
    }

    return 0;
}
