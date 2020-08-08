#include "./gp_test.h"

namespace cvpp
{

// Destructor
TestGP::~TestGP()
{
}

// Constructor
TestGP::TestGP()
{
    flag = 1;
}

// Solve
TestGP&
TestGP::solve()
{
    Kuu = calcDenseJitCov( Zt , KKuu );
    Kun = calcDenseCov( Zt , Xt , KKun ); Knu = Kun.t();
    knn = calcDiagCov( Xt , kknn );

    Luu = Kuu.chol();
    iKuu = Luu.cdbslash();

    V = Luu.cbslash( Kun );
    M = V * V.t() + calcJitNoise( Zt ).diag();

    Lm = M.chol();
    beta = Lm.cbslash( V ) * Yt;

    LSv = Sv.chol();
    qnn = Luu.cbslash( Kun ).sqsumRows().t();

    iKuu_m = Kuu.bslash( Mv );
    iKuu_S = Kuu.bslash( Sv );

    Knu_iKuu_m = Knu * iKuu_m;
    iKuu_Kun = Luu.cdbslash( Kun ); Knu_iKuu = iKuu_Kun.t();
    iKuu_Kun_2 = iKuu_Kun * Knu_iKuu;
}

// Infer
const void
TestGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
}

// Likelihood
double
TestGP::likelihood() const
{
    double sig = exp( nhyps(0) );
    double i2sig = 1.0 / ( 2.0 * sig );

    double lml;

    switch( flag )
    {
    case 1: ////// log|M|
        lml = Lm.ldsum();
        break;
    case 2: ////// 0.5 * sig^-1 * ( y' * y - beta' * beta )
        lml = i2sig * ( Yt.sqsum() - beta.sqsum() );
        break;
    case 3: ////// log( sig ) * ( n - m )
        lml = log( sig ) * ( n_tr() - n_ind() );
        break;
    case 4: ////// 0.5 * sig^-1 * tr( knn - Knm * Kmm^-1 * Kmn )
        lml = i2sig * ( knn - V.sqsumRows().t() ).sum();
        break;
    case 5: ////// sum( kmm - qmm )
        lml = ( knn - qnn ).sum();
        break;
    case 6: ////// sum( ( Yt - Knm * Kmm^-1 * Mv ).^2 )
        lml = ( Yt - Knu_iKuu_m ).sqsum();
        break;
    case 7: ////// sum( Sv .* Kmm^-1 * Kmn * Knm * Kmm^-1 )
        lml = ( Sv % iKuu_Kun_2 ).sum();
        break;
    case 8:
        lml = Kuu.sum();
        break;
    }

    return lml;
}

// Gradient
double
TestGP::gradient( Seqd& grads ) const
{
    double sig = exp( nhyps(0) );
    double i2sig = 1.0 / ( 2.0 * sig );

    Matd Lt = Luu * Lm;
    Matd iA = Lt.cdbslash();

    Matd iKuu_sig_iA = iKuu - sig * iA;

    Matd B1 = Lt.cdbslash( Kun );
    Matd b1 = Lt.t().cbslash( beta );

    Matd mu = V.t() * Lm.t().cbslash( beta );

    unsigned cnt = 0 , idx = 0 ;

    for( unsigned i = 0 ; i < n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dKuu = gradDenseCov( Zt , KKuu , i );
            Matd dKun = gradDenseCov( Zt , Xt , KKun , i ) , dKnu = dKun.t();
            Matd dknn = gradDiagCov( Xt , kknn , i );

            Matd dKnu_iKuu_m = dKnu * iKuu_m - Knu * Kuu.bslash( dKuu * iKuu_m );
            Matd Knu_iKuu_dKuu = Knu_iKuu * dKuu;

            Matd iKuu_dKuu_iKuu_m = Kuu.bslash( dKuu * iKuu_m );
            Matd iKuu_dKuu_iKuu_S = Kuu.bslash( dKuu * iKuu_S );

            switch( flag )
            {
            case 1: ////// log|M|
                grads[cnt++] = + 1.0 * ( B1.t() * dKun ).tr()
                               - 0.5 * ( iKuu_sig_iA * dKuu ).tr();
                break;
            case 2: ////// 0.5 * sig^-1 * ( y' * y - beta' * beta )
                grads[cnt++] = 0.5 * ( b1.t() * dKuu * b1 )
                             - 1.0 * ( b1.t() * dKun * ( Yt - mu ) ) / sig;
                break;
            case 3: ////// log( sig ) * ( n - m )
                grads[cnt++] = 0;
                break;
            case 4: ////// 0.5 * sig^-1 * tr( knn - Knm * Knn^-1 * Kmn )
                grads[cnt++] = i2sig * ( dknn - ( ( ( dKnu - Knu_iKuu * dKuu ) * iKuu ) % Knu
                                                  + Knu_iKuu % dKnu ).sumCols() ).sum();
                break;
            case 5: ////// sum( kff - qff )
                grads[cnt++] = ( dknn - 2.0 * ( dKnu % Knu_iKuu ).sumCols()
                                            + ( Knu_iKuu_dKuu % Knu_iKuu ).sumCols() ).sum();
                break;
            case 6: ////// sum( ( Yt - Knm * Kmm^-1 * Mv ).^2 )
                grads[cnt++] = 2.0 * ( ( Knu_iKuu_m - Yt ) % dKnu_iKuu_m ).sum();
                break;
            case 7:
                grads[cnt++] = 2.0 * ( Sv % ( Kuu.bslash( dKun * Knu_iKuu   )
                                            - Kuu.bslash( dKuu * iKuu_Kun_2 ) ) ).sum();
                break;
            case 8:
                grads[cnt++] = gradDenseCov( Zt , i ).sum();
                break;
            }
        }

    for( unsigned i = 0 ; i < n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            switch( flag )
            {
            case 1: ////// log|M|
                grads[cnt++] = 0.5 * sig * M.bslash().tr();
                break;
            case 2: ////// 0.5 * sig^-1 * ( y' * y - beta' * beta )
                grads[cnt++] = 0.5 * ( Lm.t().cbslash( beta ).sqsum()
                                   - ( Yt.sqsum() - beta.sqsum() ) / sig );
                break;
            case 3: ////// log( sig ) * ( n - m )
                grads[cnt++] = ( n_tr() - n_ind() );
                break;
            case 4: ////// 0.5 * sig^-1 * tr( knn - Knm * Knn^-1 * Kmn )
                grads[cnt++] = - i2sig * ( knn - V.sqsumRows().t() ).sum();
                break;
            case 5: ////// sum( kff - qff )
                grads[cnt++] = 0;
                break;
            case 6: ////// sum( ( Yt - Knm * Kmm^-1 * Mv ).^2 )
                grads[cnt++] = 0;
                break;
            case 7: ////// sum( Sv .* Kmm^-1 * Kmn * Knm * Kmm^-1 )
                grads[cnt++] = 0;
                break;
            case 8:
                grads[cnt++] = 0;
                break;
            }
        }

    for( unsigned i = 0 ; i < Zt.c() ; i++ )
    {
        switch( flag )
        {
        case 8:
            Matd dKuu = - 2.0 * gindDenseCov( Zt , i ).sumCols();
            dKuu.print("dKuu");
            for( unsigned j = 0 ; j < Zt.r() ; j++ )
                grads[cnt++] = dKuu(j);
            break;
        }
    }


    return likelihood();
}



}
