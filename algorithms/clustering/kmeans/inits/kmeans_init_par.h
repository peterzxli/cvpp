#ifndef KMEANS_INIT_PAR_H
#define KMEANS_INIT_PAR_H

#include "../kmeans_init.h"

namespace cvpp
{

class KMinitPAR : public KMinit
{

protected:

    Matd D;

    int l , mm ;
    double o ;

public:

    KMinitPAR( const int& l , const double& o )
    {
        this->l = l;
        this->o = o;
    }

    // Start
    const void start( KMdata* data )
    {
        KMinit::start( data );
        mm = o * m(); Z().reset( 2 * mm , d() );

        Z( c()++ ) = X( randi( 0 , n() ) );
        startM();
    }

    // Loop
    const bool loop()
    {
        double sum = M().sum() / l ;

        int st = c();
        forLOOPi( n() )
        {
            if( M(i) / sum > randd() )
                Z( c()++ ) = X( i );
        }

        updateM( st );
        return c() < mm;
    }

    // Finish
    const void finish()
    {
        D.reset( c() ).setVal(0);
        forLOOPi( n() ) D( I(i) )++;
        forLOOPii( 1 , c() ) D(i) = D(i-1) + D(i);

        Matd ZZ( m() , d() );
        #pragma omp parallel for
        forLOOPi( m() )
        {
            double rndd = randd( 0 , n() );
            int j = 0 ; while( rndd >= D(j) ) j++;
            ZZ.row(i) = Z(j);
        }

        Z() = ZZ;
        I() = X().closestRowsLBL( Z() );
        recalcM();
    }

};

}

#endif
