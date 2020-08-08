#include "../cpplot.h"

namespace cvpp
{

// Update Buffer (Matrix 2D)
TPL_T CPPlot&
CPPlot::updBuffer2D( const int& idx ,
                        const Matrix<T>& mat , const int& off )
{
    bindBuffer( idx );
    updBuffer2D( mat , off );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::updBuffer2D<float>(  const int& , const Matf& , const int& );
template CPPlot& CPPlot::updBuffer2D<double>( const int& , const Matd& , const int& );

// Update Buffer (Matrix 2D)
TPL_T CPPlot&
CPPlot::updBuffer2D( const Matrix<T>& mat ,
                     const int& off )
{
    unsigned n = mat.r() , d = 2;
    cBuffer().n = off + n;

    if( mat.r() == 0 )
        return *this;

//    if( cBuffer().n < off + n ) cBuffer().n = off + n;

    cBuffer().minX = mat.c(0).min(); cBuffer().maxX = mat.c(0).max();
    cBuffer().minY = mat.c(1).min(); cBuffer().maxY = mat.c(1).max();

    glBufferSubData( GL_ARRAY_BUFFER , off * d * sizeof(T) ,
                     n * d * sizeof(T) , mat.eig_data() );
    cBuffer().filled = true;

    return *this;
}

template CPPlot& CPPlot::updBuffer2D<float>(  const Matf& , const int& );
template CPPlot& CPPlot::updBuffer2D<double>( const Matd& , const int& );

// Update Buffer (3D Matd)
TPL_T CPPlot&
CPPlot::updBuffer3D( const int& idx ,
                     const Matrix<T>& mat , const int& off )
{
    bindBuffer( idx );
    updBuffer3D( mat , off );
    unbindBuffer();

    return *this;
}

template CPPlot& CPPlot::updBuffer3D<float>(  const int& , const Matf& , const int& );
template CPPlot& CPPlot::updBuffer3D<double>( const int& , const Matd& , const int& );

// Update Buffer (Matrix 3D)
TPL_T CPPlot&
CPPlot::updBuffer3D( const Matrix<T>& mat ,
                     const int& off )
{
    unsigned n = mat.r() , d = 3;
    cBuffer().n = off + n;

    if( mat.r() == 0 )
        return *this;

//    if( cBuffer().n < off + n ) cBuffer().n = off + n;

    cBuffer().minX = mat.c(0).min(); cBuffer().maxX = mat.c(0).max();
    cBuffer().minY = mat.c(1).min(); cBuffer().maxY = mat.c(1).max();
    cBuffer().minZ = mat.c(2).min(); cBuffer().maxZ = mat.c(2).max();

    glBufferSubData( GL_ARRAY_BUFFER , off * d * sizeof(T) ,
                     n * d * sizeof(T) , mat.eig_data() );
    cBuffer().filled = true;

    return *this;
}

template CPPlot& CPPlot::updBuffer3D<float>(  const Matf& , const int& );
template CPPlot& CPPlot::updBuffer3D<double>( const Matd& , const int& );

}
