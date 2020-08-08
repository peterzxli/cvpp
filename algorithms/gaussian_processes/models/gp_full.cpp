#include "./gp_full.h"

namespace cvpp
{

// Destructor
FullGP::~FullGP()
{
}

// Constructor
FullGP::FullGP()
{
    options.learn_hyp = true;
}

// Solve
FullGP&
FullGP::solve()
{
    Y0 = calcZeroMean( Xt , Yt , MMn );
    Knn = calcDenseNoisyJitCov( Xt , KKnn , NNn );

    Lnn = Knn.chol();
    alpha = Lnn.cdbslash( Y0 );
}

// Infer
const void
FullGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    Matd Ksn = calcDenseCov( Xs , Xt );
    Matd kss = calcDiagCov( Xs );

    Matd V = Lnn.cbslash( Ksn.t() );

    mf = Ksn * alpha + calcMean( Xs );
    vf = kss - V.sqsumRows().t() + calcNoise( Xs );
}

// Likelihood
double
FullGP::likelihood() const
{
    return + 1.0 * Lnn.ldsum()
           + 0.5 * Y0.t() * alpha
           + 0.5 * n_tr() * log( PI2 );
}

// Gradient
double
FullGP::gradient( Seqd& grads ) const
{
    Matd W = Lnn.cdbslash();
    W -= alpha * alpha.t();

    unsigned cnt = 0 , idx = 0 ;

    for( unsigned i = 0 ; i < n_mean() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dm = gradMean( Xt , MMn , i );
            grads[cnt++] = - ( dm % alpha ).sum();
        }

    for( unsigned i = 0 ; i < n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dK = gradDenseCov( Xt , KKnn , i );
            grads[cnt++] = + ( W % dK ).sum() / 2.0;
        }

    for( unsigned i = 0 ; i < n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dn = gradNoise( Xt , NNn , i );
            grads[cnt++] = + ( W % dn.diag() ).sum() / 2.0;
        }

    return likelihood();
}

}
