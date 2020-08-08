#ifndef CPPRINT_H
#define CPPRINT_H

#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>

#include <cvpp/containers/image.h>

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/macros.h>

namespace cvpp
{

class CPPrint
{

protected:

    int codec;
    unsigned current;

    cv::VideoWriter output;

public:

    ~CPPrint();

    CPPrint();

    CPPrint( const String& , const int& , const Size& , const bool& = true );
    CPPrint( const String& , const int& , const Dims& , const bool& = true );

    const bool initialise( const String& , const int& , const Size& , const bool& = true );

    void write( const CV& );
    TPL_TC void write( const Image<T,C>& img ) { write( img.cv() ); }

};

}

#endif


