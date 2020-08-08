#ifndef OBJECT_BOARD_H
#define OBJECT_BOARD_H

#include "./object.h"

namespace cvpp
{

class Board : public Object
{

protected:

public:

    ~Board();

    Board();
    Board( const Board& obj );
    Board( const String& str );

    Board( const int& ,
           const int& ,
           const int& ,
           const float& );

    void initialise( const int& ,
                           const int& ,
                           const int& ,
                           const float& );

    void draw( CPPlot& ) const;

};

}

#include "./object_board_src.h"

#endif
