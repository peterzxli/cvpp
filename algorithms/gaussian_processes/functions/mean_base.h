#ifndef MEAN_BASE_H
#define MEAN_BASE_H

#include "./func_base.h"

namespace cvpp
{

class MeanBase : public FuncBase
{

protected:

public:

    MeanBase();

    virtual Matd calcDense( const Matd& , const Vecd& ) const { disp("MEAN_BASE CALC DENSE"); }
    virtual Matd gradDense( const Matd& , const Vecd& , const Matd& , const unsigned& ) const { disp("MEAN_BASE GRAD DENSE"); }

    Matd calcDense( const Matd& , const Vecd& , SeqMatd& ) const;

    Matd gradDense( const Matd& , const Vecd& , const unsigned& ) const;
    Matd gradDense( const Matd& , const Vecd& , const SeqMatd& , const unsigned& ) const;

};

}

#endif
