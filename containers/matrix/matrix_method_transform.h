#include "../matrix.h"

namespace cvpp
{

// Rotate X (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RotateX( const T& d )
{
    T c = std::cos( d * PI / 180 );
    T s = std::sin( d * PI / 180 );

    Matrix<T> R( 3 , 3 );
    R.eig() << 1 , 0 ,  0 ,
               0 , c , -s ,
               0 , s ,  c ;
    return mlt(R);
}

// Rotate Y (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RotateY( const T& d )
{
    T c = std::cos( d * PI / 180 );
    T s = std::sin( d * PI / 180 );

    Matrix<T> R( 3 , 3 );
    R.eig() <<  c , 0 , s ,
                0 , 1 , 0 ,
               -s , 0 , c ;
    return mlt(R);
}

// Rotate Z (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RotateZ( const T& d )
{
    T c = std::cos( d * PI / 180 );
    T s = std::sin( d * PI / 180 );

    Matrix<T> R( this->c() , this->c() );

    if( this->c() == 2 )
    {
        R.eig() << c , -s ,
                   s ,  c ;
    }
    else if( this->c() == 3 )
    {
        R.eig() << c , -s , 0 ,
                   s ,  c , 0 ,
                   0 ,  0 , 1 ;
    }

    return mlt(R);
}

#ifdef OPENCV_FOUND

// Warp (NEW)
TPL_T inline Matrix<T>
Matrix<T>::warp( const CV& cv ) const
{
    Matrix<T> M( cv , COPY );
    Matrix<T> tmp = ( ( *this & 1 ) * M.t() );

    tmp.cl(2) /= tmp.cr(1);

    return tmp.delR(1);
}

// Transform (NEW)
TPL_T inline Matrix<T>
Matrix<T>::transform( const CV& cv ) const
{
    Matrix<T> M( cv , COPY );

    Matrix<T> tmp = *this * M.cl(3).t();
    tmp += M.cr(1).t();

    return tmp;
}

// Inverse Transform (NEW)
TPL_T inline Matrix<T>
Matrix<T>::itransform( const CV& cv ) const
{
    Matrix<T> M( cv , COPY );

    Matrix<T> tmp = *this - M.cr(1).t();
    tmp *= M.cl(3);

    return tmp;
}

#endif

}
