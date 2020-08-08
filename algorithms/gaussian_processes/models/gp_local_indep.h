#ifndef GP_LOCAL_INDEP_H
#define GP_LOCAL_INDEP_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionLSS.h"

namespace cvpp
{

TPL_T
class LocalIndepGP : public BaseGP
{

public:

    Seq<T*> gp;

public:

    LocalIndepGP<T>();
    ~LocalIndepGP<T>();

    const void setDraw() { draw = new DrawRegressionLSS( this ); }

    LocalIndepGP<T>& train();
    const void infer( const Matd& , Matd& , Matd& ) const;

};

}

#include "gp_local_indep_src.h"

#endif





