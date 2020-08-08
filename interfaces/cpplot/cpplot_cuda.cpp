#include "../cpplot.h"

#ifdef CUDA_FOUND

namespace cvpp
{

float*
CPPlot::cudaPointer( const int& n )
{
    cudaGraphicsResource* resources;

    cudaGraphicsGLRegisterBuffer(
        &resources , buffer(n).ptr , cudaGraphicsMapFlagsNone );
    cudaGraphicsMapResources( 1 , &resources );

    float* ptr; unsigned size;
    cudaGraphicsResourceGetMappedPointer(
        (void**)&ptr , (size_t*)&size , resources );

    return ptr;
}

}

#endif

