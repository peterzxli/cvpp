#ifndef TRACK_H
#define TRACK_H

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/image.h>

namespace cvpp
{

class Track
{

protected:

    Img1c image;
    Matd dims;

    float scale;

public:

    Track( const String& , const float& );

    const Matd& getDims() const;

    float getVal( Pt2d ) const;
    float getVal( const float& , const float& ) const;

    bool isWall( Pt2d ) const;
    bool isWall( const float& , const float& ) const;

    bool isWall( Pt2d , const Pt2d& , const int& = 20 ) const;

};

}

#endif
