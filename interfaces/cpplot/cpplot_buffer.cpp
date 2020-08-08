#include "../cpplot.h"

namespace cvpp
{

// Bind Buffer
CPPlot&
CPPlot::bindBuffer( const int& idx )
{
    idxBuffer = idx;

    switch( cBuffer().type )
    {
        case BUFFER_DATA_INT: case BUFFER_DATA_FLOAT: case BUFFER_DATA_DOUBLE:
            glBindBuffer( GL_ARRAY_BUFFER , cBuffer().ptr );
            break;

        case BUFFER_IDX:
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , cBuffer().ptr );
            break;
    }

    return *this;
}

// Unbind Buffer
CPPlot&
CPPlot::unbindBuffer()
{
    switch( cBuffer().type )
    {
        case BUFFER_DATA_INT: case BUFFER_DATA_FLOAT: case BUFFER_DATA_DOUBLE:
            glBindBuffer( GL_ARRAY_BUFFER , 0 );
            break;

        case BUFFER_IDX:
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );
            break;
    }

    idxBuffer = -1;
    return *this;
}

}
