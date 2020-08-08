#include "../matrix.h"

namespace cvpp
{

// Vector & Value
TPL_DTME Vector<Array<T,M+1>,T,M+1>
operator&( const Vector<D,T,M>& vec , const E& val )
{
    Vector<Array<T,M+1>,T,M+1> tmp( vec.n() );
    tmp.cl(M) = vec.mat(); tmp.cr(1) = val;
    return tmp;
}

// Value & Vector
TPL_DTME Vector<Array<T,M+1>,T,M+1>
operator&( const E& val , const Vector<D,T,M>& vec )
{
    Vector<Array<T,M+1>,T,M+1> tmp( vec.n() );
    tmp.cl(1) = val; tmp.cr(M) = vec.mat();
    return tmp;
}

// Vector & Vector
TPL_DTMEN Vector<Array<T,M+N>,T,M+N>
operator&( const Vector<D,T,M>& vec1 , const Vector<E,T,N>& vec2 )
{
    Vector<Array<T,M+N>,T,M+N> tmp( vec1.n() );
    tmp.cl(M) = vec1.mat(); tmp.cr(N) = vec2.mat();
    return tmp;
}

// Vector & Matrix
TPL_DTM Matrix<T>
operator&( const Vector<D,T,M>& vec , const Matrix<T>& mat )
{
    return vec.mat() & mat;
}

// Matrix & Vector
TPL_DTM Matrix<T>
operator&( const Matrix<T>& mat , const Vector<D,T,M>& vec )
{
    return mat & vec.mat();
}

// Vector | Element
TPL_DTME Vector<D,T,M>
operator|( const Vector<D,T,M>& vec , const E& elm )
{
    Vector<D,T,M> tmp( vec.n() + 1 );
    tmp.nu( vec.n() ) = vec.mat(); tmp[-1] = elm;
    return tmp;
}

// Element | Vector
TPL_DTME Vector<D,T,M>
operator|( const E& elm , const Vector<D,T,M>& vec )
{
    Vector<D,T,M> tmp( vec.n() + 1 );
    tmp[0] = elm; tmp.nu( vec.n() ) = vec.mat();
    return tmp;
}

// Vector | Vector
TPL_DTME Vector<D,T,M>
operator|( const Vector<D,T,M>& vec1 , const Vector<E,T,M>& vec2 )
{
    Vector<D,T,M> tmp( vec1.n() + vec2.n() );
    tmp.nu( vec1.n() ) = vec1.mat(); tmp.nd( vec2.n() ) = vec2.mat();
    return tmp;
}

// Vector | Matrix
TPL_DTM Vector<D,T,M>
operator|( const Vector<D,T,M>& vec , const Matrix<T>& mat )
{
    Vector<D,T,M> tmp( vec.n() + mat.r() );
    tmp.nu( vec.n() ) = vec.mat(); tmp.nd( mat.r() ) = mat;
    return tmp;
}

// Matrix | Vector
TPL_DTM Vector<D,T,M>
operator|( const Matrix<T>& mat , const Vector<D,T,M>& vec )
{
    Vector<D,T,M> tmp( vec.n() + mat.r() );
    tmp.nu( mat.r() ) = mat; tmp.nd( vec.n() ) = vec.mat();
    return tmp;
}

#ifdef OPENCV_FOUND

// Points2 & Value
TPL_DT Vector<Pt3<T>,T,3>
operator&( const Vector<Pt2<T>,T,2>& vec , const D& val )
{
    Vector<Pt3<T>,T,3> tmp( vec.n() );
    tmp.cl(2) = vec.mat(); tmp.cr(1) = val;
    return tmp;
}

// Value & Points2
TPL_DT Vector<Pt3<T>,T,3>
operator&( const D& val , const Vector<Pt2<T>,T,2>& vec )
{
    Vector<Pt3<T>,T,3> tmp( vec.n() );
    tmp.cl(1) = val; tmp.cr(2) = vec.mat();
    return tmp;
}

// Points2 & Vector
TPL_DT Vector<Pt3<T>,T,3>
operator&( const Vector<Pt2<T>,T,2>& vec1 , const Vector<D,T,1>& vec2 )
{
    Vector<Pt3<T>,T,3> tmp( vec1.n() );
    tmp.cl(2) = vec1.mat(); tmp.cr(1) = vec2.mat();
    return tmp;
}

// Vector & Points2
TPL_DT Vector<Pt3<T>,T,3>
operator&( const Vector<D,T,1>& vec1 , const Vector<Pt2<T>,T,2>& vec2 )
{
    Vector<Pt3<T>,T,3> tmp( vec1.n() );
    tmp.cl(1) = vec1.mat(); tmp.cr(2) = vec2.mat();
    return tmp;
}

#endif

}
