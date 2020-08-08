#ifndef HM_SHAPE_REGRESSOR_LOGISTIC_H
#define HM_SHAPE_REGRESSOR_LOGISTIC_H

#include "./hm_shape_regr_base.h"

namespace cvpp
{

class HMregrLogistic : public HMregrBase
{

public:

    double learning_rate;

public:

    HMregrLogistic( const double& lrate = 0.5 )
    {
        learning_rate  = lrate;
        this->weights.reset();
    }

    const void add( const Matd& means ,
                    const SeqMatd& covs )
    {
        this->weights.AppD( MatZEROSd( means.r() ) );

        forLOOPi( covs.size() )
        {
            this->covs.push_back( 4.0 * covs[i] );
            this->icovs.push_back( ( 2.0 * covs[i] ).inv() );

            Matd val,vec;
            this->covs.back().eigen( val , vec );
            this->vals.push_back( val );
            this->vecs.push_back( vec );
        }

        if( this->ctrs.empty() )
             this->ctrs = means.clone();
        else this->ctrs |= means;
    }

    const void add( const Matd& means ,
                    const SeqMatd& covs , const SeqMatd& icovs ,
                    const SeqMatd& vals , const SeqMatd& vecs )
    {
        this->weights.AppD( MatZEROSd( means.r() ) );

        forLOOPi( covs.size() )
        {
            this->covs.push_back( covs[i] );
            this->icovs.push_back( icovs[i] );
            this->vals.push_back( vals[i] );
            this->vecs.push_back( vecs[i] );
        }

        if( this->ctrs.empty() )
             this->ctrs = means.clone();
        else this->ctrs |= means;
    }

    const void add( const Matd& means , const Matd& modes ,
                    const SeqMatd& covs , const SeqMatd& icovs ,
                    const SeqMatd& vals , const SeqMatd& vecs )
    {
        add( means , covs , icovs , vals ,vecs );

        if( this->modes.empty() )
             this->modes = modes.clone();
        else this->modes |= modes;
    }

    const void train( const Matd& feats , const Matd& labels )
    {
        double prob , precomp , wsum ;

        forLOOPi( feats.r() )
        {
            wsum = 0;
            forLOOPj( feats.c() / 2 )
                wsum += feats(i,2*j+1) * weights[ feats(i,2*j) ];

            prob = 1.0 / ( 1.0 + std::exp( - ( wsum ) ) );
            precomp = learning_rate * ( labels[i] - prob );

            forLOOPj( feats.c() / 2 )
                weights[ feats(i,2*j) ] += precomp * feats(i,2*j+1);
        }
    }

    Matd query( const Matd& feats ) const
    {
        Matd res = MatZEROSd( feats.r() );

        forLOOPi( res.r() )
        {
            forLOOPj( feats.c() / 2 )
                res(i) += feats(i,2*j+1) * weights( feats(i,2*j) );
            res[i] = 1.0 / ( 1.0 + std::exp( - ( res[i] ) ) );
        }

        return res;
    }

};

}

#endif



