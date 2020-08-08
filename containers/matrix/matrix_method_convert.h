#include "../matrix.h"

namespace cvpp
{

// Convert (NEW)
TPL_T TPL_U inline Matrix<U>
Matrix<T>::convert() const
{
    Matrix<U> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < tmp.r() ; i++ )
        for( unsigned j = 0 ; j < tmp.c() ; j++ )
            tmp(i,j) = at(i,j);

    return tmp;
}

// To RGBjet (NEW)
TPL_T inline Matrix<float>
Matrix<T>::toRGBjet( const T& min , const T& max ) const
{
    Matrix<float> rgb( r() , 3 );

    #pragma omp parallel for
    forLOOPi( r() )
    {
        double c = ( at(i) - min ) / ( max - min + 1e-6 );
        c = std::min( 1.0 , c );

        if( c <= 0.33 )
        { c = ( c - 0.00 ) / 0.33 ; rgb.row(i) << 0.0 , c , 1.0 ;
        } else
        if( c <= 0.66 )
        { c = ( c - 0.33 ) / 0.33 ; rgb.row(i) << c , 1.0 , 1.0 - c ;
        } else
        if( c <= 1.00 )
        { c = ( c - 0.67 ) / 0.33 ; rgb.row(i) << 1.0 , 1.0 - c , 0.0 ;
        }
    }

    rgb.Ceil( 1.0 ).Floor( 0.0 );

    return rgb;
}

// To DEPjet (NEW)
TPL_T inline Matrix<float>
Matrix<T>::toDEPjet( const T& min , const T& max ) const
{
    Matrix<float> rgb( r() , 3 );

    int p[8];
    forLOOPi( 8 )
        p[i] = std::pow( 2 , i );

    #pragma omp parallel for
    forLOOPi( r() )
    {
        double c = ( at(i) - min ) / ( max - min );
        c = std::min( 1.0 , std::max( 0.0 , c ) ) * std::pow( 256 , 3 );

        std::bitset<24> bit( c );
        unsigned r = 0 , g = 0 , b = 0;

        forLOOPj( 8 )
        {
            r += p[j] * bit[ j +  0 ];
            g += p[j] * bit[ j +  8 ];
            b += p[j] * bit[ j + 16 ];
        }

        rgb.row(i) << r , g , b ;
    }

    rgb /= 256;
    return rgb;
}

// To RGBbnd (NEW)
TPL_T inline Matrix<float>
Matrix<T>::toRGBbnd( const T& min , const T& max , const T& bnd , const T& pad ) const
{
    Matrix<float> rgb( r() , 3 );

    T bndu = bnd + pad;
    T bndd = bnd - pad;
    T pad2 = 2.0 * pad;

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {
        double c = ( at(i) - min ) / ( max - min + 1e-6 );

        if( c <= bndd )
        { c = ( c - 0.00 ) / bndd ; rgb.row(i) << 0.0 , c , 1.0 ;
        } else
        if( c <= bndu )
        { c = ( c - bndd ) / pad2 ; rgb.row(i) << c , 1.0 , 1.0 - c ;
        } else
        if( c <= 1.00 )
        { c = ( c - bndu ) / bndd ; rgb.row(i) << 1.0 , 1.0 - c , 0.0 ;
        }
    }

    return rgb;
}

#ifdef OPENCV_FOUND

// To RGB Label (NEW)
TPL_T inline Matrix<float>
Matrix<T>::toRGBlbl() const
{
    Matrix<float> rgb( r() , 3 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {
        Scalar clr = RGBint( at(i) );
        rgb.row(i) << clr(0) , clr(1) , clr(2) ;
    }

    return rgb;
}

#endif

// To GRAYjet (NEW)
TPL_T inline Matrix<float>
Matrix<T>::toGRAYjet( const T& min , const T& max ) const
{
    Matrix<float> gray( r() , 3 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {
        double c = ( at(i) - min ) / ( max - min + 1e-6 );
        gray.row(i) << c , c , c ;
    }

    return gray;
}

TPL_T TPL_U inline void
Matrix<T>::toROSmsg( U& msg ) const
{
    msg.layout.dim.resize( 2 );

    msg.layout.dim[0].size = r();
    msg.layout.dim[1].size = c();

    msg.data.resize( s() );
    std::copy( eig_data() , eig_data() + msg.data.size() ,
               msg.data.begin() );
}

TPL_T TPL_U inline void
Matrix<T>::fromROSmsg( const U& msg )
{
    Resize( msg.layout.dim[0].size ,
            msg.layout.dim[1].size );

    std::copy( msg.data.begin() , msg.data.begin() + msg.data.size() ,
               eig_data() );
}

}
