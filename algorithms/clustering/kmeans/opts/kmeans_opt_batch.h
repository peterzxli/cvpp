#ifndef KMEANS_OPT_BATCH_H
#define KMEANS_OPT_BATCH_H

#include "../kmeans_opt.h"
#include "../kmeans_init.h"

namespace cvpp
{

class KMoptBATCH : public KMopt
{

protected:

    double btc,thr;
    double lrate,ldecr;

    SMatd batches;
    Mati II , Q;

public:

    KMoptBATCH( const double& btc = 0.1 , const double& ldecr = 1.0 , const double& thr = 0.0 )
    {
        this->btc = btc;
        this->ldecr = ldecr;
        this->thr = thr;
    }

    // Start
    const void start( KMdata* data )
    {
        KMopt::start( data );
        Q.reset( m() ); lrate = 1.0;

        if( btc < 1.0 ) btc *= n();
        btc = std::round( btc );
    }

    // Loop
    const bool loop()
    {
        c()++;

        Q.setVal( 0 );
        batches = X().splitRandRows( btc );

        forLOOPi( batches.size() )
        {
            II = batches[i].closestRowsLBL( Z() );

            forLOOPj( btc )
            {
                int lbl = II( j );
                Q( lbl )++;

                double eta = lrate / Q( lbl );
                Z( lbl ) = ( 1.0 - eta ) * Z( lbl ) + eta * batches[i].row( j );
            }
        }

        recalcM();
        I() = X().closestRowsLBL( Z() );
        lrate *= ldecr;

        return dpot() > thr;
    }
};

}

#endif



//batches = splitRandRows( b );

//error = 0;
//forLOOPj( batches.size() )
//{
//    II = batches[j].closestRowsLBL( ctr );

//    pctr = ctr;
//    forLOOPk( b )

//    {
//        int lbl = II(k);
//        Q(lbl)++;

//        double eta = 1.0 / Q(lbl);
//        ctr.row(lbl) = ( 1.0 - eta ) * ctr.row(lbl) + eta * batches[j].row(k);
//    }
//    error += ( pctr.eig() - ctr.eig() ).norm();
//}

//error /= batches.size();
//}
