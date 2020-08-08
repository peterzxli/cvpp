#ifndef MATRIX_H
#define MATRIX_H

#include "./base.h"

namespace cvpp
{

TPL_T class Sparse;
TPL_TC class Image;
TPL_DTM class Vector;

TPL_T
class Matrix : public Base<T>
{

protected:

    Pointer< DEigen > raw_ptr;
    Pointer< MEigen > eig_ptr;

public:

    // Constructor

    Matrix();
    Matrix( const String& );
    Matrix( const String& , const int& );

    Matrix( const Matrix<T>& , const bool& = SHARE );
    Matrix( const Sparse<T>& , const bool& = SHARE );

    TPL_C Matrix( const Image<T,C>& , const bool& = SHARE );

          Matrix( const SEigen& , const bool& = SHARE );
    TPL_F Matrix( const FEigen& , const bool& = SHARE );
    TPL_B Matrix( const BEigen  , const bool& = SHARE );

    Matrix( const Seq<T>&         , const bool& = SHARE );
    Matrix( const Seq<Matrix<T>>& , const bool& = SHARE );

    TPL_DM Matrix( const Vector<D,T,M>& , const bool& = SHARE );

    #ifdef OPENCV_FOUND
    Matrix( const CV& , const bool& = SHARE );
    #endif

    #ifdef SHOGUN_FOUND
    Matrix( const SGMatrix<T>& , const bool& = SHARE );
    Matrix( const SGVector<T>& , const bool& = SHARE );
    #endif

    Matrix( const Dims& );
    Matrix( const int& , const int& = 1 );

    Matrix( const int& , const int& , T* );
    Matrix( const int& , const int& ,
            const int& , const int& , const int& , T* );

    // Initialise

    void initialise( const Dims& );
    void initialise( const int& , const int& = 1 );
    void initialise( const int& , const int& ,
                           const int& , const int& , const int& , T* );

    void update();

    Matrix<T>& reset() { initialise( 0 , 0 ); return *this; }
    Matrix<T>& reset( const Dims& dims ) { initialise( dims.r , dims.c ); return *this; }
    Matrix<T>& reset( const int& r , const int& c = 1 ) { initialise( r , c ); return *this; }
    Matrix<T>& reset( T* data , const int& r , const int& c = 1 ) { initialise( 0 , 0 , r , c , c , data ); }

    // Info

    Matrix<T> clone() const { return Matrix<T>( *this , COPY ); }

    const bool empty()  const { return s() == 0; }
    const bool filled() const { return !empty(); }
    const bool valid()  const { T s = sum(); return !std::isnan( s ) && !std::isinf( s ); }

    const bool fits( const Matrix<T>& mat ) const { return r() == mat.r() && c() == mat.c(); }
    const bool fits( const Sparse<T>& spr ) const { return r() == spr.r() && c() == spr.c(); }

    TPL_C const bool fits( const Image<T,C>& img ) const { return r() == img.r() && c() == img.cd(); }

          const bool fits( const DEigen& deig ) const { return r() == deig.rows() && c() == deig.cols(); }
          const bool fits( const SEigen& seig ) const { return r() == seig.rows() && c() == seig.cols(); }
    TPL_F const bool fits( const FEigen& feig ) const { return r() == feig.rows() && c() == feig.cols(); }
    TPL_B const bool fits( const BEigen& beig ) const { return r() == beig.rows() && c() == beig.cols(); }

    const bool fits( const Seq<T>& seq ) const { return r() == seq.size() && c() == 1;       }

    #ifdef OPENCV_FOUND
    const bool fits( const CV& cv      ) const { return r() == cv.rows    && c() == cv.cols; }
    #endif

    #ifdef SHOGUN_FOUND
    const bool fits( const SGMatrix<T>& sgmat ) const { return r() == sgmat.num_rows && c() == sgmat.num_cols; }
    const bool fits( const SGVector<T>& sgvec ) const { return r() == sgvec.size()   && c() == 1;              }
    #endif

    const bool inside( const int& i , const int& j ) const
    { return i >= 0 && i < r() && j >= 0 && j < c(); }

    const int r() const { return eig_ptr->rows(); }
    const int c() const { return eig_ptr->cols(); }
    const int o() const { return eig_ptr->outerStride(); }
    const int s() const { return r() * c(); }

    const int ridx( const int& r ) const { return r >= 0 ? r : this->r() + r; }
    const int cidx( const int& c ) const { return c >= 0 ? c : this->c() + c; }

    const int nridx( const int& r , const int& nr ) const { return nr > 0 ? nr : this->r() - ridx(r) + nr; }
    const int ncidx( const int& c , const int& nc ) const { return nc > 0 ? nc : this->c() - cidx(c) + nc; }

    Dims dims() const { return Dims( r() , c() ); }

    // Data

    operator T() const { return at(0); }

    T& test( const int& r , const int& c ) const { return (*eig_ptr)( ridx(r) , cidx(c) ); }

    T& operator()( const int& r , const int& c ) { return (*eig_ptr)( ridx(r) , cidx(c) ); }
    const T& operator()( const int& r , const int& c ) const { return (*eig_ptr)( ridx(r) , cidx(c) ); }

    T& at( const int& r , const int& c ) { return (*eig_ptr)( ridx(r) , cidx(c) ); }
    const T& at( const int& r , const int& c ) const { return (*eig_ptr)( ridx(r) , cidx(c) ); }

    T& operator()( const int& n ) { return c() == 1 ? at(n,0) : at(0,n); }
    const T& operator()( const int& n ) const { return c() == 1 ? at(n,0) : at(0,n); }

    T& at( const int& n ) { return c() == 1 ? at(n,0) : at(0,n); }
    const T& at( const int& n ) const { return c() == 1 ? at(n,0) : at(0,n); }

    T& operator[]( const int& n ) { return at(n); }
    const T& operator[]( const int& n ) const { return at(n); }

    DEigen& raw() const { return *raw_ptr.get(); }
    MEigen& eig() const { return *eig_ptr.get(); }

    T* raw_data() const { return raw().data(); }
    T* eig_data() const { return eig().data(); }

    #ifdef OPENCV_FOUND
    CV cv() const { return CV( r() , c() , cv::DataType<T>::type , eig_data() ); }
    #endif

    #ifdef SHOGUN_FOUND
    SGMatrix<T> shogun() const { return shogun::SGMatrix<T>( eig_data() , r() , c() , false ); }
    #endif

    TPL_U auto operator<<( const U& val ) { return eig() << val; }

    // Eigen

    auto row( const int& r ) const { return eig().row(r); }
    auto row( const int& r , const int& n ) const { return eig().middleRows( r , n ); }

    auto urow( const int& n = 1 ) const { return eig().topRows(n); }
    auto drow( const int& n = 1 ) const { return eig().bottomRows(n); }

    auto col( const int& c ) const { return eig().col(c); }
    auto col( const int& r , const int& n ) const { return eig().middleCols( r , n ); }

    auto lcol( const int& n = 1 ) const { return eig().leftCols(n); }
    auto rcol( const int& n = 1 ) const { return eig().rightCols(n); }

    auto blk( const int& r , const int& c , const int& nr , const int& nc ) const
    { return eig().block( r , c , nr , nc ); }

    auto blk( const int& r , const int& c , const int& n ) const
    { return eig().block( r , c , n , n ); }

