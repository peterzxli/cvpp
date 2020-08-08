#ifndef RKS_FEAT_GAUSSIAN
#define RKS_FEAT_GAUSSIAN

#include "../rks_feat_base.h"

namespace cvpp
{

class RKSfeatGaussian : public RKSfeatBase
{

public:

    double mlt() const
    {
        return 2;
    }

    Matd calc( const Matd& XZ ) const
    {
        return XZ.sin() & XZ.cos();
    }

};

}

#endif
