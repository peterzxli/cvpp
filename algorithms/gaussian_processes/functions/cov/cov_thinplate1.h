#ifndef COV_THINPLATE1_H
#define COV_THINPLATE1_H

#include "../cov_base.h"

namespace cvpp
{

class CovThinPlate1 : public CovBase
{

protected:

    double C , R , R3 ;

public:

    // Constructor
    CovThinPlate1( const double& RR = 1000 , const unsigned& type = CST ) : CovBase( type )
    {
        R = RR , R3 = pow( R , 3.0 );
        C = 1.0 / 12.0;
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
        return MatXXd( X.r() ).setVal( C * R3 );
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        Matd K( X1.r() , X2.r() );
        double C = 1.0 / 12.0;

        double s = exp( hyps[0] );

        #pragma omp parallel for
        for( int i = 0 ; i < X1.r() ; ++i )
        {   for( int j = 0 ; j < X2.r() ; ++j )
            {
                double r = std::fabs( X1(i) - X2(j) ) / s;
                K(i,j) = C * ( 2.0 * pow( r , 3.0 ) - 3.0 * R * pow( r , 2.0 ) + R3 );
            }
        }

        return K;
    }

};

}

#endif
