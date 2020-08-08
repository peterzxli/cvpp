#ifndef KDTREE_H
#define KDTREE_H

#include <flann/flann.hpp>

#include <cvpp/auxiliar/definitions.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/vector.h>

namespace cvpp
{

TPL_T
class KDtree
{

protected:

    SeqMatrix<T> seq;
    flann::Index<flann::L2<T>> *tree;

public:

    SeqMatrix<T>& data() { return seq; }
    const SeqMatrix<T>& data() const { return seq; }

    KDtree();
    KDtree( const Matrix<T>& );
    ~KDtree();

    REIG<T> edata( unsigned ) const;

    Matrix<T> data( unsigned ) const;
    Matrix<T> data( unsigned , const SeqMatrix<T>& ) const;

    Matrix<T> data( const Seqi& ) const;
    Matrix<T> data( const Seqi& , const Matrix<T>& ) const;
    Matrix<T> data( const Seqi& , const SeqMatrix<T>& ) const;

    EIG<T> eig_data( unsigned ) const;

           KDtree& add( const Matrix<T>& );
    TPL_DM KDtree& add( const Vector<D,T,M>& );

    void knnSearch( const Matrix<T>& , const int& , SSeqi& , SSeq<T>& ) const;
    void radSearch( const Matrix<T>& , const T&        , SSeqi& , SSeq<T>& ) const;

};

using KDtreei = KDtree<int>;
using KDtreef = KDtree<float>;
using KDtreed = KDtree<double>;

}

#endif
