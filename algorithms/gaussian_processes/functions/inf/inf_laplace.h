#ifndef INF_LAPLACE_H
#define INF_LAPLACE_H

#include "../inf_base.h"

namespace cvpp
{

class InfLaplace : public InfBase
{

protected:

public:

    InfLaplace()
    {
    }

    double calc( LikBase* lik , const Matd& alpha ,
                 const Matd& m , const Matd& y , const Matd& K )
    {
        Matd f = K * alpha + m;
        return alpha.t() * ( f - m ) / 2.0 - lik->calc( f , y ).sum();
    }

};

}

#endif
