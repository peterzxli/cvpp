#ifndef KMEANS_OPT_H
#define KMEANS_OPT_H

#include "./kmeans_base.h"

namespace cvpp
{

class KMopt : public KMeansBase
{

public:

    KMopt() {}

    // Start
    virtual const void start( KMdata* data )
    {
        this->data = data;
        err().push( PINF );

        c() = 0;
    }

    // Loop
    virtual const bool loop() {}

    // Finish
    virtual const void finish() {}

};

}

#endif
