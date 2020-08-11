#include "../matrix.h"

namespace cvpp
{

// Shuffle Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::shuffleRows() const
{
    Seqi seq( r() );
    for( unsigned i = 0 ; i < seq.size() ; i++ ) seq[i] = i;
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle( seq.begin() , seq.end(), std::default_random_engine(seed));

    Matrix<int> idx( 0 , 0 , seq.size() , 1 , 1 , seq.data() );
    return sampleRows( idx );
}

// Shuffle Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::ShuffleRows()
{
    Seqi seq( r() );
    for( unsigned i = 0 ; i < seq.size() ; i++ ) seq[i] = i;
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle( seq.begin() , seq.end(), std::default_random_engine(seed));

    Matrix<int> idx( 0 , 0 , seq.size() , 1 , 1 , seq.data() );
    return SampleRows( idx );
}

// Shuffle Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::shuffleCols() const
{
    Seqi seq( c() );
    for( unsigned i = 0 ; i < seq.size() ; i++ ) seq[i] = i;
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle( seq.begin() , seq.end(), std::default_random_engine(seed));

    Matrix<int> idx( 0 , 0 , seq.size() , 1 , 1 , seq.data() );
    return sampleCols( idx );
}

// Shuffle Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::ShuffleCols()
{
    Seqi seq( c() );
    for( unsigned i = 0 ; i < seq.size() ; i++ ) seq[i] = i;
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle( seq.begin() , seq.end(), std::default_random_engine(seed));

    Matrix<int> idx( 0 , 0 , seq.size() , 1 , 1 , seq.data() );
    return SampleCols( idx );
}

}
