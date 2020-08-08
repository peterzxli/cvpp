#ifndef HM_ORGN_REGRESSOR_LOGISTIC_H
#define HM_ORGN_REGRESSOR_LOGISTIC_H

#include "./hm_orgn_regr_base.h"

namespace cvpp
{

struct LogisticParams
{
    LogisticParams( const double& init  = 0.500 ,
                    const double& lrate = 0.100 ,
                    const double& rfact = 0.001 )
    {
    }
};

class HMregrLogistic : public HMregrBase
{

protected:

public:

    double initial_learning_rate;
    double learning_rate_factor;
    double regularization_factor;

public:

    HMregrLogistic( const double& init  = 0.500 ,
                    const double& lrate = 0.100 ,
                    const double& rfact = 0.001 )
    {
        initial_learning_rate = init;
        learning_rate_factor  = lrate;
        regularization_factor = rfact;
    }

    const void start( const unsigned& n )
    {
        ndims = n;

        weights.reset( ndims ); weights.setVal(0);
        last_update.reset( ndims ); last_update.setVal(0);

        timestep = 1.0; intercept = 0.0;
    }

    const void train( const Sprd& feats , const Mati& labels )
    {
        learning_rate_factor = 0.1;
        initial_learning_rate = 0.5;
        regularization_factor = 0.001;

        unsigned idx;
        double prob , learning_rate , precomp1 , precomp2 , wsum ;

        forLOOPsprdout( feats )
        {
            wsum = 0;
            for( SEigd::InnerIterator it( feats.eig() , k ) ; it ; ++it )
                wsum += it.value() * weights[ it.index() ];

            prob = 1.0 / ( 1.0 + std::exp( - ( intercept + wsum ) ) );

            learning_rate = 1.0 / ( learning_rate_factor *
                                  ( 1.0 + learning_rate_factor
                                  * initial_learning_rate * timestep ) );

            precomp1 = 1.0 - 2.0 * learning_rate * regularization_factor;
            precomp2 = learning_rate * ( labels[k] - prob );

            forLOOPsprdin( feats )
            {
                idx = it.index();

                weights[idx] *= std::pow( precomp1 , timestep - last_update[idx] );
                weights[idx] += precomp2 * it.value();

                last_update[idx] = timestep;
            }

            intercept += precomp2;
            timestep++;
        }
    }

    Matd query( const Sprd& feats ) const
    {
        Matd wsums = feats * weights;
        Matd res( wsums.r() );

        #pragma omp parallel for
        forLOOPi( res.r() )
            res[i] = 1.0 / ( 1.0 + std::exp( - ( wsums[i] + intercept ) ) );
        return res;
    }

};

}

#endif



