#include "../matrix.h"

namespace cvpp
{

// Matrix >> Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator>>( const Matrix<T>& mat )
{
    this->eig_ptr = mat.eig_ptr;
    this->raw_ptr = mat.raw_ptr;

    return *this;
}

// Matrix = Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const Matrix<T>& mat )
{
    if( fits( mat ) )
          this->eig() = mat.eig();
    else *this << mat;

    return *this;
}

// Matrix << Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const Matrix<T>& mat )
{
    this->initialise( mat.dims() );
    this->raw() = mat.eig();

    return *this;
}

// Matrix = Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const Sparse<T>& spr )
{
    if( fits( spr ) )
          this->eig() = spr.eig();
    else *this << spr;

    return *this;
}

// Matrix << Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const Sparse<T>& spr )
{
    this->initialise( spr.dims() );
    this->raw() = spr.eig();

    return *this;
}

// Matrix >> Vector
TPL_T TPL_DM inline Matrix<T>&
Matrix<T>::operator>>( const Vector<D,T,M>& vec )
{
    *this >> vec.mat();
}

// Matrix = Vector
TPL_T TPL_DM inline Matrix<T>&
Matrix<T>::operator=( const Vector<D,T,M>& vec )
{
    *this = vec.mat();
}

// Matrix << Vector
TPL_T TPL_DM inline Matrix<T>&
Matrix<T>::operator<<( const Vector<D,T,M>& vec )
{
    *this << vec.mat();
}

// Matrix = Image
TPL_T TPL_C inline Matrix<T>&
Matrix<T>::operator=( const Image<T,C>& img )
{
    if( fits( img ) )
          this->eig() = img.eig();
    else *this << img;

    return *this;
}

// Matrix << Image
TPL_T TPL_C inline Matrix<T>&
Matrix<T>::operator<<( const Image<T,C>& img )
{
    this->initialise( img.r() , img.cd() );
    this->raw() = img.eig();

    return *this;
}

// Matrix = SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const SEigen& seig )
{
    if( fits( seig ) )
          this->eig() = seig;
    else *this << seig;

    return *this;
}

// Matrix << SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const SEigen& seig )
{
    this->initialise( seig.rows() , seig.cols() );
    this->eig() = seig;

    return *this;
}

// MATRIX >> FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator>>( FEigen& feig )
{
    this->initialise( 0 , 0 , feig.rows() , feig.cols() ,
                              feig.outerStride() , feig.data() );
    return *this;
}

// MATRIX = FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator=( const FEigen& feig )
{
    if( fits( feig ) )
          this->eig() = feig;
    else *this << feig;

    return *this;
}

// MATRIX << FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator<<( const FEigen& feig )
{
    this->initialise( feig.rows() , feig.cols() );
    this->eig() = feig;

    return *this;
}

// MATRIX >> BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator>>( BEigen beig )
{
    this->initialise( 0 , 0 , beig.rows() , beig.cols() ,
                              beig.outerStride() , beig.data() );
    return *this;
}

// MATRIX = BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator=( const BEigen beig )
{
    if( fits( beig ) )
          this->eig() = beig;
    else *this << beig;

    return *this;
}

// MATRIX << BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator<<( const BEigen beig )
{
    this->initialise( beig.rows() , beig.cols() );
    this->eig() = beig;

    return *this;
}

// Matrix = STD
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const Seq<T>& seq )
{
    if( seq.size() == s() )
    {
        #pragma omp parallel for
        forLOOPi( seq.size() ) at(i) = seq[i];
    }
    else *this << seq;

    return *this;
}

// Matrix << STD
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const Seq<T>& seq )
{
    initialise( seq.size() );

    #pragma omp parallel for
    forLOOPi( seq.size() ) at(i) = seq[i];

    return *this;
}

// Matrix << rseq
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const Seq<Matrix<T>>& rseq )
{
    int n = 0;
    forLOOPi( rseq.size() ) n += rseq[i].r();
    reset( n , rseq[0].c() );

    n = 0;
    forLOOPi( rseq.size() )
    {
        row( n , rseq[i].r() ) = rseq[i].eig();
        n += rseq[i].r();
    }

    return *this;
}

#ifdef OPENCV_FOUND

// Matrix >> OpenCV
TPL_T inline Matrix<T>&
Matrix<T>::operator>>( const CV& cv )
{
    this->initialise( 0 , 0 , cv.rows ,
                              cv.cols , cv.cols , (T*)cv.data );

    return *this;
}

// Matrix = OpenCV
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const CV& cv )
{
    if( fits( cv ) )
          cv.copyTo( this->cv() );
    else *this << cv;

    return *this;
}

// Matrix << OpenCV
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const CV& cv )
{
    initialise( cv.rows , cv.cols );
    cv.copyTo( this->cv() );

    return *this;
}

#endif

#ifdef SHOGUN_FOUND

// Matrix >> Shogun Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator>>( const SGMatrix<T>& sgmat )
{
    this->initialise( 0 , 0 , sgmat.num_rows ,
                              sgmat.num_cols , sgmat.num_cols , sgmat.matrix );
    return *this;
}

// Matrix = Shogun Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const SGMatrix<T>& sgmat )
{
    if( fits( sgmat ) )
    {
        #pragma omp parallel for
        forLOOPi( s() ) eig_data()[i] = sgmat.matrix[i];
    }
    else *this << sgmat;

    return *this;
}

// Matrix << Shogun Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const SGMatrix<T>& sgmat )
{
    this->initialise( sgmat.num_rows , sgmat.num_cols );

    #pragma omp parallel for
    forLOOPi( s() ) eig_data()[i] = sgmat.matrix[i];

    return *this;
}

// Matrix >> Shogun Vector
TPL_T inline Matrix<T>&
Matrix<T>::operator>>( const SGVector<T>& sgvec )
{
    this->initialise( 0 , 0 , sgvec.size() , 1 , 1 , sgvec.vector );
    return *this;
}

// Matrix = Shogun Vector
TPL_T inline Matrix<T>&
Matrix<T>::operator=( const SGVector<T>& sgvec )
{
    if( fits( sgvec ) )
    {
        #pragma omp parallel for
        forLOOPi( s() ) eig_data()[i] = sgvec.vector[i];
    }
    else *this << sgvec;

    return *this;
}

// Matrix << Shogun Vector
TPL_T inline Matrix<T>&
Matrix<T>::operator<<( const SGVector<T>& sgvec )
{
    this->initialise( sgvec.size() , 1 );

    #pragma omp parallel for
    forLOOPi( s() ) eig_data()[i] = sgvec.vector[i];

    return *this;
}

#endif

}
