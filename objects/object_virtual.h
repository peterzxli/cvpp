#ifndef OBJECT_VIRTUAL_H
#define OBJECT_VIRTUAL_H

#include <cvpp/objects/object.h>
#include <cvpp/auxiliar/macros.h>

namespace cvpp
{

class Virtual : public Object
{

protected:

    Pts3f nrms , dots;
    Scalar clr1 , clr2;
    Pts3f lims;

public:

    ~Virtual();

    Virtual();
    Virtual( const Virtual& obj );
    Virtual( const String& str );

    Virtual( const String& , const Scalar& , const Scalar& , const float& = 1.0 );
    void initialise( const String& , const Scalar& , const Scalar& , const float& = 1.0 );

    void draw( CPPlot& ) const;

    bool inside( const Pt3f& ) const;

};

}

#include "./object_virtual_src.h"

#endif
