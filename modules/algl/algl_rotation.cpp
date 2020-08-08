#include "../algl.h"

namespace cvpp {
namespace algl {

TPL_T Matrix<T>
rotationAxis( const Matrix<T>& v , const T& ang )
{
    double s = std::sin( ang * PI180 );
    double c = std::cos( ang * PI180 ) , cc = 1 - c ;

    Matrix<T> R( 3 , 3 );
    R.eig() <<          c + v(0) * v(0) * cc , - v(2) * s + v(1) * v(0) * cc ,   v(1) * s + v(2) * v(0) * cc ,
                 v(2) * s + v(0) * v(1) * cc ,          c + v(1) * v(1) * cc , - v(0) * s + v(2) * v(1) * cc ,
               - v(1) * s + v(0) * v(2) * cc ,   v(0) * s + v(1) * v(2) * cc ,          c + v(2) * v(2) * cc ;
    return R;
}

TPL_T Matrix<T>
rotationAxis( const Matrix<T>& W1 , const Matrix<T>& W2 , const T& ang )
{
    double s = std::sin( ang * PI180 ) , c = std::cos( ang * PI180 );
    return MatIDTY<T>(3) + W1 * s + W2 * ( 1 - c );
}

TPL_T Matrix<T>
rotationTwoVec( const Matrix<T>& v1 , const Matrix<T>& v2 )
{
    Matrix<T> W1 , W2 , v = algl::cross( v1 , v2 );
    algl::rotationAuxMat( v , W1 , W2 );

    double s = v.rsqsum() , c = algl::dot( v1 , v2 );
    return ( MatIDTY<T>(3) + W1 + W2 * ( 1 - c ) / ( s * s ) ).t();
}

TPL_T Matrix<T>
rotationAlign( const Matrix<T>& v1 , const Matrix<T>& v2 )
{
    Matrix<T> R( 3 , 3 );

    R.r(0) = v1 / v1.norm();
    Matd a = algl::cross( v1 , v2 );
    R.r(2) = a / a.norm();
    Matd b = algl::cross( R.r(2) , v1 );
    R.r(1) = b / b.norm();

    return R;
}

TPL_T void
rotationAuxMat( const Matrix<T>& v , Matrix<T>& W1 , Matrix<T>& W2 )
{
    W1.reset( 3 , 3 );
    W1.eig() <<  0.0 , -v(2) ,  v(1) ,
                 v(2) , 0.0  , -v(0) ,
                -v(1) , v(0) ,  0.0  ;
    W2 = W1 * W1;
}

}}

