#ifndef VECTOR_H
#define VECTOR_H

#include "./matrix.h"

namespace cvpp
{

TPL_DTM
class Vector
{

protected:

    unsigned off;

    Pointer< Seq<D> > std_ptr;
    Pointer< Matrix<T> > mat_ptr;

public:

    // Constructor

    Vector( const String& );
    Vector( const String& , const int& n );

    Vector( const Matrix<T>& );
    Vector( const Seq<D>& );

    #ifdef OPENCV_FOUND
    Vector( const KPts& );
    #endif

    Vector( const int& = 0 );

    Vector( const T& v0 , const T& v1 ) { reset(2); eig() << v0 , v1 ; }
    Vector( const T& v0 , const T& v1 , const T& v2 ) { reset(3); eig() << v0 , v1 , v2 ; }
    Vector( const T& v0 , const T& v1 , const T& v2 , const T& v3 ) { reset(4); eig() << v0 , v1 , v2 , v3 ; }
    Vector( const T& v0 , const T& v1 , const T& v2 , const T& v3 , const T& v4 ) { reset(5); eig() << v0 , v1 , v2 , v3 , v4 ; }

    Vector( const Vector<D,T,M>& , const bool& = SHARE );
    Vector( const Vector<D,T,M>& , const int& , const int& );

    // Initialise

    void initialise( const int& );
    void initialise( const Vector<D,T,M>& , const int& , const int& );

    void update( const int& off , const int& n  )
    { mat_ptr = std::make_shared< Matrix<T> >( off , 0 , n , M , M , std_data() ); }

    void update() { update( off , seq().size() - off ); }

    // Info

    Vector<D,T,M> clone() const { return Vector<D,T,M>( *this , COPY ); }

    const bool empty() const { return n() == 0; }
    const bool filled() const { return !empty(); }

    const bool fits( const Vector<D,T,M>& vec ) const { return n() == vec.n() && d() == vec.d(); }
    const bool fits( const Matrix<T>& mat     ) const { return n() == mat.r() && d() == mat.c(); }

    const bool fits( const Seq<D>& seq ) const { return n() == seq.size(); }

    #ifdef OPENCV_FOUND
    const bool fits( const KPts&   kpt ) const { return n() == kpt.size(); }
    #endif

    const int nidx( const int& n ) const { return n >= 0 ? n : this->n() + n; }
    const int didx( const int& d ) const { return d >= 0 ? d : this->d() + d; }

    const int n() const { return mat_ptr->r(); }
    const int c() const { return std_ptr->capacity(); }

    const int d() const { return M; }
    const int o() const { return M; }
    const int s() const { return n() * d(); }

    const int ob() const { return off; }
    const int oe() const { return off + n(); }

    // Data

    D& operator[]( const int& n ) { return std_ptr->at( off + nidx(n) ); }
    const D& operator[]( const int& n ) const { return std_ptr->at( off + nidx(n) ); }

    D& at( const int& n ) { return std_ptr->at( off + nidx(n) ); }
    const D& at( const int& n ) const { return std_ptr->at( off + nidx(n) ); }

    Seq<D>& seq() const { return *std_ptr.get(); }
    Matrix<T>& mat() const { return *mat_ptr.get(); }

    EIG<T>& raw() const { return mat().raw(); }
    MEIG<T>& eig() const { return mat().eig(); }

    #ifdef OPENCV_FOUND
    CV cv() const { return mat().cv(); }
    #endif

    T* eig_data() const { return mat().eig_data(); }
    T* std_data() const { return (T*)seq().data(); }

    // Sub

    Matrix<T> n( const int& r0 , const int& nr = 1 ) const { return mat_ptr->r( r0 , nr ); }
    Matrix<T> d( const int& c0 , const int& nc = 1 ) const { return mat_ptr->c( c0 , nc ); }

    Matrix<T> nu( const int& n = 1 ) const { return mat_ptr->ru( n ); }
    Matrix<T> nd( const int& n = 1 ) const { return mat_ptr->rd( n ); }

