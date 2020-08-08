#include "../matrix.h"

namespace cvpp
{

// Median
TPL_T T
Matrix<T>::median() const
{
    Matrix<T> tmp = sort();

    if( r() % 2 == 1 )
         return ( tmp.at( r() / 2 ) );
    else return ( tmp.at( r() / 2 ) + tmp.at( r() / 2 + 1 ) ) / 2.0 ;
}

// Sum Rows
TPL_T Matrix<T>
Matrix<T>::sumRows() const
{
    Matrix<T> tmp( 1 , c() );
    tmp.eig().noalias() = eig().colwise().sum();
    return tmp;
}

// Sum Cols
TPL_T Matrix<T>
Matrix<T>::sumCols() const
{
    Matrix<T> tmp( r() , 1 );
    tmp.eig().noalias() = eig().rowwise().sum();
    return tmp;
}

// Prod Rows
TPL_T Matrix<T>
Matrix<T>::prodRows() const
{
    Matrix<T> tmp( 1 , c() );
    tmp.eig().noalias() = eig().colwise().prod();
    return tmp;
}

// Prod Cols
TPL_T Matrix<T>
Matrix<T>::prodCols() const
{
    Matrix<T> tmp( r() , 1 );
    tmp.eig().noalias() = eig().rowwise().prod();
    return tmp;
}

// Median Rows
TPL_T Matrix<T>
Matrix<T>::medianRows() const
{
    Matrix<T> tmp( 1 , c() );
    forLOOPi( c() )
        tmp(i) = c(i).median();
    return tmp;
}

// Cumsum Rows (NEW)
TPL_T Matrix<T>
Matrix<T>::cumsumRows() const
{
    Matrix<T> tmp( dims() );
    tmp.r(0) = r(0);

    for( unsigned i = 1 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = tmp(i-1,j) + at(i,j);

    return tmp;
}


// Cumsum Cols (NEW)
TPL_T Matrix<T>
Matrix<T>::cumsumCols() const
{
    Matrix<T> tmp( dims() );
    tmp.c(0) = c(0);

    for( unsigned i = 1 ; i < c() ; i++ )
        for( unsigned j = 0 ; j < r() ; j++ )
            tmp(j,i) = tmp(j,i-1) + at(j,i);

    return tmp;
}

// Cumsum Rows (SELF)
TPL_T Matrix<T>&
Matrix<T>::CumsumRows()
{
    for( unsigned i = 1 ; i < r() ; i++ )
        row(i) += row(i-1);
    return *this;
}


// Cumsum Cols (SELF)
TPL_T Matrix<T>&
Matrix<T>::CumsumCols()
{
    for( unsigned i = 1 ; i < c() ; i++ )
        col(i) += col(i-1);
    return *this;
}

// Min Rows
TPL_T Matrix<T>
Matrix<T>::minRows() const
{
    Matrix<T> tmp( 1 , c() );
    tmp.eig().noalias() = eig().colwise().minCoeff();
    return tmp;
}

// Min Cols
TPL_T Matrix<T>
Matrix<T>::minCols() const
{
    Matrix<T> tmp( r() , 1 );
    tmp.eig().noalias() = eig().rowwise().minCoeff();
    return tmp;
}

// Min Rows IDX
TPL_T Matrix<int>
Matrix<T>::minRowsIDX( const Matrix<T>& min ) const
{
    Matrix<int> idx( 1 , c() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
        for( unsigned j = 0 ; j < r() ; j++ )
            if( at(j,i) == min(i) ) idx[i] = j;
    return idx;
}

// Min Cols IDX
TPL_T Matrix<int>
Matrix<T>::minColsIDX( const Matrix<T>& min ) const
{
    Matrix<int> idx( r() , 1 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) == min(i) ) idx[i] = j;
    return idx;
}

// Max Rows
TPL_T Matrix<T>
Matrix<T>::maxRows() const
{
    Matrix<T> tmp( 1 , c() );
    tmp.eig().noalias() = eig().colwise().maxCoeff();
    return tmp;
}

// Max Cols
TPL_T Matrix<T>
Matrix<T>::maxCols() const
{
    Matrix<T> tmp( r() , 1 );
    tmp.eig().noalias() = eig().rowwise().maxCoeff();
    return tmp;
}

// Max Rows IDX
TPL_T Matrix<int>
Matrix<T>::maxRowsIDX( const Matrix<T>& max ) const
{
    Matrix<int> idx( 1 , c() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
        for( unsigned j = 0 ; j < r() ; j++ )
            if( at(j,i) == max(i) ) idx[i] = j;
    return idx;
}

// Max Cols IDX
TPL_T Matrix<int>
Matrix<T>::maxColsIDX( const Matrix<T>& max ) const
{
    Matrix<int> idx( r() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) == max(i) ) idx[i] = j;
    return idx;
}

// Limits Rows
TPL_T Matrix<T>
Matrix<T>::limRows() const
{
    Matrix<T> tmp( 2 , c() );
    tmp.r(0) = minRows(); tmp.r(1) = maxRows();
    return tmp;
}

// Limits Cols
TPL_T Matrix<T>
Matrix<T>::limCols() const
{
    Matrix<T> tmp( r() , 2 );
    tmp.c(0) = minCols(); tmp.c(1) = maxCols();
    return tmp;
}

// Limits Rows IDX
TPL_T Matrix<int>
Matrix<T>::limRowsIDX() const
{
    Matrix<int> tmp( 2 , c() );
    tmp.r(0) = minRowsIDX(); tmp.r(1) = maxRowsIDX();
    return tmp;
}

// Limits Cols IDX
TPL_T Matrix<int>
Matrix<T>::limColsIDX() const
{
    Matrix<int> tmp( r() , 2 );
    tmp.c(0) = minColsIDX(); tmp.c(1) = maxColsIDX();
    return tmp;
}

// Grid Dimension
TPL_T Matrix<int>
Matrix<T>::gridSize() const
{
    Matrix<int> dims( c() );
    for( unsigned i , j = 0 ; j < c() ; j++ )
    {
        i = 1;
        while( fabs( at(i,j) - at(i-1,j) ) < 1e-9 ) i++;
        dims(j) = std::round( ( at(-1,j) - at(0,j) ) / ( at(i,j) - at(i-1,j) ) ) + 1;
    }
    return dims;
}

// Grid Resolution
TPL_T Matrix<T>
Matrix<T>::gridResolution() const
{
    Matrix<int> size = gridSize();
    Matrix<T> limits = limRows();

    Matrix<T> resolution( c() );
    for( unsigned i = 0 ; i < c() ; i++ )
        resolution(i) = ( limits(1,i) - limits(0,i) ) / ( (T)size(i) - 1 );
    return resolution;
}

// Cov Rows
TPL_T Matrix<T>
Matrix<T>::covRows( const Matrix<T>& mean ) const
{
    Matrix<T> tmp( c() , c() );
    tmp.setVal(0);

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
        for( unsigned j = i ; j < c() ; j++ )
            for( unsigned k = 0 ; k < r() ; k++ )
                tmp(i,j) += ( mean(i) - at(k,i) ) * ( mean(j) - at(k,j) );

    tmp /= r() - 1;
    forLOOPij( c() , i )
        tmp(i,j) = tmp(j,i);

    return tmp;
}

// Cov Cols
TPL_T Matrix<T>
Matrix<T>::covCols( const Matrix<T>& mean ) const
{
    Matrix<T> tmp( r() , r() );
    tmp.setVal(0);

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < r() ; j++ )
            for( unsigned k = 0 ; k < c() ; k++ )
                tmp(i,j) += ( mean(i) - at(i,k) ) * ( mean(j) - at(j,k) );

    tmp /= c() - 1;
    return tmp;
}

// Var Rows
TPL_T Matrix<T>
Matrix<T>::varRows( const Matrix<T>& mean ) const
{
    Matrix<T> tmp( 1 , c() );
    tmp.setVal(0);

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
        for( unsigned k = 0 ; k < r() ; k++ )
            tmp(i) += std::pow( mean(i) - at(k,i) , 2.0 );

    tmp /= r() - 1;
    return tmp;
}

// Var Cols
TPL_T Matrix<T>
Matrix<T>::varCols( const Matrix<T>& mean ) const
{
    Matrix<T> tmp( r() , 1 );
    tmp.setVal(0);

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned k = 0 ; k < c() ; k++ )
            tmp(i) += std::pow( mean(i) - at(i,k) , 2.0 ) ;

