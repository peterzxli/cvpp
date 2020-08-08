#include "../matrix.h"

namespace cvpp
{

// Transpose (NEW)
TPL_T inline Matrix<T>
Matrix<T>::t() const
{
    Matrix<T> tmp( c() , r() );
    tmp.eig().noalias() = eig().transpose();
    return tmp;
}

// Denominator (NEW)
TPL_T inline Matrix<T>
Matrix<T>::denom() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().cwiseInverse();
    return tmp;
}

// Denominator (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Denom()
{
    eig() = eig().cwiseInverse();
    return *this;
}

// Inverse (NEW)
TPL_T inline Matrix<T>
Matrix<T>::inv() const
{
    Matrix<T> tmp( dims() );
    tmp.eig().noalias() = eig().inverse();
    return tmp;
}

// Inverse (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Inv()
{
    eig() = eig().inverse();
    return *this;
}

// Eigenvalues (NEW)
TPL_T Matrix<T>
Matrix<T>::eigenvalues() const
{
    Matrix<T> tmp( r() );
    Eigen::EigenSolver< EIG<T> > eigensolver( eig() );

    tmp.eig() = eigensolver.eigenvalues().real();
    return tmp;
}

// Eigenvectors (NEW)
TPL_T Matrix<T>
Matrix<T>::eigenvectors() const
{
    Matrix<T> tmp( r() , c() );
    Eigen::EigenSolver< EIG<T> > eigensolver( eig() );

    tmp.eig() = eigensolver.eigenvectors().real();
    return tmp;
}

// Eigen (NEW)
TPL_T Matrix<T>
Matrix<T>::eigen( Matrix<T>& values , Matrix<T>& vectors ) const
{
    Eigen::EigenSolver< EIG<T> > eigensolver( eig() );

    values.reset( r() );
    values.eig() = eigensolver.eigenvalues().real();

    vectors.reset( r() , c() );
    vectors.eig() = eigensolver.eigenvectors().real();

    return *this;
}

// Convolution (NEW)
TPL_T Matrix<T>
Matrix<T>::conv( const Matrix<T>& K , const String& shape ) const
{
    int M = r() , N = K.r();
    Matd C( M + N - 1 );

    Matd P( C.r() ); P.setVal(0);
    P.r( N - 1 , M ) = *this;

    #pragma omp parallel for
    forLOOPi( C.r() )
    {
        C(i) = 0; forLOOPj( N )
            C(i) += P( i + j ) * K( N - 1 - j );
    }

    if( shape == "SAME" )
        C = C.r( std::ceil( N / 2 ) , M );

    return C;
}

// Convolution (SELF)
TPL_T Matrix<T>&
Matrix<T>::Conv( const Matrix<T>& K , const String& shape )
{
    *this = conv( K , shape );
    return *this;
}

// Sigmoid (NEW)
TPL_T Matrix<T>
Matrix<T>::sigmoid( const T& l , const T& x , const T& k ) const
{
    return l / ( 1.0 + ( - k * ( *this - x ) ).exp() );
}

// Sigmoid (SELF)
TPL_T Matrix<T>&
Matrix<T>::Sigmoid( const T& l , const T& x , const T& k )
{
    *this = sigmoid( l , x , k );
    return *this;
}

// Mat Sqrt (NEW)
TPL_T Matrix<T>
Matrix<T>::matsqrt() const
{
    Matrix<T> E , V ; eigen( E , V );
    return V * E.sqrt().diag() * V.inv();
}

// Mat Sqrt (SELF)
TPL_T Matrix<T>&
Matrix<T>::matSqrt()
{
    *this = matsqrt();
    return *this;
}

// Pow (NEW)
TPL_T Matrix<T>
Matrix<T>::pow( const T& val ) const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().pow( val ).matrix();
    return tmp;
}

// Pow (SELF)
TPL_T Matrix<T>&
Matrix<T>::Pow( const T& val )
{
    eig() = eig().array().pow( val ).matrix();
    return *this;
}

