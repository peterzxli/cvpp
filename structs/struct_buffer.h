#ifndef BUFFER_H
#define BUFFER_H

namespace cvpp
{

// Buffer
struct Buffer
{
    unsigned ptr = 0 , type = 0 ;
    unsigned r = 0 , c = 0 , n = 0 , d = 0 ;

    double min = 1 , max = -1 ;

    double minX = 1 , maxX = -1 ;
    double minY = 1 , maxY = -1 ;
    double minZ = 1 , maxZ = -1 ;

    bool filled = false;

    const bool started() { return ptr > 0; }
};

}

#endif

