#ifndef SPARSE_H
#define SPARSE_H

#include <cvpp/containers/base.h>

namespace cvpp
{

TPL_T
class Matrix;

TPL_T
class Sparse : public Base<T>
{

protected:

    Pointer< SEigen > eig_ptr;

public:

    // Constructor

    Sparse();
    Sparse( const String& );
    Sparse( const String& , const int& );

    Sparse( const Sparse<T>& , const bool& = SHARE );
    Sparse( const Matrix<T>& , const bool& = SHARE );

          Sparse( const SEigen& , const bool& = SHARE );
    TPL_F Sparse( const FEigen& , const bool& = SHARE );
    TPL_B Sparse( const BEigen  , const bool& = SHARE );

    Sparse( const Dims& );
    Sparse( const int& , const int& = 1 );

    Sparse( const int& , const TripletList<T>& );
    Sparse( const int& , const int& , const TripletList<T>& );

    // Initialise

    void initialise( const Dims& );
    void initialise( const int& , const int& = 1 );
    void initialise( const int& , const int& , const TripletList<T>& );

    Sparse<T>& reserve( const int& n ) { eig_ptr->reserve( n ); return *this; }

    Sparse<T>& reset() { initialise( 0 , 0 ); return *this; }
    Sparse<T>& reset( const Dims& dims ) { initialise( dims.r , dims.c ); return *this; }
    Sparse<T>& reset( const int& r , const int& c = 1 ) { initialise( r , c ); return *this; }
    Sparse<T>& reset( const int& r , const int& c , const int& z ) { initialise( r , c ); reserve( z ); return *this; }

    // Info

    Sparse<T> clone() const { return Sparse<T>( *this , COPY ); }

    const bool empty()  const { return s() == 0; }
    const bool filled() const { return !empty(); }
    const bool valid()  const { T s = sum(); return !isnan( s ) && !isinf( s ); }

    const bool fits( const Sparse<T>& spr ) const { return r() == spr.r() && c() == spr.c(); }
    const bool fits( const Matrix<T>& mat ) const { return r() == mat.r() && c() == mat.c(); }

          const bool fits( const DEigen& deig ) const { return r() == deig.rows() && c() == deig.cols(); }
          const bool fits( const SEigen& seig ) const { return r() == seig.rows() && c() == seig.cols(); }
    TPL_F const bool fits( const FEigen& feig ) const { return r() == feig.rows() && c() == feig.cols(); }
    TPL_B const bool fits( const BEigen& beig ) const { return r() == beig.rows() && c() == beig.cols(); }

    const bool fits( const Seq<T>& seq ) const { return r() == seq.size() && c() == 1;       }
    const bool fits( const CV& cv      ) const { return r() == cv.rows    && c() == cv.cols; }

    const bool inside( const int& i , const int& j ) const
    { return i >= 0 && i < r() && j >= 0 && j < c(); }

    const int r() const { return eig_ptr->rows(); }
    const int c() const { return eig_ptr->cols(); }
    const int o() const { return eig_ptr->outerSize(); }
    const int s() const { return r() * c(); }

    const int nz() const { return eig_ptr->nonZeros(); }

    const int ridx( const int& r ) const { return r >= 0 ? r : this->r() + r; }
    const int cidx( const int& c ) const { return c >= 0 ? c : this->c() + c; }

    Dims dims() const { return Dims( r() , c() ); }

    // Data

    T& operator()( const int& r , const int& c ) { return (*eig_ptr).coeffRef( ridx(r) , cidx(c) ); }
    const T& operator()( const int& r , const int& c ) const { return (*eig_ptr).coeffRef( ridx(r) , cidx(c) ); }

    T& at( const int& r , const int& c ) { return (*eig_ptr).coeffRef( ridx(r) , cidx(c) ); }
    const T& at( const int& r , const int& c ) const { return (*eig_ptr).coeffRef( ridx(r) , cidx(c) ); }

    T& operator()( const int& n ) { return c() == 1 ? at(n,0) : at(0,n); }
    const T& operator()( const int& n ) const { return c() == 1 ? at(n,0) : at(0,n); }

