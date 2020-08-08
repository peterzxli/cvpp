#include "../image.h"

namespace cvpp
{

// Convert
TPL_TC TPL_U Image<U,C>
Image<T,C>::convert() const
{
    Image<U,C> tmp( r() , c() );
    tmp.eig() = eig().template cast<U>();
    return tmp;
}

#ifdef VLFEAT_FOUND

TPL_TC inline T*
Image<T,C>::VLfeat() const
{
    T* vec = new T[ s() ];

    unsigned cnt = 0;
    for( unsigned k = 0 ; k < d() ; k++ )
        for( unsigned i = 0 ; i < r() ; i++ )
            for( unsigned j = 0 ; j < c() ; j++ )
                vec[ cnt++ ] = at(i,j,k);

    return vec;
}

#endif

}
