#ifndef RKS_FEAT_BASE
#define RKS_FEAT_BASE

#include <cvpp/containers/matrix.h>

namespace cvpp
{

class RKSfeatBase
{

public:

    virtual double mlt() const { disp("BASE RKS MLT"); }
    virtual Matd calc( const Matd& ) const { disp("BASE RKS FEATURE"); }

};

}

#endif
