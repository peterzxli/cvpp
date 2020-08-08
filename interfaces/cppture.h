#ifndef CPPTURE_H
#define CPPTURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>

#include <cvpp/containers/image.h>

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/macros.h>

namespace cvpp
{

class CPPture
{

protected:

    unsigned type,current;
    unsigned start,decimals,finish;

    SStream ss;
    String prefix,suffix;

    cv::VideoCapture capture;

public:

    // Destructor

    ~CPPture();

    // Constructor

    CPPture();
    CPPture( const String& );
    CPPture( const int& );

    CPPture( const String& , const String& ,
             const int& , const int& ,
             const int& = INT_MAX );

    // Counter

    const int counter() const { return current; }

    // Initialise

    const bool initialise( const String& );
    const bool initialise( const int& );
    const bool initialise( const String& , const String& ,
                           const int& , const int& ,
                           const int& = INT_MAX );

    // Read

    const bool read( CV& );

    TPL_TC const bool read( Image<T,C>& frame )
    { bool flag = read( frame.cv() ); frame.update(); return flag; }

    CV read() { CV cv; read( cv ); return cv; }
    TPL_TC Image<T,C> read() { Image<T,C> img; read( img ); return img; }

};

}

#endif


