#ifndef HM_ORGN_H
#define HM_ORGN_H

#include "./feats/hm_orgn_feat_base.h"
#include "./regrs/hm_orgn_regr_base.h"

namespace cvpp
{

class HMorgn
{

protected:

    unsigned batch;

    HMfeatBase* feature;
    HMregrBase* regressor;

public:

    HMorgn( HMfeatBase* , HMregrBase* );
    ~HMorgn();

    unsigned totalPoints( const Seq<Sprd>& ) const;
    const Matd& weights() const { return regressor->weights; }

    const void make3Ddataset( const Matd& , Matd& , Mati& , const double& = 0.5 ) const;

    Seq<Sprd> calcFeatures( const Matd& ) const;

    const void train( const Matd& , const Mati& );
    const void train( const Matd& , const double& = 0.5 );
    const void train( const Seq<Sprd>& , const Mati& );

    Matd query( const Matd& ) const;
    Matd query( const Seq<Sprd>& ) const;

};

}

#endif