    T& at( const int& n ) { return c() == 1 ? at(n,0) : at(0,n); }
    const T& at( const int& n ) const { return c() == 1 ? at(n,0) : at(0,n); }

    T& operator[]( const int& n ) { return at(n); }
    const T& operator[]( const int& n ) const { return at(n); }

    SEigen& eig() const { return *eig_ptr.get(); }

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

    // PRINT

    void info() const;
    void print() const;

    void hinfo() const { info(); halt(); }
    void hprint() const { print(); halt(); }

    TPL_U void info( const U& ) const;
    TPL_U void print( const U& ) const;

    TPL_U void hinfo( const U& v ) const { info( v ); halt(); }
    TPL_U void hprint( const U& v ) const { print( v ); halt(); }

    // OPERATOR_ATTRIB

    Sparse<T>& operator>>( const Sparse<T>& );
    Sparse<T>& operator= ( const Sparse<T>& );
    Sparse<T>& operator<<( const Sparse<T>& );

    Sparse<T>& share(  const Sparse<T>& spr ) { return *this >> spr; }
    Sparse<T>& assign( const Sparse<T>& spr ) { return *this =  spr; }
    Sparse<T>& copy(   const Sparse<T>& spr ) { return *this << spr; }

    Sparse<T>& operator= ( const Matrix<T>& );
    Sparse<T>& operator<<( const Matrix<T>& );

    Sparse<T>& assign( const Matrix<T>& mat ) { return *this =  mat;  }
    Sparse<T>& copy(   const Matrix<T>& mat ) { return *this << mat; }

    Sparse<T>& operator= ( const SEigen& );
    Sparse<T>& operator<<( const SEigen& );

    Sparse<T>& assign( const SEigen& seig ) { return *this =  seig; }
    Sparse<T>& copy(   const SEigen& seig ) { return *this << seig; }

    TPL_F Sparse<T>& operator= ( const FEigen& );
    TPL_F Sparse<T>& operator<<( const FEigen& );

    TPL_F Sparse<T>& assign( const FEigen& FEIG ) { return *this =  FEIG; }
    TPL_F Sparse<T>& copy(   const FEigen& FEIG ) { return *this << FEIG; }

    TPL_B Sparse<T>& operator= ( const BEigen );
    TPL_B Sparse<T>& operator<<( const BEigen );

    TPL_B Sparse<T>& assign( const BEigen beig ) { return *this =  beig; }
    TPL_B Sparse<T>& copy(   const BEigen beig ) { return *this << beig; }

    // OPERATOR_UNARY

    Sparse<T> operator+();
    Sparse<T> operator-();

    TPL_U Sparse<T>& operator+=( const U& );
    TPL_U Sparse<T>& operator-=( const U& );
    TPL_U Sparse<T>& operator*=( const U& );
    TPL_U Sparse<T>& operator/=( const U& );

    TPL_U Sparse<T>& add( const U& val ) { return *this += val; }
    TPL_U Sparse<T>& sub( const U& val ) { return *this -= val; }
    TPL_U Sparse<T>& mlt( const U& val ) { return *this *= val; }
    TPL_U Sparse<T>& div( const U& val ) { return *this /= val; }

    Sparse<T>& operator+=( const SEigen& );
    Sparse<T>& operator-=( const SEigen& );
    Sparse<T>& operator*=( const SEigen& );
    Sparse<T>& operator%=( const SEigen& );
    Sparse<T>& operator/=( const SEigen& );

    Sparse<T>& add( const SEigen& seig ) { return *this += seig; }
    Sparse<T>& sub( const SEigen& seig ) { return *this -= seig; }
    Sparse<T>& mlt( const SEigen& seig ) { return *this *= seig; }
    Sparse<T>& dot( const SEigen& seig ) { return *this %= seig; }
    Sparse<T>& div( const SEigen& seig ) { return *this /= seig; }

