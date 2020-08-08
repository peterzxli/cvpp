#ifndef GP_BASE_H
#define GP_BASE_H

#include "./base/gp_base_info.h"

#include "../functions/mean_base.h"
#include "../functions/cov_base.h"
#include "../functions/noise_base.h"
#include "../functions/lik_base.h"
#include "../functions/inf_base.h"
#include "../functions/draw_base.h"

#include <cvpp/interfaces/cpplot.h>
#include <cvpp/auxiliar/definitions/definitions_gp.h>

namespace cvpp
{

class BaseGP : public InfoGP
{

protected:

    double prop;
    double lrate_hyp,lrate_ind,lrate_var,lrate_step;
    double mom_hyp,mom_ind,mom_var;

    bool improving,better;
    double lml;

    Matd values,vectors;
    String err_str;

    NLopt *optimizer;
    Thread thread_train;

    MeanBase* mean;
    CovBase* cov;
    NoiseBase* noise;
    LikBase* lik;
    InfBase* inf;
    DrawBase* draw;

    Timer timer;

public:

    BaseGP();
    ~BaseGP();

    virtual unsigned n_lik()  const { return 0; }

    virtual Dims d_mvar() const { return Dims( 0 , 0 ); }
    virtual Dims d_svar() const { return Dims( 0 , 0 ); }
    virtual unsigned n_var()  const { return d_mvar().s() + d_svar().s(); }

    virtual const void setDraw() {}

    virtual BaseGP& solve() { disp("BASE_GP SOLVE"); }
    virtual BaseGP& solve( const Seqd& hyps ) { updateAllHyps( hyps ); solve(); return *this; }
    virtual BaseGP& solve( const Vecd& hyps ) { updateAllHyps( hyps.seq() ); solve(); return *this; }

    virtual const void infer( const Matd& , Matd& , Matd& ) const { disp("BASE_GP INFER"); }

    virtual Matd& query( const Matd& , Matd& , Matd& );
    virtual Matd& squery( const Matd& X , Matd& mf , Matd& vf ) { solve(); return query( X , mf , vf ); }

    virtual Matd& query( const Matd& X ) { return query( X , mf , vf ); }
    virtual Matd& squery( const Matd& X ) { solve(); return query( X ); }

    virtual Matd& query() { return query( Xe ); }
    virtual Matd& squery() { solve(); return query(); }

    virtual double likelihood() const { disp("BASE_GP LIKELIHOOD"); }
    virtual double slikelihood() { solve(); return likelihood(); }

    virtual double slikelihood( const Seqd& hyps ) { solve( hyps ); return likelihood(); }
    virtual double slikelihood( const Vecd& hyps ) { return slikelihood( hyps.seq() ); }

    virtual double gradient( Seqd& ) const { disp("BASE_GP GRADIENT"); }
    virtual double gradient( Vecd& grads ) const { return gradient( grads.seq() ); }

    double numeric( Seqd& );
    double numeric( Vecd& grads ) { return numeric( grads.seq() ); }

    const void numericHyp( Vecd&         );
    const void numericInd( Matd&         );
    const void numericVar( Matd& , Matd& );

    virtual const void sgradient( Vecd& ghyps , Matd& ginds , Matd& gth1 , Matd& gth2 )
    { solve(); gradient( ghyps , ginds , gth1 , gth2 ); }

    virtual const void gradient( Vecd& ghyps , Matd& ginds , Matd& gth1 , Matd& gth2 )
    { gradientHyp( ghyps ); gradientInd( ginds ); gradientVar( gth1 , gth2 ); }

    virtual const void gradientHyp( Vecd&         ) const { disp("BASE_GP GRADIENT HYP"); }
    virtual const void gradientInd( Matd&         ) const { disp("BASE_GP GRADIENT IND"); }
    virtual const void gradientVar( Matd& , Matd& ) const { disp("BASE_GP GRADIENT VAR"); }

    virtual const void prepTrain() {}
    virtual const void prepBuffers() {}

    const void runDraw();
    const void runTrain();

    const void prepNLOPT();
    const void trainNLOPT();

    const void trainNUMERIC();
    const void trainGRADIENT();
    const void trainMIN_NUM();
    const void trainMIN_GRAD();
    const void trainSTOCHASTIC();

    const void prepLearning( Vecd& , Vecd& ) const;

    const void minimizeCVPP( double (*func)( Vecd& , void* ) );
    const void minimizeMATLAB( double (*func)( Vecd& , void* ) );
    const void minimizeSGD();

    double searchBrent( Matd& , const Matd& , const Matd& , const Matd& , const Matd& );

