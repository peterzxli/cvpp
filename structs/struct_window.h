#ifndef WINDOW_H
#define WINDOW_H

#include <cvpp/auxiliar/definitions.h>

#include <cvpp/structs/struct_borders2.h>
#include <cvpp/structs/struct_screen.h>

namespace cvpp
{

class Window
{

protected:

public:

    Borders2f borders;

    SDL_Window *SDLpointer;
    SDL_GLContext SDLcontext;

    Seq<Screen> screens;

    Eig2f mouseLp , mouseLd;
    Eig2f mouseRp , mouseRd;
    Eig2f mouseMp , mouseMd;

    bool mouseL , mouseR , mouseM;

public:

    Window()
    {
        mouseL = mouseR = mouseM = false;
    }

    Window( const String& title ,
            const Borders2f& borders )
    {
        initialise( title , borders );
    }

    void
    initialise( const String& title ,
                const Borders2f& borders )
    {
        this->borders = borders;

        SDLpointer = SDL_CreateWindow( title.c_str() ,
                     borders.l() , borders.u() , borders.w() , borders.h() ,
                     SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
        SDLcontext = SDL_GL_CreateContext( SDLpointer );

        SDL_GL_MakeCurrent( SDLpointer , SDLcontext );

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
        glClearColor( 1.0 , 1.0 , 1.0 , 0.0 );

        glViewport( 0.0 , 0.0 , borders.w() , borders.h() );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable(GL_SCISSOR_TEST);

        screens.reserve( 100 );
    }

};

}

#endif
