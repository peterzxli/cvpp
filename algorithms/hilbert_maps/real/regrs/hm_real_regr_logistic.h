#ifndef HM_REAL_REGRESSOR_LOGISTIC_H
#define HM_REAL_REGRESSOR_LOGISTIC_H

#include "./hm_real_regr_base.h"

namespace cvpp
{

class HMregrLogistic : public HMregrBase
{

public:

public:

    HMregrLogistic()
    {
        this->weights.reset();
    }

    const void add( const SeqMatd& clouds , const SeqMatd& means , const SeqMatd& covs )
    {
        this->means.resize( means.size() );
        this->vars.resize( means.size() );
        this->covs.resize( means.size() );
        this->icovs.resize( means.size() );

        Matd pts( means.size() , means[0].c() );

        #pragma omp parallel for
        forLOOPi( covs.size() )
        {
            this->means[i] = means[i];
            this->vars[i] = covs[i];

            this->covs[i] = 5.0 * covs[i];
            this->icovs[i] = this->covs[i].inv();

            pts.row(i) = means[i].eig();
        }

        this->ctrs.AppD( pts );
        this->weights.AppD( MatZEROSd( pts.r() ) );
        this->kdtree.add( pts );
    }

};

}

#endif



