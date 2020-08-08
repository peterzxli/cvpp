#ifndef KMEANS_OPT_FULL_H
#define KMEANS_OPT_FULL_H

#include "../kmeans_opt.h"
#include "../kmeans_init.h"

namespace cvpp
{

class KMoptFULL : public KMopt
{

protected:

    Mati Q;
    double thr;

public:

    KMoptFULL( const double& thr = 0.0 )
    {
        this->thr = thr;
    }

    // Start
    const void start( KMdata* data )
    {
        KMopt::start( data );
        Q.reset( m() );

        loop(); c()--;
    }

    // Loop
    const bool loop()
    {
        c()++;
        recalcM();

        Matd ZZ = Z().clone();
        Z().setVal(0); Q.setVal(0);
        forLOOPi( data->n )
        {
            Z( I(i) ) += X(i);
            Q( I(i) )++;
        }

        #pragma omp parallel for
        forLOOPi( m() ) if( Q(i) == 0 ) Z(i) = ZZ.row(i) ; else Z(i) /= Q(i) ;
        err().push( ( ZZ - Z() ).sqsumCols().rsum() );

        return dpot() > thr;
    }

};

}

#endif
