#include "./mean_base.h"

namespace cvpp
{

// Constructor
MeanBase::MeanBase()
{
}

// Calculate Dense
Matd
MeanBase::calcDense( const Matd& X , const Vecd& hyps , SeqMatd& KK ) const
{
    KK.resize(1);
    KK[0] = calcDense( X , hyps );
    return KK[0];
}

// Gradient Dense (0 KK)
Matd
MeanBase::gradDense( const Matd& X , const Vecd& hyps ,
                     const unsigned& i ) const
{
    SeqMatd KK; calcDense( X , hyps , KK );
    return gradDense( X , hyps , KK , i );
}

// Gradient Dense (1 KK)
Matd
MeanBase::gradDense( const Matd& X , const Vecd& hyps ,
                     const SeqMatd& KK , const unsigned& i ) const
{
    return gradDense( X , hyps , KK[0] , i );
}

}
