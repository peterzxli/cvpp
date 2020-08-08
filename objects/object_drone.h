#ifndef OBJECT_DRONE_H
#define OBJECT_DRONE_H

#include "./object.h"

namespace cvpp
{

class Drone : public Object
{

protected:

public:

    ~Drone();

    Drone();
    Drone( const Drone& obj );
    Drone( const String& str );

    Drone( const float& );

    void initialise( const float& );

    void draw( CPPlot& ) const;

};

}

#include "./object_drone_src.h"

#endif
