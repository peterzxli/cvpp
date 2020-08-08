#ifndef RKS_ORIGINAL_H
#define RKS_ORIGINAL_H

#include <cvpp/containers/matrix.h>
#include <cvpp/algorithms/random_kitchen_sinks/models/rks_base.h>

namespace cvpp
{

class RKSoriginal : public RKSbase
{

protected:

    Matd Z,I;

public:

    RKSoriginal() : RKSbase() {}
    RKSoriginal( RKSfeatBase* feat ) : RKSbase( feat ) {}
    ~RKSoriginal() {}

    const Matd& getZ() const { return Z; }

    RKSoriginal& train( const Matd& , const Matd& , const int& ,
                        const double& = 1.0 , const double& = 0.1 );
    RKSoriginal& update( const Matd& , const Matd& );

    Matd query( const Matd& ) const;

};

}

#endif

