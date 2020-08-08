#include "../matrix.h"

namespace cvpp
{

// Normal Distribution
TPL_T Matrix<T>
Matrix<T>::toDistrNormal( const T& m , const T& v )
{
    return ( 1.0 / std::sqrt( v * PI2 ) ) * ( - 0.5 / v * ( *this - m ).square() ).exp();
}


}
