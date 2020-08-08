#ifndef MEAN_STATIONARY_H
#define MEAN_STATIONARY_H

#include "../mean_base.h"

namespace cvpp
{

class MeanStationary : public MeanBase
{

protected:

public:

    const unsigned n() const { return 1; }

    // Calculate Dense
    Matd calcDense( const Matd& X ,
                    const Vecd& hyps ) const
    {
        Matd K( X.r() );

        K = hyps[0];

        return K;
    }

    // Gradient Dense
    Matd gradDense( const Matd& X , const Vecd& hyps ,
                    const Matd& K , const unsigned& i ) const
    {
        Matd G( X.r() );

        G = 1;

        return G;
    }

};

}

#endif
