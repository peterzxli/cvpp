#include "../sparse.h"

namespace cvpp
{

// Permutate
TPL_T Sparse<T>
Sparse<T>::permutate( const Matrix<int>& idx ) const
{
    EigCol<int> perm = idx.eig();

    Sparse<T> tmp( dims() );
    tmp.eig() = eig().twistedBy( perm.asPermutation().inverse() );

    return tmp;
}

}
