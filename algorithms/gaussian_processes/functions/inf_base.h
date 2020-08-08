#ifndef INF_BASE_H
#define INF_BASE_H

#include "./func_base.h"
#include "./lik_base.h"

namespace cvpp
{

class InfBase : public FuncBase
{

protected:

public:

    InfBase();

    virtual double calc( LikBase* , const Matd& , const Matd& , const Matd& , const Matd& ) { disp("INF_BASE CALC"); }

};

}

#endif
