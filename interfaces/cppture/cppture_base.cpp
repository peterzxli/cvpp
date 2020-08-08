#include "../cppture.h"

namespace cvpp
{

// Destructor
CPPture::~CPPture()
{
}

// Constructor
CPPture::CPPture()
{
}

// String Constructor
CPPture::CPPture( const String& str )
{
    initialise( str );
}

// Unsigned Constructor
CPPture::CPPture( const int& idx )
{
    initialise( idx );
}

// Image Constructor
CPPture::CPPture( const String& prefix , const String& suffix ,
         const int& start , const int& decimals , const int& finish )
{
    initialise( prefix , suffix ,
                start , decimals , finish );
}

// Initialise Video
const bool
CPPture::initialise( const std::string& str )
{
    this->type = VIDEO;
    this->capture.open( str );

    if( !this->capture.isOpened() )
    {
        std::cout << "UNABLE TO FIND VIDEO : " << str << std::endl;
        return false;
    }

    this->current = 0;
    return true;
}

// Initialise Camera
const bool
CPPture::initialise( const int& idx )
{
    this->type = VIDEO;
    this->capture.open( idx );

    if( !this->capture.isOpened() )
    {
        std::cout << "UNABLE TO FIND CAMERA : " << idx << std::endl;
        return false;
    }

    this->current = 0;
    return true;
}

// Initialise Image
const bool
CPPture::initialise( const String& prefix , const String& suffix ,
                     const int& start , const int& decimals , const int& finish )
{
    this->type = IMAGE;

    this->prefix = prefix;
    this->suffix = suffix;

    this->start = start;
    this->decimals = decimals;
    this->finish = finish;

    this->current = this->start - 1;

    return true;
}

// Read New Frame
const bool
CPPture::read( CV& frame )
{
    this->current++;

    if( type == VIDEO )
    {
        this->capture.read( frame );
    }
    else
    if( type == IMAGE )
    {
        if( current == finish )
            return false;

        ss.str(""); ss << prefix;
        for( int i = 0 ; i < decimals - numDigits( current ) ; i++ ) ss << "0";
        ss << current << suffix;

        frame = cv::imread( ss.str() );
    }

    return !frame.empty();
}

}

