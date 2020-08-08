#include "linear_pca.h"

namespace cvpp
{

// Constructor
LinearPCA::LinearPCA( const Matd& X , const double& n )
{
    this->M = X.meanRows();
    this->X = X - this->M;

    Matd tmp = this->X.t() * this->X;
    tmp.eigen( values , vectors );

    Mati idx = values.sortRowsIDX().flipRows();
    values.SampleRows( idx ); vectors.SampleCols( idx );

    if( n >= 1 )
    {
        values.KeepU( (unsigned)n );
        vectors.KeepL( (unsigned)n );
    }
    else
    {
        values /= values.sum();
        values.CumsumRows();

        unsigned i = 0;
        while( values(i) < n ) i++;

        values.KeepU( i + 1 );
        vectors.KeepL( i + 1 );
    }
}

// Project
Matd
LinearPCA::project( const Matd& XX ) const
{
    return ( XX - M ) * vectors;
}

}
