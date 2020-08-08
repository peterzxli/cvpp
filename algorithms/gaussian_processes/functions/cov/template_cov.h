#ifndef COV_TEMPLATE_H
#define COV_TEMPLATE_H

#include "../cov_base.h"

namespace cvpp
{

class CovTEMPLATE : public CovBase
{

protected:

public:

    // Constructor
    CovTEMPLATE( const unsigned& type = ISO ) : CovBase( type )
    {
    }

    // Hyp Number
    const unsigned n() const
    {
        return 0;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        disp("NO COV DIAGONAL");
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        disp("NO COV DENSE");
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

            disp("NO COV HYPISO DENSE GRADIENT");

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
