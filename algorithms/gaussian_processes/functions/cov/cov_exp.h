#ifndef COV_EXP_H
#define COV_EXP_H

#include "../cov_base.h"

namespace cvpp
{

class CovExp : public CovBase
{

protected:

public:

    // Constructor
    CovExp( const unsigned& type = ISO ) : CovBase( type )
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
        Matd D = dist1( X1 * S , X2 * S );

        return exp( hyps[-1] ) * ( - D ).exp();
    }

    // Hyp Gradient Diagonal
    Matd gradDiag( const Matd& X ,
                   const Vecd& hyps , const Matd& K , const unsigned& i ) const
    {
        switch( ls_type )
        {
        case ISO:

            disp("NO COV HYPISO DIAGONAL GRADIENT");

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
                Matd D = dist1( X1 * S , X2 * S );

                return D % K;
            }

            if( i == 1 )
            {
                return K;
            }

        case ARD:

            disp("NO COV HYPARD DENSE GRADIENT");
        }

        return K;
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
        disp("NO COV IND DENSE GRADIENT");
    }

};

}

#endif
