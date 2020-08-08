#ifndef HM_LARD_REGRESSOR_LOGISTIC_H
#define HM_LARD_REGRESSOR_LOGISTIC_H

#include "./hm_lard_regr_base.h"

namespace cvpp
{

class HMregrLogistic : public HMregrBase
{

public:

    double intercept,timestep;
    double learning_rate;

public:

    HMregrLogistic( const double& lrate = 0.5 )
    {
        learning_rate  = lrate;
        this->weights.reset();

        timestep = 1.0;
        intercept = 0.0;
    }

    const void add( const Matd& means , const SeqMatd& covs )
    {
        Matd zeros( means.r() ); zeros.setVal(0);
        this->weights.AppD( zeros );

        Matd I( covs[0].dims() ); I.setIdentity(1e6);
        forLOOPi( covs.size() )
        {
            if( covs[i].valid() )
            {
                Matd S = ( 5.0 * covs[i] ).inv();

                double det = S.det();
                if( det > 0.0 && det < 1e10 )
                     this->orientations.push_back( S );
                else this->orientations.push_back( I );
            }
            else this->orientations.push_back( I );
        }

        this->kdtree.add( means );
    }

    const void train( const Sprd& feats , const Matd& labels )
    {
        double prob , precomp , wsum ;

        forLOOPsprdout( feats )
        {
            wsum = 0;
            forLOOPsprdin( feats )
                wsum += it.value() * this->weights[ it.index() ];

            prob = 1.0 / ( 1.0 + std::exp( - ( intercept + wsum ) ) );
            precomp = learning_rate * ( labels[k] - prob );

            forLOOPsprdin( feats )
                this->weights[ it.index() ] += precomp * it.value();

            intercept += precomp;
        }
    }

    Matd query( const Sprd& feats ) const
    {
        Matd wsums = feats * this->weights;
        Matd res( wsums.r() );

        #pragma omp parallel for
        forLOOPi( res.r() )
            res[i] = 1.0 / ( 1.0 + std::exp( - ( wsums[i] + intercept ) ) );
        return res;
    }

};

}

#endif



