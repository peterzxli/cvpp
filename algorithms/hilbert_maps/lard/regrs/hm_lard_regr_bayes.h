#ifndef HM_LARD_REGRESSOR_BAYES_H
#define HM_LARD_REGRESSOR_BAYES_H

#include "./hm_lard_regr_base.h"

namespace cvpp
{

TPL_T
class HMregrBayes : public HMregrBase<T>
{

protected:

public:

    Matrix<T> mf,vf;

public:

    HMregrBayes()
    {
    }

    const void add( const Matrix<T>& means , const Seq<Matrix<T>>& covs )
    {
        Matrix<T> zeros( means.r() );
        zeros.setVal(0);

        this->weights.AppRows( zeros );
        this->qty.AppRows( zeros );

        Matrix<T> I( covs[0].dims() ); I.setIdentity(1e6);
        for( unsigned i = 0 ; i < covs.size() ; i++ )
        {
            Matrix<T> S = ( 10.0 * covs[i] ).inv();
            if( S.det() > 0.0 )
                 this->orientations.push_back( S );
            else this->orientations.push_back( I );
        }

        this->kdtree.add( means );
    }

    const void train( const Sparse<T>& X , const Matrix<T>& Y )
    {
        T err,sum;

        for( unsigned k = 0 ; k < X.c() ; k++ )
        {
            sum = 0;
            for( typename SEIG<T>::InnerIterator it( X.eig() , k ) ; it ; ++it )
                sum += this->weights( it.index() ) * it.value();
            err = ( Y(k) - sum ) / 3.0;

            for( typename SEIG<T>::InnerIterator it( X.eig() , k ) ; it ; ++it )
            {
                if( it.value() > 0.1 )
                {
                    this->weights( it.index() ) += 1.0 / ( 5.0 + this->qty( it.index() ) ) * err / it.value();
                    this->qty( it.index() ) += 1;
                }
            }
        }
    }

    Matrix<T> query( const Sparse<T>& feats ) const
    {
        return ( this->weights.t() * feats ).t();
    }

};

using HMregrBayesf = HMregrBayes<float>;
using RegressorBayesd = HMregrBayes<double>;

}

#endif
