#include "../matrix.h"

namespace cvpp
{

// Make 3D dataset
TPL_T Matrix<T>&
Matrix<T>::make3Ddataset( const Matrix<T>& origin , Matrix<T>& X , Matrix<T>& Y ,
                          Matrix<T>& Xs , Matrix<T>& Xi , Matrix<T>& Xo )
{
    Matrix<T> start,delta;

    if( origin.r() == 1 )
         start = origin.repRows( r() );
    else start = origin;
    delta = *this - start;

    Xs = start + 1.00 * delta;
    Xi = start + 1.10 * delta;
    Xo = start + 0.90 * delta;

//    Xi.SampleRows( 0 , 2 );
//    Xo.SampleRows( 1 , 2 );

    Matrix<T> Ys( Xs.r() ); Ys.setVal( 0);
    Matrix<T> Yi( Xi.r() ); Yi.setVal(+1);
    Matrix<T> Yo( Xo.r() ); Yo.setVal(-1);

    X.AppD( Xs ).AppD( Xi ).AppD( Xo );
    Y.AppD( Ys ).AppD( Yi ).AppD( Yo );

    return *this;
}

// Make 3D dataset
TPL_T Matrix<T>&
Matrix<T>::make3DdatasetGP( const Matrix<T>& start , Matrix<T>& X , Matrix<T>& Y ,
                            Matrix<T>& Xs , Matrix<T>& Xi , Matrix<T>& Xo )
{
    Matrix<T> delta = *this - start;

    Xs = ( start + 1.00 * delta );
    Xi = ( start + 1.10 * delta ).sampleRows( 3 );

    Xo = start.clone();
    Matrix<T> rand( delta.r() ); rand.setRand( 0.1 , 0.9 );
    for( unsigned i = 0 ; i < Xo.r() ; i++ )
    {
        double rnd = ( i % 3 == 0 ? 0.9 : rand[i] );
        Xo.row(i) += rnd * delta.row(i);
    }

    Matrix<T> Ys( Xs.r() ); Ys.setVal( 0);
    Matrix<T> Yi( Xi.r() ); Yi.setVal(+1);
    Matrix<T> Yo( Xo.r() ); Yo.setVal(-1);

    X.AppD( Xs ).AppD( Xi ).AppD( Xo );
    Y.AppD( Ys ).AppD( Yi ).AppD( Yo );

    return *this;
}

// Make 3D dataset
TPL_T Matrix<T>&
Matrix<T>::makeSCANdataset( Matrix<T>& X , Matrix<T>& Y , const T& step )
{
    Matrix<T> org = c(0,3) , pts = c(3,3) , delta = pts - org;
    Matrix<int> qty = ( delta.magnCols() / step ).Ceil().toInt();

    X.reset( qty.r() + qty.sum() , 3 );
    Y.reset( X.r() );

    int cnt = 0;
    forLOOPi( qty.r() )
    {   forLOOPj( qty(i) )
        {
            X.r(cnt) = org.r(i) + ( (T)j + 0.99 * randd() ) / (T)qty(i) * delta.r(i);
            Y(cnt++) = 0;
        }
        X.r(cnt) = pts.r(i);
        Y(cnt++) = 1;
    }
}

// Make 3D dataset
TPL_T TPL_U void
Matrix<T>::makeScanset( Matrix<T>& X , Matrix<U>& Y ,
                        const double& stp , const double& thk ,
                        const int& jmp , const double& dec ) const
{
    const int d = c() / 2;
    Matrix<T> org = cl(d) , pts = cr(d) , delta = pts - org;

    Matrix<T> magn = delta.magnCols();
    Matrix<int> qty = ( magn / stp ).Ceil().toInt();

    Matrix<int> idx( std::ceil( (double)qty.r() / (double)jmp ) );
    idx.setIncrease( 0 , jmp );

    X.reset( qty.r() + qty.sr( idx ).sum() , d );
    Y.reset( X.r() );

    delta %= ( magn - 1.1 * thk ) / magn;

    int cnt = 0;
    forLOOPi( qty.r() )
    {   if( i % jmp == 0 )
        {   forLOOPj( qty(i) )
            {   if( randd() < std::pow( dec , qty(i) - j - 1 ) )
                {
                    X.r(cnt) = org.r(i) + ( (double)j + randd() ) / (double)qty(i) * delta.r(i);
                    Y(cnt++) = 0;
                }
            }
        }
        X.r(cnt) = pts.r(i);
        Y(cnt++) = 1;
    }

    X.KeepU( cnt );
    Y.KeepU( cnt );
}

}
