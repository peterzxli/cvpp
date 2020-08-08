#include "./gp_class.h"

namespace cvpp
{

// Destructor
ClassGP::~ClassGP()
{
}

// Constructor
ClassGP::ClassGP()
{
    options.learn_hyp = true;
    options.draw_3D_view = TOPVIEW;
}

// Solve
ClassGP&
ClassGP::solve()
{
    Knn = calcDenseJitCov( Xt , KKnn );
    alpha.reset( n_tr() ); alpha.setVal(0);

    m = calcMean( Xt , MMn );
    f = Knn * alpha + m;

    Matd I( n_tr() , n_tr() ); I.setIdentity();

    Matd lp = calcLik( f , Yt );
    Matd dlp = gradLik1() , d2lp = gradLik2();

    W = - d2lp;
    double Wmin = 0;

    double Psi_new = calcInf( alpha , m , Yt , Knn );
    double Psi_old = PINF , tol = 1e-6;

    unsigned it , maxit = 10;
    while( Psi_old - Psi_new > tol && it++ < maxit )
    {
        Psi_old = Psi_new;

        W = W.floor( Wmin ); sW = W.sqrt();
        Lnn = ( sW * sW.t() % Knn + I ).chol();

        Matd b = W % ( f - m ) + dlp;
        Matd dalpha = b - sW % Lnn.cdbslash( sW % ( Knn * b ) ) - alpha;

        Psi_new = searchBrent( alpha , dalpha , m , Yt , Knn );

        f = Knn * alpha + m;

        lp = calcLik( f , Yt );
        dlp = gradLik1() , d2lp = gradLik2();
        W = - d2lp; sW = W.sqrt();
    }

    Lnn = ( sW * sW.t() % Knn + I ).chol();
}

// Infer
const void
ClassGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    Matd Kns = calcDenseCov( Xt , Xs );
    Matd kss = calcDiagCov( Xs );

    Matd V = Lnn.cbslash( sW.repCols( Xs.r() ) % Kns );

    mf = Kns.t() * alpha + calcMean( Xs );
    vf = kss - V.sqsumRows().t() + calcNoise( Xs );
}

// Likelihood
double
ClassGP::likelihood() const
{
    return alpha.t() * ( f - m ) / 2.0
         + ( Lnn.ldiag() - calcLik( f, Yt ) ).sum();
}

// Gradient
double
ClassGP::gradient( Seqd& grads ) const
{
    Matd sWW = sW.repCols( n_tr() );

    Matd Z = sWW % Lnn.cdbslash( sW.diag() );
    Matd C = Lnn.bslash( sWW % Knn );
    Matd g = ( Knn.diag() - C.sqsumRows().t() ) / 2.0;

    calcLik( Knn * alpha + calcMean( Xt ) , Yt );
    Matd dfhat = g % gradLik3();

    unsigned cnt = 0 , idx = 0 ;

    for( unsigned i = 0 ; i < n_mean() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dm = gradMean( Xt , MMn , i );

            grads[cnt++] = - ( dm % alpha ).sum()
                           - dfhat.t() * ( dm - Knn * ( Z * dm ) );
        }

    for( unsigned i = 0 ; i < n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dK = gradDenseCov( Xt , KKnn , i );
            Matd b = dK * gradLik1();

            grads[cnt++] = ( Z % dK ).sum() / 2.0 - alpha.t() * dK * alpha / 2.0
                           - dfhat.t() * ( b - Knn * ( Z * b ) );
        }

    return likelihood();
}

}
