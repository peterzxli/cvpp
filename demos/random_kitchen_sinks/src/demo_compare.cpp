
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov/cov_sqexp.h>

#include <cvpp/algorithms/random_kitchen_sinks/models/rks_original.h>
#include <cvpp/algorithms/random_kitchen_sinks/models/rks_fastfood.h>
#include <cvpp/algorithms/random_kitchen_sinks/feats/rks_feat_gaussian.h>

using namespace cvpp;

int main()
{
    // LOAD DATA

    Matd Xtr( "../../gaussian_processes/data/demo_Xtr_1" );
    Matd Ytr( "../../gaussian_processes/data/demo_Ytr_1" );
    Matd Xev( "../../gaussian_processes/data/demo_Xev_1" );
    Matd Yev( "../../gaussian_processes/data/demo_Yev_1" );

    // START TIMER

    Timer t;

    // RKS ORIGINAL

    RKSoriginal rks( new RKSfeatGaussian() );
    Matd Yks = rks.train( Xtr , Ytr , 500 ).query( Xev );
    Matd Krks = rks.getK();

    t.ptick();

    // RKS FASTFOOD

    RKSfastfood ff( Xtr.c() , 250 , 1.0 );
    Matd Yff = ff.train( Xtr , Ytr ).query( Xev );
    Matd Krff = ff.getK();

    t.ptick();

    // GP SQUARED EXPONENTIAL

    CovSqExp cov;
    Vecd hyps(2); hyps.eig() << 0.0 , 0.0 ;
    Matd Kcov = cov.calcDense( Xtr , Xtr , hyps );

    t.ptick();

    // DRAW

    CPPlot draw("Window",2,2);
    draw[0].set2Dplot().setTitle("Mean"); draw[1].set2Dplot().setTitle("GP");
    draw[2].set2Dplot().setTitle("RKS"); draw[3].set2Dplot().setTitle("FF");

    unsigned buf_tr = draw.addBuffer2D( Xtr , Ytr );
    unsigned buf_ev = draw.addBuffer2D( Xev , Yev );
    unsigned buf_ks = draw.addBuffer2D( Xev , Yks );
    unsigned buf_ff = draw.addBuffer2D( Xev , Yff );

    Matd grid = MatGrid2d( Kcov );

    unsigned buf_grd = draw.addBuffer2D( grid );
    unsigned buf_idx = draw.addBufferIDXgrid( grid );
    unsigned buf_cgp = draw.addBufferRGBjet( Kcov.toCol() );
    unsigned buf_cks = draw.addBufferRGBjet( Krks.toCol() );
    unsigned buf_cff = draw.addBufferRGBjet( Krff.toCol() );

    while( draw.input() )
    {
        draw[0].clear().axes( buf_tr );
        draw.psc(5,BLA).pts2D( buf_tr );
        draw.lwc(3,BLA).line2D( buf_ev );
        draw.lwc(3,RED).line2D( buf_ks );
        draw.lwc(3,BLU).line2D( buf_ff );

        draw[1].clear().axes( grid );
        draw.grid2D( buf_grd , buf_idx , buf_cgp );
        draw[2].clear().axes( grid );
        draw.grid2D( buf_grd , buf_idx , buf_cks );
        draw[3].clear().axes( grid );
        draw.grid2D( buf_grd , buf_idx , buf_cff );

        draw.updateWindow(30);
    }

    return 0;
}

