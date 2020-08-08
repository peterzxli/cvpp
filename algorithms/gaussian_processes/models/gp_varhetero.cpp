#include "./gp_varhetero.h"

namespace cvpp
{

// Destructor
VarHeteroGP::~VarHeteroGP()
{
}

// Constructor
VarHeteroGP::VarHeteroGP()
{
    options.learn_hyp = true;
    options.learn_var = true;

    p = 1e-3;
}

// Solve
VarHeteroGP&
VarHeteroGP::solve()
{
    Kf = fgp.calcDenseJitCov( Xt , KKf );
    Kg = ggp.calcDenseNoisyJitCov( Xt , KKg , NNg );

    mu0 = Mv;
    lambda = Sv.exp();

    sqlambda = lambda.sqrt();

    Matd mI( n_tr() , n_tr() ); mI.setIdentity();
    Matd vI( n_tr() ); vI.setVal( 1.0 );

    cinvB = ( Kg % ( sqlambda * sqlambda.t() ) + mI ).chol().bslash();
    cinvBs = cinvB % ( vI * sqlambda.t() );

    beta = lambda - 0.5;
    mu = Kg * beta + mu0;

    hBLK2 = cinvBs * Kg;
    sigma = Kg - hBLK2.t() * hBLK2;

    R = ( mu - sigma.diag() / 2.0 ).exp();

    scale = 1.0 / ( p + R ).sqrt();
    Rscale = 1.0 / ( 1.0 + p / R );

    Ls = ( Kf % ( scale * scale.t() ) + Rscale.diag() ).chol();
    Lys = ( Ls.bslash( Yt % scale ) );

    alphascale = Ls.t().bslash( Lys );
    alpha = alphascale % scale;
}

// Likelihood
double
VarHeteroGP::likelihood() const
{
    return + 0.50 * Yt.t() * alpha + Ls.ldsum() - scale.lsum() + n_tr() / 2.0 * log( PI2 )
           + 0.50 * beta.t() * ( mu - mu0 ) - cinvB.ldsum() + 0.5 * cinvB.sqsum() - n_tr() / 2.0
           + 0.25 * sigma.tr();
}

// Infer
const void
VarHeteroGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    Matd Kfsn = fgp.calcDenseCov( Xs , Xt );
    Matd Kgsn = ggp.calcDenseCov( Xs , Xt );

    Matd kfss = fgp.calcDiagCov( Xs );
    Matd kgss = ggp.calcDiagCov( Xs );

    Matd I( 1 , Xs.r() ); I.setVal( 1.0 );

    Matd Vf = Ls.bslash( ( ( scale * I ) % Kfsn.t() ) );
    Matd Vg = cinvBs * Kgsn.t();

    mf.c(0) = Kfsn * alpha;
    mf.c(1) = Kgsn * beta + mu0;

    vf.c(0) = kfss - Vf.square().sumRows().t();
    vf.c(1) = kgss - Vg.square().sumRows().t();

    vf.c(0) += ( mf.c(1) + vf.c(1) / 2.0 ).exp();
}

// Gradient
double
VarHeteroGP::gradient( Seqd& grads ) const
{
    Matd invKfRs = Ls.cdbslash();
    Matd betahat = - 0.5 * ( invKfRs.diag() % Rscale - alphascale.square() % Rscale );
    Matd lambdahat = betahat + 0.5;

    Matd invBs = cinvB.t() * cinvBs;
    Matd dFlambda = - ( Kg + 0.5 * sigma.square() ) * ( lambda - lambdahat );
    Matd I( 1 , n_tr() ); I.setVal( 1.0 );

    Matd Wf = alpha * alpha.t() - invKfRs % ( scale * scale.t() );
    Matd Wg = beta * beta.t() + 2.0 * ( betahat - beta ) * beta.t()
            - invBs.t() * ( ( ( lambdahat / lambda - 1.0 ) * I ) % invBs ) - cinvBs.t() * cinvBs;

    unsigned cnt = 0 , idx = 0 ;

    for( unsigned i = 0 ; i < fgp.n_mean() ; i++ )
        if( !clamps[idx++] )
        {
            grads[cnt++] = 0;
        }

    for( unsigned i = 0 ; i < fgp.n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dK = fgp.gradDenseCov( Xt , i );
            grads[cnt++] = - ( Wf % dK ).sum() / 2.0;
        }

    for( unsigned i = 0 ; i < fgp.n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            grads[cnt++] = 0;
        }

    for( unsigned i = 0 ; i < ggp.n_mean() ; i++ )
        if( !clamps[idx++] )
        {
            grads[cnt++] = 0;
        }

    for( unsigned i = 0 ; i < ggp.n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dK = ggp.gradDenseCov( Xt , i );
            grads[cnt++] = - ( Wg % dK ).sum() / 2.0;
        }

    for( unsigned i = 0 ; i < ggp.n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dn = ggp.gradDenseCov( Xt , i );
            grads[cnt++] = - ( Wg % dn.diag() ).sum() / 2.0;
        }

    double dFmu0 = - betahat.sum();
    Matd dFvar = - lambda % dFlambda;

    grads[cnt++] = dFmu0;
    for( unsigned i = 0 ; i < dFvar.r() ; i++ )
        grads[cnt++] = dFvar(i);

    return likelihood();
}

}
