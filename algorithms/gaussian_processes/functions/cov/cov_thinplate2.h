#ifndef COV_THINPLATE2_H
#define COV_THINPLATE2_H

#include "../cov_base.h"

namespace cvpp
{

class CovThinPlate2 : public CovBase
{

protected:

    double C , R , R2 ;

public:

    // Constructor
    CovThinPlate2( const double& RR = 100 , const unsigned& type = CST ) : CovBase( type )
    {
        R = RR , R2 = pow( R , 2.0 );
        C = 1.0 + 2.0 * log( R );
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
        return MatXXd( X.r() ).setVal( R2 );
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        Matd K( X1.r() , X2.r() );

        #pragma omp parallel for
        for( int i = 0 ; i < X1.r() ; ++i )
        {   for( int j = 0 ; j < X2.r() ; ++j )
            {
                double r = ( X1.row(i) - X2.row(j) ).norm();
                K(i,j) = pow( r , 2.0 ) * ( 2.0 * log( r + 1e-6 ) - C ) + R2;
            }
        }

        return K;
    }

};

}

#endif
