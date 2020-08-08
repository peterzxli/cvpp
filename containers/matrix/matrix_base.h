#include "../matrix.h"

namespace cvpp
{

TPL_T // Base Constructor
Matrix<T>::Matrix()
{
    reset();
}

TPL_T // String Constructor
Matrix<T>::Matrix( const String& str )
{
    load( str );
}

TPL_T // String Constructor
Matrix<T>::Matrix( const String& str , const int& n )
{
    load( str , n );
}

TPL_T // Matrix Constructor
Matrix<T>::Matrix( const Matrix<T>& mat ,
                   const bool& share )
{
    if( share )
         *this >> mat;
    else *this << mat;
}

TPL_T TPL_DM // Vector Constructor
Matrix<T>::Matrix( const Vector<D,T,M>& vec ,
                   const bool& share )
{
    if( share )
         *this >> vec;
    else *this << vec;
}

TPL_T TPL_C // Image Constructor
Matrix<T>::Matrix( const Image<T,C>& img ,
                   const bool& share )
{
    *this << img;
}

TPL_T // Sparse Constructor
Matrix<T>::Matrix( const Sparse<T>& spr ,
                   const bool& share )
{
    *this << spr;
}

TPL_T // SEigen Constructor
Matrix<T>::Matrix( const SEigen& seig ,
                   const bool& share )
{
    *this << seig;
}

TPL_T TPL_F // FEigen Constructor
Matrix<T>::Matrix( const FEigen& feig ,
                   const bool& share )
{
    *this << feig;
}

TPL_T TPL_B // BEigen Constructor
Matrix<T>::Matrix( const BEigen beig ,
                   const bool& share )
{
    if( share )
         *this >> beig;
    else *this << beig;
}

TPL_T // Seq Constructor
Matrix<T>::Matrix( const Seq<T>& seq,
                   const bool& share )
{
    *this << seq;
}

TPL_T // Row Seq Constructor
Matrix<T>::Matrix( const Seq<Matrix<T>>& rseq ,
                   const bool& share )
{
    *this << rseq;
}

#ifdef OPENCV_FOUND

TPL_T // OpenCV Constructor
Matrix<T>::Matrix( const CV& cv ,
                   const bool& share )
{
    if( share )
         *this >> cv;
    else *this << cv;
}

#endif

#ifdef SHOGUN_FOUND

TPL_T // Shogun Matrix Constructor
Matrix<T>::Matrix( const SGMatrix<T>& sgmat ,
                   const bool& share )
{
    if( share )
         *this >> sgmat;
    else *this << sgmat;
}

TPL_T // Shogun Vector Constructor
Matrix<T>::Matrix( const SGVector<T>& sgvec ,
                   const bool& share )
{
    this->initialise( 0 , 0 , sgvec.size() ,
                      1 , 1 , sgvec.vector );
}

#endif

TPL_T // New Constructor
Matrix<T>::Matrix( const int& r ,
                   const int& c )
{
    initialise( r , c );
}

TPL_T // New Constructor
Matrix<T>::Matrix( const Dims& dims )
{
    initialise( dims.r , dims.c );
}

TPL_T // Data Constructor
Matrix<T>::Matrix( const int& r ,
                   const int& c , T* data )
{
    reset( data , r , c );
}

TPL_T // Block Constructor
Matrix<T>::Matrix( const int& i , const int& j ,
                   const int& r , const int& c ,
                   const int& o , T* data )
{
    initialise( i , j , r , c , o , data );
}

// New Initialise
TPL_T inline void
Matrix<T>::initialise( const Dims& dims )
{
    initialise( dims.r , dims.c );
}

// New Initialise
TPL_T inline void
Matrix<T>::initialise( const int& r ,
                       const int& c )
{
    raw_ptr = std::make_shared< DEigen >( r , c );
    update();
}

// Block Initialise
TPL_T inline void
Matrix<T>::initialise( const int& i , const int& j ,
                       const int& r , const int& c ,
                       const int& o , T* data )
{
    eig_ptr = std::make_shared< MEigen >
            ( &data[ i * o + j ] , r , c ,
              Eigen::Stride< -1 , 1 >( o , 1 ) ) ;
}

// Update
TPL_T inline void
Matrix<T>::update()
{
    eig_ptr = std::make_shared< MEigen >
            ( &raw_data()[0] , raw_ptr->rows() , raw_ptr->cols() ,
              Eigen::Stride< -1 , 1 >( raw_ptr->cols() , 1 ) );
}

}
