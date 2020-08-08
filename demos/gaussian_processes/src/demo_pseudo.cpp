
#include <cvpp/algorithms/gaussian_processes/models/gp_pseudo.h>

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
    Matd Xev( "../data/demo_Xev_" , d );
    Matd Yev( "../data/demo_Yev_" , d );
    Matd Ztr( "../data/demo_Ztr_" , d ); Ztr.RemRows( Ztr.r() / 2 );

    // CREATE GP

    PseudoGP gp;

    gp.setMean(  new MeanStationary() );
    gp.setNoise( new NoiseStationary() );
    gp.setCov( new CovSqExp(ISO) );

    // SET HYPERPARAMETERS AND CLAMPS

    Vecd hyps( gp.n_hyps() ); hyps.eig() << 0 , 1.5 , 2.0 , -1 ;
    Veci clamps( gp.n_hyps() ); clamps.eig() << 1 , 0 , 0 , 0 ;

    // SET OPTIONS

    gp.options.draw_training = true;
    gp.options.training_type = NUMERIC;

    // UPLOAD DATA TO GP

    gp.setXYZtr( Xtr , Ytr , Ztr ).setXYev( Xev , Yev );
    gp.setHyps( hyps ).setClamps( clamps );

    // TRAIN

    gp.train();

    // FINALIZE

    return 0;
}
