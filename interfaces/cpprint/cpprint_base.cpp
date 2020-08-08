#include "../cpprint.h"

namespace cvpp
{

CPPrint::~CPPrint()
{
    output.release();
}

CPPrint::CPPrint()
{
    codec = CV_FOURCC('M','J','P','G');
//    codec = CV_FOURCC('M','P','G','4');
//    codec = CV_FOURCC('X','2','6','4');
//    codec = CV_FOURCC('D','I','V','X');
}

CPPrint::CPPrint( const String& str , const int& fps , const Size& dims , const bool& color ) : CPPrint()
{
    initialise( str , fps , dims , color );
}

CPPrint::CPPrint( const String& str , const int& fps , const Dims& dims , const bool& color ) : CPPrint()
{
    initialise( str , fps , Size( dims.c , dims.r ) , color );
}

const bool
CPPrint::initialise( const String& str , const int& fps , const Size& dims , const bool& color )
{
    output.open( str , codec , fps , dims , color );

    if( !output.isOpened() )
    {
        std::cout << "UNABLE TO WRITE VIDEO : " << str << std::endl;
        return false;
    }

    this->current = 0;
    return true;
}

void
CPPrint::write( const CV& img )
{
    output.write( img );
}

}