    TPL_F Sparse<T>& operator+=( const FEigen& );
    TPL_F Sparse<T>& operator-=( const FEigen& );
    TPL_F Sparse<T>& operator*=( const FEigen& );
    TPL_F Sparse<T>& operator%=( const FEigen& );
    TPL_F Sparse<T>& operator/=( const FEigen& );

    TPL_F Sparse<T>& add( const FEigen& feig ) { return *this += feig; }
    TPL_F Sparse<T>& sub( const FEigen& feig ) { return *this -= feig; }
    TPL_F Sparse<T>& mlt( const FEigen& feig ) { return *this *= feig; }
    TPL_F Sparse<T>& dot( const FEigen& feig ) { return *this %= feig; }
    TPL_F Sparse<T>& div( const FEigen& feig ) { return *this /= feig; }

    TPL_B Sparse<T>& operator+=( const BEigen );
    TPL_B Sparse<T>& operator-=( const BEigen );
    TPL_B Sparse<T>& operator*=( const BEigen );
    TPL_B Sparse<T>& operator%=( const BEigen );
    TPL_B Sparse<T>& operator/=( const BEigen );

    TPL_B Sparse<T>& add( const BEigen beig ) { return *this += beig; }
    TPL_B Sparse<T>& sub( const BEigen beig ) { return *this -= beig; }
    TPL_B Sparse<T>& mlt( const BEigen beig ) { return *this *= beig; }
    TPL_B Sparse<T>& dot( const BEigen beig ) { return *this %= beig; }
    TPL_B Sparse<T>& div( const BEigen beig ) { return *this /= beig; }

    Sparse<T>& operator+=( const Sparse<T>& );
    Sparse<T>& operator-=( const Sparse<T>& );
    Sparse<T>& operator*=( const Sparse<T>& );
    Sparse<T>& operator%=( const Sparse<T>& );
    Sparse<T>& operator/=( const Sparse<T>& );

    Sparse<T>& add( const Sparse<T>& spr ) { return *this += spr; }
    Sparse<T>& sub( const Sparse<T>& spr ) { return *this -= spr; }
    Sparse<T>& mlt( const Sparse<T>& spr ) { return *this *= spr; }
    Sparse<T>& dot( const Sparse<T>& spr ) { return *this %= spr; }
    Sparse<T>& div( const Sparse<T>& spr ) { return *this /= spr; }

    Sparse<T>& operator+=( const Matrix<T>& );
    Sparse<T>& operator-=( const Matrix<T>& );
    Sparse<T>& operator*=( const Matrix<T>& );
    Sparse<T>& operator%=( const Matrix<T>& );
    Sparse<T>& operator/=( const Matrix<T>& );

    Sparse<T>& add( const Matrix<T>& mat ) { return *this += mat; }
    Sparse<T>& sub( const Matrix<T>& mat ) { return *this -= mat; }
    Sparse<T>& mlt( const Matrix<T>& mat ) { return *this *= mat; }
    Sparse<T>& dot( const Matrix<T>& mat ) { return *this %= mat; }
    Sparse<T>& div( const Matrix<T>& mat ) { return *this /= mat; }

    // METHOD_CONVERT

    Matrix<T> dense() const { return *this; }

    // METHOD_STORE

    Sparse<T>& load( const String& );
    void save( const String& ) const;

    Sparse<T>& load( const String& str , const int& n ) { return load( str + std::to_string( n ) ); }
    void save( const String& str , const int& n ) const { save( str + std::to_string( n ) ); }

    Sparse<T>& loadASC( const String& );
    void saveASC( const String& ) const;

    Sparse<T>& loadASC( const String& str , const int& n ) { return loadASC( str + std::to_string( n ) ); }
    void saveASC( const String& str , const int& n ) const { saveASC( str + std::to_string( n ) ); }

    Sparse<T>& loadBIN( const String& );
    void saveBIN( const String& ) const;

    Sparse<T>& loadBIN( const String& str , const int& n ) { return loadBIN( str + std::to_string( n ) ); }
    void saveBIN( const String& str , const int& n ) const { saveBIN( str + std::to_string( n ) ); }

