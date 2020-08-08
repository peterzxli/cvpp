#include "../trio.h"

namespace cvpp
{

// Base Constructor
TPL_TUV
Trio<T,U,V>::Trio()
{
    this->A.reset();
    this->B.reset();
    this->C.reset();
}

// Share Constructor
TPL_TUV
Trio<T,U,V>::Trio( const T& A , const T& B , const T& C )
{
    this->A >> A;
    this->B >> B;
    this->C >> C;
}

}

