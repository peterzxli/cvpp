#include "../image.h"

namespace cvpp
{

TPL_TC // Base Constructor
Image<T,C>::Image()
{
    initialise( 0 , 0 );
}

TPL_TC // String Constructor
Image<T,C>::Image( const String& str )
{
    load( str );
}

TPL_TC // String Constructor
Image<T,C>::Image( const String& str , const int& n )
{
    load( str , n );
}

TPL_TC // OpenCV Constructor
Image<T,C>::Image( const CV& cv ,
                   const bool& share )
{
    if( share )
         *this >> cv;
    else *this << cv;
}

TPL_TC // Image Constructor
Image<T,C>::Image( const Image<T,C>& img ,
                   const bool& share )
{
    if( share )
         *this >> img;
    else *this << img;
}

TPL_TC // Matrix Constructor
Image<T,C>::Image( const Matrix<T>& mat ,
                   const bool& share )
{
    *this << mat;
}

TPL_TC // New Constructor
Image<T,C>::Image( const int& r ,
                   const int& c )
{
    initialise( r , c );
}

TPL_TC // New Constructor
Image<T,C>::Image( const Dims& dims )
{
    initialise( dims.r , dims.c );
}

TPL_TC // Constant Constructor
Image<T,C>::Image( const int& r ,
                   const int& c , const T& val )
{
    initialise( r , c );
    setVal( val );
}

TPL_TC // Block Constructor
Image<T,C>::Image( const int& i , const int& j ,
                   const int& r , const int& c ,
                   const int& s , const int& d , CVImage img )
{
    initialise( i , j , r , c , s , d , img );
}

// New Initialise
TPL_TC void
Image<T,C>::initialise( const int& r ,
                        const int& c )
{
    cv_ptr = std::make_shared< CVImage >( r , c );

    eig_ptr = std::make_shared< IEigen > (
                   (T*)cv_ptr->data , r , c * C ,
                   Eigen::Stride< -1 , -1 >( c * C , 1 ) );
}

// Block Initialise
TPL_TC void
Image<T,C>::initialise( const int& i , const int& j ,
                        const int& r , const int& c ,
                        const int& s , const int& d , CVImage img )
{
    cv_ptr = std::make_shared< CVImage >(
                  img( cv::Rect( i , j , c , r ) ) );

    eig_ptr = std::make_shared< IEigen > (
                   (T*)cv_ptr->data + d , r , c * C ,
                   Eigen::Stride< -1 , -1 >( img.cols * C , s ) );
}

// Update
TPL_TC void
Image<T,C>::update()
{
    eig_ptr = std::make_shared< IEigen > (
                   (T*)cv_ptr->data , cv_ptr->rows , cv_ptr->cols * C ,
                   Eigen::Stride< -1 , -1 >( cv_ptr->cols * C , 1 ) );
}

}
