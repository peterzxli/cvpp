#ifndef IMAGE_H
#define IMAGE_H

#include <cmath>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cvpp/structs/struct_dims.h>
#include <cvpp/structs/struct_data_type.h>

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/macros_base.h>

#ifdef VLFEAT_FOUND

extern "C"
{
    #include <vl/generic.h>
    #include <vl/slic.h>
}

#endif

namespace cvpp
{

TPL_T
class Matrix;

TPL_DTM
class Vector;

TPL_TC
class Image
{

protected:

    Pointer< CVImage > cv_ptr;
    Pointer< IEigen > eig_ptr;

public:

    // Constructor

    Image();

    Image( const String& );
    Image( const String& , const int& );

    Image( const CV& , const bool& = SHARE );
    Image( const Image<T,C>& , const bool& = SHARE );

    Image( const Matrix<T>& , const bool& = SHARE );

    Image( const int& , const int& ,
           const int& , const int& ,
           const int& , const int& , CVImage );

    Image( const Dims& );
    Image( const int& , const int& );
    Image( const int& , const int& , const T& );

    // Initialise

    void initialise( const int& ,
                     const int& );

    void initialise( const int& , const int& ,
                     const int& , const int& ,
                     const int& , const int& , CVImage );

    Image<T,C>& reset( const int& r , const int& c )
    { initialise( r , c ); return *this; }

    Image<T,C>& reset( const int& r , const int& c , const T& val )
    { initialise( r , c ); setVal( val ); return *this; }

    void update();

    // Info

    Image<T,C> clone() const { return Image<T,C>( *this , COPY ); }

    const bool empty()  const { return s() == 0; }
    const bool filled() const { return !empty(); }

    const bool fits( const Image<T,C>& img ) const { return r() == img.r() && c() == img.c();       }
    const bool fits( const Matrix<T>&  mat ) const { return r() == mat.r() && c() == mat.c() / d(); }
    const bool fits( const CV& cv          ) const { return r() == cv.rows && c() == cv.cols;       }

    const int r() const { return cv_ptr->rows;       }
    const int c() const { return cv_ptr->cols;       }
    const int d() const { return cv_ptr->channels(); }

    const int cd() const { return c() * d(); }
    const int s() const { return r() * cd(); }

    const int ridx( const int& r ) const { return r >= 0 ? r : this->r() + r; }
    const int cidx( const int& c ) const { return c >= 0 ? c : this->c() + c; }
    const int nidx( const int& n ) const { return n >= 0 ? n :     C     + n; }

    Size size() const { return cv().size(); }
    Dims dims() const { return Dims( r() , c() ); }

    // Data

    T& operator()(const int& r , const int& c ,const int& d = 0 ) const { return ( *eig_ptr.get() )( r , c * C + d ); }
    T& at(const int& r , const int& c , const int& d = 0 ) const { return ( *this )( r , c , d ); }

    CVImage& cv() const { return *cv_ptr.get();  }
    IEigen& eig() const { return *eig_ptr.get(); }

    T* cv_data() const {  return (T*)cv().data;    }
    T* eig_data() const { return (T*)eig().data(); }

    Matrix<T> mat() const { return Matrix<T>( r() , cd() , eig_data() ); }

    // Sub

    Image<T,C> r( const int& r , const int& nr = 1 ) const { return Image<T,C>(    0    , ridx(r) , nr , c() , 1 , 0 , cv() ); }
    Image<T,C> c( const int& c , const int& nc = 1 ) const { return Image<T,C>( cidx(c) ,    0    , r() , nc , 1 , 0 , cv() ); }

    Image<T,C> ru( const int& nr = 1 ) { return r(  0  , nr ); }
    Image<T,C> rd( const int& nr = 1 ) { return r( -nr , nr ); }

    Image<T,C> cl( const int& nc = 1 ) { return c(  0  , nc ); }
    Image<T,C> cr( const int& nc = 1 ) { return c( -nc , nc ); }

    Image<T,1> rn( const int& r , const int& nr , const int& n ) const { return Image<T,1>(       0       , ridx(r) , nr  , c() , d() , nidx(n) , cv() ); }
    Image<T,1> cn( const int& c , const int& nc , const int& n ) const { return Image<T,1>( cidx(c) * d() ,    0    , r() , nc  , d() , nidx(n) , cv() ); }

