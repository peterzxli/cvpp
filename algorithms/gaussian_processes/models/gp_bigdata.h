#ifndef GP_BIGDATA_H
#define GP_BIGDATA_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionSS.h"

namespace cvpp
{

class BigDataGP : public BaseGP
{

protected:

    Matd Kuu,Kuf,Kfu,Luu,LSv,kff,qff;
    Matd iKuu_Kuf,Kfu_iKuu,iKuu_Kuf_2,Kfu_iKuu_m,iKuu_m,iKuu_S;
    Matd Yb_Kfu_iKuu_m;

    SeqMatd KKuu,KKfu,KKff;

public:

    BigDataGP();
    ~BigDataGP();

    const void setDraw() { draw = new DrawRegressionSS( this ); }

    BigDataGP& solve();
    const void infer( const Matd& , Matd& , Matd& ) const;
    double likelihood() const;

    Dims d_mvar() const { return Dims( n_ind() , 1 ); }
    Dims d_svar() const { return Dims( n_ind() , n_ind() ); }

    const void gradientHyp( Vecd& ) const;
    const void gradientInd( Matd& ) const;
    const void gradientVar( Matd& , Matd& ) const;

    const void prepTrain();

};

}

#endif
