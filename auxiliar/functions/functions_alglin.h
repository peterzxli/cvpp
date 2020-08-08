#ifndef FUNCTIONS_ALGLIN_H
#define FUNCTIONS_ALGLIN_H

#include <cvpp/containers/matrix.h>

namespace cvpp
{

TPL_T
float len( const Pt3<T>& p1 , const Pt3<T>& p2 )
{
    Pt3<T> d = p2 - p1;
    return sqrt( d.x * d.x + d.y * d.y + d.z * d.z );
}

TPL_T
Matrix<T> cross( const Matrix<T>& vec1 , const Matrix<T>& vec2 )
{
    Matrix<T> res( vec1.dims() );

    res(0) = vec1(1) * vec2(2) - vec1(2) * vec2(1);
    res(1) = vec1(2) * vec2(0) - vec1(0) * vec2(2);
    res(2) = vec1(0) * vec2(1) - vec1(1) * vec2(0);

    return res;
}

TPL_T
Pt3f cross( const Pt3<T>& vec1 , const Pt3<T>& vec2 )
{
    Pt3f res;

    res.x = vec1.y * vec2.z - vec1.z * vec2.y;
    res.y = vec1.z * vec2.x - vec1.x * vec2.z;
    res.z = vec1.x * vec2.y - vec1.y * vec2.x;

    return res;
}

TPL_T
T dot( const Matrix<T>& vec1 , const Matrix<T>& vec2 )
{
    return ( vec1 % vec2 ).sum();
}

TPL_T
T dot( const Pt3<T>& vec1 , const Pt3<T>& vec2 )
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z ;
}

// DIST

TPL_T
T len( const Pt2<T>& pt )
{
    return std::sqrt( std::pow( pt.x , 2.0 ) +
                      std::pow( pt.y , 2.0 ) );
}

TPL_T
T len( const Pt3<T>& pt )
{
    return std::sqrt( std::pow( pt.x , 2.0 ) +
                      std::pow( pt.y , 2.0 ) +
                      std::pow( pt.z , 2.0 ) );
}

TPL_T
T dist( const Pt2<T>& pt1 , const Pt2<T>& pt2 )
{
    return len( pt2 - pt1 );
}

TPL_T
T dist( const Pt3<T>& pt1 , const Pt3<T>& pt2 )
{
    return len( pt2 - pt1 );
}

TPL_T
T norm( const Pt2<T>& pt1 , const Pt2<T>& pt2 )
{
    return len( pt2 - pt1 );
}

TPL_T
T norm( const Pt3<T>& pt1 , const Pt3<T>& pt2 )
{
    return len( pt2 - pt1 );
}

TPL_T
T normAngle( const T& a )
{
    if( a < - PI ) return a + 2 * PI;
    if( a > + PI ) return a - 2 * PI;

    return a;
}

TPL_T
T orient( const Pt2<T>& pt1 , const Pt2<T>& pt2 )
{
    Pt2<T> d = pt2 - pt1;
    T a = atan2( d.y , d.x );

    return normAngle( a );
}

}

#endif