    Image<T,1> rn( const int& r , const int& n ) const { return rn( r , 1 , n ); }
    Image<T,1> cn( const int& c , const int& n ) const { return cn( c , 1 , n ); }

    Image<T,1> run( const int& nr , const int& n ) const { return rn(  0  , nr , n ); }
    Image<T,1> rdn( const int& nr , const int& n ) const { return rn( -nr , nr , n ); }

    Image<T,1> cln( const int& nc , const int& n ) const { return cn(  0  , nc , n ); }
    Image<T,1> crn( const int& nc , const int& n ) const { return cn( -nc , nc , n ); }

    Image<T,C> b( const int& r , const int& c , const int& nr , const int& nc ) const { return Image<T,C>( cidx(c) , ridx(r) , nr , nc , 1 , 0 , cv() ); }
    Image<T,C> b( const int& r , const int& c , const int& nb                      ) const { return Image<T,C>( cidx(c) , ridx(r) , nb , nb , 1 , 0 , cv() ); }

    Image<T,C> blu( const int& nr , const int& nc ) const { return b(  0  ,  0  , nr , nc ); }
    Image<T,C> bld( const int& nr , const int& nc ) const { return b( -nr ,  0  , nr , nc ); }
    Image<T,C> bru( const int& nr , const int& nc ) const { return b(  0  , -nc , nr , nc ); }
    Image<T,C> brd( const int& nr , const int& nc ) const { return b( -nr , -nc , nr , nc ); }

    Image<T,C> blu( const int& nb ) const { return blu( nb , nb ); }
    Image<T,C> bld( const int& nb ) const { return bld( nb , nb ); }
    Image<T,C> bru( const int& nb ) const { return bru( nb , nb ); }
    Image<T,C> brd( const int& nb ) const { return brd( nb , nb ); }

    Image<T,1> bn( const int& r , const int& c , const int& nr , const int& nc , const int& n ) const{ return Image<T,1>( cidx(c) * d() , ridx(r) , nr , nc , d() , nidx(n) , cv() ); }
    Image<T,1> bn( const int& r , const int& c , const int& nb ,                      const int& n ) const{ return Image<T,1>( cidx(c) * d() , ridx(r) , nb , nb , d() , nidx(n) , cv() ); }

    Image<T,1> blun( const int& nr , const int& nc , const int& n ) const{ return b(  0  ,  0  , nr , nc , n ); }
    Image<T,1> bldn( const int& nr , const int& nc , const int& n ) const{ return b( -nr ,  0  , nr , nc , n ); }
    Image<T,1> brun( const int& nr , const int& nc , const int& n ) const{ return b(  0  , -nc , nr , nc , n ); }
    Image<T,1> brdn( const int& nr , const int& nc , const int& n ) const{ return b( -nr , -nc , nr , nc , n ); }

    Image<T,1> blun( const int& nb , const int& n ) const{ return blun( nb , nb , n ); }
    Image<T,1> bldn( const int& nb , const int& n ) const{ return bldn( nb , nb , n ); }
    Image<T,1> brun( const int& nb , const int& n ) const{ return brun( nb , nb , n ); }
    Image<T,1> brdn( const int& nb , const int& n ) const{ return brdn( nb , nb , n ); }

    Image<T,C> p( const int& r , const int& c ) const { return Image( c , r , 1 , 1 , 1 , 0 , cv() ); }

    Image<T,1> d( const int& n ) const { return Image<T,1>( 0 , 0 , r() , c() , d() , n , cv() ); }
    Image<T,1> operator[]( const int& n ) const { return d( n ); }

    // PRINT

    void printCV() const;
    void printEIG() const;

    void print() const { printEIG(); }
    void info() const;

    TPL_U void printCV( const U& ) const;
    TPL_U void printEIG( const U& ) const;

    TPL_U void print( const U& str ) const { printEIG( str ); }
    TPL_U void info( const U& ) const;

    // OPERATOR_ATTRIB

    Image<T,C>& operator>>( const Image<T,C>& );
    Image<T,C>& operator= ( const Image<T,C>& );
    Image<T,C>& operator<<( const Image<T,C>& );

