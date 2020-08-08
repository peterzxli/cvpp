#ifndef GP_SPARSE_H
#define GP_SPARSE_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionSS.h"

namespace cvpp
{

class SparseGP : public BaseGP
{

protected:

    Matd Kuu,Kun,Knu;
    Matd Luu,Lm,V,M,beta;

    SeqMatd KKuu,KKun,NNuu;

public:

    SparseGP();
    ~SparseGP();

    const void setDraw() { draw = new DrawRegressionSS( this ); }

    SparseGP& solve();
    const void infer( const Matd& , Matd& , Matd& ) const;
    double likelihood() const;
    double gradient( Seqd& ) const;

};

}

#endif
