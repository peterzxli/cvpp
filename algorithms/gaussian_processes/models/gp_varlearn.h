#ifndef GP_VARLEARN_H
#define GP_VARLEARN_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionSS.h"

namespace cvpp
{

class VarLearnGP : public BaseGP
{

protected:

    Matd Kuu,Kun,Knu,knn;
    Matd Luu,Lm,V,M,S,beta;

    SeqMatd KKuu,KKun,NNu,kknn;

public:

    VarLearnGP();
    ~VarLearnGP();

    const void setDraw() { draw = new DrawRegressionSS( this ); }

    VarLearnGP& solve();
    double likelihood() const;
    const void infer( const Matd& , Matd& , Matd& ) const;
    double gradient( Seqd& ) const;

};

}

#endif
