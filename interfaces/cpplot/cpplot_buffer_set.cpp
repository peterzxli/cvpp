#include "../cpplot.h"

namespace cvpp
{

// Set Buffer (Empty 2D)
TPL_T CPPlot&
CPPlot::setBuffer2D( const int& idx ,
                     const int& n )
{
    bindBuffer( idx );
    setBuffer2D<T>( n );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::setBuffer2D<int>(    const int& , const int& );
template CPPlot& CPPlot::setBuffer2D<float>(  const int& , const int& );
template CPPlot& CPPlot::setBuffer2D<double>( const int& , const int& );

// Set Buffer (Empty 2D)
TPL_T CPPlot&
CPPlot::setBuffer2D( const int& n )
{
    unsigned d = 2;

    cBuffer().n = 0; cBuffer().d = d;
    glBufferData( GL_ARRAY_BUFFER , n * d * sizeof(T) ,
                  nullptr , GL_STATIC_DRAW );

    return *this;
}

template CPPlot& CPPlot::setBuffer2D<int>(    const int& );
template CPPlot& CPPlot::setBuffer2D<float>(  const int& );
template CPPlot& CPPlot::setBuffer2D<double>( const int& );

// Set Buffer (Empty 3D)
TPL_T CPPlot&
CPPlot::setBuffer3D( const int& idx ,
                     const int& n )
{
    bindBuffer( idx );
    setBuffer3D<T>( n );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::setBuffer3D<int>(    const int& , const int& );
template CPPlot& CPPlot::setBuffer3D<float>(  const int& , const int& );
template CPPlot& CPPlot::setBuffer3D<double>( const int& , const int& );

// Set Buffer (Empty 3D)
TPL_T CPPlot&
CPPlot::setBuffer3D( const int& n )
{
    unsigned d = 3;

    cBuffer().n = 0; cBuffer().d = d;
    glBufferData( GL_ARRAY_BUFFER , n * d * sizeof(T) ,
                  nullptr , GL_STATIC_DRAW );

    return *this;
}

template CPPlot& CPPlot::setBuffer3D<int>(    const int& );
template CPPlot& CPPlot::setBuffer3D<float>(  const int& );
template CPPlot& CPPlot::setBuffer3D<double>( const int& );

// Set Buffer (Matrix 2D)
TPL_T CPPlot&
CPPlot::setBuffer2D( const int& idx ,
                     const Matrix<T>& mat )
{
    bindBuffer( idx );
    setBuffer2D( mat );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::setBuffer2D<int>(    const int& , const Mati& );
template CPPlot& CPPlot::setBuffer2D<float>(  const int& , const Matf& );
template CPPlot& CPPlot::setBuffer2D<double>( const int& , const Matd& );

// Set Buffer (Matrix 2D)
TPL_T CPPlot&
CPPlot::setBuffer2D( const Matrix<T>& mat )
{
    unsigned n = mat.r() , d = 2 ;

    cBuffer().n = n; cBuffer().d = d;
    cBuffer().minX = mat.c(0).min(); cBuffer().maxX = mat.c(0).max();
    cBuffer().minY = mat.c(1).min(); cBuffer().maxY = mat.c(1).max();

    glBufferData( GL_ARRAY_BUFFER , n * d * sizeof(T) ,
                  mat.eig_data() , GL_STATIC_DRAW );
    cBuffer().filled = true;

    return *this;
}

template CPPlot& CPPlot::setBuffer2D<int>(    const Mati& );
template CPPlot& CPPlot::setBuffer2D<float>(  const Matf& );
template CPPlot& CPPlot::setBuffer2D<double>( const Matd& );

// Set Buffer (Matrix 3D)
TPL_T CPPlot&
CPPlot::setBuffer3D( const int& idx ,
                     const Matrix<T>& mat )
{
    bindBuffer( idx );
    setBuffer3D( mat );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::setBuffer3D<int>(    const int& , const Mati& );
template CPPlot& CPPlot::setBuffer3D<float>(  const int& , const Matf& );
template CPPlot& CPPlot::setBuffer3D<double>( const int& , const Matd& );

// Set Buffer (Matrix 3D)
TPL_T CPPlot&
CPPlot::setBuffer3D( const Matrix<T>& mat )
{
    unsigned n = mat.r() , d = 3 ;

    cBuffer().n = n; cBuffer().d = d;
    cBuffer().minX = mat.c(0).min(); cBuffer().maxX = mat.c(0).max();
    cBuffer().minY = mat.c(1).min(); cBuffer().maxY = mat.c(1).max();
    cBuffer().minZ = mat.c(2).min(); cBuffer().maxZ = mat.c(2).max();

    glBufferData( GL_ARRAY_BUFFER , n * d * sizeof(T) ,
                  mat.eig_data() , GL_STATIC_DRAW );
    cBuffer().filled = true;

    return *this;
}

template CPPlot& CPPlot::setBuffer3D<int>(    const Mati& );
template CPPlot& CPPlot::setBuffer3D<float>(  const Matf& );
template CPPlot& CPPlot::setBuffer3D<double>( const Matd& );

// Set Buffer (Grid IDX)
CPPlot&
CPPlot::setBufferIDXgrid( const int& idx ,
                          const int& nx , const int& ny )
{
    bindBuffer( idx );
    setBufferIDXgrid( nx , ny );
    unbindBuffer();

    return *this;
}

// Set Buffer (Grid IDX)
CPPlot&
CPPlot::setBufferIDXgrid( const int& nx , const int& ny )
{
    unsigned nqx = nx - 1 , nqy = ny - 1 , nqt = nqx * nqy;
    cBuffer().r = nqx; cBuffer().c = nqy; cBuffer().n = nqt;

    unsigned* idx = new unsigned[ 4 * nqt ];

    unsigned cnt_idx = 0 , cnt_data = 0;
    for( unsigned i = 0 ; i < nx ; i++ )
    {   for( unsigned j = 0 ; j < ny ; j++ )
        {   if( i < nqx && j < nqy )
            {
                idx[cnt_idx++] = cnt_data;
                idx[cnt_idx++] = cnt_data + 1;
                idx[cnt_idx++] = cnt_data + ny + 1;
                idx[cnt_idx++] = cnt_data + ny;
            }
            cnt_data++;
        }
    }

    glBufferData( GL_ELEMENT_ARRAY_BUFFER , 4 * nqt * sizeof(unsigned) ,
                  idx , GL_STATIC_DRAW );
    cBuffer().filled = true; delete[] idx;

    return *this;
}

// Set Buffer (Trid IDX)
CPPlot&
CPPlot::setBufferIDXtrid( const int& idx ,
                          const int& nx , const int& ny )
{
    bindBuffer( idx );
    setBufferIDXtrid( nx , ny );
    unbindBuffer();

    return *this;
}

// Set Buffer (Trid IDX)
CPPlot&
CPPlot::setBufferIDXtrid( const int& nx , const int& ny )
{
    unsigned n = std::ceil( (double)nx / 2.0 ) , m = std::floor( (double)nx / 2.0 );
    unsigned ny2 = 2 * ny - 1;

    unsigned nqx = n - 1 , nqy = ny - 1 , nqt = 4 * nqx * nqy;
    cBuffer().r = nqx; cBuffer().c = nqy; cBuffer().n = nqt;

    unsigned* idx = new unsigned[ 3 * nqt ];

    unsigned cnt_idx = 0 , cnt_data = 0;
    forLOOPij( n - 1 , ny - 1 )
    {
        cnt_data = ny2 * i + j;

        idx[ cnt_idx++ ] = cnt_data;
        idx[ cnt_idx++ ] = cnt_data + 1;
        idx[ cnt_idx++ ] = cnt_data + ny;

        idx[ cnt_idx++ ] = cnt_data + 1;
        idx[ cnt_idx++ ] = cnt_data + ny;
        idx[ cnt_idx++ ] = cnt_data + 1 + ny2;

        idx[ cnt_idx++ ] = cnt_data + ny;
        idx[ cnt_idx++ ] = cnt_data + 1 + ny2;
        idx[ cnt_idx++ ] = cnt_data + ny2;

        idx[ cnt_idx++ ] = cnt_data;
        idx[ cnt_idx++ ] = cnt_data + ny;
        idx[ cnt_idx++ ] = cnt_data + ny2;
    }

    glBufferData( GL_ELEMENT_ARRAY_BUFFER , 3 * nqt * sizeof(unsigned) ,
                  idx , GL_STATIC_DRAW );
    cBuffer().filled = true; delete[] idx;

    return *this;
}

// Set Buffer (RGB Knn)
TPL_T CPPlot&
CPPlot::setBufferRGBknn( const int& idx ,
                         const Matrix<T>& grd , const Matrix<T>& pts , const Matrix<T>& clr )
{
    bindBuffer( idx );
    setBufferRGBknn( grd , pts , clr );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::setBufferRGBknn<float>(  const int& , const Matf& , const Matf& , const Matf& );
template CPPlot& CPPlot::setBufferRGBknn<double>( const int& , const Matd& , const Matd& , const Matd& );

// Set Buffer (RGB Knn)
TPL_T CPPlot&
CPPlot::setBufferRGBknn( const Matrix<T>& grd , const Matrix<T>& pts , const Matrix<T>& clr )
{
    KDtree<T> kd;
    kd.add( pts );

    SSeqi idx; SSeq<T> dst;
    kd.knnSearch( grd , 1 , idx , dst );

    Matrix<T> colors( grd.r() , 3 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < idx.size() ; i++ )
        colors.r(i) = kd.data( idx[i] , clr );

    return setBuffer3D( colors );
}

template CPPlot& CPPlot::setBufferRGBknn<float>(  const Matf& , const Matf& , const Matf& );
template CPPlot& CPPlot::setBufferRGBknn<double>( const Matd& , const Matd& , const Matd& );

}
