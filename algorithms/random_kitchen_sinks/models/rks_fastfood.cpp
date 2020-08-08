#include "./rks_fastfood.h"

namespace cvpp
{

RKSfastfood::RKSfastfood()
{
}

RKSfastfood::RKSfastfood( const int& d , const int& n , const double& sgm )
{
    initialise( d , n , sgm );
}

const void
RKSfastfood::initialise( const int& dd , const int& nn , const double& ssgm )
{
    d = pow( 2.0 , std::ceil( std::log2( dd ) ) );
    k = std::ceil( nn / (double)d );
    n = d * k , sgm = ssgm;

    I = MatIDTYd( 2 * n , 0.1 ) ;

    B.load( "../data/allB" ); B = B.t();
    G.load( "../data/allG" ); G = G.t();
    T.load( "../data/allT" ); T = T.t();
    Matd tmp( "../data/allP" );
    P = tmp.toInt() - 1; P = P.t();

//    B = 2 * MatRANDd(k,d).round() - 1;
//    G = MatXXd(k,d).setRandn();
//    T.reset(k,d); forLOOPmat( T )
//        T(r,c) = boost::math::gamma_q_inv( (double)d / 2.0 , randd( 0 , 1 ) );
//    P.reset(k,d); forLOOPi( k )
//        P.r(i) = MatXXi(d).setIncrease().ShuffleRows().t();

    S.reset(k,d); forLOOPi( k )
        S.r(i) = ( 2.0 * T.r(i) ).sqrt() / G.r(i).rsqsum();
    S = S.toRow();
}


RKSfastfood::~RKSfastfood()
{
}

Matd
RKSfastfood::pad( const Matd& X ) const
{
    Matd XX( X.r() , d );
    XX.cl( X.c() ) = X;
    XX.cr( XX.c() - X.c() ) = 0;
    return XX;
}

Matd
RKSfastfood::fwht( const Matd& M ) const
{
    Matd X = M.rboCols();

    forLOOPiii( 0 , X.c() - 1 , 2 )
    {
        X.col(i  ) = X.col(i) + 1.0 * X.col(i+1);
        X.col(i+1) = X.col(i) - 2.0 * X.col(i+1);
    }

    Matd Y( X.r() , d );

    int L = 1;
    forLOOPii( 1 , log2(d) )
    {
        int M = pow( 2 , L );
        int J = 0 , K = 0;

        while( K < d )
        {
            forLOOPjjj( J , J + M , 2 )
            {
                Y.col(K  ) = X.col(j  ) + X.col(j+M  );
                Y.col(K+1) = X.col(j  ) - X.col(j+M  );
                Y.col(K+2) = X.col(j+1) + X.col(j+M+1);
                Y.col(K+3) = X.col(j+1) - X.col(j+M+1);

                K += 4;
            }
            J += 2 * M;
        }
        L += 1;

        X = Y;
    }

    return X / d;
}

Matd
RKSfastfood::kernel( const Matd& M ) const
{
    Matd T , X = pad( M );
    Matd THT( X.r() , n );

    forLOOPi( k )
    {
        X %= B.r(i);

        T = fwht( X );
        T = T.sc( P.r(i).t() ) % ( G.r(i) * d );
        T = fwht( T );

        THT.c( i * d , d ) = T;
    }

    THT %= S * sqrt( d );
    T = THT / sgm;

//    return ( T.cos() & T.sin() );// / sqrt( n );
    return ( T.cos() & T.sin() ) / sqrt( n );
}

RKSfastfood&
RKSfastfood::train( const Matd& X , const Matd& Y )
{
    phi = kernel( X );
    wgt = ( phi.t() * phi + I ).bslash( phi.t() * Y );

    return *this;
}

Matd
RKSfastfood::query( const Matd& X ) const
{
    return kernel( X ) * wgt;
}

}
