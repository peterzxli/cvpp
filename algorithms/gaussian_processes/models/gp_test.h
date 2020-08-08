#ifndef GP_TEST_H
#define GP_TEST_H

#include "./gp_base.h"

#include <cvpp/algorithms/gaussian_processes/functions/draw/draw_full.h>

namespace cvpp
{

class TestGP : public BaseGP
{

protected:

    Matd Kuu,Kun,Knu,knn,qnn;
    Matd Luu,V,M,Lm,LSv,beta,iKuu;

    Matd iKuu_Kun,Knu_iKuu,iKuu_Kun_2;
    Matd iKuu_m,iKuu_S,Knu_iKuu_m;

    SeqMatd KKuu,KKun,NNuu,kknn;

public:

    unsigned flag;

public:

    TestGP();
    ~TestGP();

    unsigned n_lik() const { return 0; }
    const void setDraw() { draw = new DrawFull( this ); }

    TestGP& solve();
    const void infer( const Matd& , Matd& , Matd& ) const;
    double likelihood() const;
    double gradient( Seqd& ) const;

};

}

#endif
