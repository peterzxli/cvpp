#ifndef HM_ORGN_REGRESSOR_H
#define HM_ORGN_REGRESSOR_H

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>
#include <cvpp/algorithms/kdtree/kdtree.h>

namespace cvpp
{

class HMregrBase
{

protected:

public:

    unsigned ndims;

    double intercept,timestep;
    Matd weights,last_update;

public:

    virtual const void start( const unsigned& ) {}
    virtual const void add( const Matd& ) {}

    virtual const void train( const Sprd& , const Mati& ) {}
    virtual Matd query( const Sprd& ) const {}

};

}

#endif