    Image<T,C>& share(  const Image<T,C>& mat ) { return *this >> mat; }
    Image<T,C>& assign( const Image<T,C>& mat ) { return *this =  mat; }
    Image<T,C>& copy(   const Image<T,C>& mat ) { return *this << mat; }

    Image<T,C>& operator= ( const Matrix<T>& );
    Image<T,C>& operator<<( const Matrix<T>& );

    Image<T,C>& assign( const Matrix<T>& mat ) { return *this =  mat; }
    Image<T,C>& copy(   const Matrix<T>& mat ) { return *this << mat; }

    Image<T,C>& operator>>( const CV& );
    Image<T,C>& operator= ( const CV& );
    Image<T,C>& operator<<( const CV& );

    Image<T,C>& share(  const CV& cv ) { return *this >> cv; }
    Image<T,C>& assign( const CV& cv ) { return *this =  cv; }
    Image<T,C>& copy(   const CV& cv ) { return *this << cv; }

    Image<T,C>& operator=( const T& val ) { return setVal( val ); }
    Image<T,C>& assign( const T& val ) { return *this = val; }

    // OPERATOR_UNARY

    TPL_U Image<T,C>& operator+=( const U& val ) { eig().array() += val; return *this; }
    TPL_U Image<T,C>& operator-=( const U& val ) { eig().array() -= val; return *this; }
    TPL_U Image<T,C>& operator*=( const U& val ) { eig().array() *= val; return *this; }
    TPL_U Image<T,C>& operator/=( const U& val ) { eig().array() /= val; return *this; }

    TPL_U Image<T,C>& add( const U& val ) { return *this += val; }
    TPL_U Image<T,C>& sub( const U& val ) { return *this -= val; }
    TPL_U Image<T,C>& mlt( const U& val ) { return *this *= val; }
    TPL_U Image<T,C>& div( const U& val ) { return *this /= val; }

    // METHOD_CHANGE

    Image<T,1> grayscale() const;

    Image<T,C> LABscale() const;
    Image<T,C> HSVscale() const;
    Image<T,C> YUVscale() const;
    Image<T,C> XYZscale() const;

    Image<T,C> equalise() const;

    Image<T,C> resize( const int& , const int& ) const;
    Image<T,C> resize( const Dims&  dims ) const { return resize( dims.r , dims.c ); }
    Image<T,C> resize( const double& s ) const { return resize( (double)r() * s , (double)c() * s ); }

    Image<T,C>& Resize( const int& , const int& );
    Image<T,C>& Resize( const Dims& dims ) { return Resize( dims.r , dims.c ); }
    Image<T,C>& Resize( const double& s ) { return Resize( (double)r() * s , (double)c() * s ); }

    Image<T,C>& Normalise( const T& = 0 , const T& = 255 );
    Image<T,C> normalise( const T& = 0 , const T& = 255 ) const;

    // METHOD_GRADIENT

    Image<float,1> gradRow() const;
    Image<float,1> gradCol() const;
    Image<float,1> gradDiagU() const;
    Image<float,1> gradDiagD() const;

    // METHOD_CONVERT

    TPL_U Image<U,C> convert() const;

    Image<int,C> toInt() const { return convert<int>(); }
    Image<float,C> toFloat() const { return convert<float>(); }
    Image<double,C> toDouble() const { return convert<double>(); }
    Image<unsigned int,C> toUInt() const { return convert<unsigned int>(); }
    Image<unsigned char,C> toUChar() const { return convert<unsigned char>(); }

    #ifdef VLFEAT_FOUND
    T* VLfeat() const;
    #endif

    // METHOD_REDUCTION

    T min() const { return eig().minCoeff(); }
    T max() const { return eig().maxCoeff(); }
    T ntv() const { return max() - min();    }

    T min( unsigned& r , unsigned& c ) const { return eig().minCoeff( &r , &c ); }
    T max( unsigned& r , unsigned& c ) const { return eig().maxCoeff( &r , &c ); }

    Pt2i minPt() { unsigned r , c ; min( r , c ); return Pt2i( c , r ); }
    Pt2i maxPt() { unsigned r , c ; max( r , c ); return Pt2i( c , r ); }

