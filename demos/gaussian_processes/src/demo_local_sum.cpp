
#include <cvpp/algorithms/gaussian_processes/models/gp_local_sum.h>
#include <cvpp/algorithms/gaussian_processes/models/gp_full.h>

#include <cvpp/algorithms/gaussian_processes/functions/mean/mean_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise/noise_stationary.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov/cov_sqexp.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // SET NUMBER OF NEIGHBOURS

    unsigned k = 20 ;

    // LOAD DATA

    unsigned d = atoi( argv[1] );

    Matd Xtr( "../data/demo_Xtr_" , d );
    Matd Ytr( "../data/demo_Ytr_" , d );
    Matd Xev( "../data/demo_Xev_" , d );
    Matd Yev( "../data/demo_Yev_" , d );
    Matd Ztr( "../data/demo_Ztr_" , d ); Ztr.SampleRows( 2 );

    // CREATE GP

    LocalSumGP<FullGP> gp( k );

    // SET FUNCTIONS

    gp.setMean(  new MeanStationary() );
    gp.setNoise( new NoiseStationary() );
    gp.setCov( new CovSqExp(ISO) );

    // SET OPTIONS

    gp.options.draw_type = INPUT;
    gp.options.optimizer = NL_COBYLA;
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
        if( d == 1 ) disp( "Sanity Check" , gp.lmls()[9].y , -427.90794 );
        if( d == 2 ) disp( "Sanity Check" , gp.lmls()[9].y , -532.73305 );
    }

    // FINALIZE

    return 0;




//    // CHOOSE DATASET

////    String dataset = "synthetic" ; unsigned m = 500 , k = 50 , iter = 20;
//    String dataset = "riegl" ; unsigned m = 1000 , k =  50 , iter = 20;

//    // LOAD DATASET

//    Matd trn,tst;
//    trn.loadCSV( "../data/" + dataset + "_points_training.csv" );
//    tst.loadCSV( "../data/" + dataset + "_points_testing.csv"  );

//    // SEPARATE X AND Y

//    Matd Xtr = trn.cl(3).clone();
//    Matd Ytr = trn.cr(1).clone();

//    Matd Xev = tst.cl(3).clone();
//    Matd Yev = tst.cr(1).clone();

//    // CALCULATE CLUSTERS

//    Matd Ztr = Xtr.kmeansCTR( m );

//    // START GP

//    LocalSumGP<FullGP> gp( k );

//    gp.setMean( new MeanStationary() );
//    gp.setNoise( new NoiseStationary() );
//    gp.setCov( new CovSqExp(ISO) );

//    gp.options.draw_type = NONE;
//    gp.options.optimizer = NL_COBYLA;
//    gp.options.error_metric = NLPD;
//    gp.options.max_evaluation = iter;

//    gp.setXYZtr( Xtr , Ytr , Ztr );

//    Vecd hyps( gp.n_hyps() ); hyps.eig() << 0 , 0 , 0 , 0 ;
//    Veci clamps( gp.n_hyps() ); clamps.eig() << 0 , 0 , 0 , 0 ;
//    gp.setHyps( hyps ).setClamps( clamps );

//    // TRAIN GP

//    gp.train();

//    // QUERY GP

//    gp.query( Xev );

//    // SAVE RESULTS

//    Matd res = ( Yev & gp.mf & gp.vf );
//    res.save( dataset + "_results");

//    // CHECK ACCURACY

//    forLOOPi( res.r() ) res(i,1) = res(i,1) < 0.5 ? 0 : 1 ;
//    double sum = ( res.c(1) - res.c(0) ).absum() , tot = res.r();
//    disp( 1.0 - sum / tot );

//    return 0;
}
