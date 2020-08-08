#include "../matrix.h"

namespace cvpp
{

// Make 2D Grid

TPL_T inline Matrix<T>
MatGrid2( const T& xi , const T& xf ,
          const T& yi , const T& yf ,
          const T& xs , const T& ys )
{
    unsigned nx = std::round( ( xf - xi ) / xs ) + 1 ;
    unsigned ny = std::round( ( yf - yi ) / ys ) + 1 ;

    Matrix<T> tmp( nx * ny , 2 );

    for( unsigned cnt = 0 , i = 0 ; i < nx ; i++ )
    {   for( unsigned j = 0 ; j < ny ; j++ )
        {
            tmp( cnt , 0 ) = xi + T(i) * xs ;
            tmp( cnt , 1 ) = yi + T(j) * ys ;
            cnt++;
        }
    }

    return tmp;
}

inline auto MatGrid2i( const int& xi , const int& xf , const int& yi , const int& yf , const int& xs , const int& ys ) { return MatGrid2<int>( xi , xf , yi , yf , xs , ys ); }
inline auto MatGrid2f( const float& xi , const float& xf , const float& yi , const float& yf , const float& xs , const float& ys ) { return MatGrid2<float>( xi , xf , yi , yf , xs , ys ); }
inline auto MatGrid2d( const double& xi , const double& xf , const double& yi , const double& yf , const double& xs , const double& ys ) { return MatGrid2<double>( xi , xf , yi , yf , xs , ys ); }

TPL_T inline Matrix<T> MatGrid2( const T& xi , const T& xf , const T& yi , const T& yf , const T& s )
{ return MatGrid2<T>( xi , xf , yi , yf , s , s ); }

inline auto MatGrid2i( const int& xi , const int& xf , const int& yi , const int& yf , const int& s ) { return MatGrid2<int>( xi , xf , yi , yf , s ); }
inline auto MatGrid2f( const float& xi , const float& xf , const float& yi , const float& yf , const float& s ) { return MatGrid2<float>( xi , xf , yi , yf , s ); }
inline auto MatGrid2d( const double& xi , const double& xf , const double& yi , const double& yf , const double& s ) { return MatGrid2<double>( xi , xf , yi , yf , s ); }

TPL_T inline Matrix<T> MatGrid2( const T& i , const T& f , const T& s )
{ return MatGrid2<T>( i , f , i , f , s ); }

inline auto MatGrid2i( const int& i , const int& f , const int& s ) { return MatGrid2<int>( i , f , s ); }
inline auto MatGrid2f( const float& i , const float& f , const float& s ) { return MatGrid2<float>( i , f , s ); }
inline auto MatGrid2d( const double& i , const double& f , const double& s ) { return MatGrid2<double>( i , f , s ); }

TPL_T inline Matrix<T> MatGrid2( const Matrix<T>& mat , const T& s , const T& px = 0.0 , const T& py = 0.0 )
{ T minx = mat.c(0).min() , maxx = mat.c(0).max() , miny = mat.c(1).min() , maxy = mat.c(1).max();
  T difx = px * ( maxx - minx ) , dify = py * ( maxy - miny );
  return MatGrid2( minx - difx , maxx + difx , miny - dify , maxy + dify , s ); }

inline auto MatGrid2i( const Matrix<int>& mat , const int& s , const int& px = 0.0 , const int& py = 0.0 ) { return MatGrid2<int>( mat , s , px , py ); }
inline auto MatGrid2f( const Matrix<float>& mat , const float& s , const float& px = 0.0 , const float& py = 0.0 ) { return MatGrid2<float>( mat , s , px , py ); }
inline auto MatGrid2d( const Matrix<double>& mat , const double& s , const double& px = 0.0 , const double& py = 0.0 ) { return MatGrid2<double>( mat , s , px , py ); }

TPL_T inline Matrix<T> MatGrid2( const Matrix<T>& mat )
{ return MatGrid2<T>( 0 , mat.r() - 1 , 0 , mat.c() - 1 , 1 ); }

inline auto MatGrid2i( const Matrix<int>& mat ) { return MatGrid2<int>( mat ); }
inline auto MatGrid2f( const Matrix<float>& mat ) { return MatGrid2<float>( mat ); }
inline auto MatGrid2d( const Matrix<double>& mat ) { return MatGrid2<double>( mat ); }

// Make 2D Trid

TPL_T inline Matrix<T>
MatTrid2( const T& xi , const T& xf ,
          const T& yi , const T& yf ,
          const T& xs , const T& ys )
{
    unsigned nx = std::round( ( xf - xi ) / xs ) + 1 ;
    unsigned ny = std::round( ( yf - yi ) / ys ) + 1 ;

    Matrix<T> tmp( nx * ny + ( nx - 1 ) * ( ny - 1 ) , 2 );

    int cnt = 0;
    for( int i = 0 ; i < 2 * nx - 1 ; i += 1 )
    {
        T off = i % 2 == 0 ? 0.0 : 0.5 * ys;
        int set = off == 0.0 ? 0 : 1;

        for( int j = 0 ; j < ny - set ; j += 1 )
        {
            tmp.row( cnt++ ) << xi + 0.5 * T(i) * xs,
                                yi + 1.0 * T(j) * ys + off ;
        }
    }

    return tmp;
}

inline auto MatTrid2i( const int& xi , const int& xf , const int& yi , const int& yf , const int& xs , const int& ys ) { return MatTrid2<int>( xi , xf , yi , yf , xs , ys ); }
inline auto MatTrid2f( const float& xi , const float& xf , const float& yi , const float& yf , const float& xs , const float& ys ) { return MatTrid2<float>( xi , xf , yi , yf , xs , ys ); }
inline auto MatTrid2d( const double& xi , const double& xf , const double& yi , const double& yf , const double& xs , const double& ys ) { return MatTrid2<double>( xi , xf , yi , yf , xs , ys ); }

TPL_T inline Matrix<T> MatTrid2( const T& xi , const T& xf , const T& yi , const T& yf , const T& s )
{ return MatTrid2<T>( xi , xf , yi , yf , s , s ); }

inline auto MatTrid2i( const int& xi , const int& xf , const int& yi , const int& yf , const int& s ) { return MatTrid2<int>( xi , xf , yi , yf , s ); }
inline auto MatTrid2f( const float& xi , const float& xf , const float& yi , const float& yf , const float& s ) { return MatTrid2<float>( xi , xf , yi , yf , s ); }
inline auto MatTrid2d( const double& xi , const double& xf , const double& yi , const double& yf , const double& s ) { return MatTrid2<double>( xi , xf , yi , yf , s ); }

TPL_T inline Matrix<T> MatTrid2( const T& i , const T& f , const T& s )
{ return MatTrid2<T>( i , f , i , f , s ); }

inline auto MatTrid2i( const int& i , const int& f , const int& s ) { return MatTrid2<int>( i , f , s ); }
inline auto MatTrid2f( const float& i , const float& f , const float& s ) { return MatTrid2<float>( i , f , s ); }
inline auto MatTrid2d( const double& i , const double& f , const double& s ) { return MatTrid2<double>( i , f , s ); }

TPL_T inline Matrix<T> MatTrid2( const Matrix<T>& mat , const T& s , const T& px = 0.0 , const T& py = 0.0 )
{ T minx = mat.c(0).min() , maxx = mat.c(0).max() , miny = mat.c(1).min() , maxy = mat.c(1).max();
  T difx = px * ( maxx - minx ) , dify = py * ( maxy - miny );
  return MatTrid2( minx - difx , maxx + difx , miny - dify , maxy + dify , s ); }

inline auto MatTrid2i( const Matrix<int>& mat , const int& s , const int& px = 0.0 , const int& py = 0.0 ) { return MatTrid2<int>( mat , s , px , py ); }
inline auto MatTrid2f( const Matrix<float>& mat , const float& s , const float& px = 0.0 , const float& py = 0.0 ) { return MatTrid2<float>( mat , s , px , py ); }
inline auto MatTrid2d( const Matrix<double>& mat , const double& s , const double& px = 0.0 , const double& py = 0.0 ) { return MatTrid2<double>( mat , s , px , py ); }

TPL_T inline Matrix<T> MatTrid2( const Matrix<T>& mat )
{ return MatTrid2<T>( 0 , mat.r() - 1 , 0 , mat.c() - 1 , 1 ); }

inline auto MatTrid2i( const Matrix<int>& mat ) { return MatTrid2<int>( mat ); }
inline auto MatTrid2f( const Matrix<float>& mat ) { return MatTrid2<float>( mat ); }
inline auto MatTrid2d( const Matrix<double>& mat ) { return MatTrid2<double>( mat ); }

// Make 3D Grid

TPL_T inline Matrix<T>
MatGrid3( const T& xi , const T& xf ,
          const T& yi , const T& yf ,
          const T& zi , const T& zf ,
          const T& xs , const T& ys , const T& zs )
{
    unsigned nx = std::round( ( xf - xi ) / xs ) + 1 ;
    unsigned ny = std::round( ( yf - yi ) / ys ) + 1 ;
    unsigned nz = std::round( ( zf - zi ) / zs ) + 1 ;

    Matrix<T> tmp( nx * ny * nz , 3 );

    for( unsigned cnt = 0 , i = 0 ; i < nx ; i++ )
    {   for( unsigned j = 0 ; j < ny ; j++ )
        {   for( unsigned k = 0 ; k < nz ; k++ )
            {
                tmp( cnt , 0 ) = xi + T(i) * xs;
                tmp( cnt , 1 ) = yi + T(j) * ys;
                tmp( cnt , 2 ) = zi + T(k) * zs;
                cnt++;
            }
        }
    }

    return tmp;
}

inline auto MatGrid3i( const int& xi , const int& xf , const int& yi , const int& yf , const int& zi , const int& zf , const int& xs , const int& ys , const int& zs ) { return MatGrid3<int>( xi , xf , yi , yf , zi , zf , xs , ys , zs ); }
inline auto MatGrid3f( const float& xi , const float& xf , const float& yi , const float& yf , const float& zi , const float& zf , const float& xs , const float& ys , const float& zs ) { return MatGrid3<float>( xi , xf , yi , yf , zi , zf , xs , ys , zs ); }
inline auto MatGrid3d( const double& xi , const double& xf , const double& yi , const double& yf , const double& zi , const double& zf , const double& xs , const double& ys , const double& zs ) { return MatGrid3<double>( xi , xf , yi , yf , zi , zf , xs , ys , zs ); }

TPL_T inline Matrix<T> MatGrid3( const T& xi , const T& xf , const T& yi , const T& yf , const T& zi , const T& zf , const T& s )
{ return MatGrid3<T>( xi , xf , yi , yf , zi , zf , s , s , s ); }

inline auto MatGrid3i( const int& xi , const int& xf , const int& yi , const int& yf , const int& zi , const int& zf , const int& s ) { return MatGrid3<int>( xi , xf , yi , yf , zi , zf , s ); }
inline auto MatGrid3f( const float& xi , const float& xf , const float& yi , const float& yf , const float& zi , const float& zf , const float& s ) { return MatGrid3<float>( xi , xf , yi , yf , zi , zf , s ); }
inline auto MatGrid3d( const double& xi , const double& xf , const double& yi , const double& yf , const double& zi , const double& zf , const double& s ) { return MatGrid3<double>( xi , xf , yi , yf , zi , zf , s ); }

TPL_T inline Matrix<T> MatGrid3( const T& i , const T& f , const T& s )
{ return MatGrid3<T>( i , f , i , f , i , f , s ); }

inline auto MatGrid3i( const int& i , const int& f , const int& s ) { return MatGrid3<int>( i , f , s ); }
inline auto MatGrid3f( const float& i , const float& f , const float& s ) { return MatGrid3<float>( i , f , s ); }
inline auto MatGrid3d( const double& i , const double& f , const double& s ) { return MatGrid3<double>( i , f , s ); }

TPL_T inline Matrix<T> MatGrid3( const Matrix<T>& mat , const T& s )
{ Matrix<T> lim = mat.limRows();
  return MatGrid3( lim(0,0) , lim(1,0) , lim(0,1) , lim(1,1) , lim(0,2) , lim(1,2) , s ); }

inline auto MatGrid3i( const Matrix<int>& lim , const int& s ) { return MatGrid3<int>( lim , s ); }
inline auto MatGrid3f( const Matrix<float>& lim , const float& s ) { return MatGrid3<float>( lim , s ); }
inline auto MatGrid3d( const Matrix<double>& lim , const double& s ) { return MatGrid3<double>( lim , s ); }

// Make 2D Circle

TPL_T inline Matrix<T>
MatCircle2( const T& x  , const T& y  ,
            const T& ri , const T& rf , const int& n )
{
    Matrix<T> tmp( n , 2 );
    for( unsigned i = 0 ; i < tmp.r() ; ++i )
    {
        double a = randd( 0 , PI2 ) , r = randd( ri , rf );
        tmp.row(i) << x + r * std::cos( a ) ,
                      y + r * std::sin( a ) ;
    }

    return tmp;
}

inline auto MatCircle2i( const int& x , const int& y , const int& ri , const int& rf , const int& n ) { return MatCircle2<int>( x , y , ri , rf , n ); }
inline auto MatCircle2f( const float& x , const float& y , const float& ri , const float& rf , const int& n ) { return MatCircle2<float>( x , y , ri , rf , n ); }
inline auto MatCircle2d( const double& x , const double& y , const double& ri , const double& rf , const int& n ) { return MatCircle2<double>( x , y , ri , rf , n ); }

// Make 3D Circle

TPL_T inline Matrix<T>
MatCircle3( const T& x  , const T& y  , const T& z ,
            const T& ri , const T& rf , const int& n )
{
    Matrix<T> tmp( n , 3 );
    for( unsigned i = 0 ; i < tmp.r() ; ++i )
    {
        double a = randd( 0 , PI2 ) , b = randd( 0 , PI ) , r = randd( ri , rf );
        tmp.row(i) << x + r * std::sin( b ) * std::cos( a ) ,
                      y + r * std::sin( b ) * std::sin( a ) ,
                      z + r * std::cos( b ) ;
    }

    return tmp;
}

inline auto MatCircle3i( const int& x , const int& y , const int& z , const int& ri , const int& rf , const int& n ) { return MatCircle3<int>( x , y , z , ri , rf , n ); }
inline auto MatCircle3f( const float& x , const float& y , const float& z , const float& ri , const float& rf , const int& n ) { return MatCircle3<float>( x , y , z , ri , rf , n ); }
inline auto MatCircle3d( const double& x , const double& y , const double& z , const double& ri , const double& rf , const int& n ) { return MatCircle3<double>( x , y , z , ri , rf , n ); }

// Make 3D Triangle

TPL_T inline Matrix<T>
MatTriang3( const Matrix<T>& pts , const int& n )
{
    Matrix<T> tmp( n , 3 );
    forLOOPi( tmp.r() )
    {
        double r1 = sqrt( randd() );
        double r2 = randd();

        forLOOPj( tmp.c() )
        {
            tmp(i,j) =          ( 1 - r1 ) * pts(j,0) +
                       ( r1 * ( 1 - r2 ) ) * pts(j,1) +
                               ( r1 * r2 ) * pts(j,2) ;
        }
    }

//    Matrix<T> R = algl::rotationTwoVec( Mat13d( 1.0 , 0.0 , 0.0 ) ,
//                                        alg::normal( pts ) );

//    Matrix<T> noise = MatZEROS<T>( n , 3 );
//    noise.c(0).setRand( 0.1 ); tmp += noise * R;

    return tmp;
}

inline auto MatTriang3i( const Mati& pts , const int& n ) { return MatTriang3<int>( pts , n ); }
inline auto MatTriang3f( const Matf& pts , const int& n ) { return MatTriang3<float>( pts , n ); }
inline auto MatTriang3d( const Matd& pts , const int& n ) { return MatTriang3<double>( pts , n ); }

// Make 2D Wall

TPL_T inline Matrix<T>
MatWall2( const T& xi , const T& xf ,
          const T& yi , const T& yf , const int& n )
{
    Matrix<T> tmp( n , 2 );

    tmp.c(0).setRand( xi , xf );
    tmp.c(1).setRand( yi , yf );

    return tmp;
}

inline auto MatWall2i( const int& xi , const int& xf , const int& yi , const int& yf , const int& n ) { return MatWall2<int>( xi , xf , yi , yf , n ); }
inline auto MatWall2f( const float& xi , const float& xf , const float& yi , const float& yf , const int& n ) { return MatWall2<float>( xi , xf , yi , yf , n ); }
inline auto MatWall2d( const double& xi , const double& xf , const double& yi , const double& yf , const int& n ) { return MatWall2<double>( xi , xf , yi , yf , n ); }

// Make 3D wall

TPL_T inline Matrix<T>
MatWall3( const T& xi , const T& xf,
          const T& yi , const T& yf ,
          const T& zi , const T& zf , const int& n )
{
    Matrix<T> tmp( n , 3 );

    tmp.c(0).setRand( xi , xf );
    tmp.c(1).setRand( yi , yf );
    tmp.c(2).setRand( zi , zf );

    return tmp;
}

inline auto MatWall3i( const int& xi , const int& xf , const int& yi , const int& yf , const int& zi , const int& zf , const int& n ) { return MatWall3<int>( xi , xf , yi , yf , zi , zf , n ); }
inline auto MatWall3f( const float& xi , const float& xf , const float& yi , const float& yf , const float& zi , const float& zf , const int& n ) { return MatWall3<float>( xi , xf , yi , yf , zi , zf , n ); }
inline auto MatWall3d( const double& xi , const double& xf , const double& yi , const double& yf , const double& zi , const double& zf , const int& n ) { return MatWall3<double>( xi , xf , yi , yf , zi , zf , n ); }

}
