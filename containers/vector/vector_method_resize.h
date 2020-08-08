#include "../vector.h"

namespace cvpp
{

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::reset( const int& n )
{
    off = 0;

    std_ptr = std::make_shared< Seq<D> >( n );
    update( off , n );

    return *this;
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::resize( const int& n )
{
    if( this->n() != n )
    {
        std_ptr->resize( n );
        update( off , n );
    }

    return *this;
}

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::reserve( const int& n )
{
    seq().reserve( n );
    update();

    return *this;
}


}
