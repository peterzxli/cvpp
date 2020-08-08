#include "../matrix.h"

namespace cvpp
{

// Save
TPL_T void
Matrix<T>::save( const String& str ) const
{
    if( str.length() < 5 ) return saveASC( str );
    String suf = str.substr( str.length() - 3 , 3 );

    if( suf == "csv" || suf == "CSV" ) return saveCSV( str );
    if( suf == "bin" || suf == "BIN" ) return saveBIN( str );
    if( suf == "npy" || suf == "NPY" ) return saveNPY( str );

    return saveASC( str );
}

// Load
TPL_T Matrix<T>&
Matrix<T>::load( const String& str )
{
    if( str.length() < 5 ) return loadASC( str );
    String suf = str.substr( str.length() - 3 , 3 );

    if( suf == "csv" || suf == "CSV" ) return loadCSV( str );
    if( suf == "bin" || suf == "BIN" ) return loadBIN( str );
    if( suf == "npy" || suf == "NPY" ) return loadNPY( str );

    return loadASC( str );
}

// Save ASCII
TPL_T void
Matrix<T>::saveASC( const String& str ) const
{
    OFile file( str );
    if( file.is_open() )
    {
        file << r() << " " << c() << "\n\n";
        for( unsigned i = 0 ; i < r() ; i++ )
        {
            for( unsigned j = 0 ; j < c() ; j++ )
                file << std::fixed << std::setprecision(10)
                     << at(i,j) << " ";
            file << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "COULD NOT SAVE " << str << " FILE!" << std::endl;
    }
}

// Load ASCII
TPL_T Matrix<T>&
Matrix<T>::loadASC( const String& str )
{
    IFile file( str );
    if( file.is_open() )
    {
        unsigned n,d;
        file >> n >> d;

        reset( n , d );
        for( unsigned i = 0 ; i < n ; i++ )
            for( unsigned j = 0 ; j < d ; j++ )
                file >> at(i,j);

        file.close();
    }
    else
    {
        reset();
        std::cout << "COULD NOT LOAD " << str << " FILE!" << std::endl;
    }

    return *this;
}

// Save BINARY
TPL_T void
Matrix<T>::saveBIN( const String& str ) const
{
    unsigned r,c;

    OFile file( str , std::ios::binary | std::ios::out );
    if( file.is_open() )
    {
        r = this->r() ; c = this->c();
        file.write( (char*)&r , sizeof(unsigned) );
        file.write( (char*)&c , sizeof(unsigned) );

        for( unsigned j = 0 ; j < c ; j++ )
            for( unsigned i = 0 ; i < r ; i++ )
                file.write( (char*)&at(i,j) , sizeof(double) );
        file.close();
    }
    else
    {
        std::cout << "COULD NOT SAVE " << str << " FILE!" << std::endl;
    }
}

// Load BINARY
TPL_T Matrix<T>&
Matrix<T>::loadBIN( const String& str )
{
    IFile file( str , std::ios::binary | std::ios::in );
    if( file.is_open() )
    {
        unsigned r,c;
        file.read( (char*)&r , sizeof(unsigned) );
        file.read( (char*)&c , sizeof(unsigned) );

        reset(r,c);
        for( unsigned j = 0 ; j < c ; j++ )
            for( unsigned i = 0 ; i < r ; i++ )
                file.read( (char*)&at(i,j) , sizeof(double) );
        file.close();
    }
    else
    {
        reset();
        std::cout << "COULD NOT LOAD " << str << " FILE!" << std::endl;
    }

    return *this;
}

// Save NUMPY
TPL_T void
Matrix<T>::saveNPY( const String& str ) const
{
    const unsigned shape[] = { (unsigned int)r() , (unsigned int)c() };
    cnpy::npy_save( str , eig_data() , shape , 2 , "w" );
}

// Load NUMPY
TPL_T Matrix<T>&
Matrix<T>::loadNPY( const String& str )
{
    cnpy::NpyArray arr = cnpy::npy_load( str );
    double* loaded_data = reinterpret_cast<double*>( arr.data );

    reset( arr.shape[0] , arr.shape[1] );

    int cnt = 0;
    forLOOPij( r() , c() )
        at(i,j) = loaded_data[ cnt++ ];

    return *this;
}

// Save CSV
TPL_T void
Matrix<T>::saveCSV( const String& str , const char& token ) const
{
    OFile file( str );
    if( file.is_open() )
    {
        for( unsigned i = 0 ; i < r() ; i++ )
        {
            for( unsigned j = 0 ; j < c() ; j++ )
                file << std::fixed << std::setprecision(10)
                     << at(i,j) << token;
            file << "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "COULD NOT SAVE " << str << " FILE!" << std::endl;
    }
}

// Load CSV
TPL_T Matrix<T>&
Matrix<T>::loadCSV( const String& str , const char& token )
{
    IFile file( str );
    if( file.is_open() )
    {
        String line , value ; std::getline( file , line );
        unsigned c = std::count( line.begin() , line.end() , token ) + 1;

        file.close();
        file.open( str );

        reset( 10 , c ); unsigned i = 0 , j = 0;
        while( std::getline( file , line , '\n' ) )
        {
            SStream stream; stream << line;
            while( std::getline( stream , value , token ) )
            {
                at(i,j++) = std::stod( value );
                if( j == c ) j = 0 , i++;
                if( i == r() ) AppD( r() );
            }
        }
        KeepU( i );

        file.close();
    }
    else
    {
        reset();
        std::cout << "COULD NOT LOAD " << str << " FILE!" << std::endl;
    }

    return *this;
}

// Save STRING
TPL_T String
Matrix<T>::saveSTR() const
{
    SStream ss;
    ss << r() << " " << c() << "\n\n";

    forLOOPi( r() )
    {
        forLOOPj( c() )
            ss << at(i,j) << " ";
        if( i < r() - 1 ) ss << "\n";
    }

    return ss.str();
}

// Load STRING
TPL_T Matrix<T>&
Matrix<T>::loadSTR( const String& str )
{
    String buf;
    SStream ss( str );

    unsigned r , c;
    ss >> r ; ss >> c ;
    reset( r , c );

    r = c = 0;
    while ( ss >> buf )
    {
        at(r,c) = stod( buf );
        if( ++c == this->c() )
            r++ , c = 0;
    }

    return *this;
}

}
