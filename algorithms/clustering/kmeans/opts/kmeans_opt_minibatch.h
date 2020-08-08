#ifndef KMEANS_OPT_MINIBATCH_H
#define KMEANS_OPT_MINIBATCH_H

#include "../kmeans_opt.h"
#include "../kmeans_init.h"

namespace cvpp
{

class KMoptMINIBATCH : public KMopt
{

protected:

    double btc,thr;

    Matd B ;
    Mati II , Q , R ;


public:

    KMoptMINIBATCH( const double& btc = 0.1 , const double& thr = 0.0 )
    {
        this->btc = btc;
        this->thr = thr;
    }

    // Start
    const void start( KMdata* data )
    {
        KMopt::start( data );
        Q.reset( m() ).setVal(0); B.reset( m() );
        R.reset( n() ).setIncrease();

        if( btc < 1.0 ) btc *= n();
        btc = std::round( btc );
    }

    // Loop
    const bool loop()
    {
        c()++;

        forLOOPi( std::ceil( n() / btc ) )
        {
            R.ShuffleRows();
            B = X().sampleRows( R.keepU( btc ) );
            II = B.closestRowsLBL( Z() );

            forLOOPj( btc )
            {
                int lbl = II( j );

                double eta = 1.0 / ( ++Q( lbl ) );
                Z( lbl ) = ( 1.0 - eta ) * Z( lbl ) +
                           (       eta ) * B.row( j );
            }
        }

        recalcM();
        I() = X().closestRowsLBL( Z() );

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
