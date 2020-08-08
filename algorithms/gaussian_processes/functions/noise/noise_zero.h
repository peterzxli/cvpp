#ifndef NOISE_ZERO_H
#define NOISE_ZERO_H

#include "../noise_base.h"

namespace cvpp
{

class NoiseZero : public NoiseBase
{

protected:

public:

    const unsigned n() const { return 0; }

    // Calculate Dense
    Matd calcDense( const Matd& X ,
                    const Vecd& hyps ) const
    {
        Matd K( X.r() );

        K = 0;

        return K;
    }

};

}

#endif
