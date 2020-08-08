#ifndef TRIO_H
#define TRIO_H

#include <cvpp/auxiliar/definitions.h>

namespace cvpp
{

TPL_T
class Matrix;

TPL_TUV
class Trio
{

protected:

    T A;
    U B;
    V C;

public:

    T& first() { return A; }
    const T& first() const { return A; }

    U& second() { return B; }
    const U& second() const { return B; }

    V& third() { return C; }
    const V& third() const { return C; }

};

TPL_T using TrioMMM = Trio< Matrix<T> , Matrix<T> , Matrix<T> >;
using TrioiMMM = TrioMMM< int >;
using TriofMMM = TrioMMM< float >;
using TriodMMM = TrioMMM< double >;

}

#include "trio_src.h"

#endif
