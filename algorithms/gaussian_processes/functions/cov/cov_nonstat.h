#ifndef COV_NONSTAT_H
#define COV_NONSTAT_H

#include "../cov_base.h"

namespace cvpp
{

class CovNonStat : public CovBase
{

protected:

public:

    // Constructor
    CovNonStat( const unsigned& type = CST ) : CovBase( type )
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
        return calcDense( X , X , hyps ).diagonal();
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        SeqMatd SS1( X1.r() ); Seqd DD1( X1.r() );
        if( X1.c() == 6 )
        {   forLOOPi( X1.r() )
            {
                SS1[i] = X1.b(i,2,1,4).reshape(2,2) * 2.0;
                DD1[i] = SS1[i].det();
            }
        }

        SeqMatd SS2( X2.r() ); Seqd DD2( X2.r() );
        if( X2.c() == 6 )
        {   forLOOPi( X2.r() )
            {
                SS2[i] = X2.b(i,2,1,4).reshape(2,2) * 2.0;
                DD2[i] = SS2[i].det();
            }
        }

        Matd K( X1.r() , X2.r() );

        if( X1.c() == 6 && X2.c() == 6 )
        {
            #pragma omp parallel for
            forLOOPi( X1.r() )
            {
                Matd m1(1,2);
                m1 << X1(i,0) , X1(i,1);

                Matd m2(1,2),dm(1,2);
                forLOOPj( X2.r() )
                {
                    m2 << X2(j,0) , X2(j,1);
                    dm = m2 - m1;

                    double V,P,Q;
                    Matd S = ( SS1[i] + SS2[j] ) / 2.0;
                    V = ( pow( DD1[i] , 0.25 ) * pow( DD2[j] , 0.25 ) ) / pow( S.det() , 0.5 );

                    P = dm * dm.t();
                    Q = dm * S.inv() * dm.t();

//                    K(i,j) = V * covSqExp( Q );
//                    K(i,j) = V * covThinplate( Q );

//                    K(i,j) = covSqExp( P );
                    K(i,j) = covThinplate( P );
//                    K(i,j) = V * covSqExp( Q ) + covThinplate( P );
                }
            }
        }
        else
        if( X1.c() == 2 && X2.c() == 6 )
        {
            Matd SS1 = Mat22d( 0.01 , 0.0 , 0.0 , 0.01 );
            double DD1 = SS1.det();

            #pragma omp parallel for
            forLOOPj( X2.r() )
            {
                Matd m2(1,2);
                m2 << X2(j,0) , X2(j,1);

                double V,P,Q;
                Matd S = ( SS1 + SS2[j] ) / 2.0;
                V = ( pow( DD1 , 0.25 ) * pow( DD2[j] , 0.25 ) ) / pow( S.det() , 0.5 );
                Matd iS = S.inv();

                Matd m1(1,2),dm(1,2);
                forLOOPi( X1.r() )
                {
                    m1 << X1(i,0) , X1(i,1);
                    dm = m2 - m1;

                    P = dm * dm.t();
                    Q = dm * iS * dm.t();

//                    K(i,j) = V * covSqExp( Q );
//                    K(i,j) = V * covThinplate( Q );

//                    K(i,j) = covSqExp( P );
                    K(i,j) = covThinplate( P );
//                    K(i,j) = V * covSqExp( Q ) + covThinplate( P );
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
