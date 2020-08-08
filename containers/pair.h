#ifndef PAIR_H
#define PAIR_H

#include <cvpp/auxiliar/definitions.h>

namespace cvpp
{

TPL_T
class Matrix;

TPL_DTM
class Vector;

TPL_TU
class Pair
{

protected:

    T A;
    U B;

public:

    // Constructor

    Pair();
    Pair( const T& , const T& );

    // Data

    T& first() { return A; }
    const T& first() const { return A; }

    U& second() { return B; }
    const U& second() const { return B; }

};

TPL_TU using PairMM = Pair< Matrix<T> , Matrix<U> >;

using PairMiMi = PairMM< int    , int >;
using PairMfMi = PairMM< float  , int >;
using PairMdMi = PairMM< double , int >;

using PairMiMf = PairMM< int    , float >;
using PairMfMf = PairMM< float  , float >;
using PairMdMf = PairMM< double , float >;

using PairMiMd = PairMM< int    , double >;
using PairMfMd = PairMM< float  , double >;
using PairMdMd = PairMM< double , double >;

using PairiMM = PairMiMi;
using PairfMM = PairMfMf;
using PairdMM = PairMdMd;

TPL_TU using PairVV = Pair< Vector<T,T,1> , Vector<U,U,1> >;

using PairViVi = PairVV< int    , int >;
using PairVfVi = PairVV< float  , int >;
using PairVdVi = PairVV< double , int >;

using PairViVf = PairVV< int    , float >;
using PairVfVf = PairVV< float  , float >;
using PairVdVf = PairVV< double , float >;

using PairViVd = PairVV< int    , double >;
using PairVfVd = PairVV< float  , double >;
using PairVdVd = PairVV< double , double >;

using PairiVV = PairViVi;
using PairfVV = PairVfVf;
using PairdVV = PairVdVd;

}

#include "pair_src.h"

#endif
