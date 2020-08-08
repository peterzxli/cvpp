#include "../device.h"

namespace cvpp
{

// Cholesky
TPL_T Device<T>
Device<T>::chol() const
{
    afArray tmp( r() , c() );
    af::cholesky( tmp , arr() );
    return tmp;
}



}
