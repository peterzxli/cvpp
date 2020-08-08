#include "./gp_bigdata.h"

namespace cvpp
{

// Destructor
BigDataGP::~BigDataGP()
{
}

// Constructor
BigDataGP::BigDataGP()
{
    options.learn_hyp = true;
}

// Solve
BigDataGP&
BigDataGP::solve()
{
    Kuu = calcDenseJitCov( Zt , KKuu ) ; Luu = Kuu.chol();
    Kfu = calcDenseCov( Xb , Zt , KKfu ) ; Kuf = Kfu.t();
    kff = calcDiagCov( Xb , KKff );

    LSv = Sv.chol();
    qff = Luu.cbslash( Kuf ).sqsumRows().t();

    iKuu_m = Kuu.bslash( Mv );
    iKuu_S = Kuu.bslash( Sv );

    Kfu_iKuu_m = Kfu * iKuu_m;
    iKuu_Kuf = Luu.cdbslash( Kuf ); Kfu_iKuu = iKuu_Kuf.t();
    iKuu_Kuf_2 = iKuu_Kuf * Kfu_iKuu;

    Yb_Kfu_iKuu_m = Yb - Kfu_iKuu_m;
}

// Likelihood
double
BigDataGP::likelihood() const
{
    double s2 = exp( nhyps(0) );
    double i2s2 = 0.5 / s2;

    double term1 = Yb_Kfu_iKuu_m.sqsum();
    double term2 = ( kff - qff ).sum();
    double term3 = ( Sv % iKuu_Kuf_2 ).sum();
    double term4 = n_btc() / 2.0 * log( PI2 * s2 );

    double kl = 0.5 * ( iKuu_S.tr() + ( Mv.t() * iKuu_m ) - n_ind() )
                      + Luu.ldsum() - LSv.ldsum();

    return ( i2s2 * ( term1 + term2 + term3 ) + term4 ) / prop + kl;
}

// Hyp Gradient
const void
BigDataGP::gradientHyp( Vecd& ghyps ) const
{
    double s2 = exp( nhyps(0) );
    double is2 = 1.0 / s2;
    double i2s2 = 0.5 / s2;

    unsigned cnt = 0 , idx = 0 ;

    for( unsigned i = 0 ; i < n_mean() ; i++ )
        if( !clamps[idx++] )
        {
            ghyps[cnt++] = 0;
        }

    for( unsigned i = 0 ; i < n_cov() ; i++ )
        if( !clamps[idx++] )
        {
            Matd dKuu = gradDenseCov( Zt , KKuu , i );
            Matd dKfu = gradDenseCov( Xb , Zt , KKfu , i ) , dKuf = dKfu.t();
            Matd dkff = gradDiagCov( Xb , KKff , i );

            Matd dKfu_iKuu_m = ( dKfu - Kfu * Kuu.bslash( dKuu ) ) * iKuu_m;
            Matd Kfu_iKuu_dKuu = Kfu_iKuu * dKuu;

            Matd iKuu_dKuu_iKuu_m = Kuu.bslash( dKuu * iKuu_m );
            Matd iKuu_dKuu_iKuu_S = Kuu.bslash( dKuu * iKuu_S );

            double germ1 = - is2 * ( Yb_Kfu_iKuu_m % dKfu_iKuu_m ).sum();

            double germ2 = i2s2 * ( dkff - 2.0 * ( dKfu % Kfu_iKuu ).sumCols()
                                  + ( Kfu_iKuu_dKuu % Kfu_iKuu ).sumCols() ).sum();

            double germ3 = i2s2 * ( Sv % ( - Kuu.bslash( dKuu * iKuu_Kuf_2 )
                                           + Kuu.bslash( dKuf * Kfu_iKuu   )
                                           + ( iKuu_Kuf   * dKfu ).slash( Kuu )
                                           - ( iKuu_Kuf_2 * dKuu ).slash( Kuu ) ) ).sum();

            double germ4 = 0.5 * ( - iKuu_dKuu_iKuu_S.tr() - ( Mv.t() * iKuu_dKuu_iKuu_m )
                                   + Kuu.bslash( dKuu ).tr() );

            ghyps[cnt++] = ( germ1 + germ2 + germ3 ) / prop + germ4;
        }

    for( unsigned i = 0 ; i < n_noise() ; i++ )
        if( !clamps[idx++] )
        {
            double germ1 = i2s2 * Yb_Kfu_iKuu_m.sqsum() - n_btc() / 2.0;
            double germ2 = i2s2 * ( kff - qff ).sum();
            double germ3 = i2s2 * ( Sv % iKuu_Kuf_2 ).sum();

            ghyps[cnt++] = - ( germ1 + germ2 + germ3 ) / prop;
        }
}

// Ind Gradient
const void
BigDataGP::gradientInd( Matd& ginds ) const
{
    double s2 = exp( nhyps(0) );
    double is2 = 1.0 / s2;

    Matd iKuu = Luu.cdbslash();
    Matd Kfu_iKuu_S_iKuu = Kfu_iKuu * Sv * iKuu;

    Matd D1 = is2 * ( Yb_Kfu_iKuu_m * Mv.t() * iKuu + Kfu_iKuu - Kfu_iKuu_S_iKuu ) / prop;
    Matd D2 = is2 * ( Kfu_iKuu_S_iKuu.t() * Kfu_iKuu - iKuu * Mv * Yb_Kfu_iKuu_m.t() * Kfu_iKuu - 0.5 * iKuu_Kuf_2 ) / prop
                  + 0.5 * ( iKuu * ( Mv * Mv.t() + Sv ) * iKuu - iKuu );

    unsigned cnt = 0;

    for( unsigned i = 0 ; i < d_in() ; i++ )
    {
        Matd dKuu = gindDenseCov( Zt , i );
        Matd dKun = gindDenseCov( Zt , Xb , i );

        Matd dZi = + ( D1.t() % dKun ).sumCols()
                   + ( ( D2 + D2.t() ) % dKuu ).sumCols()
                   - D2.diag() % dKuu.diag();

        for( unsigned j = 0 ; j < dZi.r() ; j++ )
            ginds[cnt++] = - dZi(j);
    }
}

// Var Gradient
const void
BigDataGP::gradientVar( Matd& gth1 , Matd& gth2 ) const
{
    double s2 = exp( nhyps(0) );
    double is2 = 1.0 / s2;

    gth1 = is2 * Kuu.bslash( Kuf * Yb ) / prop + 2.0 * th2 * Mv;
    gth2 = - 0.5 * ( is2 * iKuu_Kuf_2 / prop + Kuu.bslash() ) - th2;
}

// Infer
const void
BigDataGP::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    Matd Kus = calcDenseCov( Zt , Xs );
    Matd kss = calcDiagCov( Xs );

    Matd A = Kuu.bslash( Kus );
    Matd B = Luu.cbslash( Kus );

    mf = Kus.t() * Luu.cdbslash( Mv );
    vf = kss + ( A % ( Sv * A ) - B.square() ).sumRows().t() + exp( nhyps(0) );
}

// Prepare Train
const void
BigDataGP::prepTrain()
{
    prop = (double)n_btc() / (double)n_tr();

    th1 = Sv.bslash( Mv );
    th2 = - 0.5 * Sv.bslash();
}

}
