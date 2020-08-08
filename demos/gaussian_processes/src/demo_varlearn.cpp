
#include <cvpp/algorithms/gaussian_processes/models/gp_varlearn.h>

#include <cvpp/algorithms/gaussian_processes/functions/mean/mean_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise/noise_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov/cov_sqexp.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // LOAD DATA

    unsigned d = atoi( argv[1] );

    Matd Xtr( "../data/demo_Xtr_" , d );
    Matd Ytr( "../data/demo_Ytr_" , d );
    Matd Ztr( "../data/demo_Ztr_" , d ); Ztr /= 2.0;
    Matd Xev( "../data/demo_Xev_" , d );
    Matd Yev( "../data/demo_Yev_" , d );

    // CREATE GP

    VarLearnGP gp;

    // SET FUNCTIONS

    gp.setMean(  new MeanStationary() );
    gp.setNoise( new NoiseStationary() );
    gp.setCov( new CovSqExp(ISO) );

    // SET OPTIONS

    gp.options.draw_type = INPUT;
    gp.options.optimizer = NUMERIC;
    gp.options.error_metric = RMSE;

    // UPLOAD DATA TO GP

    gp.setXYZtr( Xtr , Ytr , Ztr );
    gp.setXYev( Xev , Yev );

    // SET HYPERPARAMETERS AND CLAMPS

    Vecd hyps( gp.n_hyps() ); hyps.setRand(1);
    Veci clamps( gp.n_hyps() ); clamps.setVal(0);
    gp.setHyps( hyps ).setClamps( clamps );

    // TRAIN

    gp.train();

    // SANITY CHECK

    if( gp.lmls().n() >= 10 )
    {
        if( d == 1 ) disp( "Sanity Check" , gp.lmls()[9].y , 661.44387 );
        if( d == 2 ) disp( "Sanity Check" , gp.lmls()[9].y , 509.18560 );
    }

    // FINALIZE

    return 0;
}