    auto lublk( const int& r , const int& c ) const { return eig().topLeftCorner( r , c ); }
    auto ldblk( const int& r , const int& c ) const { return eig().bottomLeftCorner( r , c ); }
    auto rublk( const int& r , const int& c ) const { return eig().topRightCorner( r , c ); }
    auto rdblk( const int& r , const int& c ) const { return eig().bottomRightCorner( r , c ); }

    auto lublk( const int& n ) const { return eig().topLeftCorner( n , n ); }
    auto ldblk( const int& n ) const { return eig().bottomLeftCorner( n , n ); }
    auto rublk( const int& n ) const { return eig().topRightCorner( n , n ); }
    auto rdblk( const int& n ) const { return eig().bottomRightCorner( n , n ); }

    // Blocks

    Matrix<T> r( const int& r0 , const int& nr = 1 ) const
    { return Matrix( ridx(r0) , 0 , nridx(r0,nr) , c() , o() , eig_ptr->data() ); }

    Matrix<T> ru( const int& n = 1 ) const { return r(  0 , n ); }
    Matrix<T> rd( const int& n = 1 ) const { return r( -n , n ); }
    Matrix<T> rm( const int& ni , const int& nf = 0 ) const { return r( ni , r() - nf - ni ); }

    Matrix<T> c( const int& c0 , const int& nc = 1 ) const
    { return Matrix( 0 , cidx(c0) , r() , ncidx(c0,nc) , o() , eig_ptr->data() ); }

    Matrix<T> cl( const int& n = 1 ) const { return c(  0 , n ); }
    Matrix<T> cr( const int& n = 1 ) const { return c( -n , n ); }
    Matrix<T> cm( const int& ni , const int& nf = 0 ) const { return c( ni , c() - nf - ni ); }

    Matrix<T> b( const int& r0 , const int& c0 , const int& nr , const int& nc ) const
    { return Matrix( ridx(r0) , cidx(c0) , nridx(r0,nr) , ncidx(c0,nc) , o() , eig_ptr->data() ); }

    Matrix<T> b( const int& r0 , const int& c0 , const int& n = 1 ) const
    { return Matrix( ridx(r0) , cidx(c0) , n , n , o() , eig_ptr->data() ); }

    Matrix<T> blu( const int& n ) const { return b(  0 ,  0 , n , n ); }
    Matrix<T> bld( const int& n ) const { return b( -n ,  0 , n , n ); }
    Matrix<T> brd( const int& n ) const { return b( -n , -n , n , n ); }
    Matrix<T> bru( const int& n ) const { return b(  0 , -n , n , n ); }

    Matrix<T> blu( const int& r , const int& c ) const { return b(  0 ,  0 , r , c ); }
    Matrix<T> bld( const int& r , const int& c ) const { return b( -r ,  0 , r , c ); }
    Matrix<T> brd( const int& r , const int& c ) const { return b( -r , -c , r , c ); }
    Matrix<T> bru( const int& r , const int& c ) const { return b(  0 , -c , r , c ); }

    Matrix<T> sr( const int& jmp ) const { return sampleRows( jmp ); }
    Matrix<T> sc( const int& jmp ) const { return sampleCols( jmp ); }

    Matrix<T> sr( int st , const int& jmp ) const { return sampleRows( st , jmp ); }
    Matrix<T> sc( int st , const int& jmp ) const { return sampleCols( st , jmp ); }

    Matrix<T> sr( const int& st , const int& ntv , const int& jmp ) const { return sampleRows( st , ntv , jmp ); }
    Matrix<T> sc( const int& st , const int& ntv , const int& jmp ) const { return sampleCols( st , ntv , jmp ); }

    Matrix<T> sr( const Matrix<int>& idx ) const { return sampleRows( idx ); }
    Matrix<T> sc( const Matrix<int>& idx ) const { return sampleCols( idx ); }

    Matrix<T> rr( const int& jmp ) const { return removeRows( jmp ); }
    Matrix<T> rc( const int& jmp ) const { return removeCols( jmp ); }

    Matrix<T> rr( int st , const int& jmp ) const { return removeRows( st , jmp ); }
    Matrix<T> rc( int st , const int& jmp ) const { return removeCols( st , jmp ); }

    Matrix<T> rr( const int& st , const int& ntv , const int& jmp ) const { return removeRows( st , ntv , jmp ); }
    Matrix<T> rc( const int& st , const int& ntv , const int& jmp ) const { return removeCols( st , ntv , jmp ); }

    Matrix<T> rr( const Matrix<int>& idx ) const { return removeRows( idx ); }
    Matrix<T> rc( const Matrix<int>& idx ) const { return removeCols( idx ); }

    #ifdef OPENCV_FOUND
    Pt2<T> rpt2( const int& i ) const { return Pt2<T>( at(i,0) , at(i,1)           ); }
    Pt3<T> rpt3( const int& i ) const { return Pt3<T>( at(i,0) , at(i,1) , at(i,2) ); }
    #endif

    // PRINT

    void info() const;
    void print() const;
    void show() const;

    void hinfo() const { info(); halt(); }
    void hprint() const { print(); halt(); }
    void hshow() const { show(); halt(); }

    TPL_U void info( const U& ) const;
    TPL_U void print( const U& ) const;

    TPL_U void hinfo( const U& v ) const { info( v ); halt(); }
    TPL_U void hprint( const U& v ) const { print( v ); halt(); }

    // OPERATOR_ATTRIB

    Matrix<T>& operator>>( const Matrix<T>& );
    Matrix<T>& operator= ( const Matrix<T>& );
    Matrix<T>& operator<<( const Matrix<T>& );

    Matrix<T>& share(  const Matrix<T>& mat ) { return *this >> mat; }
    Matrix<T>& assign( const Matrix<T>& mat ) { return *this =  mat; }
    Matrix<T>& copy(   const Matrix<T>& mat ) { return *this << mat; }

    Matrix<T>& operator= ( const Sparse<T>& );
    Matrix<T>& operator<<( const Sparse<T>& );

    Matrix<T>& assign( const Sparse<T>& spr ) { return *this =  spr; }
    Matrix<T>& copy(   const Sparse<T>& spr ) { return *this << spr; }

    TPL_DM Matrix<T>& operator>>( const Vector<D,T,M>& );
    TPL_DM Matrix<T>& operator= ( const Vector<D,T,M>& );
    TPL_DM Matrix<T>& operator<<( const Vector<D,T,M>& );

    TPL_DM Matrix<T>& share(  const Vector<D,T,M>& vec ) { return *this >> vec; }
    TPL_DM Matrix<T>& assign( const Vector<D,T,M>& vec ) { return *this =  vec; }
    TPL_DM Matrix<T>& copy(   const Vector<D,T,M>& vec ) { return *this << vec; }

    TPL_C Matrix<T>& operator= ( const Image<T,C>& );
    TPL_C Matrix<T>& operator<<( const Image<T,C>& );

    TPL_C Matrix<T>& assign( const Image<T,C>& img ) { return *this =  img; }
    TPL_C Matrix<T>& copy(   const Image<T,C>& img ) { return *this << img; }

    Matrix<T>& operator=(  const SEigen& );
    Matrix<T>& operator<<( const SEigen& );

