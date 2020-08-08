#ifndef COV_PROD_H
#define COV_PROD_H

#include "../cov_base.h"

namespace cvpp
{

class CovProd : public CovBase
{

protected:

    Seq< CovBase* > covs;

public:

    // Constructor
    CovProd() : CovBase()
    {
    }

    // Add Covariance
    CovProd& add( CovBase* cov )
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
        k.setVal(1);

        unsigned nh , h = 0;
        for( unsigned i = 0 ; i < covs.size() ; i++ )
        {
            nh = covs[i]->ls_n( X.c() );
            k %= covs[i]->calcDiag( X , hyps( h , nh ) );
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
        K.setVal(1);

        unsigned c , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X1.c() );
            KK[c] = covs[c]->calcDense( X1 , X2 , hyps( h , nh ) );
            K %= KK[c]; h += nh;
        }

        return K;
    }

    // Hyp Gradient Diagonal
    Matd gradDiag( const Matd& X ,
                   const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        unsigned c , d , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X.c() );
            if( h + nh > i ) break;
            h += nh;
        }

        Matd G( X.r() );
        G.setVal(1);

        for( d = 0 ; d < covs.size() ; d++ )
        {
            if( d == c )
                 G %= covs[c]->gradDiag( X , hyps( h , nh ) , KK[c] , i - h );
            else G %= KK[d];
        }

        return G;
    }

    // Hyp Gradient Dense
    Matd gradDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        unsigned c , d , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            nh = covs[c]->ls_n( X1.c() );
            if( h + nh > i ) break;
            h += nh;
        }

        Matd G( X1.r() , X2.r() );
        G.setVal(1);

        for( d = 0 ; d < covs.size() ; d++ )
        {
            if( d == c )
                 G %= covs[c]->gradDense( X1 , X2 , hyps( h , nh ) , KK[c] , i - h );
            else G %= KK[d];
        }

        return G;
    }

    // Ind Gradient Diagonal
    Matd gindDiag( const Matd& X ,
                   const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        Matd G( X.r() ) , H( X.r() );
        G.setVal(0);

        unsigned c , d , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            H.setVal(1);

            nh = covs[c]->ls_n( X.c() );
            for( d = 0 ; d < covs.size() ; d++ )
            {
                if( d == c )
                     H %= covs[c]->gindDiag( X , hyps( h , nh ) , KK[c] , i );
                else H %= KK[d];
            }
            h += nh;

            G += H;
        }

        return G;
    }

    // Ind Gradient Dense
    Matd gindDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
    {
        Matd G( X1.r() , X2.r() ) , H( X1.r() , X2.r() );
        G.setVal(0);

        unsigned c , d , nh , h = 0;
        for( c = 0 ; c < covs.size() ; c++ )
        {
            H.setVal(1);

            nh = covs[c]->ls_n( X1.c() );
            for( d = 0 ; d < covs.size() ; d++ )
            {
                if( d == c )
                     H %= covs[c]->gindDense( X1 , X2 , hyps( h , nh ) , KK[c] , i );
                else H %= KK[d];
            }
            h += nh;

            G += H;
        }

        return G;
    }

};

}


#endif