    Matrix<T> dl( const int& n = 1 ) const { return mat_ptr->cl( n ); }
    Matrix<T> dr( const int& n = 1 ) const { return mat_ptr->cr( n ); }

    Matrix<T> r( const int& r0 , const int& nr = 1 ) const { return n( r0 , nr ); }
    Matrix<T> c( const int& c0 , const int& nc = 1 ) const { return d( c0 , nc ); }

    Matrix<T> ru( const int& n = 1 ) const { return nu( n ); }
    Matrix<T> rd( const int& n = 1 ) const { return nd( n ); }

    Matrix<T> cl( const int& n = 1 ) const { return dl( n ); }
    Matrix<T> cr( const int& n = 1 ) const { return dr( n ); }

    Matrix<T> b( const int& r0 , const int& c0 , const int& nr , const int& nc ) const
    { return mat_ptr->b( r0 , c0 , nr , nc ); }

    Matrix<T> blu( const int& r , const int& c ) const { return mat_ptr->blu( r , c ); }
    Matrix<T> blu( const int& n ) const { return blu( n , n ); }

    Matrix<T> bru( const int& r , const int& c ) const { return mat_ptr->bru( r , c ); }
    Matrix<T> bru( const int& n ) const { return bru( n , n ); }

    Matrix<T> bld( const int& r , const int& c ) const { return mat_ptr->bld( r , c ); }
    Matrix<T> bld( const int& n ) const { return bld( n , n ); }

    Matrix<T> brd( const int& r , const int& c ) const { return mat_ptr->brd( r , c ); }
    Matrix<T> brd( const int& n ) const { return brd( n , n ); }

    Vector<D,T,M> operator()( const int& n0 , const int& n = 1 ) const
    { return Vector<D,T,M>( *this , nidx(n0) , n ); }

    Vector<D,T,M> v( const int& n0 , const int& n = 1 ) const
    { return Vector<D,T,M>( *this , nidx(n0) , n ); }

    Vector<D,T,M> vf( const int& n = 1 ) const { return v(   0 , n ); }
    Vector<D,T,M> vb( const int& n = 1 ) const { return v( - n , n ); }

    // PRINT

    void print() const;
    void print( const String& ) const;

    void info() const;
    void info( const String& ) const;

    // OPERATOR_ATTRIB

    Vector<D,T,M>& operator>>( const Vector<D,T,M>& );
    Vector<D,T,M>& operator= ( const Vector<D,T,M>& );
    Vector<D,T,M>& operator<<( const Vector<D,T,M>& );

    Vector<D,T,M>& share(  const Vector<D,T,M>& vec ) { return *this >> vec; }
    Vector<D,T,M>& assign( const Vector<D,T,M>& vec ) { return *this =  vec; }
    Vector<D,T,M>& copy(   const Vector<D,T,M>& vec ) { return *this << vec; }

    Vector<D,T,M>& operator= ( const Matrix<T>& );
    Vector<D,T,M>& operator<<( const Matrix<T>& );

    Vector<D,T,M>& assign( const Matrix<T>& mat ) { return *this =  mat; }
    Vector<D,T,M>& copy(   const Matrix<T>& mat ) { return *this << mat; }

    Vector<D,T,M>& operator= ( const Seq<D>& );
    Vector<D,T,M>& operator<<( const Seq<D>& );

    Vector<D,T,M>& assign( const Seq<D>& seq ) { return *this =  seq; }
    Vector<D,T,M>& copy(   const Seq<D>& seq ) { return *this << seq; }

    #ifdef OPENCV_FOUND

    Vector<D,T,M>& operator= ( const KPts& );
    Vector<D,T,M>& operator<<( const KPts& );

    Vector<D,T,M>& assign( const KPts& kpt ) { return *this =  kpt; }
    Vector<D,T,M>& copy(   const KPts& kpt ) { return *this << kpt; }