    Matrix<T>& assign( const SEigen& seig ) { return *this =  seig; }
    Matrix<T>& copy(   const SEigen& seig ) { return *this << seig; }

    TPL_F Matrix<T>& operator>>(       FEigen& );
    TPL_F Matrix<T>& operator= ( const FEigen& );
    TPL_F Matrix<T>& operator<<( const FEigen& );

    TPL_F Matrix<T>& share(        FEigen& feig ) { return *this >> feig; }
    TPL_F Matrix<T>& assign( const FEigen& feig ) { return *this =  feig; }
    TPL_F Matrix<T>& copy(   const FEigen& feig ) { return *this << feig; }

    TPL_B Matrix<T>& operator>>(       BEigen );
    TPL_B Matrix<T>& operator= ( const BEigen );
    TPL_B Matrix<T>& operator<<( const BEigen );

    TPL_B Matrix<T>& share(        BEigen beig ) { return *this >> beig; }
    TPL_B Matrix<T>& assign( const BEigen beig ) { return *this =  beig; }
    TPL_B Matrix<T>& copy(   const BEigen beig ) { return *this << beig; }

    Matrix<T>& operator=(  const Seq<T>& );
    Matrix<T>& operator<<( const Seq<T>& );

    Matrix<T>& assign( const Seq<T>& seq ) { return *this =  seq; }
    Matrix<T>& copy(   const Seq<T>& seq ) { return *this << seq; }

    Matrix<T>& operator<<( const Seq<Matrix<T>>& );

    Matrix<T>& copy(   const Seq<Matrix<T>>& seq ) { return *this << seq; }

    #ifdef OPENCV_FOUND

    Matrix<T>& operator>>( const CV& );
    Matrix<T>& operator=(  const CV& );
    Matrix<T>& operator<<( const CV& );

    Matrix<T>& share(  const CV& cv ) { return *this >> cv; }
    Matrix<T>& assign( const CV& cv ) { return *this =  cv; }
    Matrix<T>& copy(   const CV& cv ) { return *this << cv; }

    #endif

    #ifdef SHOGUN_FOUND 

    Matrix<T>& operator>>( const SGMatrix<T>& );
    Matrix<T>& operator= ( const SGMatrix<T>& );
    Matrix<T>& operator<<( const SGMatrix<T>& );

    Matrix<T>& share(  const SGMatrix<T>& sgmat ) { return *this >> sgmat; }
    Matrix<T>& assign( const SGMatrix<T>& sgmat ) { return *this =  sgmat; }
    Matrix<T>& copy(   const SGMatrix<T>& sgmat ) { return *this << sgmat; }

    Matrix<T>& operator>>( const SGVector<T>& );
    Matrix<T>& operator= ( const SGVector<T>& );
    Matrix<T>& operator<<( const SGVector<T>& );

    Matrix<T>& share(  const SGVector<T>& sgvec ) { return *this >> sgvec; }
    Matrix<T>& assign( const SGVector<T>& sgvec ) { return *this =  sgvec; }
    Matrix<T>& copy(   const SGVector<T>& sgvec ) { return *this << sgvec; }

    #endif

    // OPERATOR_COMPARISON

    TPL_U Matrix<int> operator==( const U& val ) const { return equalIDX( val ); }
    TPL_U Matrix<int> operator> ( const U& val ) const { return biggerIDX( val ); }
    TPL_U Matrix<int> operator< ( const U& val ) const { return smallerIDX( val ); }
    TPL_U Matrix<int> operator>=( const U& val ) const { return eqbiggerIDX( val ); }
    TPL_U Matrix<int> operator<=( const U& val ) const { return eqsmallerIDX( val ); }

    // OPERATOR_APPEND

    Matrix<T>& operator&=( const Matrix<T>& mat ) { return AppR( mat ); }
    Matrix<T>& operator|=( const Matrix<T>& mat ) { return AppD( mat ); }

    Matrix<T> appR1() { Matrix<T> M( r() , 1 ); M.setVal(1); return *this & M; }
    Matrix<T> appD1() { Matrix<T> M( 1 , c() ); M.setVal(1); return *this | M; }

    // OPERATOR_UNARY

    Matrix<T> operator+() const;
    Matrix<T> operator-() const;

    TPL_U Matrix<T>& operator+=( const U& val ) { eig().array() += val; return *this; }
    TPL_U Matrix<T>& operator-=( const U& val ) { eig().array() -= val; return *this; }
    TPL_U Matrix<T>& operator*=( const U& val ) { eig().array() *= val; return *this; }
    TPL_U Matrix<T>& operator/=( const U& val ) { eig().array() /= val; return *this; }

    TPL_U Matrix<T>& add( const U& val ) { return *this += val; }
    TPL_U Matrix<T>& sub( const U& val ) { return *this -= val; }
    TPL_U Matrix<T>& mlt( const U& val ) { return *this *= val; }
    TPL_U Matrix<T>& div( const U& val ) { return *this /= val; }

    Matrix<T>& operator+=( const SEigen& );
    Matrix<T>& operator-=( const SEigen& );
    Matrix<T>& operator*=( const SEigen& );
    Matrix<T>& operator%=( const SEigen& );
    Matrix<T>& operator/=( const SEigen& );

    Matrix<T>& add( const SEigen& seig ) { return *this += seig; }
    Matrix<T>& sub( const SEigen& seig ) { return *this -= seig; }
    Matrix<T>& mlt( const SEigen& seig ) { return *this *= seig; }
    Matrix<T>& dot( const SEigen& seig ) { return *this %= seig; }
    Matrix<T>& div( const SEigen& seig ) { return *this /= seig; }

    TPL_F Matrix<T>& operator+=( const FEigen& );
    TPL_F Matrix<T>& operator-=( const FEigen& );
    TPL_F Matrix<T>& operator*=( const FEigen& );
    TPL_F Matrix<T>& operator%=( const FEigen& );
    TPL_F Matrix<T>& operator/=( const FEigen& );

    TPL_F Matrix<T>& add( const FEigen& feig ) { return *this += feig; }
    TPL_F Matrix<T>& sub( const FEigen& feig ) { return *this -= feig; }
    TPL_F Matrix<T>& mlt( const FEigen& feig ) { return *this *= feig; }
    TPL_F Matrix<T>& dot( const FEigen& feig ) { return *this %= feig; }
    TPL_F Matrix<T>& div( const FEigen& feig ) { return *this /= feig; }

    TPL_B Matrix<T>& operator+=( const BEigen );
    TPL_B Matrix<T>& operator-=( const BEigen );
    TPL_B Matrix<T>& operator*=( const BEigen );
    TPL_B Matrix<T>& operator%=( const BEigen );
    TPL_B Matrix<T>& operator/=( const BEigen );

    TPL_B Matrix<T>& add( const BEigen beig ) { return *this += beig; }
    TPL_B Matrix<T>& sub( const BEigen beig ) { return *this -= beig; }
    TPL_B Matrix<T>& mlt( const BEigen beig ) { return *this *= beig; }
    TPL_B Matrix<T>& dot( const BEigen beig ) { return *this %= beig; }
    TPL_B Matrix<T>& div( const BEigen beig ) { return *this /= beig; }

