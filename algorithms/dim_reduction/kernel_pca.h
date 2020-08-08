#ifndef KERNEL_PCA_H
#define KERNEL_PCA_H

#include <cvpp/containers/matrix.h>

namespace cvpp
{

class KernelPCA
{

protected:

    Matd K,I,X;
    Matd vectors,values,transf;

    double gamma;

public:

    KernelPCA( const Matd& , const unsigned& , const double& = 1 );

    Matd kernel( const double& , const Matd& , const Matd& ) const;

    Matd project( const Matd& ) const;

};

}

#endif
