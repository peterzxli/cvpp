#include "../pair.h"

namespace cvpp
{

// Base Constructor
TPL_TU
Pair<T,U>::Pair()
{
    this->A.reset();
    this->B.reset();
}

// Share Constructor
TPL_TU
Pair<T,U>::Pair( const T& A , const T& B )
{
    this->A >> A;
    this->B >> B;
}

}
