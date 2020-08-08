#ifndef KMEANS_INIT_RND_H
#define KMEANS_INIT_RND_H

#include "../kmeans_init.h"

namespace cvpp
{

class KMinitRND : public KMinit
{

protected:

public:

    KMinitRND() {}

    // Start
    const void start( KMdata* data )
    {
        KMinit::start( data );

        Z( c()++ ) = X( randi( 0 , n() ) );
//        startM();
    }

    // Loop
    const bool loop()
    {
        Z( c() ) = X( randi( 0 , n() ) );

//        updateM();
        return ++c() < m();
    }

};

}

#endif
