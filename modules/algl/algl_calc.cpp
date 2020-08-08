#include "../algl.h"

namespace cvpp {
namespace algl {

TPL_T T
dot( const Matrix<T>& v1 ,
     const Matrix<T>& v2 )
{
    T val = 0;
    forLOOPi( v1.c() ) val += v1(i) * v2(i);
    return val;
}

TPL_T Matrix<T>
cross( const Matrix<T>& v1 ,
       const Matrix<T>& v2 )
{
    Matd c( v1.dims() );
    c(0) = + ( v1(1) * v2(2) - v1(2) * v2(1) );
    c(1) = - ( v1(0) * v2(2) - v1(2) * v2(0) );
    c(2) = + ( v1(0) * v2(1) - v1(1) * v2(0) );
    return c;
}

TPL_T Matrix<T>
normal( const Matrix<T>& v1 ,
        const Matrix<T>& v2 )
{
    Matrix<T> n = algl::cross( v1 , v2 );
    return n / n.rsqsum();
}

TPL_T Matrix<T>
normal( const Matrix<T>& V )
{
    return algl::normal( V.r(1) - V.r(0) ,
                         V.r(2) - V.r(0) );
}

TPL_T Matrix<T>
normal( const Matrix<T>& v1 ,
        const Matrix<T>& v2 ,
        const Matrix<T>& v3 )
{
    return algl::normal( v2 - v1 ,
                         v3 - v1 );
}


}}

