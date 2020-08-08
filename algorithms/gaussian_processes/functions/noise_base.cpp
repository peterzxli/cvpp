#include "./noise_base.h"

namespace cvpp
{

NoiseBase::NoiseBase()
{
}

// Calculate Dense
Matd
NoiseBase::calcDense( const Matd& X , const Vecd& hyps , SeqMatd& KK ) const
{
    KK.resize(1);
    KK[0] = calcDense( X , hyps );
    return KK[0];
}

// Gradient Dense (0 KK)
Matd
NoiseBase::gradDense( const Matd& X , const Vecd& hyps ,
                      const unsigned& i ) const
{
    SeqMatd KK; calcDense( X , hyps , KK );
    return gradDense( X , hyps , KK , i );
}

// Gradient Dense (1 KK)
Matd
NoiseBase::gradDense( const Matd& X , const Vecd& hyps ,
                      const SeqMatd& KK , const unsigned& i ) const
{
    return gradDense( X , hyps , KK[0] , i );
}

}

