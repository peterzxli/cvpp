#include "./marching3D.h"
#include "./marching3Dcases.h"

namespace cvpp
{

TPL_T Matrix<T>
marching3D( const Matrix<T>& grid ,
            const Matrix<T>& prob , const T& thr )
{
    Matrix<int> size = grid.gridSize();
    Matrix<T> res = grid.gridResolution();

    unsigned r = size(0); s3x = res(0);
    unsigned c = size(1); s3y = res(1);
    unsigned d = size(2); s3z = res(2);

    unsigned cd = c * d;

    Pt3<T> org; Pts3<T> pts;
    pts.reserve( 4 * grid.r() );

    unsigned binary , cnt;
    forLOOPijk( r - 1 , c - 1 , d - 1 )
    {
        binary = 0;
        cnt = i * cd + j * d + k;

        p1 = prob( cnt              ) - thr; if( p1 > 0 ) binary ^= 1 << 0;
        p2 = prob( cnt + 1          ) - thr; if( p2 > 0 ) binary ^= 1 << 1;
        p3 = prob( cnt + d + 1      ) - thr; if( p3 > 0 ) binary ^= 1 << 2;
        p4 = prob( cnt + d          ) - thr; if( p4 > 0 ) binary ^= 1 << 3;
        p5 = prob( cnt + cd         ) - thr; if( p5 > 0 ) binary ^= 1 << 4;
        p6 = prob( cnt + cd + 1     ) - thr; if( p6 > 0 ) binary ^= 1 << 5;
        p7 = prob( cnt + cd + d + 1 ) - thr; if( p7 > 0 ) binary ^= 1 << 6;
        p8 = prob( cnt + cd + d     ) - thr; if( p8 > 0 ) binary ^= 1 << 7;

        if( binary == 0 || binary == 255 )
            continue;

        org.x = grid( cnt , 0 );
        org.y = grid( cnt , 1 );
        org.z = grid( cnt , 2 );

        marching3Dcases( binary , org , pts );
    }

    return pts.mat().clone();
}

//template Matf marching3D( const Matf& , const Matf& , const float& );
template Matd marching3D( const Matd& , const Matd& , const double& );

TPL_T Matrix<T>
marching3D( const Matrix<T>& grid , const Matrix<int>& idx ,
            const Matrix<T>& prob , const T& thr )
{
    Matrix<int> size = grid.gridSize();
    Matrix<T> res = grid.gridResolution();

    unsigned r = size(0); s3x = res(0);
    unsigned c = size(1); s3y = res(1);
    unsigned d = size(2); s3z = res(2);

    unsigned cd = c * d;

    Pt3<T> org; Pts3<T> pts;
    pts.reserve( 4 * grid.r() );

    unsigned binary , cnt;
    forLOOPi( idx.r() )
    {
        binary = 0;
        cnt = idx(i);

        p1 = prob( cnt              ) - thr; if( p1 > 0 ) binary ^= 1 << 0;
        p2 = prob( cnt + 1          ) - thr; if( p2 > 0 ) binary ^= 1 << 1;
        p3 = prob( cnt + d + 1      ) - thr; if( p3 > 0 ) binary ^= 1 << 2;
        p4 = prob( cnt + d          ) - thr; if( p4 > 0 ) binary ^= 1 << 3;
        p5 = prob( cnt + cd         ) - thr; if( p5 > 0 ) binary ^= 1 << 4;
        p6 = prob( cnt + cd + 1     ) - thr; if( p6 > 0 ) binary ^= 1 << 5;
        p7 = prob( cnt + cd + d + 1 ) - thr; if( p7 > 0 ) binary ^= 1 << 6;
        p8 = prob( cnt + cd + d     ) - thr; if( p8 > 0 ) binary ^= 1 << 7;

        if( binary == 0 || binary == 255 )
            continue;

        org.x = grid( cnt , 0 );
        org.y = grid( cnt , 1 );
        org.z = grid( cnt , 2 );

        marching3Dcases( binary , org , pts );
    }

    return pts.mat().clone();
}

//template Matf marching3D( const Matf& , const Matf& , const float& );
template Matd marching3D( const Matd& , const Mati& , const Matd& , const double& );








//////////////////////////////////////////////////////////////////////////////////////////////

TPL_T Pts3<T>
marching3D( const Matrix<int>& size ,  const Matrix<T>& res ,
            const Matrix<T>& grid , const Matrix<int>& idx ,
            const Matrix<T>& prob , const T& thr )
{
    unsigned r = size(0); s3x = res(0);
    unsigned c = size(1); s3y = res(1);
    unsigned d = size(2); s3z = res(2);

    unsigned cd = c * d;

    Pt3<T> org; Pts3<T> pts;
    pts.reserve( 4 * grid.r() );

    unsigned binary , cnt;
    forLOOPi( idx.r() )
    {
        binary = 0;
        cnt = idx(i);

        p1 = prob( cnt              ) - thr; if( p1 > 0 ) binary ^= 1 << 0;
        p2 = prob( cnt + 1          ) - thr; if( p2 > 0 ) binary ^= 1 << 1;
        p3 = prob( cnt + d + 1      ) - thr; if( p3 > 0 ) binary ^= 1 << 2;
        p4 = prob( cnt + d          ) - thr; if( p4 > 0 ) binary ^= 1 << 3;
        p5 = prob( cnt + cd         ) - thr; if( p5 > 0 ) binary ^= 1 << 4;
        p6 = prob( cnt + cd + 1     ) - thr; if( p6 > 0 ) binary ^= 1 << 5;
        p7 = prob( cnt + cd + d + 1 ) - thr; if( p7 > 0 ) binary ^= 1 << 6;
        p8 = prob( cnt + cd + d     ) - thr; if( p8 > 0 ) binary ^= 1 << 7;

        if( binary == 0 || binary == 255 )
            continue;

        org.x = grid( cnt , 0 );
        org.y = grid( cnt , 1 );
        org.z = grid( cnt , 2 );

        marching3Dcases( binary , org , pts );
    }

    return pts;
}

//template Matf marching3D( const Matf& , const Matf& , const float& );
template Pts3d marching3D( const Mati& , const Matd& , const Matd& , const Mati& , const Matd& , const double& );

TPL_T Matrix<T>
marching3D( const Matrix<T>& grid , const Matrix<int>& idx ,
            const Matrix<T>& prob , const T& thr , const T& batch )
{
    Matrix<int> size = grid.gridSize();
    Matrix<T> res = grid.gridResolution();

    int b = std::floor( (T)idx.r() * batch );

    Seq<Pts3d> pts( b + 1 );

    #pragma omp parallel for
    forLOOPi( b ) pts[i] = marching3D( size , res , grid , idx.r( i * b , b ) , prob , thr );
    pts.back() = marching3D( size , res,  grid , idx.rd( idx.r() - b * batch ) , prob , thr );

    int qty = 0;
    forLOOPi( pts.size() ) qty += pts[i].n();

    Matd mat( qty , 3 );

    #pragma omp parallel for
    forLOOPi( b ) mat.r( i * b , b ) = pts[i].mat();
    mat.rd( pts.back().n() ) = pts.back().mat();

    return mat;
}

//template Matf marching3D( const Matf& , const Matf& , const float& );
template Matd marching3D( const Matd& , const Mati& , const Matd& , const double& , const double& );

//////////////////////////////////////////////////////////////////////////////////////////////

















}

