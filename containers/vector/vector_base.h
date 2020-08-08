#include "../vector.h"

namespace cvpp
{

TPL_DTM // Base Constructor
Vector<D,T,M>::Vector( const int& n )
{
    initialise( n );
}

TPL_DTM // String Constructor
Vector<D,T,M>::Vector( const String& str )
{
    load( str );
}

TPL_DTM // String Constructor
Vector<D,T,M>::Vector( const String& str , const int& n )
{
    load( str , n );
}

TPL_DTM // Matrix Constructor
Vector<D,T,M>::Vector( const Matrix<T>& mat )
{
    initialise( mat.r() );
    this->mat() = mat;
}

TPL_DTM // seqConstructor
Vector<D,T,M>::Vector( const Seq<D>& seq )
{
    initialise( seq.size() );
    *this = seq;
}

#ifdef OPENCV_FOUND

TPL_DTM // KPts Constructor
Vector<D,T,M>::Vector( const KPts& kpt )
{
    initialise( kpt.size() );
    *this = kpt;
}

#endif

TPL_DTM // Vector Constructor
Vector<D,T,M>::Vector( const Vector<D,T,M>& vec ,
                       const bool& share )
{
    if( share )
         *this >> vec;
    else *this << vec;
}

TPL_DTM // Block Constructor
Vector<D,T,M>::Vector( const Vector<D,T,M>& vec ,
                       const int& off , const int& n )
{
    initialise( vec , off , n );
}

// New Initialise
TPL_DTM inline void
Vector<D,T,M>::initialise( const int& n )
{
    this->off = 0;
    this->std_ptr = std::make_shared< Seq<D> >( n );
    this->mat_ptr = std::make_shared< Matrix<T> >(
                         0 , 0 , n , M , M , std_data() );
}

// Block Initialise
TPL_DTM inline void
Vector<D,T,M>::initialise( const Vector<D,T,M>& vec ,
                           const int& off , const int& n )
{
    this->off = vec.off + off;
    this->std_ptr = vec.std_ptr;
    this->mat_ptr = std::make_shared< Matrix<T> >(
                         this->off , 0 , n , M , M , std_data() );
}

}
