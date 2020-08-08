#ifndef LINEAR_PCA_H
#define LINEAR_PCA_H

#include <cvpp/containers/matrix.h>

namespace cvpp
{

class LinearPCA        
{

protected:

    Matd X,M;
    Matd vectors,values;

public:

    LinearPCA( const Matd& , const double& );

    Matd project( const Matd& ) const;


};

}

#endif