    #endif

    Vector<D,T,M>& operator=( const D& );

    Vector<D,T,M>& assign( const D& elm ) { return *this = elm; }

    // OPERATOR_UNARY

    Vector<D,T,M> operator-() const;

    Vector<D,T,M>& operator+=( const D& );
    Vector<D,T,M>& operator-=( const D& );

    Vector<D,T,M>& add( const D& elm ) { return *this += elm; }
    Vector<D,T,M>& sub( const D& elm ) { return *this -= elm; }

    TPL_U Vector<D,T,M>& operator*=( const U& );
    TPL_U Vector<D,T,M>& operator/=( const U& );

    TPL_U Vector<D,T,M>& mlt( const U& val ) { return *this *= val; }
    TPL_U Vector<D,T,M>& div( const U& val ) { return *this /= val; }

    Vector<D,T,M>& operator+=( const Vector<D,T,M>& );
    Vector<D,T,M>& operator-=( const Vector<D,T,M>& );
    Vector<D,T,M>& operator%=( const Vector<D,T,M>& );
    Vector<D,T,M>& operator/=( const Vector<D,T,M>& );

    Vector<D,T,M>& add( const Vector<D,T,M>& vec ) { return *this += vec; }
    Vector<D,T,M>& sub( const Vector<D,T,M>& vec ) { return *this -= vec; }
    Vector<D,T,M>& dot( const Vector<D,T,M>& vec ) { return *this %= vec; }
    Vector<D,T,M>& div( const Vector<D,T,M>& vec ) { return *this /= vec; }

    Vector<D,T,M>& operator*=( const Matrix<T>& );
    Vector<D,T,M>& mlt( const Matrix<T>& mat ) { return *this *= mat; }

    // METHOD_RESIZE

    Vector<D,T,M>& reset( const int& = 0 );
    Vector<D,T,M>& resize( const int& );
    Vector<D,T,M>& reserve( const int& );

    Vector<D,T,M>& enlarge( const int& n ) { return resize( this->n() + n ); }

    // METHOD_CHANGE

    Vector<D,T,M>& insert( const String& );
    Vector<D,T,M>& insert( const String& , const int& );

    Vector<D,T,M>& insert( const D& );
    Vector<D,T,M>& insert( const Seq<D>& );
    Vector<D,T,M>& insert( const Vector<D,T,M>& );
    Vector<D,T,M>& insert( const Matrix<T>& );

    Vector<D,T,M>& push( const String& str ) { insert( str ).update(); return *this; }
    Vector<D,T,M>& push( const String& str , const int& n ) { insert( str , n ).update(); return *this; }

    Vector<D,T,M>& push( const D& elm ) { insert( elm ).update(); return *this; }
    Vector<D,T,M>& push( const Seq<D>& seq ) { insert( seq ).update(); return *this; }
    Vector<D,T,M>& push( const Vector<D,T,M>& vec ) { insert( vec ).update(); return *this; }
    Vector<D,T,M>& push( const Matrix<T>& mat ) { insert( mat ).update(); return *this; }

    Vector<D,T,M>& push( const D& elm , const int& i )
    { seq().insert( seq().begin() + i , elm ); update(); return *this; }

    Vector<D,T,M>& erase( const int& i )
    { seq().erase( seq().begin() + i ); update(); return *this; }

    Vector<D,T,M>& keepFront( const int& );
    Vector<D,T,M>& keepBack( const int& );

    Vector<D,T,M>& trimFront( const int& n ) { return keepBack( this->n() - n ); }
    Vector<D,T,M>& trimBack( const int& n ) { return keepFront( this->n() - n ); }

    Vector<D,T,M>& trim( const int& f , const int& b ) { return trimFront( f ).trimBack( b ); }
    Vector<D,T,M>& trim( const int& n ) { return trimFront( n ).trimBack( n ); }

    // METHOD_TRANSFORM

