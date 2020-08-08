#include "../image.h"

namespace cvpp
{

// Save Image
TPL_TC void
Image<T,C>::save( const String& str ) const
{
    String suf = str.substr( str.length() - 3 , 3 );

    if( suf == "jpg" || suf == "JPG" ) return saveIMG( str );
    if( suf == "png" || suf == "PNG" ) return saveIMG( str );

    return saveASC( str );
}

// Load Image
TPL_TC Image<T,C>&
Image<T,C>::load( const String& str )
{
    String suf = str.substr( str.length() - 3 , 3 );

    if( suf == "jpg" || suf == "JPG" ) return loadIMG( str );
    if( suf == "png" || suf == "PNG" ) return loadIMG( str );

    return loadASC( str );
}

// Save Image
TPL_TC void
Image<T,C>::saveIMG( const String& str ) const
{
    cv::imwrite( str , cv() );
}

// Load Image
TPL_TC Image<T,C>&
Image<T,C>::loadIMG( const String& str )
{
    switch( C )
    {
    case 1: *this << cv::imread( str , CV_LOAD_IMAGE_GRAYSCALE ); break;
    case 3: *this << cv::imread( str , CV_LOAD_IMAGE_COLOR     ); break;
    case 4: *this << cv::imread( str , CV_LOAD_IMAGE_UNCHANGED ); break;
    }
    return *this;
}

// Save File
TPL_TC void
Image<T,C>::saveASC( const String& str ) const
{
    OFile file( str );
    if( file.is_open() )
    {
        file << r() << " " << c() << " " << d() << "\n\n";

        for( unsigned i = 0 ; i < r() ; i++ )
        {   for( unsigned j = 0 ; j < c() ; j++ )
            {   for( unsigned k = 0 ; k < d() ; k++ )
                {
                    file << std::fixed << std::setprecision(10)
                         << (unsigned)at(i,j,k) << " ";
                }
            }
            file << "\n";
        }

        file.close();
    }
}

// Load File
TPL_TC Image<T,C>&
Image<T,C>::loadASC( const String& str )
{
    IFile file( str );
    if( file.is_open() )
    {
        unsigned r,c,d;
        file >> r >> c >> d;

        this->reset( r , c );
        for( unsigned i = 0 ; i < r ; i++ )
            for( unsigned j = 0 ; j < c ; j++ )
                for( unsigned k = 0 ; k < d ; k++ )
                    file >> at(i,j,k);

        file.close();
    }
    return *this;
}

}