    Matrix<T>& operator+=( const Matrix<T>& );
    Matrix<T>& operator-=( const Matrix<T>& );
    Matrix<T>& operator*=( const Matrix<T>& );
    Matrix<T>& operator%=( const Matrix<T>& );
    Matrix<T>& operator/=( const Matrix<T>& );

    Matrix<T>& add( const Matrix<T>& mat ) { return *this += mat; }
    Matrix<T>& sub( const Matrix<T>& mat ) { return *this -= mat; }
    Matrix<T>& mlt( const Matrix<T>& mat ) { return *this *= mat; }
    Matrix<T>& dot( const Matrix<T>& mat ) { return *this %= mat; }
    Matrix<T>& div( const Matrix<T>& mat ) { return *this /= mat; }

    Matrix<T>& operator+=( const Sparse<T>& );
    Matrix<T>& operator-=( const Sparse<T>& );
    Matrix<T>& operator*=( const Sparse<T>& );
    Matrix<T>& operator%=( const Sparse<T>& );
    Matrix<T>& operator/=( const Sparse<T>& );

    Matrix<T>& add( const Sparse<T>& spr ) { return *this += spr; }
    Matrix<T>& sub( const Sparse<T>& spr ) { return *this -= spr; }
    Matrix<T>& mlt( const Sparse<T>& spr ) { return *this *= spr; }
    Matrix<T>& dot( const Sparse<T>& spr ) { return *this %= spr; }
    Matrix<T>& div( const Sparse<T>& spr ) { return *this /= spr; }

    // METHOD_STORE

    Matrix<T>& load( const String& );
    void save( const String& ) const;

    Matrix<T>& load( const String& str , const int& n ) { return load( strn( str , n ) ); }
    void save( const String& str , const int& n ) const { save( strn( str , n ) ); }

    Matrix<T>& loadASC( const String& );
    void saveASC( const String& ) const;

    Matrix<T>& loadASC( const String& str , const int& n ) { return loadASC( strn( str , n ) ); }
    void saveASC( const String& str , const int& n ) const { saveASC( strn( str , n ) ); }

    Matrix<T>& loadBIN( const String& );
    void saveBIN( const String& ) const;

    Matrix<T>& loadBIN( const String& str , const int& n ) { return loadBIN( strn( str , n ) ); }
    void saveBIN( const String& str , const int& n ) const { saveBIN( strn( str , n ) ); }

    Matrix<T>& loadNPY( const String& );
    void saveNPY( const String& ) const;

    Matrix<T>& loadNPY( const String& str , const int& n ) { return loadNPY( strn( str , n ) ); }
    void saveNPY( const String& str , const int& n ) const { saveNPY( strn( str , n ) ); }

    Matrix<T>& loadCSV( const String& , const char& = ',' );
    void saveCSV( const String& , const char& = ',' ) const;

    Matrix<T>& loadSTR( const String& );
    void saveSTR( String& str ) const { str = saveSTR(); }
    String     saveSTR() const;


    // METHOD_SET

    Matrix<T>& setVal( const T& );
    Matrix<T>& operator=( const T& val ) { return setVal( val ); }

    Matrix<T>& setRand( const T& , const T& );
    Matrix<T>& setRand( const T& val ) { return setRand( -val , +val ); }
    Matrix<T>& setRand() { return setRand( 0 , 1 ); }

    Matrix<T>& setRandn( const T& , const T& );
    Matrix<T>& setRandn( const T& v ) { return setRandn( 0 , v ); }
    Matrix<T>& setRandn() { return setRandn( 0 , 1 ); }

    Matrix<T> addRand( const T& , const T& ) const;
    Matrix<T> addRand( const T& val ) const { return addRand( -val , +val ); }
    Matrix<T> addRand() const { return addRand( 0 , 1 ); }

    Matrix<T>& AddRand( const T& , const T& );
    Matrix<T>& AddRand( const T& val ) { return AddRand( -val , +val ); }
    Matrix<T>& AddRand() { return AddRand( 0 , 1 ); }

    Matrix<T> addRandn( const T& , const T& ) const;
    Matrix<T> addRandn( const T& v ) const { return addRandn( 0 , v ); }
    Matrix<T> addRandn() const { return addRandn( 0 , 1 ); }

    Matrix<T>& AddRandn( const T& , const T& );
    Matrix<T>& AddRandn( const T& v ) { return AddRandn( 0 , v ); }
    Matrix<T>& AddRandn() { return AddRandn( 0 , 1 ); }

    Matrix<T>& setIncrease( const T& , const T& );
    Matrix<T>& setIncrease( const T& val = 1 ) { return setIncrease( 0 , val ); }

    Matrix<T>& setInterval( const T& st , const T& fn ) { return setIncrease( st , ( fn - st ) / T( s() - 1 ) ); }
    Matrix<T>& setInterval( const T& fn ) { return setInterval( 0 , fn ); }

    Matrix<T>& setIdentity();
    Matrix<T>& setIdentity( const T& val ) { return setIdentity().mlt( val ); }

    // METHOD_CONVERT

    Sparse<T> sparse() const { return *this; }

    TPL_U Matrix<U> convert() const;

    Matrix<int> toInt() const { return convert<int>(); }
    Matrix<float> toFloat() const { return convert<float>(); }
    Matrix<double> toDouble() const { return convert<double>(); }
    Matrix<unsigned int> toUInt() const { return convert<unsigned int>(); }
    Matrix<unsigned char> toUChar() const { return convert<unsigned char>(); }

    Matrix<float> toRGBjet( const T& , const T& ) const;
    Matrix<float> toRGBjet() const { return toRGBjet( min() , max() ); }

    Matrix<float> toDEPjet( const T& , const T& ) const;
    Matrix<float> toDEPjet() const { return toDEPjet( min() , max() ); }

    Matrix<float> toRGBbnd( const T& , const T& , const T& = 0.5 , const T& = 0.05 ) const;
    Matrix<float> toRGBbnd( const T& val = 0.5 , const T& pad = 0.05 ) const { return toRGBbnd( min() , max() , val , pad ); }

    Matrix<float> toRGBlbl() const;

    Matrix<float> toGRAYjet( const T& , const T& ) const;
    Matrix<float> toGRAYjet() const { return toGRAYjet( min() , max() ); }

    TPL_U void toROSmsg( U& ) const;
    TPL_U void fromROSmsg( const U& );

    // METHOD_RESIZE

    Matrix<T>& Resize( const int& r , const int& c = 1 );

    Matrix<T> append( const int& r , const int& c ) const;
    Matrix<T> append( const int& n ) const { return append( n , n ); }

    Matrix<T>& Append( const int& r , const int& c );
    Matrix<T>& Append( const int& n ) { return Append( n , n ); }

    Matrix<T> repRows( const int& ) const;
    Matrix<T> repCols( const int& ) const;

    Matrix<T> appL( const int& ) const;
    Matrix<T> appU( const int& ) const;
    Matrix<T> appR( const int& ) const;
    Matrix<T> appD( const int& ) const;

    Matrix<T>& AppL( const int& );
    Matrix<T>& AppU( const int& );
    Matrix<T>& AppR( const int& );
    Matrix<T>& AppD( const int& );

    Matrix<T> appL( const Matrix<T>& ) const;
    Matrix<T> appU( const Matrix<T>& ) const;
    Matrix<T> appR( const Matrix<T>& ) const;
    Matrix<T> appD( const Matrix<T>& ) const;

