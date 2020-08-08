#ifndef RKS_BASE_H
#define RKS_BASE_H

#include "../rks_feat_base.h"

namespace cvpp
{

class RKSbase
{

protected:

    Matd phi,wgt;
    RKSfeatBase* feat;

public:

    RKSbase()
    {
    }

    RKSbase( RKSfeatBase* feat ) : RKSbase()
    {
        setFeature( feat );
    }

    ~RKSbase()
    {
    }

    const Matd& getKernel()  const { return phi; }
    const Matd& getWeights() const { return wgt; }

    Matd getK() const { return phi * phi.t(); }

    RKSbase& setFeature( RKSfeatBase* feat ) { this->feat = feat; return *this; }

    virtual RKSbase& train( const Matd& , const Matd& , const int& , const double& ) { disp(" BASE RKS TRAIN" ); }
    virtual RKSbase& update( const Matd& , const Matd& ) { disp(" BASE RKS UPDATE" ); }

    virtual Matd query( const Matd& ) const { disp( "BASE RKS QUERY" ); }

};

}

#endif

