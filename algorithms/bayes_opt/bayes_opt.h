#ifndef BAYES_OPT_H
#define BAYES_OPT_H

#include <cvpp/algorithms/gaussian_processes/models/gp_full.h>

#include <cvpp/algorithms/bayes_opt/functions/acq_base.h>
#include <cvpp/algorithms/gaussian_processes/functions/mean_base.h>
#include <cvpp/algorithms/gaussian_processes/functions/cov_base.h>
#include <cvpp/algorithms/gaussian_processes/functions/noise_base.h>

#include <cvpp/algorithms/optimiser/optimiser_nlopt.h>

namespace cvpp
{

class BayesOpt
{

protected:

    FullGP model;

    Matd X,Y,P,C;
    Matd bounds;

    AcqBase* acq;
    Optimiser* optim;

public:

    const Matd& mf() const { return model.mf;    }
    const Matd& vf() const { return model.vf;    }
    const Matd uvf() const { return model.uvf(); }
    const Matd lvf() const { return model.lvf(); }

    const Matd& Xtr() const { return model.Xtr(); }
    const Matd& Ytr() const { return model.Ytr(); }

    const Matd& Ptr() const { return P; }
    const Matd& Ctr() const { return C; }

    FullGP& gp() { return model; }

    unsigned d_in() const { return model.Xtr().c(); }
    unsigned n_gp_hyps() const { return model.n_hyps(); }
    unsigned n_bo_hyps() const { return acq->n_hyps(); }

    Matd calcAcq( const Matd& rnds )
    { return acq->calc( P , rnds , model ); }

    BayesOpt();

    BayesOpt& query( const Matd& );
    BayesOpt& setBoundaries( const Matd& );

    BayesOpt& setMean(  MeanBase*  mean  ) { model.setMean(  mean  ); return *this; }
    BayesOpt& setCov(   CovBase*   cov   ) { model.setCov(   cov   ); return *this; }
    BayesOpt& setNoise( NoiseBase* noise ) { model.setNoise( noise ); return *this; }
    BayesOpt& setAcq(   AcqBase*   acq   ) { this->acq = acq;         return *this; }

    BayesOpt& setGPhyps( const Vecd& hyps ) { model.setHyps( hyps ); return *this; }
    BayesOpt& setBOhyps( const Vecd& hyps ) { acq->setHyps( hyps );  return *this; }

    BayesOpt& prepare( const Matd& , const Matd& , const Matd& );
    BayesOpt& insert( const Matd& , const Matd& , const Matd& );

    BayesOpt& prepare( const Matd& X , const Matd& Y ) { return prepare( X , X , Y ); }
    BayesOpt& insert( const Matd& X , const Matd& Y ) { return insert( X , X , Y ); }

    BayesOpt& start();
    BayesOpt& solve() { model.solve(); return *this; }

    Matd search( const int& );
    Matd randomise( const int& );
    Matd optimise( const Matd& );

};

inline double
optFunction( const Seqd& pars , Seqd& grads , void* ptr )
{
    Matd X = pars;
    BayesOpt* bo = static_cast<BayesOpt*>( ptr );
    bo->gp().query( X );

    return bo->calcAcq( X );
}

}

#endif
