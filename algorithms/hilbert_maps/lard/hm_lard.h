#ifndef HM_LARD_H
#define HM_LARD_H

#include "./feats/hm_lard_feat_base.h"
#include "./regrs/hm_lard_regr_base.h"

namespace cvpp
{

class HMlard
{

protected:

    unsigned batch;

public:

    HMfeatBase* feature;
    HMregrBase* regressor;

public:

    HMlard( HMfeatBase* , HMregrBase* , const unsigned& = 2000 );
    ~HMlard();

    unsigned totalPoints( const SeqSprd& ) const;
    Matd& weights() const { return regressor->weights; }

    HMlard& add( const Matd& );
    HMlard& add( const Matd& , const SeqMatd& );

    const void makeDataset( const Matd& ,
                            Matd& , Matd& , const double& = 0.5 ) const;

    SeqSprd calcFeatures( const Matd& ) const;

    HMlard& train( const Matd& , const double& = 0.5 );

    HMlard& train( const  Matd& , const Matd& );
    HMlard& train( const  Sprd& , const Matd& );
    HMlard& train( const SeqSprd& , const Matd& );

    Matd query( const Matd& ) const;
    const void query( const Matd& , Matd& , Matd& ) const;

    Matd query( const Sprd& ) const;
    const void query( const Sprd& , Matd& , Matd& ) const;

    Matd query( const SeqSprd& ) const;
    const void query( const SeqSprd& , Matd& , Matd& ) const;

};

}

#endif
