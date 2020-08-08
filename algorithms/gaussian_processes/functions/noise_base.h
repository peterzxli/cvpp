#ifndef NOISE_BASE_H
#define NOISE_BASE_H

#include "./func_base.h"

namespace cvpp
{

class NoiseBase : public FuncBase
{

protected:

public:

    NoiseBase();

    virtual Matd calcDense( const Matd& , const Vecd& ) const { disp("NOISE_BASE CALC DENSE"); }
    virtual Matd gradDense( const Matd& , const Vecd& , const Matd& , const unsigned& ) const { disp("NOISE_BASE GRAD DENSE"); }

    Matd calcDense( const Matd& , const Vecd& , SeqMatd& ) const;

    Matd gradDense( const Matd& , const Vecd& , const unsigned& ) const;
    Matd gradDense( const Matd& , const Vecd& , const SeqMatd& , const unsigned& ) const;

};

}

#endif
