#ifndef GP_LOCAL_SUM_H
#define GP_LOCAL_SUM_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionSS.h"

namespace cvpp
{

TPL_T
class LocalSumGP : public BaseGP
{

public:

    int k;

    T* gpQuery;
    Vector<T*,unsigned,0> gpTrain;
    KDtreed tree;

public:

    LocalSumGP<T>( const unsigned& );
    ~LocalSumGP<T>();

    const void setDraw() { draw = new DrawRegressionSS( this ); }

    LocalSumGP<T>& solve();
    double likelihood() const;
    const void infer( const Matd& , Matd& , Matd& ) const;

    const void prepTrain();

};

}

#include "gp_local_sum_src.h"

#endif





