#ifndef KMEANS_INIT_H
#define KMEANS_INIT_H

#include "./kmeans_base.h"

namespace cvpp
{

class KMinit : public KMeansBase
{

public:

    KMinit() {}

    // Start
    virtual const void start( KMdata* data )
    {
        this->data = data;

        pot().push( NAN );
        err().push( NAN );

        Z().reset( m() , d() );
        M().reset( n() ); I().reset( n() ).setVal( 0 );
        c() = 0;
    }

    // Loop
    virtual const bool loop() {}

    // Finish
    virtual const void finish() {}

};

}

#endif