    // METHOD_SET

    Image<T,C>& setVal( const T& = 0 );
    Image<T,C>& setIncrease( const T& = 0 , const T& = 1 );

    // METHOD_SEGMENT

    Image<unsigned char,1> pixelSLIC( const int& , const int& , const float& ) const;

    Seq<Pt2f> getContour() const;

    // METHOD_MATCH

    Image<float,1> matchTemplate( const Image<T,C>& );

    // METHOD_STORE

    Image<T,C>& load( const String& );
    void save( const String& ) const;

    Image<T,C>& load( const String& str , const int& n ) { return load( strn( str , n ) ); }
    void save( const String& str , const int& n ) const { save( strn( str , n ) ); }

    Image<T,C>& loadASC( const String& );
    void saveASC( const String& ) const;

    Image<T,C>& loadASC( const String& str , const int& n ) { return loadASC( strn( str , n ) ); }
    void saveASC( const String& str , const int& n ) const { saveASC( strn( str , n ) ); }

    Image<T,C>& loadIMG( const String& );
    void saveIMG( const String& ) const;

    Image<T,C>& loadIMG( const String& str , const int& n ) { return loadIMG( strn( str , n ) ); }
    void saveIMG( const String& str , const int& n ) const { saveIMG( strn( str , n ) ); }

    // TRANSFORM

    Image<T,C> warp( const CV& M ) const
    { Image<T,C> tmp( dims() ); tmp.Warp( *this , M ); return tmp; }

    Image<T,C>& Warp( const Image<T,C>& img , const CV& M )
    { cv::warpPerspective( img.cv() , cv() , M , img.size() ); return *this; }

    TPL_DUM Image<T,C> warp( const Vector<D,U,M>& pts1 , const Vector<D,U,M>& pts2  ) const
    { Image<T,C> tmp( dims() ); tmp.Warp( *this , pts1 , pts2 ); return tmp; }

    TPL_DUM Image<T,C>& Warp( const Image<T,C>& img , const Vector<D,U,M>& pts1 , const Vector<D,U,M>& pts2  )
    { cv::warpPerspective( img.cv() , cv() , cv::getPerspectiveTransform( pts1.seq() , pts2.seq() ) , img.size() ); return *this; }

};

template< unsigned C > using Imgi = Image< int , C >;
template< unsigned C > using Imgf = Image< float , C >;
template< unsigned C > using Imgd = Image< double , C >;
template< unsigned C > using Imgu = Image< unsigned char , C >;

using Img1i = Image< int           , 1 >;
using Img1f = Image< float         , 1 >;
using Img1d = Image< double        , 1 >;
using Img1u = Image< unsigned int  , 1 >;
using Img1c = Image< unsigned char , 1 >;

using Img2i = Image< int           , 2 >;
using Img2f = Image< float         , 2 >;
using Img2d = Image< double        , 2 >;
using Img2u = Image< unsigned int  , 2 >;
using Img2c = Image< unsigned char , 2 >;

using Img3i = Image< int           , 3 >;
using Img3f = Image< float         , 3 >;
using Img3d = Image< double        , 3 >;
using Img3u = Image< unsigned int  , 3 >;
using Img3c = Image< unsigned char , 3 >;

using Img4i = Image< int           , 4 >;
using Img4f = Image< float         , 4 >;
using Img4d = Image< double        , 4 >;
using Img4u = Image< unsigned int  , 4 >;
using Img4c = Image< unsigned char , 4 >;

TPL_TC using SeqImage = Seq<Image<T,C>>;

using SeqImg1i = SeqImage< int           , 1 >;
using SeqImg1f = SeqImage< float         , 1 >;
using SeqImg1d = SeqImage< double        , 1 >;
using SeqImg1u = SeqImage< unsigned int  , 1 >;
using SeqImg1c = SeqImage< unsigned char , 1 >;

using SeqImg3i = SeqImage< int           , 3 >;
using SeqImg3f = SeqImage< float         , 3 >;
using SeqImg3d = SeqImage< double        , 3 >;
using SeqImg3u = SeqImage< unsigned int  , 3 >;
using SeqImg3c = SeqImage< unsigned char , 3 >;

}

#include "image_src.h"

#endif
