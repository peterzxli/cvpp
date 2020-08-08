#include "../vector.h"

namespace cvpp
{

TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::RotateX( const T& a )
{
    mat().RotateX( a );
    return *this;
}

TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::RotateY( const T& a )
{
    mat().RotateY( a );
    return *this;
}

TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::RotateZ( const T& a )
{
    mat().RotateZ( a );
    return *this;
}

}
