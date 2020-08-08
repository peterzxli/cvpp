#include "../image.h"

namespace cvpp
{

// Grayscale (NEW)
TPL_TC inline Image<T,1>
Image<T,C>::grayscale() const
{
    Image<T,1> tmp( dims() );
    cv::cvtColor( cv() , tmp.cv() , CV_BGR2GRAY );
    return tmp;
}

// LAB Scale (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::LABscale() const
{
    Image<T,C> tmp( dims() );
    cv::cvtColor( cv() , tmp.cv() , CV_BGR2Lab );
    return tmp;
}

// HSV Scale (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::HSVscale() const
{
    Image<T,C> tmp( dims() );
    cv::cvtColor( cv() , tmp.cv() , CV_BGR2HSV );
    return tmp;
}

// YUV Scale (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::YUVscale() const
{
    Image<T,C> tmp( dims() );
    cv::cvtColor( cv() , tmp.cv() , CV_BGR2YUV );
    return tmp;
}

// XYZ Scale (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::XYZscale() const
{
    Image<T,C> tmp( dims() );
    cv::cvtColor( cv() , tmp.cv() , CV_BGR2XYZ );
    return tmp;
}

// XYZ Scale (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::equalise() const
{
    Image<T,C> tmp( dims() );
    cv::equalizeHist( cv() , tmp.cv() );
    return tmp;
}

// Resize (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::resize( const int& r ,
                    const int& c ) const
{
    Image<T,C> tmp( r , c );

//    cv::resize( cv() , tmp.cv() ,
//                Size( tmp.c() , tmp.r() ) , 0 , 0 , cv::INTER_LINEAR );

    cv::resize( cv() , tmp.cv() ,
                Size( tmp.c() , tmp.r() ) , 0 , 0 , cv::INTER_NEAREST );

    return tmp;
}

// Resize (SELF)
TPL_TC inline Image<T,C>&
Image<T,C>::Resize( const int& r ,
                    const int& c )
{
    cv::resize( cv() , cv() ,
                Size( c , r ) , cv::INTER_LINEAR );
    update(); return *this;
}

// Normalize (NEW)
TPL_TC inline Image<T,C>
Image<T,C>::normalise( const T& low , const T& upp ) const
{
    return clone().Normalise( low , upp );
}

// Normalize (SELF)
TPL_TC inline Image<T,C>&
Image<T,C>::Normalise( const T& low , const T& upp )
{
    *this = ( *this - min() ) * ( ( upp - low ) / ntv() ) + low;
    return *this;
}

}