    Matrix<T>& AppL( const Matrix<T>& );
    Matrix<T>& AppU( const Matrix<T>& );
    Matrix<T>& AppR( const Matrix<T>& );
    Matrix<T>& AppD( const Matrix<T>& );

    Matrix<T> delL( const int& ) const;
    Matrix<T> delU( const int& ) const;
    Matrix<T> delR( const int& ) const;
    Matrix<T> delD( const int& ) const;

    Matrix<T>& DelL( const int& );
    Matrix<T>& DelU( const int& );
    Matrix<T>& DelR( const int& );
    Matrix<T>& DelD( const int& );

    Matrix<T> keepL( const int& n ) const { return delR( c() - n ); }
    Matrix<T> keepU( const int& n ) const { return delD( r() - n ); }
    Matrix<T> keepR( const int& n ) const { return delL( c() - n ); }
    Matrix<T> keepD( const int& n ) const { return delU( r() - n ); }

    Matrix<T>& KeepL( const int& n ) { return DelR( c() - n ); }
    Matrix<T>& KeepU( const int& n ) { return DelD( r() - n ); }
    Matrix<T>& KeepR( const int& n ) { return DelL( c() - n ); }
    Matrix<T>& KeepD( const int& n ) { return DelU( r() - n ); }

    Matrix<T> appRows( const int& , const int& = 1 ) const;
    Matrix<T> appCols( const int& , const int& = 1 ) const;

    Matrix<T>& AppRows( const int& , const int& = 1 );
    Matrix<T>& AppCols( const int& , const int& = 1 );

    Matrix<T> appRows( const int& , const Matrix<T>& ) const;
    Matrix<T> appCols( const int& , const Matrix<T>& ) const;

    Matrix<T>& AppRows( const int& , const Matrix<T>& );
    Matrix<T>& AppCols( const int& , const Matrix<T>& );

    Matrix<T> delRows( const int& , const int& = 1 ) const;
    Matrix<T> delCols( const int& , const int& = 1 ) const;

    Matrix<T>& DelRows( const int& , const int& = 1 );
    Matrix<T>& DelCols( const int& , const int& = 1 );

    Matrix<T> delCross( const int& i , const int& n = 1 ) const { return delRows(i,n).DelCols(i,n); }
    Matrix<T>& DelCross( const int& i , const int& n = 1 ) { return DelRows(i,n).DelCols(i,n); }

    Matrix<T> keepRows( const int& , const int& = 1 ) const;
    Matrix<T> keepCols( const int& , const int& = 1 ) const;

    Matrix<T>& KeepRows( const int& , const int& = 1 );
    Matrix<T>& KeepCols( const int& , const int& = 1 );

    // METHOD_RESHAPE

    Matrix<T> reshape( const int& , const int& ) const;

    Matrix<T> toRow() const { return reshape( 1 , s() ); }
    Matrix<T> toCol() const { return reshape( s() , 1 ); }

    Matrix<int> coord() const;
    Matrix<T> lblMat() const;

    // METHOD_SAMPLE

    Matrix<T> sampleRows( int , const int& ) const;
    Matrix<T> sampleCols( int , const int& ) const;

    Matrix<T>& SampleRows( int , const int& );
    Matrix<T>& SampleCols( int , const int& );

    Matrix<T> sampleRows( const int& , const int& , const int& ) const;
    Matrix<T> sampleCols( const int& , const int& , const int& ) const;

    Matrix<T>& SampleRows( const int& , const int& , const int& );
    Matrix<T>& SampleCols( const int& , const int& , const int& );

    Matrix<T> sampleRows( const int& jmp ) const { return jmp > 0 ? sampleRows( 0 , jmp ) : sampleRows( -1 , jmp ); }
    Matrix<T> sampleCols( const int& jmp ) const { return jmp > 0 ? sampleCols( 0 , jmp ) : sampleCols( -1 , jmp ); }

    Matrix<T>& SampleRows( const int& jmp ) { return jmp > 0 ? SampleRows( 0 , jmp ) : SampleRows( -1 , jmp ); }
    Matrix<T>& SampleCols( const int& jmp ) { return jmp > 0 ? SampleCols( 0 , jmp ) : SampleCols( -1 , jmp ); }

    Matrix<T> sampleRows( const Matrix<int>& ) const;
    Matrix<T> sampleCols( const Matrix<int>& ) const;

    Matrix<T>& SampleRows( const Matrix<int>& idx ) { *this >> sampleRows( idx ); return *this; }
    Matrix<T>& SampleCols( const Matrix<int>& idx ) { *this >> sampleCols( idx ); return *this; }

    Matrix<T> sampleRows( const Matrix<int>& , const int& ) const;
    Matrix<T> sampleCols( const Matrix<int>& , const int& ) const;

    Matrix<T>& SampleRows( const Matrix<int>& idx , const int& n ) { *this >> sampleRows( idx , n ); return *this; }
    Matrix<T>& SampleCols( const Matrix<int>& idx , const int& n ) { *this >> sampleCols( idx , n ); return *this; }

    Matrix<T> sampleRandRows( const int& ) const;
    Matrix<T> sampleRandCols( const int& ) const;

    Matrix<T>& SampleRandRows( const int& );
    Matrix<T>& SampleRandCols( const int& );

    Matrix<T> uniqueRows() const;
    Matrix<T> uniqueCols() const;

    // METHOD_REMOVE

    Matrix<T> removeRows( int , const int& ) const;
    Matrix<T> removeCols( int , const int& ) const;

    Matrix<T>& RemoveRows( int , const int& );
    Matrix<T>& RemoveCols( int , const int& );

    Matrix<T> removeRows( const int& , const int& , int ) const;
    Matrix<T> removeCols( const int& , const int& , int ) const;

    Matrix<T>& RemoveRows( const int& , const int& , int );
    Matrix<T>& RemoveCols( const int& , const int& , int );

    Matrix<T> removeRows( const int& jmp ) const { return jmp > 0 ? removeRows( 0 , jmp ) : removeRows( -1 , jmp ); }
    Matrix<T> removeCols( const int& jmp ) const { return jmp > 0 ? removeCols( 0 , jmp ) : removeCols( -1 , jmp ); }

    Matrix<T>& RemoveRows( const int& jmp ) { return jmp > 0 ? RemoveRows( 0 , jmp ) : RemoveRows( -1 , jmp ); }
    Matrix<T>& RemoveCols( const int& jmp ) { return jmp > 0 ? RemoveCols( 0 , jmp ) : RemoveCols( -1 , jmp ); }

    Matrix<T> removeRows( const Matrix<int>& ) const;
    Matrix<T> removeCols( const Matrix<int>& ) const;

    Matrix<T>& RemoveRows( const Matrix<int>& idx ) { *this >> removeRows( idx ); return *this; }
    Matrix<T>& RemoveCols( const Matrix<int>& idx ) { *this >> removeCols( idx ); return *this; }

    Matrix<T> removeRows( const Matrix<int>& , const int& ) const;
    Matrix<T> removeCols( const Matrix<int>& , const int& ) const;

    Matrix<T>& RemoveRows( const Matrix<int>& idx , const int& n ) { *this >> removeRows( idx , n ); return *this; }
    Matrix<T>& RemoveCols( const Matrix<int>& idx , const int& n ) { *this >> removeCols( idx , n ); return *this; }

