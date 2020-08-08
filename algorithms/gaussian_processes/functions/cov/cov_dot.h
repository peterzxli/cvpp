#ifndef COV_DOT_H
#define COV_DOT_H

#include "../cov_base.h"

namespace cvpp
{

class CovDot : public CovBase
{

protected:

public:

    // Constructor
    CovDot( const unsigned& type = CST ) : CovBase( type )
    {
    }

    // Hyp Number
    const unsigned n() const
    {
        return 3;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        return exp( hyps[-1] ) * ( ( X.square() ).sumCols()
                                 + exp( hyps[0] ) ).pow( hyps[1] );
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        return exp( hyps[-1] ) * ( ( X1 * X2.t() )
                                 + exp( hyps[0] ) ).pow( hyps[1] );
    }

};

}

#endif