    Vector<D,T,M>& RotateX( const T& );
    Vector<D,T,M>& RotateY( const T& );
    Vector<D,T,M>& RotateZ( const T& );

    #ifdef OPENCV_FOUND

    Vector<D,T,M> warp( const CV& cv ) const { return mat().warp( cv ); }
    Vector<D,T,M>& Warp( const Vector<D,T,M>& vec , const CV& cv ) { mat() = vec.mat().warp( cv ); return *this; }

    Vector<D,T,M> transform( const CV& cv ) const { return mat().transform( cv ); }
    Vector<D,T,M>& Transform( const Vector<D,T,M>& vec , const CV& cv ) { mat() = vec.mat().transform( cv ); return *this; }

    Vector<D,T,M> itransform( const CV& cv ) const { return mat().itransform( cv ); }
    Vector<D,T,M>& iTransform( const Vector<D,T,M>& vec , const CV& cv ) { mat() = vec.mat().itransform( cv ); return *this; }

    #endif

    // METHOD_CALC

    T sum() const { return mat().sum(); }
    T sqsum() const { return mat().sqsum(); }

    T norm2() const { return sqsum(); }
    T norm2( const Vector<D,T,M>& vec ) const { return ( mat() % vec.mat() ).sum(); }

    // METHOD_REDUCTION

    Matrix<T> limRows() const { return mat().limRows(); }
    Matrix<T> limCols() const { return mat().limCols(); }

    Matrix<T> sumRows() const { return mat().sumRows(); }
    Matrix<T> sumCols() const { return mat().sumCols(); }

    // METHOD_CONVERT

    Matrix<T> toRGBjet() const { return mat().toRGBjet(); }
    Matrix<T> toRGBjet( const T& min , const T& max ) const { return mat().toRGBjet( min , max ); }

    // METHOD_SET

    Vector<D,T,M>& load( const String& );
    void save( const String& ) const;

    Vector<D,T,M>& load( const String& str , const int& n ) { return load( str + std::to_string(n) ); }
    void save( const String& str , const int& n ) const { save( str + std::to_string(n) ); }

    Vector<D,T,M>& setVal( const D& );
    Vector<D,T,M>& setIncrease( const D& = 0 , const D& = 1 );

    Vector<D,T,M>& setRand( const T& min = 0 , const T& max = 1 )
    { mat().setRand( min , max ); return *this; }

    Vector<D,T,M>& Shuffle();

    // METHOD_SAMPLE

    Vector<D,T,M> sample( int st , const int& jmp ) const { return mat().sampleRows( st , jmp ); }
    Vector<D,T,M> sample( const int& jmp ) const { return jmp > 0 ? mat().sampleRows( 0 , jmp ) : mat().sampleRows( -1 , jmp ); }

    Vector<D,T,M> sample( const int& st , const int& ntv , const int& jmp ) const { return mat().sampleRows( st , ntv , jmp ); }

    Vector<D,T,M> sample( const Matrix<int>& idx ) const { return mat().sampleRows( idx ); }
    Vector<D,T,M> sample( const Matrix<int>& idx , const int& n ) const { return mat().sampleRows( idx , n ); }

    Vector<D,T,M> sampleRand( const int& n ) const { return mat().sampleRandRows( n ); }

    // METHOD_REMOVE

    Vector<D,T,M> remove( int st , const int& jmp ) const { return mat().removeRows( st , jmp ); }
    Vector<D,T,M> remove( const int& jmp ) const { return jmp > 0 ? mat().removeRows( 0 , jmp ) : mat().removeRows( -1 , jmp ); }

    Vector<D,T,M> remove( const int& st , const int& ntv , const int& jmp ) const { return mat().removeRows( st , ntv , jmp ); }

