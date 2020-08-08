#ifndef OBJECT_KEYFRAME_H
#define OBJECT_KEYFRAME_H

#include "./object.h"
#include "./object_camera.h"

namespace cvpp
{

class Keyframe : public Object
{

protected:

    Camera* cam;

public:

    Matd mean,var;    
    Img3c frame,cmean,cvar;

    Vecf vars;

public:

    Keyframe();
    ~Keyframe();

    Keyframe( const String& str ) : Object( str ) {}
    Keyframe( const String& str , const int& n ) : Object( str , n ) {}

    Keyframe( const Keyframe& );
    Keyframe( Camera& );

    Vecf& variance() { return vars; }
    const Vecf& variance() const { return vars; }

    void save( const String& ) const;
    void save( const String& str , const int& n ) const { save( str + std::to_string(n) ); }

    void load( const String& );
    void load( const String& str , const int& n ) { load( str + std::to_string(n) ); }



    void initialise( Camera& );

    void draw( CPPlot& ) const;


};

}

#include "./object_keyframe_src.h"

#endif