    const void updateSGDhyp( const double& , const double& , Vecd& , Vecd& );
    const void updateSGDind( const double& , const double& , Matd& , Matd& );
    const void updateSGDvar( const double& , const double& , Matd& , Matd& , Matd& , Matd& );

    const void prepLikelihood();
    const void prepLikelihood( const Seqd& hyps ) { prepLikelihood(); solve( hyps ); }
    const void prepLikelihood( const Vecd& hyps ) { prepLikelihood(); solve( hyps ); }

    const void postLikelihood( const double& );

    const void setErrorString();
    const void calcErrors( const Matd& );

    const void selectBatch();
    const void selectSingleBatch();

    virtual const void save( const String& ) const;

    virtual const void load( const String& );
    virtual const void sload( const String& str ) { return load( str ); solve(); }

    virtual BaseGP& train();

    const bool isImproving( const double& lml )
    { return data.lmls.empty() || lml < data.lmls[-1].y; }

    double grad_likelihood( const Seqd& , Seqd& , void* = NULL );
    double free_likelihood( const Seqd& , Seqd& , void* = NULL );
    double  num_likelihood( const Seqd& , Seqd& , void* = NULL );

    Seqd num_likelihood( const Seqd& hyps )
    { Seqd grads( hyps.size() ); num_likelihood( hyps , grads ); return grads; }

    const void checkDerivatives( const Seqd& );
    const void checkDerivatives( const Vecd& vec ) { checkDerivatives( vec.seq() ); }

    const void checkHypDerivatives( const Vecd& );
    const void checkIndDerivatives( const Matd& );
    const void checkVarDerivatives( const Matd& , const Matd& );

    const void checkAllDerivatives( const Vecd& ghyps , const Matd& ginds , const Matd& gth1 , const Matd& gth2 )
    { checkHypDerivatives( ghyps ); checkIndDerivatives( ginds ); checkVarDerivatives( gth1 , gth2 ); }

    unsigned n_mean()  const { return mean->n();           }
    unsigned n_cov()   const { return cov->ls_n( d_in() ); }
    unsigned n_noise() const { return noise->n();          }

    unsigned n_cov( const unsigned& d ) const { return cov->ls_n( d ); }
    unsigned n_hyps( const unsigned& d ) const { return n_mean() + n_cov( d ) + n_noise() + n_lik(); }

    unsigned n_hyps() const { return n_mean() + n_cov() + n_noise() + n_lik(); }
    unsigned n_train() const { return n_freehyp() + n_freeind() + n_freevar(); }

    const Vecd&  hyps() const { return all_hyps;   }
    const Vecd& thyps() const { return train_hyps; }

    const Vecd& mhyps() const { return mean_hyps;  }
    const Vecd& khyps() const { return cov_hyps;   }
    const Vecd& nhyps() const { return noise_hyps; }
    const Vecd& lhyps() const { return lik_hyps;   }

    const double&  hyps( const int& i ) const { return all_hyps[i];   }
    const double& mhyps( const int& i ) const { return mean_hyps[i];  }
    const double& khyps( const int& i ) const { return cov_hyps[i];   }
    const double& nhyps( const int& i ) const { return noise_hyps[i]; }
    const double& lhyps( const int& i ) const { return lik_hyps[i];   }

    virtual BaseGP& prepHyps();
    virtual BaseGP& updateAllHyps( const Seqd& );
    virtual BaseGP& updateTrainHyps();

    BaseGP& setMvar( const Matd& M ) { Mv = M; return updateTrainHyps(); }
    BaseGP& setSvar( const Matd& S ) { Sv = S; return updateTrainHyps(); }
    BaseGP& setMSvar( const Matd& M , const Matd& S ) { Mv = M; Sv = S; return updateTrainHyps(); }

    BaseGP& setHyps( const Vecd& hyps ) { all_hyps = hyps; return prepHyps(); }
    BaseGP& loadHyps( const String& str ) { all_hyps.load( str ); return prepHyps(); }

    BaseGP& setClamps( const Veci& vec ) { clamps = vec; return updateTrainHyps(); }
    BaseGP& loadClamps( const String& str ) { clamps.load( str ); return updateTrainHyps(); }

    BaseGP& clamp( const unsigned& i ) { clamps[i] = 1; return updateTrainHyps(); }
    BaseGP& clamp( const unsigned& i , const unsigned& j ) { clamps[i] = clamps[j] = 1; return updateTrainHyps(); }
    BaseGP& clamp( const unsigned& i , const unsigned& j , const unsigned& k ) { clamps[i] = clamps[j] = clamps[k] = 1; return updateTrainHyps(); }

    BaseGP& unclamp( const unsigned& i ) { clamps[i] = 0; return updateTrainHyps(); }
    BaseGP& unclamp( const unsigned& i , const unsigned& j ) { clamps[i] = clamps[j] = 0; return updateTrainHyps(); }
    BaseGP& unclamp( const unsigned& i , const unsigned& j , const unsigned& k ) { clamps[i] = clamps[j] = clamps[k] = 0; return updateTrainHyps(); }

