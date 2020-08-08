#ifndef WORLD_H
#define WORLD_H

#include "./object.h"

namespace cvpp
{

class World
{

protected:

    Seq< Pts3f* > points;
    Seq< Object* > objects;

public:

    World() {}
    ~World() {}

    const int qtyPoints() const { return points.size(); }
    const int qtyObjects() const { return objects.size(); }

    Pts3f& operator()( const int& idx ) { return *points[idx]; }
    const Pts3f& operator()( const int& idx ) const { return *points[idx]; }

    Pts3f& pts( const int& idx ) { return *points[idx]; }
    const Pts3f& pts( const int& idx ) const { return *points[idx]; }

    Object& operator[]( const int& idx ) { return *objects[idx]; }
    const Object& operator[]( const int& idx ) const { return *objects[idx]; }

    Object& obj( const int& idx ) { return *objects[idx]; }
    const Object& obj( const int& idx ) const { return *objects[idx]; }

    const int push( Pts3f& pts ) { points.push_back( &pts ); return points.size() - 1; }
    const int push( Object& obj ) { objects.push_back( &obj ); return objects.size() - 1; }

};

}

#endif
