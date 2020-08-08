#ifndef COV_STATIONARY_H
#define COV_STATIONARY_H

#include "../cov_base.h"

namespace cvpp
{

class CovStationary : public CovBase
{

protected:

public:

    // Constructor
    CovStationary( const unsigned& type = CST ) : CovBase( type )
    {
    }

    // Hyp Number
    const unsigned n() const
    {
        return 1;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        return MatXXd( X.r() ).setVal( exp( hyps[-1] ) );
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        return MatXXd( X1.r() , X2.r() ).setVal( exp( hyps[-1] ) );
    }

};

}

#endif