    tmp /= c() - 1;
    return tmp;
}

// Mean + Cov Rows
TPL_T Matrix<T>&
Matrix<T>::mcovRows( const Matrix<int>& idx ,
                     Seq<Matrix<T>>& clouds , Seq<Matrix<T>>& means , Seq<Matrix<T>>& covs )
{
    unsigned min = idx.min() , max = idx.max() + 1 , n = max - min;
    clouds.resize(n); means.resize(n); covs.resize(n);

    #pragma omp parallel for
    for( unsigned i = min ; i < max ; i++ )
    {
        clouds[i] = sampleRows( idx , i );
        clouds[i].mcovRows( means[i] , covs[i] );
    }
    return *this;
}

// Mean + Cov Cols
TPL_T Matrix<T>&
Matrix<T>::mcovCols( const Matrix<int>& idx ,
                     Seq<Matrix<T>>& clouds , Seq<Matrix<T>>& means , Seq<Matrix<T>>& covs )
{
    unsigned min = idx.min() , max = idx.max() + 1 , n = max - min;
    clouds.resize(n); means.resize(n); covs.resize(n);

    #pragma omp parallel for
    for( unsigned i = min ; i < max ; i++ )
    {
        clouds[i] = sampleCols( idx , i );
        clouds[i].mcovCols( means[i] , covs[i] );
    }
    return *this;
}

// Bin
TPL_T void
Matrix<T>::bin( const int& m , const T& min , const T& max ,
                Matrix<T>& binx , Matrix<T>& biny ) const
{
    Matrix<T> v( m + 1 );
    v.setInterval( min , max );

    binx.reset( m );
    forLOOPi( m )
        binx[i] = ( v[i] + v[i+1] ) / 2.0;
    biny.reset( m ).setVal(0);

    forLOOPi( r() )
    {   if( at(i) >= v[0] && at(i) <= v[-1] )
        {   forLOOPj( m )
            {   if( v[j+1] > at(i) )
                {
                    biny[j]++;
                    break;
                }
            }
        }
    }
}








}
