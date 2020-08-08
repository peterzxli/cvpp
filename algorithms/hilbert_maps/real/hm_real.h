#ifndef HM_REAL_H
#define HM_REAL_H

#include "./feats/hm_real_feat_base.h"
#include "./regrs/hm_real_regr_base.h"

namespace cvpp
{

class HMreal
{

protected:

    unsigned batch;

public:

    HMfeatBase* feature;
    HMregrBase* regressor;

    KDtreed kdtree; // Added

public:

    HMreal( HMfeatBase* , HMregrBase* , const unsigned& = 2000 );
    ~HMreal();

    Matd& ctrs() const { return regressor->ctrs; }
    Matd& weights() const { return regressor->weights; }

    SeqMatd& means() const { return regressor->means; }
    SeqMatd& vars()  const { return regressor->vars;  }
    SeqMatd& covs()  const { return regressor->covs;  }
    SeqMatd& icovs() const { return regressor->icovs; }

    void cluster( const Matd& , SeqMatd& , SeqMatd& , SeqMatd& , const double& , const int& = 5 );
    void cluster( const Matd& , const Matd& , SeqMatd& , SeqMatd& , SeqMatd& , const double& , const double& , const int& = 5 );

    HMreal& add( const SeqMatd& , const SeqMatd& , const SeqMatd& );

    Matd query( const Matd& );
    Matd query2( const Matd& , const int& nn = 5 );
    Matd query3( const Matd& , const int& nn = 5 );

};

}

#endif
