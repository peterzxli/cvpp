#include "../array.h"

namespace cvpp
{

// Print
TPL_TC void
Array<T,C>::print() const
{
    for( unsigned i = 0 ; i < C ; i++ )
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

// Info
TPL_TC void
Array<T,C>::info() const
{
    std::cout << "ARRAY " << C << std::endl;
}

}
