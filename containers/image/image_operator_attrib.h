#include "../image.h"

namespace cvpp
{

// Image >> Image
TPL_TC Image<T,C>&
Image<T,C>::operator>>( const Image<T,C>& img )
{
    cv_ptr = img.cv_ptr;
    eig_ptr = img.eig_ptr;

    return *this;
}

// Image = Image
TPL_TC Image<T,C>&
Image<T,C>::operator=( const Image<T,C>& img )
{
    if( fits( img ) )
         eig() = img.eig();
    else *this << img;

    return *this;
}

// Image << Image
TPL_TC Image<T,C>&
Image<T,C>::operator<<( const Image<T,C>& img )
{
    initialise( img.r() , img.c() );
    eig() = img.eig();

    return *this;
}

// Image >> CV
TPL_TC Image<T,C>&
Image<T,C>::operator>>( const CV& cv )
{
    cv_ptr = std::make_shared< CVImage >( cv );
    update(); return *this;
}

// Image = CV
TPL_TC Image<T,C>&
Image<T,C>::operator=( const CV& cv )
{
    if( fits( cv ) )
         cv.copyTo( this->cv() );
    else *this << cv;

    return *this;
}

// Image << CV
TPL_TC Image<T,C>&
Image<T,C>::operator<<( const CV& cv )
{
    initialise( cv.rows , cv.cols );
    cv.copyTo( this->cv() );
    return *this;
}

// Image = Matrix
TPL_TC Image<T,C>&
Image<T,C>::operator=( const Matrix<T>& mat )
{
    if( fits( mat ) )
        eig() = mat.eig();
    else *this << mat;

    return *this;
}

// Image << Matrix
TPL_TC Image<T,C>&
Image<T,C>::operator<<( const Matrix<T>& mat )
{
    initialise( mat.r() , mat.c() / d() );
    eig() = mat.eig();
    return *this;
}

}