    // METHOD_SET

    TPL_U Sparse<T>& insert( const int& r , const int& c , const U& val )
    { eig_ptr->insert( ridx(r) , cidx(c) ) = val; return *this; }

    TPL_U Sparse<T>& insert( const int& r , const U& val )
    { eig_ptr->insert( ridx(r) , 0 ) = val; return *this; }

    Sparse<T>& set( const TripletList<T>& );

    Sparse<T>& setVal( double , const T& );

    Sparse<T>& setIncrease( double , const T& , const T& );
    Sparse<T>& setIncrease( double n , const T& val = 1 ) { return setIncrease( n , 0 , val ); }

    Sparse<T>& setRand( double , const T& , const T& );
    Sparse<T>& setRand( double n , const T& val ) { return setRand( n , -val , +val ); }
    Sparse<T>& setRand( double n ) { return setRand( n , 0 , 1 ); }

    Sparse<T>& setRandRows( double , const T& , const T& );
    Sparse<T>& setRandRows( double n , const T& val ) { return setRandRows( n , -val , +val ); }
    Sparse<T>& setRandRows( double n ) { return setRandRows( n , 0 , 1 ); }

    Sparse<T>& setRandCols( double , const T& , const T& );
    Sparse<T>& setRandCols( double n , const T& val ) { return setRandCols( n , -val , +val ); }
    Sparse<T>& setRandCols( double n ) { return setRandCols( n , 0 , 1 ); }

    Sparse<T>& setIdentity() { eig().setIdentity(); return *this; }
    Sparse<T>& setIdentity( const T& val ) { return setIdentity().mlt( val ); }

    // METHOD_CHANGE

    Sparse<T> permutate( const Matrix<int>& ) const;

    // METHOD_CALC

    Sparse<T> t() const;
    Sparse<T> transpose() const { return t(); }

    Sparse<T> denominator() const;
    Sparse<T> denom() const { return denominator(); }

    Sparse<T>& Denominator();
    Sparse<T>& Denom() { return Denominator(); }

    Sparse<T>& Pow( const double& );
    Sparse<T> pow( const double& ) const;

    Sparse<T>& Root( const double& val ) { return Pow( 1.0 / val ); }
    Sparse<T> root( const double& val ) const { return pow( 1.0 / val ); }

    Sparse<T>& Square() { return Pow( 2.0 ); }
    Sparse<T> square() const { return pow( 2.0 ); }

    Sparse<T>& Cube() { return Pow( 3.0 ); }
    Sparse<T> cube() const { return pow( 3.0 ); }

    Sparse<T>& Sqrt();
    Sparse<T> sqrt() const;

    Sparse<T>& Cbrt();
    Sparse<T> cbrt() const;

    Sparse<T>& Exp();
    Sparse<T> exp() const;

    Sparse<T>& Log();
    Sparse<T> log() const;

    Sparse<T>& Sin();
    Sparse<T> sin() const;

    Sparse<T>& Cos();
    Sparse<T> cos() const;

    Sparse<T>& Asin();
    Sparse<T> asin() const;

    Sparse<T>& Acos();
    Sparse<T> acos() const;

    Sparse<T>& Abs();
    Sparse<T> abs() const;

    // METHOD_REDUCTION

    T sum() const { return eig().sum(); }

    // METHOD_SOLVE

    Matrix<T> bslash( const Matrix<T>& ) const;
    void bslash( Matrix<T>* ) const;

    Matrix<T> cbslash( const Matrix<T>& ) const;
    void cbslash( Matrix<T>* ) const;

};

using Spri = Sparse<int>;
using Sprf = Sparse<float>;
using Sprd = Sparse<double>;
using Spru = Sparse<unsigned>;

TPL_T using SeqSparse = Seq<Sparse<T>>;

using SeqSpri = SeqSparse<int>;
using SeqSprf = SeqSparse<float>;
using SeqSprd = SeqSparse<double>;
using SeqSpru = SeqSparse<unsigned>;

}

#include "sparse_src.h"

#endif
