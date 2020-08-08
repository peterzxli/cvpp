#include "./gp_varlearn.h"

namespace cvpp
{

// Destructor
VarLearnGP::~VarLearnGP()
{
}

// Constructor
VarLearnGP::VarLearnGP()
{
    options.learn_hyp = true;
    options.learn_ind = true;
}

// Solve
VarLearnGP&
VarLearnGP::solve()
{
    double sig = exp( nhyps(0) );

    Kuu = calcDenseJitCov( Zt , KKuu );
    Kun = calcDenseCov( Zt , Xt , KKun ) , Knu = Kun.t();
    knn = calcDiagCov( Xt , kknn );

    Luu = Kuu.chol();
    V = Luu.bslash( Kun );
    M = V * V.t() + calcJitNoise( Zt ).diag();

    Lm = M.chol();
    beta = Lm.bslash( V ) * Yt;

    S = ( Kuu + Kun * Knu / sig ).inv();
    Mv = ( Kuu * S * Kun * Yt ) / sig;
    Sv = Kuu * S * Kuu;
}

// Likelihood
double
VarLearnGP::likelihood() const
{
    double sig = exp( nhyps(0) );

    return  + 1.0 * Lm.ldsum()
            + 0.5 * ( n_tr() - n_ind() ) * log( sig )
            + 0.5 * ( Yt.sqsum() - beta.sqsum() ) / sig
            + 0.5 * ( knn - ( V.sqsumRows().t()) ).sum() / sig;
}

// Infer
const void
VarLearnGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    Matd Kus = calcDenseCov( Zt , Xs ) , Ksu = Kus.t();
    Matd kss = calcDiagCov( Xs );

    Matd A = Kuu.bslash( Kus );
    Matd B = Luu.cbslash( Kus );

    mf = Ksu * Luu.cdbslash( Mv );
    vf = kss + ( A % ( Sv * A ) - B.square() ).sumRows().t() + calcNoise( Xs );
}

// Gradient
double
VarLearnGP::gradient( Seqd& grads ) const
{
    double sig = exp( nhyps(0) );

    Matd Lt = Luu * Lm;
    Matd iA = Lt.cdbslash();

    Matd iKuu_sig_iA = Luu.cdbslash() - sig * iA;
    Matd mu = ( Lm.t().bslash( beta ).t() * V ).t();
    Matd Knu_iKuu = Knu.slash( Kuu );

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
            Matd dKun = gradDenseCov( Zt , Xt , KKun , i ) , dKnu = dKun.t();
            Matd dknn = gradDiagCov( Xt , kknn , i );

            grads[cnt++] = + 1.0 * ( B1.t() * dKun ).tr()
                           - 0.5 * ( iKuu_sig_iA * dKuu ).tr()
                           + 0.5 * ( b1.t() * dKuu * b1 )
                           - 1.0 * b1.t() * dKun * ( Yt - mu ) / sig
                           + 0.5 * ( dknn - ( ( ( dKnu - Knu_iKuu * dKuu ).slash( Kuu ) ) % Knu
                                              + Knu_iKuu % dKnu ).sumCols() ).sum() / sig;

        }

    for( unsigned i = 0 ; i < n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            grads[cnt++] = 0.5 * ( + sig * Lm.cdbslash().tr()
                                   + n_tr() - n_ind()
                                   + Lm.t().bslash( beta ).sqsum()
                                   - ( Yt.sqsum() - beta.sqsum() ) / sig
                                   - ( knn - V.sqsumRows().t() ).sum() / sig );
        }

    return likelihood();
}

}