    BaseGP& setMean(  MeanBase* mean ) { this->mean =  mean; return *this; }
    BaseGP& setMean(  MeanBase& mean ) { this->mean = &mean; return *this; }

    BaseGP& setCov( CovBase* cov ) { this->cov =  cov; return *this; }
    BaseGP& setCov( CovBase& cov ) { this->cov = &cov; return *this; }

    BaseGP& setNoise( NoiseBase* noise ) { this->noise =  noise; return *this; }
    BaseGP& setNoise( NoiseBase& noise ) { this->noise = &noise; return *this; }

    BaseGP& setLik( LikBase* lik ) { this->lik =  lik; return *this; }
    BaseGP& setLik( LikBase& lik ) { this->lik = &lik; return *this; }

    BaseGP& setInf( InfBase* inf ) { this->inf =  inf; return *this; }
    BaseGP& setInf( InfBase& inf ) { this->inf = &inf; return *this; }

    Matd calcMean( const Matd& X ) const { return mean->calcDense( X , mean_hyps ); }
    Matd calcMean( const Matd& X , SeqMatd& MM ) const { return mean->calcDense( X , mean_hyps , MM ); }

    Matd calcNoise( const Matd& X ) const { return noise->calcDense( X , noise_hyps ); }
    Matd calcNoise( const Matd& X , SeqMatd& NN ) const { return noise->calcDense( X , noise_hyps , NN ); }

    Matd calcJitNoise( const Matd& X ) const { return calcNoise( X ).AddJitter( options.jitter ); }
    Matd calcJitNoise( const Matd& X , SeqMatd& NN ) const { return calcNoise( X , NN ).AddJitter( options.jitter ); }

    Matd calcDenseCov( const Matd& X ) const { return cov->calcDense( X , X , cov_hyps ); }
    Matd calcDenseCov( const Matd& X , SeqMatd& KK ) const { return cov->calcDense( X , X , cov_hyps , KK ); }

    Matd calcDenseJitCov( const Matd& X ) const { return calcDenseCov( X ).addJitter( options.jitter ); }
    Matd calcDenseJitCov( const Matd& X , SeqMatd& KK ) const { return calcDenseCov( X , KK ).addJitter( options.jitter ); }

    Matd calcDenseCov( const Matd& X1 , const Matd& X2 ) const { return cov->calcDense( X1 , X2 , cov_hyps ); }
    Matd calcDenseCov( const Matd& X1 , const Matd& X2 , SeqMatd& KK ) const { return cov->calcDense( X1 , X2 , cov_hyps , KK ); }

    Matd calcZeroMean( const Matd& X , const Matd& Y ) const { return Y - calcMean( X ); }
    Matd calcZeroMean( const Matd& X , const Matd& Y , SeqMatd& MM ) const { return Y - calcMean( X , MM ); }

    Matd calcDenseNoisyCov( const Matd& X ) const { return calcDenseCov( X ) + calcNoise( X ).diag(); }
    Matd calcDenseNoisyCov( const Matd& X , SeqMatd& KK , SeqMatd& NN ) const { return calcDenseCov( X , KK ) + calcNoise( X , NN ).diag(); }

    Matd calcDenseNoisyJitCov( const Matd& X ) const { return calcDenseNoisyCov( X ).AddJitter( options.jitter ); }
    Matd calcDenseNoisyJitCov( const Matd& X , SeqMatd& KK , SeqMatd& NN ) const { return calcDenseNoisyCov( X , KK , NN ).AddJitter( options.jitter ); }

    Matd calcDiagCov( const Matd& X ) const { return cov->calcDiag( X , cov_hyps ); }
    Matd calcDiagCov( const Matd& X , SeqMatd& KK ) const { return cov->calcDiag( X , cov_hyps , KK ); }

    Matd calcLik( const Matd& m , const Matd& y ) const { return lik->calc( m , y ); }
    Matd calcLik( const Matd& m ) const { Matd y( m.r() ); y.setVal(1); return calcLik( m , y ); }

    Matd gradLik1() const { return lik->grad1(); }
    Matd gradLik2() const { return lik->grad2(); }
    Matd gradLik3() const { return lik->grad3(); }

    double calcInf( const Matd& alpha , const Matd& m , const Matd& y , const Matd& K ) const { return inf->calc( lik , alpha , m , y , K ); }

    Matd gradMean( const Matd& X , const unsigned& i ) const { return mean->gradDense( X , mean_hyps , i ); }
    Matd gradMean( const Matd& X , const SeqMatd& MM , const unsigned& i ) const { return mean->gradDense( X , mean_hyps , MM , i ); }

