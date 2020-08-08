
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/algorithms/gaussian_processes/models/gp_full.h>
#include <cvpp/algorithms/gaussian_processes/functions/mean/mean_zero.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov/cov_sqexp.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise/noise_stationary.h>

#include <cvpp/algorithms/bayes_opt/bayes_opt.h>
#include <cvpp/algorithms/bayes_opt/functions/acq/acq_variance.h>

using namespace cvpp;

int main()
{
    // GROUND TRUTH

    FullGP gt;

    gt.setMean( new MeanZero() );
    gt.setCov( new CovSqExp(ISO) );
    gt.setNoise( new NoiseStationary() );

    int n = 200;
    Matd Xtr( n , 2 ); Xtr.setRand( -2 , +2 );
    Matd Ytr = ( ( 4.0 * Xtr.c(0) ).sin() + ( 4.0 * Xtr.c(1) ).cos() ).addRand( 0.1 );
    gt.setXYtr( Xtr , Ytr );

    Vecd hyps( 3 ); hyps.eig() << 0.0 , 0.0 , 0.0 ;
    gt.setHyps( hyps );

    gt.options.verbose = false;
    gt.train();

    // BAYES OPTIMIZATION

    BayesOpt bo;

    bo.setMean( new MeanZero() );
    bo.setCov( new CovSqExp(ISO) );
    bo.setNoise( new NoiseStationary() );
    bo.setAcq( new AcqVariance() );

    Matd Xst( 1 , gt.d_in() ); Xst << 0.0 , 0.0 ;
    Matd Yst = gt.query( Xst );
    bo.prepare( Xst , Yst );

    Matd bnd( 2 , gt.d_in() ); bnd << -2.0 , -2.0 ,
                                      +2.0 , +2.0 ;
    bo.setBoundaries( bnd );

    Vecd bo_hyps( bo.n_bo_hyps() );
    bo_hyps.eig() << 1.0 ;
    bo.setBOhyps( bo_hyps );

    Vecd gp_hyps = gt.hyps();
    bo.setGPhyps( gp_hyps );

    bo.start();

    // DRAW

    Matd Xev = MatGrid2d( -2 , +2 , 0.1 );
    gt.query( Xev ); bo.query( Xev );

    CPPlot draw( "Window" , ULHW( 0 , 0 , 2 * 400 , 3 * 600 ) , 2 , 3 );
    draw[0].set3Dplot().setAxes( Xtr , Ytr , 0.0 , 0.0 , 0.1 );
    draw[1].set3Dplot().setAxes( Xtr , Ytr , 0.0 , 0.0 , 0.1 );
    draw[3].set3Dplot().setAxes( Xtr , Ytr , 0.0 , 0.0 , 0.1 );
    draw[4].set3Dplot().setAxes( Xtr , Ytr , 0.0 , 0.0 , 0.1 );
    draw[2].set2Dplot().setTitle( "Decrease in error values" );
    draw[5].set2Dplot().setTitle( "Decrease in variance values" );

    unsigned buf_tr = draw.addBuffer3D( Xtr , Ytr );

    unsigned buf_mf1 = draw.addBuffer3D(  Xev , gt.mf   );
    unsigned buf_mf2  = draw.addBuffer3D( Xev , bo.mf() );

    unsigned buf_vf1 = draw.addBuffer3D(  Xev , gt.vf   );
    unsigned buf_vf2  = draw.addBuffer3D( Xev , bo.vf() );

    unsigned buf_idx = draw.addBufferIDXgrid( Xev );

    unsigned buf_mc1 = draw.addBufferRGBjet( gt.mf   );
    unsigned buf_mc2 = draw.addBufferRGBjet( bo.mf() );

    unsigned buf_vc1 = draw.addBufferRGBjet( gt.vf   );
    unsigned buf_vc2 = draw.addBufferRGBjet( bo.vf() );

    Pts2f errs,vars;
    errs.push( Pt2f( errs.n() , ( bo.mf() - gt.mf ).rsqsum() ) );
    vars.push( Pt2f( vars.n() , bo.vf().sum() ) );

    while( draw.input() )
    {
        draw[0].clear().axes();
        draw.psc(5,BLA).pts3D( buf_tr );
        draw.wgrid3D( buf_mf1 , buf_idx , buf_mc1 );

        draw[1].clear().axes();
        draw.psc(5,BLA).pts3D( bo.Xtr() , bo.Ytr()  );
        draw.wgrid3D( buf_mf2 , buf_idx , buf_mc2 );

        draw[3].clear().axes();
        draw.wgrid3D( buf_vf1 , buf_idx , buf_vc1 );

        draw[4].clear().axes();
        draw.wgrid3D( buf_vf2 , buf_idx , buf_vc2 );

        if( errs.n() > 1 )
        {
            draw[2].clear().axes( 0 , errs.n() - 1 , 0 , errs.mat().c(1).max() );
            draw.lwc(4,RED).line2D( errs );
        }

        if( vars.n() > 1 )
        {
            draw[5].clear().axes( 0 , vars.n() - 1 , 0 , vars.mat().c(1).max() );
            draw.lwc(4,RED).line2D( vars );
        }

        draw.updateWindow(30);
        halt(500);

//        if( draw.keys.enter )
//        {
            Matd Xadd = bo.search( 50 );
            Matd Yadd = gt.query( Xadd );

            bo.insert( Xadd , Yadd ).query( Xev );

            draw.updBuffer3D( buf_mf2  , Xev , bo.mf()  );
            draw.updBuffer3D( buf_mc2 , bo.mf().toRGBjet() );

            draw.updBuffer3D( buf_vf2  , Xev , bo.vf()  );
            draw.updBufferRGBjet( buf_vc2 , bo.vf() );

            gt.query( Xev );
            errs.push( Pt2f( errs.n() , ( bo.mf() - gt.mf ).rsqsum() ) );
            vars.push( Pt2f( vars.n() , bo.vf().sum() ) );

//            halt(100);
//        }
    }

	return 0;
}
