#include "./kdtree.h"

namespace cvpp
{

TPL_T // Constructor
KDtree<T>::KDtree()
{
    tree = new flann::Index< flann::L2<T> >( flann::KDTreeSingleIndexParams() );
//    tree = new flann::Index< flann::L2<T> >( flann::KDTreeIndexParams() );
    seq.reserve(100);
}

TPL_T // Constructor
KDtree<T>::KDtree( const Matrix<T>& data ) : KDtree()
{
    add( data );
}

TPL_T // Destructor
KDtree<T>::~KDtree()
{
    delete tree;
}

// Data index
TPL_T REIG<T>
KDtree<T>::edata( unsigned idx ) const
{
    unsigned i = 0;
    while( idx > seq[i].r() )
        idx -= seq[i].r() , i++ ;
    return seq[i].row(idx);
}

// Data index
TPL_T Matrix<T>
KDtree<T>::data( unsigned idx ) const
{
    unsigned i = 0;
    while( idx > seq[i].r() )
        idx -= seq[i].r() , i++ ;
    return seq[i].r(idx);
}

// Data Index SeqMatrix
TPL_T Matrix<T>
KDtree<T>::data( unsigned idx , const SeqMatrix<T>& seq ) const
{
    unsigned i = 0;
    while( idx > seq[i].r() )
        idx -= seq[i].r() , i++ ;
    return seq[i].r(idx);
}

// Data Vector
TPL_T Matrix<T>
KDtree<T>::data( const Seqi& idx ) const
{
    Matrix<T> res( idx.size() , seq[0].c() );
    for( unsigned i = 0 ; i < res.r() ; i++ )
        res.r(i) = data( idx[i] );
    return res;
}

// Data Vector SeqMatrix
TPL_T Matrix<T>
KDtree<T>::data( const Seqi& idx , const SeqMatrix<T>& seq ) const
{
    Matrix<T> res( idx.size() , seq[0].c() );
    for( unsigned i = 0 ; i < res.r() ; i++ )
        res.r(i) = data( idx[i] , seq );
    return res;
}

// Data Vector Matrix
TPL_T Matrix<T>
KDtree<T>::data( const Seqi& idx , const Matrix<T>& mat ) const
{
    Matrix<T> res( idx.size() , mat.c() );
    for( unsigned i = 0 ; i < res.r() ; i++ )
        res.r(i) = mat.r( idx[i] );
    return res;
}

// Eigen Data index
TPL_T EIG<T>
KDtree<T>::eig_data( unsigned idx ) const
{
    unsigned i = 0;
    while( idx > seq[i].r() )
        idx -= seq[i].r() , i++ ;
    return seq[i].row(idx);
}

// Add Matrix
TPL_T KDtree<T>&
KDtree<T>::add( const Matrix<T>& mat )
{
    seq.resize( seq.size() + 1 );
    seq.back() >> mat;

    flann::Matrix<T> flann( seq.back().eig_data() ,
                            seq.back().r() , seq.back().c() );

    if( seq.size() == 1 )
        tree->buildIndex( flann );
    else tree->addPoints( flann );

    return *this;
}

// Add Vector
TPL_T TPL_DM KDtree<T>&
KDtree<T>::add( const Vector<D,T,M>& pts )
{
    return add( pts.mat() );
}

// KNN Search
TPL_T void
KDtree<T>::knnSearch( const Matrix<T>& mat , const int& n ,
                      SSeqi& idxs , SSeq<T>& dists ) const
{
    flann::Matrix<T> flann( mat.eig_data() , mat.r() , mat.c() );
    tree->knnSearch( flann , idxs , dists , n , flann::SearchParams( 128 ) );
}

// Radius Search
TPL_T void
KDtree<T>::radSearch( const Matrix<T>& mat , const T& r ,
                      SSeqi& idxs , SSeq<T>& dists ) const
{
    flann::Matrix<T> flann( mat.eig_data() , mat.r() , mat.c() );
    tree->radiusSearch( flann , idxs , dists , r , flann::SearchParams( 128 ) );
}

template class KDtree<float>;
template class KDtree<double>;

}
