#include "../sparse.h"

namespace cvpp
{

// Save
TPL_T void
Sparse<T>::save( const String& str ) const
{
    String suf = str.substr( str.length() - 3 , 3 );

         if( suf == "bin" || suf == "BIN" ) saveBIN( str );
    else                                    saveASC( str );
}

// Load ASCII
TPL_T Sparse<T>&
Sparse<T>::load( const String& str )
{
    String suf = str.substr( str.length() - 3 , 3 );

         if( suf == "bin" || suf == "BIN" ) return loadBIN( str );
    else                                    return loadASC( str );
}

// Save ASCII
TPL_T void
Sparse<T>::saveASC( const String& str ) const
{
    OFile file( str );
    if( file.is_open() )
    {
        file << r() << " " << c() << " " << nz() << "\n\n";

        for ( unsigned k = 0 ; k < o() ; k++ )
            for ( typename SEigen::InnerIterator it( eig() , k ) ; it ; ++it )
                file << it.row() << " " << it.col() << " " << it.value() << "\n";

        file.close();
    }
    else
    {
        std::cout << "COULD NOT SAVE " << str << " FILE!" << std::endl;
    }
}

// Load ASCII
TPL_T Sparse<T>&
Sparse<T>::loadASC( const String& str )
{
    IFile file( str );
    if( file.is_open() )
    {        
        unsigned u,v,n,d,z;
        file >> n >> d >> z;

        reset( n , d , z );
        for( unsigned i = 0 ; i < z ; i++ )
        {
            file >> u >> v;
            file >> at( u , v );
        }

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
Sparse<T>::saveBIN( const String& str ) const
{
    OFile file( str , std::ios::binary | std::ios::out );
    if( file.is_open() )
    {
        unsigned r = this->r() , c = this->c() , nz = this->nz();

        file.write( (char*)&r  , sizeof(unsigned) );
        file.write( (char*)&c  , sizeof(unsigned) );
        file.write( (char*)&nz , sizeof(unsigned) );

        T v;
        for ( unsigned k = 0 ; k < o() ; k++ )
        {   for ( typename SEigen::InnerIterator it( eig() , k ) ; it ; ++it )
            {
                r = it.row() ; c = it.col() ; v = it.value();

                file.write( (char*)&r , sizeof(unsigned) );
                file.write( (char*)&c , sizeof(unsigned) );
                file.write( (char*)&v , sizeof(T)        );
            }
        }

        file.close();
    }
    else
    {
        std::cout << "COULD NOT SAVE " << str << " FILE!" << std::endl;
    }
}

// Load BINARY
TPL_T Sparse<T>&
Sparse<T>::loadBIN( const String& str )
{
    IFile file( str , std::ios::binary | std::ios::in );
    if( file.is_open() )
    {
        unsigned r , c , nz;
        file.read( (char*)&r  , sizeof(unsigned) );
        file.read( (char*)&c  , sizeof(unsigned) );
        file.read( (char*)&nz , sizeof(unsigned) );

        reset(r,c);
        for( unsigned i = 0 ; i < nz ; i++ )
        {
            file.read( (char*)&r       , sizeof(unsigned) );
            file.read( (char*)&c       , sizeof(unsigned) );
            file.read( (char*)&at(r,c) , sizeof(T)        );
        }

        file.close();
    }
    else
    {
        reset();
        std::cout << "COULD NOT LOAD " << str << " FILE!" << std::endl;
    }

    return *this;
}

}
