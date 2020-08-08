#ifndef KMEANS_INIT_PP_H
#define KMEANS_INIT_PP_H

#include "../kmeans_init.h"

namespace cvpp
{

class KMinitPP : public KMinit
{

protected:

    Matd D;

public:

    KMinitPP() {}

    // Start
    const void start( KMdata* data )
    {
        KMinit::start( data );
        D.reset( n() );

        Z( c()++ ) = X( randi( 0 , n() ) );
        startM();
    }

    // Loop
    const bool loop()
    {
        D(0) = M(0); forLOOPii( 1 , n() )
            D(i) = D(i-1) + M(i);

        double rndd = randd( 0 , D(-1) );
        int j = 0 ; while( rndd >= D(j) ) j++;
        Z( c() ) = X(j);

        updateM();
        return ++c() < m();
    }

};

}

#endif
