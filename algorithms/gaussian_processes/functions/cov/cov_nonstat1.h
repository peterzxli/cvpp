#ifndef COV_NonStat11_H
#define COV_NonStat11_H

#include "../cov_base.h"

namespace cvpp
{

class CovNonStat1 : public CovBase
{

protected:

public:

    // Constructor
    CovNonStat1( const unsigned& type = CST ) : CovBase( type )
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
        return calcDense( X , X , hyps ).diagonal();
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        Seqd SS1( X1.r() ); if( X1.c() == 2 ) forLOOPi( X1.r() ) SS1[i] = X1(i,1);
        Seqd SS2( X2.r() ); if( X2.c() == 2 ) forLOOPi( X2.r() ) SS2[i] = X2(i,1);

        Matd K( X1.r() , X2.r() );
        if( X1.c() == 2 && X2.c() == 2 )
        {
            #pragma omp parallel for
            forLOOPi( X1.r() )
            {
                double m2,dm,m1 = X1(i,0);

                forLOOPj( X2.r() )
                {
                    m2 = X2(j,0) , dm = m2 - m1;

                    double S = ( SS1[i] + SS2[j] ) / 2.0;
                    double V = ( pow( SS1[i] , 0.25 ) * pow( SS2[j] , 0.25 ) ) / pow( S , 0.5 );
                    double P = dm * dm , Q = P / S;

//                    K(i,j) = exp( hyps[0] ) * V * covSqExp( Q );
                    K(i,j) = V * covThinplate( Q );
                }
            }
        }
        else
        if( X1.c() == 1 && X2.c() == 2 )
        {
            double SS1 = 0.01;

            #pragma omp parallel for
            forLOOPj( X2.r() )
            {
                double m1,dm,m2 = X2(j,0);

                double S = ( SS1 + SS2[j] ) / 2.0;
                double V = ( pow( SS1 , 0.25 ) * pow( SS2[j] , 0.25 ) ) / pow( S , 0.5 );

                forLOOPi( X1.r() )
                {
                    m1 = X1(i,0) , dm = m2 - m1;

                    double P = dm * dm , Q = P / S;

//                    K(i,j) = exp( hyps[0] ) * V * covSqExp( Q );
                    K(i,j) = V * covThinplate( Q );
                }
            }
        }

        return K;
    }

    double covSqExp( const double& r2 ) const
    {
        return exp( - 0.5 * r2 );
    }

    double covThinplate( const double& r2 ) const
    {
        double r = sqrt( r2 );
        double R = 100 , R2 = pow( R , 2.0 );
        double C = 1.0 + 2.0 * log( R );

        return pow( r , 2.0 ) * ( 2.0 * log( r + 1e-6 ) - C ) + R2;
    }

};

}

#endif
