#include "../sparse.h"

namespace cvpp
{

TPL_T // Base Constructor
Sparse<T>::Sparse()
{
    reset();
}

TPL_T // String Constructor
Sparse<T>::Sparse( const String& str )
{
    load( str );
}

TPL_T // String Constructor
Sparse<T>::Sparse( const String& str , const int& n )
{
    load( str , n );
}

TPL_T // Matrix Constructor
Sparse<T>::Sparse( const Matrix<T>& mat ,
                   const bool& share )
{
    *this << mat;
}

TPL_T // Sparse Constructor
Sparse<T>::Sparse( const Sparse<T>& spr ,
                   const bool& share )
{
    if( share )
         *this >> spr;
    else *this << spr;
}

TPL_T // SEigen Constructor
Sparse<T>::Sparse( const SEigen& seig ,
                   const bool& share )
{
    *this << seig;
}

TPL_T TPL_F // FEigen Constructor
Sparse<T>::Sparse( const FEigen& feig ,
                   const bool& share )
{
    *this << feig;
}

TPL_T TPL_B // BEigen Constructor
Sparse<T>::Sparse( const BEigen beig ,
                   const bool& share )
{
    *this << beig;
}

TPL_T // New Constructor
Sparse<T>::Sparse( const int& r ,
                   const int& c )
{
    initialise( r , c );
}

TPL_T // New Constructor
Sparse<T>::Sparse( const Dims& dims )
{
    initialise( dims.r , dims.c );
}

TPL_T // Triplet Constructor
Sparse<T>::Sparse( const int& r ,
                   const int& c , const TripletList<T>& list )
{
    initialise( r , c , list );
}

TPL_T // Triplet Constructor
Sparse<T>::Sparse( const int& r , const TripletList<T>& list )
{
    initialise( r , 1 , list );
}

// New Initialise
TPL_T inline void
Sparse<T>::initialise( const Dims& dims )
{
    initialise( dims.r , dims.c );
}

// New Initialise
TPL_T inline void
Sparse<T>::initialise( const int& r ,
                       const int& c )
{
    eig_ptr = std::make_shared< SEigen >( r , c );
}

// Triplet Initialise
TPL_T inline void
Sparse<T>::initialise( const int& r ,
                       const int& c , const TripletList<T>& list )
{
    initialise( r , c );
    set( list );
}

}