    // METHOD_SPLIT

    Seq<Matrix<T>> separateRows( const Matrix<int>& ) const;
    Seq<Matrix<T>> separateCols( const Matrix<int>& ) const;

    Seq<Matrix<T>> splitRows( const Matrix<int>& idx , const int& n ) const;
    Seq<Matrix<T>> splitCols( const Matrix<int>& idx , const int& n ) const;

    Seq<Matrix<T>> splitRows( const int& n ) const { Matrix<int> idx( r() ); return splitRows( idx.setIncrease() , n ); }
    Seq<Matrix<T>> splitCols( const int& n ) const { Matrix<int> idx( c() ); return splitCols( idx.setIncrease() , n ); }

    Seq<Matrix<T>> splitRandRows( const int& n ) const { Matrix<int> idx( r() ); return splitRows( idx.setIncrease().ShuffleRows() , n ); }
    Seq<Matrix<T>> splitRandCols( const int& n ) const { Matrix<int> idx( c() ); return splitCols( idx.setIncrease().ShuffleRows() , n ); }

    // METHOD_SORT

    Matrix<T>& Sort();
    Matrix<T> sort() const;

    Matrix<T>& Sort( const int& n );
    Matrix<T> sort( const int& n ) const;

    Matrix<T> sortRows() const;
    Matrix<T> sortCols() const;

    Matrix<T>& SortRows();
    Matrix<T>& SortCols();

    Matrix<int> sortRowsIDX() const;
    Matrix<int> sortColsIDX() const;

    // METHOD_SHUFFLE

    Matrix<T> shuffleRows() const;
    Matrix<T> shuffleCols() const;

    Matrix<T>& ShuffleRows();
    Matrix<T>& ShuffleCols();

    // METHOD_FIND

    Matrix<int> biggerIDX( const T& ) const;
    Matrix<int> smallerIDX( const T& ) const;
    Matrix<int> eqbiggerIDX( const T& ) const;
    Matrix<int> eqsmallerIDX( const T& ) const;

    Matrix<T> bigger( const T& v ) const { return sampleRows( biggerIDX( v ) ); }
    Matrix<T> smaller( const T& v ) const { return sampleRows( smallerIDX( v ) ); }

    Matrix<int> equalIDX( const T& ) const;
    Matrix<int> equalIDX( const T& , const T& ) const;

    Matrix<T> equal( const T& v ) const { return sampleRows( equalIDX( v ) ); }
    Matrix<T> equal( const T& v , const T& e ) const { return sampleRows( equalIDX( v , e ) ); }

    TPL_U Matrix<int> findEqual( const Matrix<U>& ) const;
    TPL_U Matrix<int> findDiff( const Matrix<U>& ) const;

    TPL_U unsigned findEqualQty( const Matrix<U>& mat ) const { return findEqual( mat ).r(); }
    TPL_U unsigned findDiffQty( const Matrix<U>& mat ) const { return findDiff( mat ).r(); }

    TPL_U double findEqualPerc( const Matrix<U>& mat ) const { return (double)findEqualQty( mat ) / (double)s(); }
    TPL_U double findDiffPerc( const Matrix<U>& mat ) const { return (double)findDiffQty( mat ) / (double)s(); }

    Matrix<int> gridClosest( const Matrix<T>& , const Matrix<T>& ,
                             const Matrix<T>& , const Matrix<int>& ) const;
    Matrix<int> gridClosest( const Matrix<T>& mat )
    { return gridClosest( mat , mat.minRows() , mat.gridResolutin() , mat.gridSize() ); }

    // METHOD_FILTER

    Matrix<int> filterRowsIDX( const Matrix<T>& ) const;
    Matrix<int> filterColsIDX( const Matrix<T>& ) const;

    Matrix<T> filterRows( const Matrix<T>& lim ) const { return sampleRows( filterRowsIDX( lim ) ); }
    Matrix<T> filterCols( const Matrix<T>& lim ) const { return sampleCols( filterColsIDX( lim ) ); }

    Matrix<T>& FilterRows( const Matrix<T>& lim ) { return SampleRows( filterRowsIDX( lim ) ); }
    Matrix<T>& FilterCols( const Matrix<T>& lim ) { return SampleCols( filterColsIDX( lim ) ); }

    // METHOD_CALC

    Matrix<T> t() const;
    Matrix<T> transpose() const { return t(); }

    Matrix<T>& Inv();
    Matrix<T> inv() const;

    Matrix<T>& Inverse() { return Inv(); }
    Matrix<T> inverse() const { return inv(); }

    Matrix<T>& Denom();
    Matrix<T> denom() const;

    Matrix<T>& Denominator() { return Denom(); }
    Matrix<T> denominator() const { return denom(); }

    Matrix<T> eigenvalues() const;
    Matrix<T> eigenvectors() const;
    Matrix<T> eigen( Matrix<T>& , Matrix<T>& ) const;

    Matrix<T>& Conv( const Matrix<T>& , const String& = "SAME" );
    Matrix<T> conv( const Matrix<T>& , const String& = "SAME" ) const;

    Matrix<T>& matSqrt();
    Matrix<T> matsqrt() const;

    Matrix<T>& Sigmoid( const T& , const T& , const T& );
    Matrix<T> sigmoid( const T& , const T& , const T& ) const;

    Matrix<T>& Pow( const T& );
    Matrix<T> pow( const T& ) const;

    Matrix<T>& Root( const T& );
    Matrix<T> root( const T& ) const;

    Matrix<T>& Square();
    Matrix<T> square() const;

    Matrix<T>& Cube();
    Matrix<T> cube() const;

    Matrix<T>& Sqrt();
    Matrix<T> sqrt() const;

    Matrix<T>& Cbrt();
    Matrix<T> cbrt() const;

    Matrix<T>& Exp();
    Matrix<T> exp() const;

    Matrix<T>& Log();
    Matrix<T> log() const;

    Matrix<T>& Sin();
    Matrix<T> sin() const;

    Matrix<T>& Cos();
    Matrix<T> cos() const;

    Matrix<T>& Asin();
    Matrix<T> asin() const;

    Matrix<T>& Acos();
    Matrix<T> acos() const;

    Matrix<T>& Abs();
    Matrix<T> abs() const;

    // METHOD_CHANGE

    Matrix<T> diagonal() const;
    Matrix<T> diag() const { return diagonal(); }
    Matrix<T> ldiag() const { return diagonal().log(); }

    Matrix<T> addJitter( const T& ) const;
    Matrix<T>& AddJitter( const T& );

    Matrix<T> replace( const T& , const T& ) const;
    Matrix<T>& Replace( const T& , const T& );

    Matrix<T>& FlipRows();
    Matrix<T> flipRows() const;

    Matrix<T>& FlipCols();
    Matrix<T> flipCols() const;

    Matrix<T>& RboRows() { return *this = rboRows(); }
    Matrix<T> rboRows() const;

    Matrix<T>& RboCols() { return *this = rboCols(); }
    Matrix<T> rboCols() const;

    Matrix<T>& Floor();
    Matrix<T> floor() const;

    Matrix<T>& Round();
    Matrix<T> round() const;

    Matrix<T>& Ceil();
    Matrix<T> ceil() const;

    Matrix<T>& Floor( const T& );
    Matrix<T> floor( const T& ) const;

