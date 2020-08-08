#ifndef RKS_FASTFOOD_H
#define RKS_FASTFOOD_H

#include <cvpp/containers/matrix.h>
#include <cvpp/algorithms/random_kitchen_sinks/models/rks_base.h>

#include <boost/math/special_functions/gamma.hpp>

namespace cvpp
{

class RKSfastfood : public RKSbase
{

protected:

    int d,n,k;
    double sgm;

    Matd B,G,T,S,I;
    Mati P;

public:

    RKSfastfood();
    RKSfastfood( const int& , const int& , const double& );

    ~RKSfastfood();

    const void initialise( const int& , const int& , const double& );

    RKSfastfood& train( const Matd& , const Matd& );
    Matd query( const Matd& ) const;

    Matd pad( const Matd& ) const;
    Matd fwht( const Matd& ) const;

    Matd kernel( const Matd& ) const;

};

}

#endif

