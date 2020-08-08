#ifndef MEAN_ZERO_H
#define MEAN_ZERO_H

#include "../mean_base.h"

namespace cvpp
{

class MeanZero : public MeanBase
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
