#include "kernel_pca.h"

namespace cvpp
{

// Constructor
KernelPCA::KernelPCA( const Matd& X , const unsigned& n , const double& gamma )
{
    this->X = X;
    this->gamma = gamma;

    K = kernel( gamma , X , X );

    I.reset( K.dims() ).setVal( 1.0 / (double)X.r() );
    Matd KK = K - I * K - K * I + I * K * I;
    KK.eigen( values , vectors );

    Mati idx = values.sortRowsIDX().flipRows();
    values.SampleRows( idx ).KeepU( n );
    vectors.SampleCols( idx ).KeepL( n );

    transf = vectors / values.t();
}

// Kernel
Matd
KernelPCA::kernel( const double& gamma , const Matd& pts1 , const Matd& pts2 ) const
{
    Matd K( pts1.r() , pts2.r() );
    for( int i = 0 ; i < K.r() ; i++ )
        for( int j = 0 ; j < K.c() ; j++ )
            K(i,j) = exp( - gamma * ( pow( pts1(i,0) - pts2(j,0) , 2.0 )
                                    + pow( pts1(i,1) - pts2(j,1) , 2.0 ) ) );
    return K;
}

Matd
KernelPCA::project( const Matd& XX ) const
{
    Matd KK = kernel( gamma , XX , X );

    Matd II( KK.dims() ); II.setVal( 1.0 / (double)X.r() );
    KK = KK - II * K - KK * I + II * K * I;

    return KK * transf;
}

}
