#ifndef LIK_BASE_H
#define LIK_BASE_H

#include "./func_base.h"

namespace cvpp
{

class LikBase : public FuncBase
{

protected:

public:

    LikBase();

    virtual Matd calc( const Matd& , const Matd& ) { disp("LIK_BASE CALC"); }

    virtual Matd grad1() const { disp("LIK_BASE GRAD1"); }
    virtual Matd grad2() const { disp("LIK_BASE GRAD2"); }
    virtual Matd grad3() const { disp("LIK_BASE GRAD3"); }

};

}

#endif
