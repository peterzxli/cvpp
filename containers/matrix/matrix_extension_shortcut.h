#include "../matrix.h"

namespace cvpp
{

// IDENTITY

TPL_T
inline auto MatIDTY( const int& n , const T& v = 1 )
{ Matrix<T> tmp( n , n ); tmp.setIdentity( v ); return tmp; }

inline auto MatIDTYi( const int& n , const int& v = 1 ) { return MatIDTY<int>( n , v ); }
inline auto MatIDTYf( const int& n , const float& v = 1 ) { return MatIDTY<float>( n , v ); }
inline auto MatIDTYd( const int& n , const double& v = 1 ) { return MatIDTY<double>( n , v ); }
inline auto MatIDTYu( const int& n , const int& v = 1 ) { return MatIDTY<unsigned>( n , v ); }

// ZEROS

TPL_T
inline auto MatZEROS( const int& r = 1 , const int& c = 1 )
{ Matrix<T> tmp( r , c ); tmp.setVal( 0 ); return tmp; }

inline auto MatZEROSi( const int& r = 1 , const int& c = 1 ) { return MatZEROS<int>( r , c ); }
inline auto MatZEROSf( const int& r = 1 , const int& c = 1 ) { return MatZEROS<float>( r , c ); }
inline auto MatZEROSd( const int& r = 1 , const int& c = 1 ) { return MatZEROS<double>( r , c ); }
inline auto MatZEROSu( const int& r = 1 , const int& c = 1 ) { return MatZEROS<unsigned>( r , c ); }

// ONES

TPL_T
inline auto MatONES( const int& r = 1 , const int& c = 1 )
{ Matrix<T> tmp( r , c ); tmp.setVal( 1 ); return tmp; }

inline auto MatONESi( const int& r = 1 , const int& c = 1 ) { return MatONES<int>( r , c ); }
inline auto MatONESf( const int& r = 1 , const int& c = 1 ) { return MatONES<float>( r , c ); }
inline auto MatONESd( const int& r = 1 , const int& c = 1 ) { return MatONES<double>( r , c ); }
inline auto MatONESu( const int& r = 1 , const int& c = 1 ) { return MatONES<unsigned>( r , c ); }

// INCREASE

TPL_T
inline auto MatINCR( const int& r , const int& c , const T& i , const T& j )
{ Matrix<T> tmp( r , c ); tmp.setIncrease( i , j ); return tmp; }

inline auto MatINCRi( const int& r , const int& c , const int& i , const int& j ) { return MatINCR<int>( r , c , i , j ); }
inline auto MatINCRf( const int& r , const int& c , const float& i , const float& j ) { return MatINCR<float>( r , c , i , j ); }
inline auto MatINCRd( const int& r , const int& c , const double& i , const double& j ) { return MatINCR<double>( r , c , i , j ); }
inline auto MatINCRu( const int& r , const int& c , const int& i , const int& j ) { return MatINCR<unsigned>( r , c , i , j ); }

TPL_T
inline auto MatINCR( const int& r , const T& i , const T& j )
{ Matrix<T> tmp( r , 1 ); tmp.setIncrease( i , j ); return tmp; }

inline auto MatINCRi( const int& r , const int& i , const int& j ) { return MatINCR<int>( r , i , j ); }
inline auto MatINCRf( const int& r , const float& i , const float& j ) { return MatINCR<float>( r , i , j ); }
inline auto MatINCRd( const int& r , const double& i , const double& j ) { return MatINCR<double>( r , i , j ); }
inline auto MatINCRu( const int& r , const int& i , const int& j ) { return MatINCR<unsigned>( r , i , j ); }

TPL_T
inline auto MatINCR( const int& r , const T& j = 1 )
{ Matrix<T> tmp( r , 1 ); tmp.setIncrease( 0 , j ); return tmp; }

inline auto MatINCRi( const int& r , const int& j = 1 ) { return MatINCR<int>( r , j ); }
inline auto MatINCRf( const int& r , const float& j = 1 ) { return MatINCR<float>( r , j ); }
inline auto MatINCRd( const int& r , const double& j = 1 ) { return MatINCR<double>( r , j ); }
inline auto MatINCRu( const int& r , const int& j = 1 ) { return MatINCR<unsigned>( r , j ); }

// INTERVAL

TPL_T
inline auto MatINTRV( const int& r , const int& c , const T& i , const T& f )
{ Matrix<T> tmp( r , c ); tmp.setInterval( i , f ); return tmp; }

inline auto MatINTRVi( const int& r , const int& c , const int& i , const int& f ) { return MatINTRV<int>( r , c , i , f ); }
inline auto MatINTRVf( const int& r , const int& c , const float& i , const float& f ) { return MatINTRV<float>( r , c , i , f ); }
inline auto MatINTRVd( const int& r , const int& c , const double& i , const double& f ) { return MatINTRV<double>( r , c , i , f ); }
inline auto MatINTRVu( const int& r , const int& c , const int& i , const int& f ) { return MatINTRV<unsigned>( r , c , i , f ); }

TPL_T
inline auto MatINTRV( const int& r , const T& i , const T& f )
{ Matrix<T> tmp( r , 1 ); tmp.setInterval( i , f ); return tmp; }

inline auto MatINTRVi( const int& r , const int& i , const int& f ) { return MatINTRV<int>( r , i , f ); }
inline auto MatINTRVf( const int& r , const float& i , const float& f ) { return MatINTRV<float>( r , i , f ); }
inline auto MatINTRVd( const int& r , const double& i , const double& f ) { return MatINTRV<double>( r , i , f ); }
inline auto MatINTRVu( const int& r , const int& i , const int& f ) { return MatINTRV<unsigned>( r , i , f ); }

TPL_T
inline auto MatINTRV( const int& r , const T& f )
{ Matrix<T> tmp( r , 1 ); tmp.setInterval( f ); return tmp; }

inline auto MatINTRVi( const int& r , const int& f ) { return MatINTRV<int>( r , f ); }
inline auto MatINTRVf( const int& r , const float& f ) { return MatINTRV<float>( r , f ); }
inline auto MatINTRVd( const int& r , const double& f ) { return MatINTRV<double>( r , f ); }
inline auto MatINTRVu( const int& r , const int& f ) { return MatINTRV<unsigned>( r , f ); }

// RANDOM

TPL_T
inline auto MatRAND( const int& r , const int& c , const T& min , const T& max )
{ Matrix<T> tmp( r , c ); tmp.setRand( min , max ); return tmp; }

inline auto MatRANDi( const int& r , const int& c , const int& min , const int& max ) { return MatRAND<int>( r , c , min , max ); }
inline auto MatRANDf( const int& r , const int& c , const float& min , const float& max ) { return MatRAND<float>( r , c , min , max ); }
inline auto MatRANDd( const int& r , const int& c , const double& min , const double& max ) { return MatRAND<double>( r , c , min , max ); }
inline auto MatRANDu( const int& r , const int& c , const int& min , const int& max ) { return MatRAND<unsigned>( r , c , min , max ); }

TPL_T
inline auto MatRAND(  const int& r , const int& c = 1 ) { return MatRAND<T>( r , c , 0 , 1 ); }
inline auto MatRANDi( const int& r , const int& c = 1 ) { return MatRAND<int>( r , c ); }
inline auto MatRANDf( const int& r , const float& c = 1 ) { return MatRAND<float>( r , c ); }
inline auto MatRANDd( const int& r , const double& c = 1 ) { return MatRAND<double>( r , c ); }
inline auto MatRANDu( const int& r , const int& c = 1 ) { return MatRAND<unsigned>( r , c ); }

TPL_T
inline auto MatRAND(  const int& r , const int& c , const T& val ) { return MatRAND<T>( r , c , -val , +val ); }
inline auto MatRANDi( const int& r , const int& c , const int& val ) { return MatRAND<int>( r , c , val ); }
inline auto MatRANDf( const int& r , const float& c , const float& val ) { return MatRAND<float>( r , c , val ); }
inline auto MatRANDd( const int& r , const double& c , const double& val ) { return MatRAND<double>( r , c , val ); }
inline auto MatRANDu( const int& r , const int& c , const int& val ) { return MatRAND<unsigned>( r , c , val ); }

// NEW

TPL_T inline auto MatXX( const int& r = 1 , const int& c = 1 ) { return Matrix<T>( r , c ); }
TPL_T inline auto MatXX( const Dims& dims ) { return Matrix<T>( dims ); }

inline auto MatXXi( const int& r = 1 , const int& c = 1 ) { return MatXX<int>( r , c ); }
inline auto MatXXf( const int& r = 1 , const int& c = 1 ) { return MatXX<float>( r , c ); }
inline auto MatXXd( const int& r = 1 , const int& c = 1 ) { return MatXX<double>( r , c ); }

inline auto MatXXi( const Dims& dims ) { return MatXX<int>( dims ); }
inline auto MatXXf( const Dims& dims ) { return MatXX<float>( dims ); }
inline auto MatXXd( const Dims& dims ) { return MatXX<double>( dims ); }

// MATRIX 1 x 1

TPL_T
inline auto Mat11( const T& a )
{ Matrix<T> tmp( 1 , 1 ); tmp << a ; return tmp; }

inline auto Mat11i( const int& a ) { return Mat11<int>( a ); }
inline auto Mat11f( const float& a ) { return Mat11<float>( a ); }
inline auto Mat11d( const double& a ) { return Mat11<double>( a ); }
inline auto Mat11u( const int& a ) { return Mat11<unsigned>( a ); }

// MATRIX 2 x 1

TPL_T
inline auto Mat21( const T& a , const T& b )
{ Matrix<T> tmp( 2 , 1 ); tmp << a , b ; return tmp; }

inline auto Mat21i( const int& a , const int& b ) { return Mat21<int>( a , b ); }
inline auto Mat21f( const float& a , const float& b ) { return Mat21<float>( a , b ); }
inline auto Mat21d( const double& a , const double& b ) { return Mat21<double>( a , b ); }
inline auto Mat21u( const int& a , const int& b ) { return Mat21<unsigned>( a , b ); }

TPL_T
inline auto Mat21(  const T& a ) { return Mat21( a , a ); }
inline auto Mat21i( const int& a ) { return Mat21<int>( a ); }
inline auto Mat21f( const float& a ) { return Mat21<float>( a ); }
inline auto Mat21d( const double& a ) { return Mat21<double>( a ); }
inline auto Mat21u( const int& a ) { return Mat21<unsigned>( a ); }

// MATRIX 1 x 2

TPL_T
inline auto Mat12( const T& a , const T& b )
{ Matrix<T> tmp( 1 , 2 ); tmp << a , b ; return tmp; }

inline auto Mat12i( const int& a , const int& b ) { return Mat12<int>( a , b ); }
inline auto Mat12f( const float& a , const float& b ) { return Mat12<float>( a , b ); }
inline auto Mat12d( const double& a , const double& b ) { return Mat12<double>( a , b ); }
inline auto Mat12u( const int& a , const int& b ) { return Mat12<unsigned>( a , b ); }

TPL_T
inline auto Mat12(  const T& a ) { return Mat12( a , a ); }
inline auto Mat12i( const int& a ) { return Mat12<int>( a ); }
inline auto Mat12f( const float& a ) { return Mat12<float>( a ); }
inline auto Mat12d( const double& a ) { return Mat12<double>( a ); }
inline auto Mat12u( const int& a ) { return Mat12<unsigned>( a ); }

// MATRIX 2 x 2

TPL_T
inline auto Mat22( const T& a , const T& b , const T& c , const T& d )
{ Matrix<T> tmp( 2 , 2 ); tmp << a , b , c , d ; return tmp; }

inline auto Mat22i( const int& a , const int& b , const int& c , const int& d ) { return Mat22<int>( a , b , c , d ); }
inline auto Mat22f( const float& a , const float& b , const float& c , const float& d ) { return Mat22<float>( a , b , c , d ); }
inline auto Mat22d( const double& a , const double& b , const double& c , const float& d ) { return Mat22<double>( a , b , c , d ); }
inline auto Mat22u( const int& a , const int& b , const int& c , const int& d ) { return Mat22<unsigned>( a , b , c , d ); }

TPL_T
inline auto Mat22(  const T& a ) { return Mat22( a , a , a , a ); }
inline auto Mat22i( const int& a ) { return Mat22<int>( a ); }
inline auto Mat22f( const float& a ) { return Mat22<float>( a ); }
inline auto Mat22d( const double& a ) { return Mat22<double>( a ); }
inline auto Mat22u( const int& a ) { return Mat22<unsigned>( a ); }

// MATRIX 3 x 1

TPL_T
inline auto Mat31( const T& a , const T& b , const T& c )
{ Matrix<T> tmp( 3 , 1 ); tmp << a , b , c ; return tmp; }

inline auto Mat31i( const int& a , const int& b , const int& c ) { return Mat31<int>( a , b , c ); }
inline auto Mat31f( const float& a , const float& b , const float& c ) { return Mat31<float>( a , b , c ); }
inline auto Mat31d( const double& a , const double& b , const double& c ) { return Mat31<double>( a , b , c ); }
inline auto Mat31u( const int& a , const int& b , const int& c ) { return Mat31<unsigned>( a , b , c ); }

TPL_T
inline auto Mat31(  const T& a ) { return Mat31( a , a , a ); }
inline auto Mat31i( const int& a ) { return Mat31<int>( a ); }
inline auto Mat31f( const float& a ) { return Mat31<float>( a ); }
inline auto Mat31d( const double& a ) { return Mat31<double>( a ); }
inline auto Mat31u( const int& a ) { return Mat31<unsigned>( a ); }

// MATRIX 1 x 3

TPL_T
inline auto Mat13( const T& a , const T& b , const T& c )
{ Matrix<T> tmp( 1 , 3 ); tmp << a , b , c ; return tmp; }

inline auto Mat13i( const int& a , const int& b , const int& c ) { return Mat13<int>( a , b , c ); }
inline auto Mat13f( const float& a , const float& b , const float& c ) { return Mat13<float>( a , b , c ); }
inline auto Mat13d( const double& a , const double& b , const double& c ) { return Mat13<double>( a , b , c ); }
inline auto Mat13u( const int& a , const int& b , const int& c ) { return Mat13<unsigned>( a , b , c ); }

TPL_T
inline auto Mat13(  const T& a ) { return Mat13( a , a , a ); }
inline auto Mat13i( const int& a ) { return Mat13<int>( a ); }
inline auto Mat13f( const float& a ) { return Mat13<float>( a ); }
inline auto Mat13d( const double& a ) { return Mat13<double>( a ); }
inline auto Mat13u( const int& a ) { return Mat13<unsigned>( a ); }

}