    Matrix<T>& Ceil( const T& );
    Matrix<T> ceil( const T& ) const;

    Matrix<T>& Limits( const T& , const T& );
    Matrix<T> limits( const T& , const T& ) const;

    Matrix<T>& Min( const Matrix<T>& );
    Matrix<T> min( const Matrix<T>& ) const;

    Matrix<T>& Max( const Matrix<T>& );
    Matrix<T> max( const Matrix<T>& ) const;

    Matrix<T>& Lim( const Matrix<T>& );
    Matrix<T> lim( const Matrix<T>& ) const;

    Matrix<T>& Mod( const T& );
    Matrix<T> mod( const T& ) const;

    Matrix<T> subMeanRows() const { return *this - meanRows(); }
    Matrix<T> subMeanCols() const { return *this - meanCols(); }

    Matrix<T>& SubMeanRows() { return sub( meanRows() ); }
    Matrix<T>& SubMeanCols() { return sub( meanCols() ); }

    Matrix<T> gridDouble2D() const;
    Matrix<T> gridDoubleCol2D() const;

    // METHOD_REDUCTION

    T sum()  const { return eig().sum(); }
    T prod() const { return eig().prod(); }

    T mean() const { return sum() / s(); }
    T abmean() const { return absum() / s(); }

    T norm() const { return std::sqrt( sqsum() ); }

    T median() const;

    T det() const { return eig().determinant(); }
    T logdet() const { return std::log( det() ); }

    T trace() const { return eig().trace(); }
    T tr() const { return trace(); }

    T lsum() const  { return log().sum();        }
    T ldsum() const { return diag().log().sum(); }
    T sqsum() const { return square().sum();     }
    T absum() const  { return abs().sum();       }

    T rsum() const { return std::sqrt( sum() ); }
    T rmean() const { return std::sqrt( mean() ); }

    T rsqsum() const { return std::sqrt( square().sum() ); }
    T rsqmean() const { return std::sqrt( square().mean() ); }

    T min() const { return eig().minCoeff(); }
    T max() const { return eig().maxCoeff(); }

    T min( unsigned& r , unsigned& c ) const { return eig().minCoeff( &r , &c ); }
    T max( unsigned& r , unsigned& c ) const { return eig().maxCoeff( &r , &c ); }

    int minIDX() const { unsigned r , c ; this->min( r , c ) ; return this->r() == 1 ? c : r ; }
    int maxIDX() const { unsigned r , c ; this->max( r , c ) ; return this->r() == 1 ? c : r ; }

    #ifdef OPENCV_FOUND
    Pt2i minPt() { unsigned r , c ; this->min( r , c ); return Pt2i( c , r ); }
    Pt2i maxPt() { unsigned r , c ; this->max( r , c ); return Pt2i( c , r ); }
    #endif

    Matrix<T> sumRows() const;
    Matrix<T> sumCols() const;

    Matrix<T> sqsumRows() const { return square().sumRows(); }
    Matrix<T> sqsumCols() const { return square().sumCols(); }

    Matrix<T> normRows() const { return *this / sqsumRows().sqrt(); }
    Matrix<T> normCols() const { return *this / sqsumCols().sqrt(); }

    Matrix<T>& NormRows() { return *this /= sqsumRows().sqrt(); }
    Matrix<T>& NormCols() { return *this /= sqsumCols().sqrt(); }

    Matrix<T> magnRows() const { return sqsumRows().Sqrt(); }
    Matrix<T> magnCols() const { return sqsumCols().Sqrt(); }

    Matrix<T> cumsumRows() const;
    Matrix<T> cumsumCols() const;

    Matrix<T>& CumsumRows();
    Matrix<T>& CumsumCols();

    Matrix<T> prodRows() const;
    Matrix<T> prodCols() const;

    Matrix<T> minRows() const;
    Matrix<T> minCols() const;

    Matrix<int> minRowsIDX( const Matrix<T>& min ) const;
    Matrix<int> minColsIDX( const Matrix<T>& min ) const;

    Matrix<int> minRowsIDX() const { return minRowsIDX( minRows() ); }
    Matrix<int> minColsIDX() const { return minColsIDX( minCols() ); }

    Matrix<T> maxRows() const;
    Matrix<T> maxCols() const;

    Matrix<int> maxRowsIDX( const Matrix<T>& max ) const;
    Matrix<int> maxColsIDX( const Matrix<T>& max ) const;

    Matrix<int> maxRowsIDX() const { return maxRowsIDX( maxRows() ); }
    Matrix<int> maxColsIDX() const { return maxColsIDX( maxCols() ); }

    Matrix<T> limRows() const;
    Matrix<T> limCols() const;

    Matrix<T> limRows( const T& pd ) const { Matrix<T> lim = limRows(); lim.r(0) -= pd; lim.r(1) += pd; return lim; }
    Matrix<T> limCols( const T& pd ) const { Matrix<T> lim = limCols(); lim.c(0) -= pd; lim.c(1) += pd; return lim; }

    Matrix<int> limRowsIDX() const;
    Matrix<int> limColsIDX() const;

    Matrix<int> gridSize() const;
    Matrix<T> gridResolution() const;

    Dims gridDims() const
    { Matrix<int> size = gridSize(); return Dims( size(0) , size(1) ); }

    Matrix<T> meanRows() const { return sumRows() / (T)r(); }
    Matrix<T> meanCols() const { return sumCols() / (T)c(); }

    Matrix<T> medianRows() const;

    Matrix<T> midRows() const { return ( maxRows() + minRows() ) / 2.0; }
    Matrix<T> midCols() const { return ( maxCols() + minCols() ) / 2.0; }

    Matrix<T> diffRows() const { return maxRows() - minRows(); }
    Matrix<T> diffCols() const { return maxCols() - minCols(); }

    Matrix<T> covRows( const Matrix<T>& ) const;
    Matrix<T> covCols( const Matrix<T>& ) const;

    Matrix<T> covRows() const { return covRows( meanRows() ); }
    Matrix<T> covCols() const { return covCols( meanCols() ); }

    Matrix<T> varRows( const Matrix<T>& ) const;
    Matrix<T> varCols( const Matrix<T>& ) const;

    Matrix<T> varRows() const { return varRows( meanRows() ); }
    Matrix<T> varCols() const { return varCols( meanCols() ); }

    Matrix<T>& mcovRows( Matrix<T>& mean , Matrix<T>& cov ) { mean = meanRows(); cov = covRows(mean); return *this; }
    Matrix<T>& mcovCols( Matrix<T>& mean , Matrix<T>& cov ) { mean = meanCols(); cov = covCols(mean); return *this; }

    Matrix<T>& mcovRows( const Matrix<int>& , Seq<Matrix<T>>& , Seq<Matrix<T>>& , Seq<Matrix<T>>& );
    Matrix<T>& mcovCols( const Matrix<int>& , Seq<Matrix<T>>& , Seq<Matrix<T>>& , Seq<Matrix<T>>& );

    void bin( const int& , const T& , const T& , Matrix<T>& , Matrix<T>& ) const;
    void bin( const int& m , Matrix<T>& bx , Matrix<T>& by ) const { bin( m , min() , max() , bx , by ); }
    Matrix<T> bin( const int& m ) const { Matrix<T> bx , by; bin( m , bx , by ); return by; }

