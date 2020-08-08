#include "../vector.h"

namespace cvpp
{

TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::load( const String& str )
{
    IFile file( str );
    if( file.is_open() )
    {
        unsigned n,d;
        file >> n >> d;

        reset( n );
        forLOOPij( n , d )
            file >> mat().at(i,j);

        file.close();
    }

    return *this;
}

TPL_DTM void
Vector<D,T,M>::save( const String& str ) const
{
    mat().save( str );
}

// Set Val
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::setVal( const D& val )
{
    #pragma omp parallel for
    forLOOPi( n() )
        at(i) = val;
    return *this;
}

// Set Increase
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::setIncrease( const D& start ,
                            const D& step )
{
    #pragma omp parallel for
    forLOOPi( n() )
        at(i) = start + (T)i * step;
    return *this;
}

// Set Increase
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::Shuffle()
{
    std::random_shuffle( seq().begin() , seq().end() );
    return *this;
}

}
