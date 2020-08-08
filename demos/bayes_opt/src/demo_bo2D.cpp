
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

    int n = 100;
    Matd Xtr( n , 1 ); Xtr.setInterval( 0 , 10 );
    Matd Ytr = Xtr.sin().addRand( 0.1 );
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

    Matd Xst( gt.d_in() ); Xst << 5.0 ;
    Matd Yst = gt.query( Xst );
    bo.prepare( Xst , Yst );

    Matd bnd( 2 , gt.d_in() ); bnd << 0.0 , 10.0;
    bo.setBoundaries( bnd );

    Vecd bo_hyps( bo.n_bo_hyps() );
    bo_hyps.eig() << 1.0 ;
    bo.setBOhyps( bo_hyps );

    Vecd gp_hyps = gt.hyps();
    bo.setGPhyps( gp_hyps );

    bo.start();

    // DRAW

    Matd Xev( 5 * n , 1 );
    Xev.setInterval( 0 , 10 );
    gt.query( Xev ); bo.query( Xev );

    CPPlot draw( "Window" , ULHW( 0 , 0 , 2 * 400 , 3 * 600 ) , 2 , 3 );
    draw[0].set2Dplot().setAxes( Xtr , Ytr , 0.0 , 0.1 );
    draw[1].set2Dplot().setAxes( Xtr , Ytr , 0.0 , 0.1 );
    draw[3].set2Dplot().setAxes( Xev , gt.vf , 0.0 , 0.1 );
    draw[4].set2Dplot().setAxes( Xev , bo.vf() , 0.0 , 0.1 );
    draw[2].set2Dplot().setTitle( "Decrease in error values" );
    draw[5].set2Dplot().setTitle( "Decrease in variance values" );

    unsigned buf_mf1  = draw.addBuffer2D( Xev , gt.mf    );
    unsigned buf_mf2  = draw.addBuffer2D( Xev , bo.mf()  );

    unsigned buf_uvf1 = draw.addBuffer2D( Xev , gt.uvf() );
    unsigned buf_lvf1 = draw.addBuffer2D( Xev , gt.lvf() );

    unsigned buf_uvf2 = draw.addBuffer2D( Xev , bo.uvf() );
    unsigned buf_lvf2 = draw.addBuffer2D( Xev , bo.lvf() );

    unsigned buf_vf1 = draw.addBuffer2D( Xev , gt.vf   );
    unsigned buf_vf2 = draw.addBuffer2D( Xev , bo.vf() );

    Pts2f errs,vars;
    errs.push( Pt2f( errs.n() , ( bo.mf() - gt.mf ).rsqsum() ) );
    vars.push( Pt2f( vars.n() , bo.vf().sum() ) );

    while( draw.input() )
    {
        draw[0].clear().axes();

        draw.psc(5,BLA).pts2D( gt.Xtr() , gt.Ytr() );
        draw.lwc(3,RED).line2D( buf_mf1  );
        draw.lwc(3,BLU).line2D( buf_uvf1 );
        draw.lwc(3,BLU).line2D( buf_lvf1 );

        draw[1].clear().axes();

        draw.psc(5,BLA).pts2D( bo.Xtr() , bo.Ytr()  );
        draw.lwc(3,RED).line2D( buf_mf2  );
        draw.lwc(3,BLU).line2D( buf_uvf2 );
        draw.lwc(3,BLU).line2D( buf_lvf2 );

        draw[3].clear().axes();
        draw.lwc(3,BLU).line2D( buf_vf1 );

        draw[4].clear().axes();
        draw.lwc(3,BLU).line2D( buf_vf2 );

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

            draw.updBuffer2D( buf_mf2  ,  Xev   , bo.mf()  );
            draw.updBuffer2D( buf_uvf2 ,  Xev   , bo.uvf() );
            draw.updBuffer2D( buf_lvf2 ,  Xev   , bo.lvf() );

            draw.updBuffer2D( buf_vf2  , Xev , bo.vf()  );
            draw[4].setAxes( Xev , bo.vf() , 0.0 , 0.1 );

            gt.query( Xev );
            errs.push( Pt2f( errs.n() , ( bo.mf() - gt.mf ).rsqsum() ) );
            vars.push( Pt2f( vars.n() , bo.vf().sum() ) );

//            halt(100);
//        }
    }

	return 0;
}
