#ifndef COV_RATQUAD_H
#define COV_RATQUAD_H

#include "../cov_base.h"

namespace cvpp
{

class CovRatQuad : public CovBase
{

protected:

public:

    // Constructor
    CovRatQuad( const unsigned& type = ISO ) : CovBase( type )
    {
    }

    // Hyp Number
    const unsigned n() const
    {
        return 2;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        Matd k( X.r() );
        k = exp( hyps[-1] );
        return k;
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        Matd S = LSeqMat1( hyps , 0 , X1.c() );
        Matd D = dist2( X1 * S , X2 * S ) ;

        double alpha = exp( hyps[-2] );
        Matd D2 = D / ( 2.0 * alpha ) + 1.0;

        return exp( hyps[-1] ) * D2.pow( - alpha );
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
                Matd D = dist2( X1 * S , X2 * S );

                double alpha = exp( hyps[-2] );
                Matd D2 = D / ( 2.0 * alpha ) + 1.0;

                return exp( hyps[-1] ) * D / D2.pow( alpha + 1.0 );
            }

            if( i == 1 )
            {
                Matd S = LSeqMat1( hyps , 0 , X1.c() );
                Matd D = dist2( X1 * S , X2 * S );

                double alpha = exp( hyps[-2] );
                Matd D2 = D / ( 2.0 * alpha ) + 1.0;

                return exp( hyps[-1] ) * ( 0.5 * D / D2.pow( alpha + 1.0 )
                                           - alpha * D2.log() / D2.pow( alpha ) );
            }

            if( i == 2 )
            {
                return K;
            }

        case ARD:

            disp("NO COV HYPARD DENSE GRADIENT");
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
