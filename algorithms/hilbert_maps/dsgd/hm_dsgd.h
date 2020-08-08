#ifndef HM_DSGD_H
#define HM_DSGD_H

#include <cvpp/algorithms/hilbert_maps/dsgd/regrs/hm_dsgd_regr_base.h>

namespace cvpp
{

class HMdsgd
{

protected:

    HMregrBase* regr;

public:

    HMdsgd( HMregrBase* , RKSfeatBase* );
    ~HMdsgd();

    const void setData( const Matd& X , const Matd& Y )
    { regr->setData( X , Y ); }

    const void setParams( const double& p1 , const double& p2 , const double& p3 , const double& p4 ,
                          const unsigned& p5 , const unsigned& p6 , const unsigned& p7 )
    { regr->setParams( p1 , p2 , p3 , p4 , p5 , p6 , p7 ); }

    const Matd& weights() const { return regr->weights(); }

    const void train();
    Matd query( const Matd& ) const;

};

}

#endif
