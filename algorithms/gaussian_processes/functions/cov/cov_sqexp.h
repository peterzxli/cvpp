#ifndef COV_SQEXP_H
#define COV_SQEXP_H

#include "../cov_base.h"

namespace cvpp
{

class CovSqExp : public CovBase
{

protected:

public:

    // Constructor
    CovSqExp( const unsigned& type = ISO ) : CovBase( type )
    {
    }

    // Hyp Number
    const unsigned n() const
    {
        return 1;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        Matd K( X.r() );
        K = exp( hyps[-1] );
        return K;
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        Matd S = LSeqMat1( hyps , 0 , X1.c() );
        Matd D = dist2( X1 * S , X2 * S );

        return exp( hyps[-1] ) * ( - 0.5 * D ).exp();
    }

    // Hyp Gradient Diagonal
    Matd gradDiag( const Matd& X ,
                   const Vecd& hyps , const Matd& K , const unsigned& i ) const
    {
        switch( ls_type )
        {
        case ISO:

            if( i == 0 )
            {
                Matd G( X.r() );
                G = 0;
                return G;
            }

            if( i == 1 )
            {
                Matd G( X.r() );
                G = exp( hyps[i] );
                return G;
            }

        case ARD:

            disp("NO COV HYPARD DIAGONAL GRADIENT");
        }
    }

    // Hyp Gradient Dense
    Matd gradDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const Matd& K , const unsigned& i ) const
    {
        switch( ls_type )
        {
        case ISO:

            if( i == 0 )
            {
                Matd S = LSeqMat1( hyps , 0 , X1.c() );
                Matd D = dist2( X1 * S , X2 * S );

                return D % K;
            }

            if( i == 1 )
            {
                return K;
            }

        case ARD:

            if( i < X1.c() )
            {
                Matd S = LSeqMat1( hyps , i , 1 );
                Matd D = dist2( X1.c(i) * S , X2.c(i) * S );

                return D % K;
            }

            if( i == X1.c() )
            {
                return K;
            }
        }
    }

    // Ind Gradient Diagonal
    Matd gindDiag( const Matd& X ,
                   const Vecd& hyps , const Matd& K , const unsigned& i ) const
    {
        disp("NO COV IND DIAGONAL GRADIENT");
    }

    // Ind Gradient Dense
    Matd gindDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const Matd& K , const unsigned& i ) const
    {
        Matd S = LSeqMat2( hyps , i , 1 );
        Matd D = dist0( X1.c(i) * S , X2.c(i) * S );

        return - D % K;
    }

};

}

#endif
