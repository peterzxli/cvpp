#ifndef OBJECT_WALL_H
#define OBJECT_WALL_H

#include <cvpp/objects/object.h>
#include <cvpp/structs/struct_borders3.h>

namespace cvpp
{

class Wall : public Object
{

protected:

    Scalar clr;
    Pts3f lims;

    int tex;
    Seq<Borders3f> brds;

public:

    ~Wall();

    Wall();
    Wall( const Wall& obj );
    Wall( const String& str );

    Wall( const float& , const float& , const float& , const int& );
    Wall( const float& , const float& , const float& , const Scalar& );

    void initialise( const float& , const float& , const float& );
    void initialise( const float& , const float& , const float& , const int& );
    void initialise( const float& , const float& , const float& , const Scalar& );

    void draw( CPPlot& ) const;

    bool inside( const Pt3f& ) const;

};

}

#include "./object_wall_src.h"

#endif
