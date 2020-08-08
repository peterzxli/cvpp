#ifndef COV_SUM_H
#define COV_SUM_H

#include "../cov_base.h"

namespace cvpp
{

class CovSum : public CovBase
{

protected:

    Seq< CovBase* > covs;

public:

    // Constructor
    CovSum() : CovBase()
    {
    }

    // Add Covariance
    CovSum& add( CovBase* cov )
    {
        covs.push_back( cov );
        return *this;
    }

    // Hyp Number
    const unsigned n() const
    {
        unsigned tot = 0;
        for( unsigned i = 0 ; i < covs.size() ; i++ )
            tot += covs[i]->n();
        return tot;
    }

    // LS Hyp Number
    const unsigned ls_n( const unsigned& d ) const
    {
        unsigned tot = 0;
        for( unsigned i = 0 ; i < covs.size() ; i++ )
            tot += covs[i]->ls_n( d );
        return tot;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        Matd k( X.r() );
        k.setVal(0);

        unsigned nh , h = 0;
        for( unsigned i = 0 ; i < covs.size() ; i++ )
        {
            nh = covs[i]->ls_n( X.c() );
            k += covs[i]->calcDiag( X , hyps( h , nh ) );
            h += nh;
        }

        return k;
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , SeqMatd& KK ) const
    {
        KK.resize( covs.size() );
        Matd K( X1.r() , X2.r() );
        K.setVal(0);

        unsigned c , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X1.c() );
            KK[c] = covs[c]->calcDense( X1 , X2 , hyps( h , nh ) );
            K += KK[c]; h += nh;
        }

        return K;
    }

    // Hyp Gradient Diagonal
    Matd gradDiag( const Matd& X ,
                   const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        unsigned c , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X.c() );
            if( h + nh > i ) break;
            h += nh;
        }

        return covs[c]->gradDiag( X , hyps( h , nh ) , KK[c] , i - h );
    }

    // Hyp Gradient Dense
    Matd gradDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        unsigned c , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X1.c() );
            if( h + nh > i ) break;
            h += nh;
        }

        return covs[c]->gradDense( X1 , X2 , hyps( h , nh ) , KK[c] , i - h );
    }

    // Ind Gradient Diagonal
    Matd gindDiag( const Matd& X ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        Matd G( X.r() );
        G.setVal(0);

        unsigned c , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X.c() );
            G += covs[c]->gindDiag( X , hyps( h , nh ) , KK[c] , i );
            h += nh;
        }

        return G;
    }

    // Ind Gradient Dense
    Matd gindDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        Matd G( X1.r() , X2.r() );
        G.setVal(0);

        unsigned c , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X1.c() );
            G += covs[c]->gindDense( X1 , X2 , hyps( h , nh ) , KK[c] , i );
            h += nh;
        }

        return G;
    }

};

}

#endif