// Root (NEW)
TPL_T Matrix<T>
Matrix<T>::root( const T& val ) const
{
    return pow( 1.0 / val );
}

// Root (SELF)
TPL_T Matrix<T>&
Matrix<T>::Root( const T& val )
{
    return Pow( 1.0 / val );
}

// Square (NEW)
TPL_T Matrix<T>
Matrix<T>::square() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().square().matrix();
    return tmp;
}

// Square (SELF)
TPL_T Matrix<T>&
Matrix<T>::Square()
{
    eig() = eig().array().square().matrix();
    return *this;
}

// Cube (NEW)
TPL_T Matrix<T>
Matrix<T>::cube() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().cube().matrix();
    return tmp;
}

// Cube (SELF)
TPL_T Matrix<T>&
Matrix<T>::Cube()
{
    eig() = eig().array().cube().matrix();
    return *this;
}

// Sqrt (NEW)
TPL_T Matrix<T>
Matrix<T>::sqrt() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().sqrt().matrix();
    return tmp;
}

// Sqrt (SELF)
TPL_T Matrix<T>&
Matrix<T>::Sqrt()
{
    eig() = eig().array().sqrt().matrix();
    return *this;
}

// Cbrt (NEW)
TPL_T Matrix<T>
Matrix<T>::cbrt() const
{
    return root( 3.0 );
}

// Cbrt (SELF)
TPL_T Matrix<T>&
Matrix<T>::Cbrt()
{
    return Root( 3.0 );
}

// Exp (NEW)
TPL_T Matrix<T>
Matrix<T>::exp() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().exp().matrix();
    return tmp;
}

// Exp (SELF)
TPL_T Matrix<T>&
Matrix<T>::Exp()
{
    eig() = eig().array().exp().matrix();
    return *this;
}

// Log (NEW)
TPL_T Matrix<T>
Matrix<T>::log() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().log().matrix();
    return tmp;
}

// Log (SELF)
TPL_T Matrix<T>&
Matrix<T>::Log()
{
    eig() = eig().array().log().matrix();
    return *this;
}

// Sin (NEW)
TPL_T Matrix<T>
Matrix<T>::sin() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().sin().matrix();
    return tmp;
}

// Sin (SELF)
TPL_T Matrix<T>&
Matrix<T>::Sin()
{
    eig() = eig().array().sin().matrix();
    return *this;
}

// Cos (NEW)
TPL_T Matrix<T>
Matrix<T>::cos() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().array().cos().matrix();
    return tmp;
}

// Cos (SELF)
TPL_T Matrix<T>&
Matrix<T>::Cos()
{
    eig() = eig().array().cos().matrix();
    return *this;
}

// ArcSin (NEW)
TPL_T Matrix<T>
Matrix<T>::asin() const
{
    Matrix<T> tmp( dims() );
    #pragma omp parallel for
    forLOOPmatp tmp(r,c) = std::asin( at(r,c) );
    return tmp;
}

// ArcSin (SELF)
TPL_T Matrix<T>&
Matrix<T>::Asin()
{
    #pragma omp parallel for
    forLOOPmatp at(r,c) = std::asin( at(r,c) );
    return *this;
}

// ArcCos (NEW)
TPL_T Matrix<T>
Matrix<T>::acos() const
{
    Matrix<T> tmp( dims() );
    #pragma omp parallel for
    forLOOPmatp tmp(r,c) = std::acos( at(r,c) );
    return tmp;
}

// ArcCos (SELF)
TPL_T Matrix<T>&
Matrix<T>::Acos()
{
    #pragma omp parallel for
    forLOOPmatp at(r,c) = std::acos( at(r,c) );
    return *this;
}

// Abs (NEW)
TPL_T Matrix<T>
Matrix<T>::abs() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().cwiseAbs();
    return tmp;
}

// Abs (SELF)
TPL_T Matrix<T>&
Matrix<T>::Abs()
{
    eig() = eig().cwiseAbs();
    return *this;
}

}
