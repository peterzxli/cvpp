#include "../matrix.h"

#include <cvpp/structs/struct_data_type.h>
#include <cvpp/auxiliar/timer.h>

namespace cvpp
{

#ifdef OPENCV_FOUND

// OpenCV Kmeans
TPL_T inline void
Matrix<T>::kmeans( const int& n , Matrix<T>& ctr , Matrix<int>& lbl ,
                   const int& iter , const int& attempts , const double& tol ) const
{
    DataType<T> type;

    if( type.get() == 1 )
    {
        lbl.reset( r() );
        ctr.reset( n , c() );

        cv::kmeans( cv() , n , lbl.cv() ,
                    cv::TermCriteria( cv::TermCriteria::COUNT + cv::TermCriteria::EPS , iter , tol ) ,
                    attempts , cv::KMEANS_PP_CENTERS , ctr.cv() );
    }
    else
    {
        lbl.reset( r() );

        Matrix<float> matf = convert<float>();
        Matrix<float> ctrf( n , c() );

        cv::kmeans( matf.cv() , n , lbl.cv() ,
                    cv::TermCriteria( cv::TermCriteria::COUNT + cv::TermCriteria::EPS , iter , tol ) ,
                    attempts , cv::KMEANS_PP_CENTERS , ctrf.cv() );

        ctr = ctrf.convert<T>();
    }
}

#endif

// Mini-Batch Kmeans
TPL_T inline void
Matrix<T>::kmeans( const int& n , const int& b ,
                   Matrix<T>& ctr , Matrix<int>& lbl ,
                   const int& iter, const double& tol ) const
{
    if( ctr.empty() )
        ctr = sampleRandRows( n );
    lbl.reset( r() );

    Matrix<int> clusters( b ) , counts( n );
    counts.setVal(0);

    Matrix<T> pctr;
    Seq<Matrix<T>> batches;

    double error = tol + 1;
    for( unsigned i = 0 ; i < iter && error > tol ; i++ )
    {
        batches = splitRandRows( b );

        error = 0;
        forLOOPj( batches.size() )
        {
            clusters = batches[j].closestRowsLBL( ctr );

            pctr = ctr;
            forLOOPk( b )
            {
                int lbl = clusters(k);
                counts(lbl)++;

                double eta = 1.0 / counts(lbl);
                ctr.row(lbl) = ( 1.0 - eta ) * ctr.row(lbl) + eta * batches[j].row(k);
            }
            error += ( pctr.eig() - ctr.eig() ).norm();
        }

        error /= batches.size();
    }

//    lbl = closestRowsLBL( ctr );
}

// Kmeans++
TPL_T inline void
Matrix<T>::kmeanspp( const int& n ,
                     Matrix<T>& ctr , Matrix<int>& lbl ) const
{
    ctr.reset( n , c() );
    lbl.reset( r() ); lbl.setVal(0);

    Matrix<T> C( r() , n );
    Matrix<T> D( dims() );

    ctr.r(0) = r( randi( r() ) );

    Matrix<T> curr = ctr.r(0).t();
    C.c(0) = 2.0 * (*this) * curr - curr.sqsumRows();

    T rndj;
    for( unsigned i = 1 ; i < n ; i++ )
    {
        #pragma omp parallel for
        forLOOPj( r() ) D.row(j) = row(j) - ctr.row( lbl(j) );

        D = D.Square().sumCols();
        D.CumsumRows();

        unsigned j = 0;
        rndj = randd( D(-1) );
        while( rndj >= D(j) ) j++;
        ctr.row(i) = row(j);

        curr = ctr.r(i).t();
        C.c(i) = 2.0 * (*this) * curr - curr.sqsumRows();

        #pragma omp parallel for
        forLOOPj( r() )
            if( C( j , i ) > C( j , lbl(j) ) )
                lbl(j) = i;
    }
}

// Scalable Kmeans
TPL_T inline void
Matrix<T>::kmeanspar( const int& n , const int& l ,
                      Matrix<T>& ctr , Matrix<int>& lbl ) const
{
    double sum;
    unsigned cnt;

    Matd dst( r() );
    Matd nctr( n / 2 , c() );

    ctr = r( randi( r() ) );
    lbl.reset( r() ).setVal( 0 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        dst[i] = ( row(i) - ctr.row(0) ).squaredNorm();
    sum = dst.sum();

    while( true )
    {
        cnt = 0;
        for( unsigned i = 0 ; i < r() ; i++ )
            if( l * dst[i] / sum > randd() )
                nctr.row( cnt++ ) = row( i );

        if( ctr.r() >= n )
            break;

        #pragma omp parallel for
        for( unsigned i = 0 ; i < r() ; i++ )
        {
            double dist;
            for( unsigned j = 0 ; j < cnt ; j++ )
            {
                dist = 0;
                for( unsigned k = 0 ; k < 3 ; k++ )
                    dist += std::pow( at(i,k) - nctr(j,k) , 2 );

                if( dist < dst[i] ) dst[i] = dist , lbl[i] = j + ctr.r();
            }
        }
        sum = dst.sum();

        ctr.AppRows( nctr.ru( cnt ) );
    }
}

}