    Vector<D,T,M> remove( const Matrix<int>& idx ) const { return mat().removeRows( idx ); }
    Vector<D,T,M> remove( const Matrix<int>& idx , const int& n ) const { return mat().removeRows( idx , n ); }

//    Vector<D,T,M> removeRand( const int& n ) const { return mat().removeRandRows( n ); }

};

TPL_T using Vec = Vector< T , T , 1 >;
using Veci = Vec<int>;
using Vecf = Vec<float>;
using Vecd = Vec<double>;
using Vecu = Vec<unsigned int>;
using Vecc = Vec<unsigned char>;

using VVecd = Seq<Vecd>;

#ifdef OPENCV_FOUND

TPL_T using Pts2 = Vector< Pt2<T> , T , 2 >;
using Pts2i = Pts2<int>;
using Pts2f = Pts2<float>;
using Pts2d = Pts2<double>;

TPL_T using Pts3 = Vector< Pt3<T> , T , 3 >;
using Pts3i = Pts3<int>;
using Pts3f = Pts3<float>;
using Pts3d = Pts3<double>;

TPL_T using SeqPts2 = Seq<Pts2<T>>;
using SeqPts2i = SeqPts2<int>;
using SeqPts2f = SeqPts2<float>;
using SeqPts2d = SeqPts2<double>;

TPL_T using SeqPts3 = Seq<Pts3<T>>;
using SeqPts3i = SeqPts3<int>;
using SeqPts3f = SeqPts3<float>;
using SeqPts3d = SeqPts3<double>;

#endif

TPL_TC using VecN = Vector< Array<T,C> , T , C >;
TPL_C using VecNi = VecN<int,C>;
TPL_C using VecNf = VecN<float,C>;
TPL_C using VecNd = VecN<double,C>;
TPL_C using VecNu = VecN<unsigned int,C>;
TPL_C using VecNc = VecN<unsigned char,C>;

TPL_T using VecMatrix = Vector< Matrix<T> , unsigned , 0 >;
using VecMati = VecMatrix<int>;
using VecMatf = VecMatrix<float>;
using VecMatd = VecMatrix<double>;

TPL_T using VSparse = Vector< Sparse<T> , unsigned , 0 >;
using VecSpri = VSparse<int>;
using VecSprf = VSparse<float>;
using VecSprd = VSparse<double>;

using Vec1i = VecNi<1>; using Vec1f = VecNf<1>; using Vec1d = VecNd<1>; using Vec1u = VecNu<1>; using Vec2c = VecNc<2>;
using Vec2i = VecNi<2>; using Vec2f = VecNf<2>; using Vec2d = VecNd<2>; using Vec2u = VecNu<2>; using Vec2c = VecNc<2>;
using Vec3i = VecNi<3>; using Vec3f = VecNf<3>; using Vec3d = VecNd<3>; using Vec3u = VecNu<3>; using Vec3c = VecNc<3>;
using Vec4i = VecNi<4>; using Vec4f = VecNf<4>; using Vec4d = VecNd<4>; using Vec4u = VecNu<4>; using Vec4c = VecNc<4>;
using Vec5i = VecNi<5>; using Vec5f = VecNf<5>; using Vec5d = VecNd<5>; using Vec5u = VecNu<5>; using Vec5c = VecNc<5>;
using Vec6i = VecNi<6>; using Vec6f = VecNf<6>; using Vec6d = VecNd<6>; using Vec6u = VecNu<6>; using Vec6c = VecNc<6>;
using Vec7i = VecNi<7>; using Vec7f = VecNf<7>; using Vec7d = VecNd<7>; using Vec7u = VecNu<7>; using Vec7c = VecNc<7>;
using Vec8i = VecNi<8>; using Vec8f = VecNf<8>; using Vec8d = VecNd<8>; using Vec8u = VecNu<8>; using Vec8c = VecNc<8>;
using Vec9i = VecNi<9>; using Vec9f = VecNf<9>; using Vec9d = VecNd<9>; using Vec9u = VecNu<9>; using Vec9c = VecNc<9>;

}

#include "vector_src.h"

#endif
