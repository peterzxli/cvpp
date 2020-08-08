#ifndef KMEANS_BASE_H
#define KMEANS_BASE_H

#include <cvpp/structs/struct_kmeans.h>

namespace cvpp
{

class KMeansBase
{

protected:

    KMdata* data;

public:

    int& n() const { return data->n; }
    int& m() const { return data->m; }
    int& d() const { return data->d; }
    int& c() const { return data->c; }
    int& t() const { return data->t; }

    auto X( const int& i ) const { return data->X.row(i); }
    auto Z( const int& i ) const { return data->Z.row(i); }
    auto P( const int& i ) const { return data->P.row(i); }

    double& M( const int& i ) const { return data->M(i); }
    int& I( const int& i ) const { return data->I(i); }

    Seqi& idx() const { return data->idx; }
    int& idx( const int& i ) const { return data->idx[i]; }

    Matd& X() const { return data->X; }
    Matd& Z() const { return data->Z; }
    Matd& P() const { return data->P; }

    Matd& M() const { return data->M; }
    Mati& I() const { return data->I; }

    Vecd& pot() const { return data->pot; }
    Vecd& err() const { return data->err; }

    double cpot() const { return data->pot[-1]; }
    double ppot() const { return data->pot[-2]; }
    double dpot() const { return 1.0 - cpot() / ppot(); }
    double cerr() const { return data->err[-1]; }

    // Start M
    const void startM()
    {
        #pragma omp parallel for
        forLOOPi( n() ) M(i) = ( X(i) - Z(0) ).squaredNorm();
        pot().push( M().sum() );
    }

    // Update M
    const void updateM()
    {
        #pragma omp parallel for
        forLOOPi( n() )
        {
            double dst = ( X(i) - Z( c() ) ).squaredNorm();
            if( dst < M(i) ) { M(i) = dst ; I(i) = c() ; }
        }
        pot().push( M().sum() );
    }

    // Update M
    const void updateM( const int& st )
    {
        #pragma omp parallel for
        forLOOPi( n() )
        {   forLOOPjj( st , c() )
            {
                double dst = ( X(i) - Z(j) ).squaredNorm();
                if( dst < M(i) ) { M(i) = dst ; I(i) = j ; }
            }
        }
        pot().push( M().sum() );
    }

    // Recalculate M
    const void recalcM()
    {
        #pragma omp parallel for
        forLOOPi( n() )
        {
            M(i) = PINF;
            forLOOPj( m() )
            {
                double dst = ( X(i) - Z(j) ).squaredNorm();
                if( dst < M(i) ) { M(i) = dst ; I(i) = j ; }
            }
        }
        pot().push( M().sum() );
    }

};

}

#endif
