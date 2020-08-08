#include "./gp_sparse.h"

namespace cvpp
{

// Destructor
SparseGP::~SparseGP()
{
}

// Constructor
SparseGP::SparseGP()
{
    options.learn_hyp = true;
}

// Solve
SparseGP&
SparseGP::solve()
{
    Kuu = calcDenseJitCov( Zt , KKuu );
    Kun = calcDenseCov( Zt , Xt , KKun ) , Knu = Kun.t();

    Luu = Kuu.chol();
    V = Luu.bslash( Kun );
    M = V * V.t() + calcJitNoise( Zt ).diag();

    Lm = M.chol();
    beta = Lm.bslash( V ) * Yt;
}

// Infer
const void
SparseGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    double sig = exp( nhyps(0) );

    Matd Kus = calcDenseCov( Zt , Xs ) , Ksu = Kus.t();
    Matd kss = calcDiagCov( Xs );

    Matd Lss = Luu.bslash( Kus );
    Matd Lms = Lm.bslash( Lss );

    mf = Lms.t() * beta;
    vf = kss - Lss.sqsumRows().t() + sig * Lms.sqsumRows().t() + sig;
}

// Likelihood
double
SparseGP::likelihood() const
{
    double sig = exp( nhyps(0) );

    return  + 1.0 * Lm.ldsum()
            + 0.5 * ( n_tr() - n_ind() ) * log( sig )
            + 0.5 * ( Yt.sqsum() - beta.sqsum() ) / sig;
}

// Gradient
double
SparseGP::gradient( Seqd& grads ) const
{
    double sig = exp( nhyps(0) );

    Matd Lt = Luu * Lm;
    Matd iA = Lt.cdbslash();

    Matd iKuu_sig_iA = Luu.cdbslash() - sig * iA;
    Matd mu = ( Lm.t().bslash( beta ).t() * V ).t();

    Matd B1 = Lt.cdbslash( Kun );
    Matd b1 = Lt.t().bslash( beta );

    unsigned cnt = 0 , idx = 0 ;

    for( unsigned i = 0 ; i < n_mean() ; i++ )
        if( !clamps[idx++] )
        {
            grads[cnt++] = 0;
        }

    for( unsigned i = 0 ; i < n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dKuu = gradDenseCov( Zt , KKuu , i );
            Matd dKun = gradDenseCov( Zt , Xt , KKun , i );

            grads[cnt++] = + 1.0 * ( B1.t() * dKun ).tr()
                           - 0.5 * ( iKuu_sig_iA * dKuu ).tr()
                           + 0.5 * ( b1.t() * dKuu * b1 )
                           - 1.0 * b1.t() * dKun * ( Yt - mu ) / sig;
        }

    for( unsigned i = 0 ; i < n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            grads[cnt++] = 0.5 * ( + sig * M.bslash().tr()
                                   + n_tr() - n_ind()
                                   + Lm.t().bslash( beta ).sqsum()
                                   - ( Yt.sqsum() - beta.sqsum() ) / sig );
        }

    return likelihood();
}

}
