#ifndef STRUCT_TEXTURE_H
#define STRUCT_TEXTURE_H

namespace cvpp
{

// Texture
struct Texture
{
    unsigned ptr = 0 ;
    unsigned r = 0 , c = 0 , d = 0 ;

    bool filled = false;

    const bool started() { return ptr > 0; }
};

}

#endif
