#ifndef GP_FULL_H
#define GP_FULL_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionSS.h"

namespace cvpp
{

class FullGP : public BaseGP
{

protected:

    Matd Knn,Lnn;
    Matd Y0,alpha;

    SeqMatd MMn,KKnn,NNn;

public:

    FullGP();
    ~FullGP();

    const void setDraw() { draw = new DrawRegressionSS( this ); }

    FullGP& solve();
    double likelihood() const;
    const void infer( const Matd& , Matd& , Matd& ) const;
    double gradient( Seqd& ) const;

};

}

#endif