    Matd gradDenseCov( const Matd& X , const SeqMatd& KK , const unsigned& i ) const { return cov->gradDense( X , X , cov_hyps , KK , i ); }
    Matd gradDenseCov( const Matd& X1 , const Matd& X2 , const SeqMatd& KK , const unsigned& i ) const { return cov->gradDense( X1 , X2 , cov_hyps , KK , i ); }

    Matd gradDenseCov( const Matd& X , const unsigned& i ) const { return cov->gradDense( X , X , cov_hyps , i ); }
    Matd gradDenseCov( const Matd& X1 , const Matd& X2 , const unsigned& i ) const { return cov->gradDense( X1 , X2 , cov_hyps , i ); }

    Matd gradDiagCov( const Matd& X , const SeqMatd& KK , const unsigned& i ) const { return cov->gradDiag( X , cov_hyps , KK , i ); }
    Matd gindDiagCov( const Matd& X , const SeqMatd& KK , const unsigned& i ) const { return cov->gindDiag( X , cov_hyps , KK , i ); }

    Matd gradDiagCov( const Matd& X , const unsigned& i ) const { return cov->gradDiag( X , cov_hyps , i ); }
    Matd gindDiagCov( const Matd& X , const unsigned& i ) const { return cov->gindDiag( X , cov_hyps , i ); }

    Matd gindDenseCov( const Matd& X , const SeqMatd& KK , const unsigned& i ) const { return cov->gindDense( X , X , cov_hyps , KK , i ); }
    Matd gindDenseCov( const Matd& X1 , const Matd& X2 , const SeqMatd& KK , const unsigned& i ) const { return cov->gindDense( X1 , X2 , cov_hyps , KK , i ); }

    Matd gindDenseCov( const Matd& X , const unsigned& i ) const { return cov->gindDense( X , X , cov_hyps , i ); }
    Matd gindDenseCov( const Matd& X1 , const Matd& X2 , const unsigned& i ) const { return cov->gindDense( X1 , X2 , cov_hyps , i ); }

    Matd gradNoise( const Matd& X , const unsigned& i ) const { return noise->gradDense( X , noise_hyps , i ); }
    Matd gradNoise( const Matd& X , const SeqMatd& NN , const unsigned& i ) const { return noise->gradDense( X , noise_hyps , NN , i ); }

    Matd calcLS1() const { return cov->LSeqMat1( cov_hyps , 0 , d_in() ); }
    Matd calcLS2() const { return cov->LSeqMat2( cov_hyps , 0 , d_in() ); }

    Matd calcLS1dist0( const Matd& X ) const { return cov->LS1dist0( X , cov_hyps , 0 , X.c() ); }
    Matd calcLS1dist0( const Matd& X1 , const Matd& X2 ) const { return cov->LS1dist0( X1 , X2 , cov_hyps , 0 , X1.c() ); }

    Matd calcLS2dist0( const Matd& X ) const { return cov->LS2dist0( X , cov_hyps , 0 , X.c() ); }
    Matd calcLS2dist0( const Matd& X1 , const Matd& X2 ) const { return cov->LS2dist0( X1 , X2 , cov_hyps , 0 , X1.c() ); }

    Matd calcLS1dist1( const Matd& X ) const { return cov->LS1dist1( X , cov_hyps , 0 , X.c() ); }
    Matd calcLS1dist1( const Matd& X1 , const Matd& X2 ) const { return cov->LS1dist1( X1 , X2 , cov_hyps , 0 , X1.c() ); }

    Matd calcLS2dist1( const Matd& X ) const { return cov->LS2dist1( X , cov_hyps , 0 , X.c() ); }
    Matd calcLS2dist1( const Matd& X1 , const Matd& X2 ) const { return cov->LS2dist1( X1 , X2 , cov_hyps , 0 , X1.c() ); }

    Matd calcLS1dist2( const Matd& X ) const { return cov->LS1dist2( X , cov_hyps , 0 , X.c() ); }
    Matd calcLS1dist2( const Matd& X1 , const Matd& X2 ) const { return cov->LS1dist2( X1 , X2 , cov_hyps , 0 , X1.c() ); }

    Matd calcLS2dist2( const Matd& X ) const { return cov->LS2dist2( X , cov_hyps , 0 , X.c() ); }
    Matd calcLS2dist2( const Matd& X1 , const Matd& X2 ) const { return cov->LS2dist2( X1 , X2 , cov_hyps , 0 , X1.c() ); }

    Matd calcJitter( const Matd& X ) const { Matd I( X.r() , X.r() ); I.setIdentity( options.jitter ); return I; }

};

}

#endif
