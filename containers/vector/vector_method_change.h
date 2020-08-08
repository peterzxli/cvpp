#include "../vector.h"

namespace cvpp
{

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::insert( const String& str )
{
    return insert( Vector<D,T,M>( str ) );
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::insert( const String& str , const int& n )
{
    return insert( Vector<D,T,M>( str , n ) );
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::insert( const D& val )
{
    std_ptr->push_back( val );
    return *this;
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::insert( const Seq<D>& seq )
{
    reserve( n() + seq.size() );
    forLOOPi( seq.size() )
        std_ptr->push_back( seq[i] );
    return *this;
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::insert( const Vector<D,T,M>& vec )
{
    reserve( n() + vec.n() );
    forLOOPi( vec.n() )
        std_ptr->push_back( vec[i] );
    return *this;
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::insert( const Matrix<T>& mat )
{
    resize( n() + mat.r() );
    n( n() - mat.r() , mat.r() ) = mat;
    return *this;
}

TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::keepFront( const int& n )
{
    return resize( n );
}

TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::keepBack( const int& n )
{
    off += this->n() - n; update( off , n );
    return *this;
}

}