    // METHOD_SOLVE

    Matrix<T> bslash()  const;
    Matrix<T> cbslash() const { return bslash(); }

    Matrix<T> bslash( const Matrix<T>& ) const;
    Matrix<T> cbslash( const Matrix<T>& mat ) const { return bslash( mat ); }

    Matrix<T>& bslash( Matrix<T>* );
    Matrix<T>& cbslash( Matrix<T>* mat ) { return bslash( mat ); }

    Matrix<T> dbslash() const;
    Matrix<T> cdbslash() const { return dbslash(); }

    Matrix<T> dbslash( const Matrix<T>& ) const;
    Matrix<T> cdbslash( const Matrix<T>& mat ) const { return dbslash( mat ); }

    Matrix<T>& dbslash( Matrix<T>* );
    Matrix<T>& cdbslash( Matrix<T>* mat ) { return dbslash( mat ); }

    Matrix<T> slash( const Matrix<T>& mat ) const
    { return mat.t().bslash( t() ).t(); }

    // METHOD_CHOLESKY

    Matrix<T> chol() const;

    Matrix<T>& Rank1update( const Matrix<T>& );
    Matrix<T> rank1update( const Matrix<T>& mat ) const { return clone().Rank1update( mat ); }

    Matrix<T>& DelCrossChol( const int& );
    Matrix<T> delCrossChol( const int& n ) const { return clone().DelCrossChol( n ); }

    // METHOD_TRANSFORM

    Matrix<T>& RotateX( const T& );
    Matrix<T>& RotateY( const T& );
    Matrix<T>& RotateZ( const T& );

    Matrix<T>& Rotate( const T& d ) { return RotateZ( d ); }

    Matrix<T> rotateX( const T& d ) const { Matrix<T> tmp = clone(); tmp.RotateX( d ); return tmp; }
    Matrix<T> rotateY( const T& d ) const { Matrix<T> tmp = clone(); tmp.RotateY( d ); return tmp; }
    Matrix<T> rotateZ( const T& d ) const { Matrix<T> tmp = clone(); tmp.RotateZ( d ); return tmp; }

    Matrix<T> rotate( const T& d ) const { return rotateZ( d ); }

    Matrix<T>& SpinX( const T& d ) { Matrix<T> mean = meanRows(); return sub( mean ).RotateX( d ).add( mean ); }
    Matrix<T>& SpinY( const T& d ) { Matrix<T> mean = meanRows(); return sub( mean ).RotateY( d ).add( mean ); }
    Matrix<T>& SpinZ( const T& d ) { Matrix<T> mean = meanRows(); return sub( mean ).RotateZ( d ).add( mean ); }

    Matrix<T>& Spin( const T& d ) { Matrix<T> mean = meanRows(); return sub( mean ).RotateZ( d ).add( mean ); }

    Matrix<T> spinX( const T& d ) const { Matrix<T> tmp = clone(); tmp.SpinX( d ); return tmp; }
    Matrix<T> spinY( const T& d ) const { Matrix<T> tmp = clone(); tmp.SpinY( d ); return tmp; }
    Matrix<T> spinZ( const T& d ) const { Matrix<T> tmp = clone(); tmp.SpinZ( d ); return tmp; }

    Matrix<T> spin( const T& d ) const { return spinZ( d ); }

    #ifdef OPENCV_FOUND

    Matrix<T> warp( const CV& ) const;
    Matrix<T>& Warp( const Matrix<T>& mat , const CV& cv ) { *this = mat.warp( cv ); }

    Matrix<T> transform( const CV& ) const;
    Matrix<T>& Transform( const Matrix<T>& mat , const CV& cv ) { *this = mat.transform( cv ); }

    Matrix<T> itransform( const CV& ) const;
    Matrix<T>& iTransform( const Matrix<T>& mat , const CV& cv ) { *this = mat.itransform( cv ); }

    #endif

    // METHOD_DISTANCE

    Matrix<T> vecDistRows() const;
    Matrix<T> matDistRows() const;

    // METHOD_DISTRIBUTION

    Matrix<T> toDistrNormal( const T& , const T& );

    // METHOD_CLUSTER

    Matrix<T> closestRowsDST( const Matrix<T>& ) const;
    Matrix<int> closestRowsLBL( const Matrix<T>& ) const;

    unsigned mergeClusters( Matrix<T>& , Matrix<int>& , const int& ) const;
    unsigned RemoveClusters( Matrix<T>& , Matrix<int>& , const int& );

    Matrix<int> removeClustersIDX( Matrix<T>& , Matrix<int>& , const int& ) const;

    // METHOD_MAKE

    Matrix<T>& make3Ddataset( const Matrix<T>& , Matrix<T>& , Matrix<T>& , Matrix<T>& , Matrix<T>& , Matrix<T>& );
    Matrix<T>& make3DdatasetGP( const Matrix<T>& , Matrix<T>& , Matrix<T>& , Matrix<T>& , Matrix<T>& , Matrix<T>& );

    Matrix<T>& makeSCANdataset( Matrix<T>& , Matrix<T>& , const T& = 0.5 );

    TPL_U void make3Dscanset( Matrix<T>& , Matrix<U>& , T = 0.0 , const int& = 1 );

    TPL_U void makeScanset( Matrix<T>& X , Matrix<U>& Y ,
                                  const double& stp = 0 , const double& thk = 0 ,
                                  const int& jmp = 1 , const double& dec = 1 ) const;

    // ROUTINE_KMEANS

    void kmeans( const int& , Matrix<T>& , Matrix<int>& ,
                       const int& iter = 20 , const int& attempts = 5 , const double& tol = 0.05 ) const;
    void kmeans( const int& , const int& , Matrix<T>& , Matrix<int>& ,
                       const int& iter = 10 , const double& tol = 0.05 ) const;

    Matrix<T> kmeansCTR( const int& n ) const
    { Matrix<T> ctr; Matrix<int> lbl; kmeans( n , ctr , lbl ); return ctr; }

    Matrix<int> kmeansLBL( const int& n ) const
    { Matrix<T> ctr; Matrix<int> lbl; kmeans( n , ctr , lbl ); return lbl; }

    void kmeanspp( const int& , Matrix<T>& , Matrix<int>& ) const;
    void kmeanspar( const int& , const int& , Matrix<T>& , Matrix<int>& ) const;

};

using Mati = Matrix<int>;
using Matf = Matrix<float>;
using Matd = Matrix<double>;
using Matu = Matrix<unsigned int>;
using Matc = Matrix<unsigned char>;

TPL_T using SeqMatrix = Seq<Matrix<T>>;

using SeqMati = SeqMatrix<int>;
using SeqMatf = SeqMatrix<float>;
using SeqMatd = SeqMatrix<double>;
using SeqMatu = SeqMatrix<unsigned int>;
using SeqMatc = SeqMatrix<unsigned char>;

TPL_T using SSeqMatrix = Seq<Seq<Matrix<T>>>;

using SSeqMati = SSeqMatrix<int>;
using SSeqMatf = SSeqMatrix<float>;
using SSeqMatd = SSeqMatrix<double>;
using SSeqMatu = SSeqMatrix<unsigned int>;
using SSeqMatc = SSeqMatrix<unsigned char>;

}

#include "matrix_src.h"

#endif
