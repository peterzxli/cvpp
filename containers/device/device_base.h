#include "../device.h"

namespace cvpp
{

TPL_T // Base Constructor
Device<T>::Device()
{
    initialise( 1 , 1 );
}

TPL_T // New Constructor
Device<T>::Device( const int& r ,
                   const int& c )
{
    initialise( r , c );
}

TPL_T // New Constructor
Device<T>::Device( const Dims& dims )
{
    initialise( dims.r , dims.c );
}

TPL_T // Data Constructor
Device<T>::Device( const int& r ,
                   const int& c , T* data )
{
    initialise( r , c , data );
}

TPL_T // afArray Constructor
Device<T>::Device( const afArray& afa ,
                   const bool& share )
{
    if( share )
         *this >> afa;
    else *this << afa;
}

TPL_T // afProxy Constructor
Device<T>::Device( const afProxy& afp ,
                   const bool& share )
{
    if( share )
         *this >> afp;
    else *this << afp;
}

TPL_T // Device Constructor
Device<T>::Device( const Device<T>& dev ,
                   const bool& share )
{
    if( share )
         *this >> dev;
    else *this << dev;
}

TPL_T // Device Block Constructor
Device<T>::Device( const Device<T>& dev ,
                   const int& r0 , const int& c0 ,
                   const int& nr , const int& nc )
{
    initialise( dev , r0 , c0 , nr , nc );
}

TPL_T // Matrix Constructor
Device<T>::Device( const Matrix<T>& mat )
{
    *this << mat;
}

// New Initialise
TPL_T void
Device<T>::initialise( const int& r ,
                       const int& c )
{
    raw_ptr = std::make_shared< afArray >( r , c );
    arr_ptr = std::make_shared< afProxy >( raw_ptr->rows( 0 , r - 1 ) );
}

// Block Initialise
TPL_T void
Device<T>::initialise( const int& r ,
                       const int& c , T* data )
{
    raw_ptr = std::make_shared< afArray >( r , c , data );
    arr_ptr = std::make_shared< afProxy >( raw_ptr->rows( 0 , r - 1 ) );
}

// Block Initialise
TPL_T void
Device<T>::initialise( const Device<T>& dev ,
                       const int& r0 , const int& c0 ,
                       const int& nr , const int& nc )
{
    arr_ptr = std::make_shared< afProxy >( dev.raw()( afSeq( r0 , r0 + nr - 1 ) ,
                                                      afSeq( c0 , c0 + nc - 1 ) ) );
}


}
