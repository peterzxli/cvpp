
#include <cvpp/algorithms/gaussian_processes/models/gp_varhetero.h>

#include <cvpp/algorithms/gaussian_processes/functions/mean/mean_zero.h>
#include <cvpp/algorithms/gaussian_processes/functions/mean/mean_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise/noise_zero.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise/noise_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov/cov_sqexp.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // LOAD DATA

    unsigned d = atoi( argv[1] );

    Matd Xtr( "../data/hetero_Xtr_" , d );
    Matd Ytr( "../data/hetero_Ytr_" , d );
    Matd Xev( "../data/hetero_Xev_" , d );

    // CREATE GP

    VarHeteroGP gp;

    // SET FUNCTIONS

    gp.setFMean( new MeanZero() );
    gp.setFNoise( new NoiseZero() );
    gp.setFCov( new CovSqExp(ISO) );

    gp.setGMean( new MeanZero() );
    gp.setGNoise( new NoiseStationary() );
    gp.setGCov( new CovSqExp(ISO) );

    // SET OPTIONS

    gp.options.draw_type = INPUT;
    gp.options.draw_3D_view = TOPVIEW;
    gp.options.draw_wire = false;

    gp.options.optimizer = GRADIENT;
    gp.options.error_metric = RMSE;

    // UPLOAD DATA TO GP

    gp.setXYtr( Xtr , Ytr );
    gp.setXev( Xev );

    // SET HYPERPARAMETERS AND CLAMPS

    Vecd hyps( gp.n_hyps() );
    Matd Mvar( gp.d_mvar() ) , Svar( gp.d_svar() );

    switch( d )
    {
    case 1:

        hyps.eig() << 1.5 , 5.0 , 1.5 , 0 , 0 ;
        Mvar = 1.0; Svar = log( 0.5 );

        break;

    case 2:

        hyps.eig() << -1.5 , -4.0 , -1.5 , 0 , -1.5 ;
        Mvar = -8.0; Svar = log( 0.5 );

        break;
    }

    Veci clamps( gp.n_hyps() );
    clamps.setVal( 0 );

    gp.setHyps( hyps ).setClamps( clamps );
    gp.setMSvar( Mvar , Svar );

    // TRAIN

    gp.train();

    // SANITY CHECK

    if( gp.lmls().n() >= 10 )
    {
        if( d == 1 ) disp( "Sanity Check" , gp.lmls()[9].y ,  775.14277 );
        if( d == 2 ) disp( "Sanity Check" , gp.lmls()[9].y , -370.24719 );
    }

    // FINALIZE

    return 0;
}
