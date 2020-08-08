#ifndef COV_LIN_H
#define COV_LIN_H

#include "../cov_base.h"

namespace cvpp
{

class CovLin : public CovBase
{

protected:

public:

    // Constructor
    CovLin( const unsigned& type = ISO ) : CovBase( type )
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
        Matd S = LSeqMat2( hyps , 0 , X.c() );
        return exp( hyps[-1] ) * ( X.square() * S ).sumCols();
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        Matd S = LSeqMat2( hyps , 0 , X1.c() );
        return exp( hyps[-1] ) * X1 * S * X2.t();
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
                return - 2.0 * K;
            }

            if( i == 1 )
            {
                return K;
            }

        case ARD:

            if( i < X.c() )
            {
                Matd S = LSeqMat2( hyps , i , 1 );
                return - 2.0 * exp( hyps[-1] ) * ( X.c(i).square() * S ).sumCols();
            }

            if( i == X.c() )
            {
                return K;
            }
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
                return - 2.0 * K;
            }

            if( i == 1 )
            {
                return K;
            }

        case ARD:

            if( i < X1.c() )
            {
                Matd S = LSeqMat2( hyps , i , 1 );
                return - 2.0 * exp( hyps[-1] ) * X1.c(i) * S * X2.c(i).t();
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
        disp("NO COV IND DENSE GRADIENT");
    }

};

}

#endif

