
#include <cvpp/algorithms/gaussian_processes/models/gp_bigdata.h>

#include <cvpp/algorithms/gaussian_processes/functions/mean/mean_zero.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise/noise_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov/cov_sqexp.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // LOAD DATA

    unsigned d = atoi( argv[1] );

    Matd Xtr( "../data/demo_Xtr_" , d );
    Matd Ytr( "../data/demo_Ytr_" , d );
    Matd Ztr( "../data/demo_Ztr_" , d );
    Matd Xev( "../data/demo_Xev_" , d );
    Matd Yev( "../data/demo_Yev_" , d );

    // CREATE GP

    BigDataGP gp;

    // SET FUNCTIONS

    gp.setMean(  new MeanZero() );
    gp.setNoise( new NoiseStationary() );
    gp.setCov( new CovSqExp(ISO) );

    // SET OPTIONS

    gp.options.draw_type = INPUT;
    gp.options.optimizer = STOCHASTIC;
    gp.options.error_metric = RMSE;

    gp.options.max_evaluation = 1000;
    gp.options.jitter = 1e-4;

    gp.options.epoch_hyp =  5;
    gp.options.epoch_ind = -1;
    gp.options.epoch_var =  0;

    // UPLOAD DATA TO GP

    gp.setXYZtr( Xtr , Ytr , Ztr );
    gp.setXYev( Xev , Yev );

    // SET HYPERPARAMETERS AND CLAMPS

    Vecd hyps( gp.n_hyps() ); hyps.setRand(1).sub(2);
    Veci clamps( gp.n_hyps() ); clamps.setVal(0);
    gp.setHyps( hyps ).setClamps( clamps );

    Matd Mvar( gp.d_mvar() ); Mvar.setVal( 0 );
    Matd Svar( gp.d_svar() ); Svar.setIdentity( 0.1 );
    gp.setMSvar( Mvar , Svar );

    // TRAIN

    gp.setBatchSize( 200 );
    gp.train();

    // SANITY CHECK

    if( gp.lmls().n() >= 10 )
    {
        if( d == 1 ) disp( "Sanity Check" , gp.lmls()[9].y , 985.81333 );
        if( d == 2 ) disp( "Sanity Check" , gp.lmls()[9].y , 764.54514 );
    }

    // FINALIZE

    return 0;
}
