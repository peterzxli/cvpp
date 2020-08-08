#ifndef GP_CLASS_H
#define GP_CLASS_H

#include "./gp_base.h"
#include "../functions/draw/draw_classificationSS.h"

namespace cvpp
{

class ClassGP : public BaseGP
{

protected:

    Matd Knn,Lnn,W,sW;
    Matd m,f,alpha;

    SeqMatd MMn,KKnn,NNn;

public:

    ClassGP();
    ~ClassGP();

    const void setDraw() { draw = new DrawClassificationSS( this ); }

    ClassGP& solve();
    double likelihood() const;
    const void infer( const Matd& , Matd& , Matd& ) const;
    double gradient( Seqd& ) const;

};

}

#endif
