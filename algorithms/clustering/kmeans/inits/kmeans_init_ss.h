#ifndef KMEANS_INIT_SS_H
#define KMEANS_INIT_SS_H

#include "../kmeans_init.h"

namespace cvpp
{

class KMinitSS : public KMinit
{

protected:

    Matd D,V;

    int p;
    double max,thr;

public:

    KMinitSS( const int& p , const double& thr = 0.0 )
    {
        this->p = p;
        this->thr = thr;

    }

    // Start
    const void start( KMdata* data )
    {
        KMinit::start( data );
        P().reset( p , d() ).setVal( NINF ); idx().resize( p ) ;
        D.reset( n() ); V.reset( n() ).setIncrease();

        Z( c()++ ) = X( randi( 0 , n() ) );
        startM();
    }

    // Loop
    const bool loop()
    {
        max = M().max();

//        #pragma omp parallel for
        forLOOPi( p )
        {
            while( 1 )
            {
                int rndi = V( randi( 0 , t() ) );
                if( M( rndi ) > sqrt( randd( 0 , max ) ) )
                {
                    idx(i) = rndi ;
                    P(i) = X( rndi );
                    break ;
                }
            }
        }

        float best = NINF ; int rndi ;
        forLOOPi( p )
        {
            if( M( idx(i) ) > best )
                best = M( idx(i) ) , rndi = idx(i) ;
        }
        Z( c() ) = X( rndi );

        if( thr == 0.0 )
        {
            updateM();
        }
        else
        {
            #pragma omp parallel for
            forLOOPi( t() )
            {
                int ii = V(i);
                D(ii) = ( X(ii) - Z( c() ) ).squaredNorm();
                if( D(ii) < M(ii) ) { M(ii) = D(ii) ; I(ii) = c() ; }
            }

            forLOOPi( t() )
                if( M( V(i) ) < thr ) V( i-- ) = V( --t() );
            pot().push( M().sum() );
        }

        return ++c() < m() && t() > 0;
    }

    // Finish
    const void finish()
    {
        if( c() < m() )
        {
            m() = c();
            Z().KeepU( m() );
        }
    }
};

}

#endif
