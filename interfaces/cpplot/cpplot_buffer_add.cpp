#include "../cpplot.h"

namespace cvpp
{

// Add Buffer
const int
CPPlot::addBuffer()
{
    buffers.resize( buffers.size() + 1 );
    glGenBuffers( 1 , &buffers.back().ptr );
    return buffers.size() - 1;
}

// Add Buffer (Empty 2D)
TPL_T const int
CPPlot::addBuffer2D( const int& n )
{
    unsigned idx = addBuffer();
    DataType<T> type; buffer(idx).type = type.get();
    setBuffer2D<T>( idx , n ); return idx;
}

template const int CPPlot::addBuffer2D<int>(    const int& );
template const int CPPlot::addBuffer2D<float>(  const int& );
template const int CPPlot::addBuffer2D<double>( const int& );

// Add Buffer (Empty 3D)
TPL_T const int
CPPlot::addBuffer3D( const int& n )
{
    unsigned idx = addBuffer();
    DataType<T> type; buffer(idx).type = type.get();
    setBuffer3D<T>( idx , n ); return idx;
}

template const int CPPlot::addBuffer3D<int>(    const int& );
template const int CPPlot::addBuffer3D<float>(  const int& );
template const int CPPlot::addBuffer3D<double>( const int& );

// Add Buffer (Matrix 2D)
TPL_T const int
CPPlot::addBuffer2D( const Matrix<T>& mat )
{
    unsigned idx = addBuffer();
    DataType<T> type; buffer(idx).type = type.get();
    setBuffer2D( idx , mat ); return idx;
}

template const int CPPlot::addBuffer2D<int>(    const Mati& );
template const int CPPlot::addBuffer2D<float>(  const Matf& );
template const int CPPlot::addBuffer2D<double>( const Matd& );

// Add Buffer (Matrix 3D)
TPL_T const int
CPPlot::addBuffer3D( const Matrix<T>& mat )
{
    unsigned idx = addBuffer();
    DataType<T> type; buffer(idx).type = type.get();
    setBuffer3D( idx , mat ); return idx;
}

template const int CPPlot::addBuffer3D<int>(    const Mati& );
template const int CPPlot::addBuffer3D<float>(  const Matf& );
template const int CPPlot::addBuffer3D<double>( const Matd& );

// Add Buffer (IDX Grid)
const int
CPPlot::addBufferIDXgrid( const int& u ,
                          const int& v )
{
    unsigned idx = addBuffer();
    buffer(idx).type = BUFFER_IDX;
    setBufferIDXgrid( idx , u , v );
    return idx;
}

// Add Buffer (IDX Trid)
const int
CPPlot::addBufferIDXtrid( const int& u ,
                          const int& v )
{
    unsigned idx = addBuffer();
    buffer(idx).type = BUFFER_IDX;
    setBufferIDXtrid( idx , u , v );
    return idx;
}

// Add Buffer (RGB Knn)
TPL_T const int
CPPlot::addBufferRGBknn( const Matrix<T>& grd , const Matrix<T>& pts , const Matrix<T>& clr )
{
    unsigned idx = addBuffer();
    DataType<T> type; buffer(idx).type = type.get();
    setBufferRGBknn( idx , grd , pts , clr ); return idx;
}

template const int CPPlot::addBufferRGBknn<float>(  const Matf& , const Matf& , const Matf& );
template const int CPPlot::addBufferRGBknn<double>( const Matd& , const Matd& , const Matd& );

}
