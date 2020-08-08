#ifndef NOISE_STATIONARY_H
#define NOISE_STATIONARY_H

#include "../noise_base.h"

namespace cvpp
{

class NoiseStationary : public NoiseBase
{

protected:

public:

    const unsigned n() const { return 1; }

    // Calculate Dense
    Matd calcDense( const Matd& X ,
                    const Vecd& hyps ) const
    {
        Matd K( X.r() );

        K = exp( hyps[0] );

        return K;
    }

    // Gradient Dense
    Matd gradDense( const Matd& X , const Vecd& hyps ,
                    const Matd& K , const unsigned& i ) const
    {
        return K;
    }

};

}

#endif
