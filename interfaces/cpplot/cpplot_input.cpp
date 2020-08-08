#include "../cpplot.h"

namespace cvpp
{

const bool
CPPlot::input()
{
    while( SDL_PollEvent( &event ) )
    {
        switch( event.type )
        {
            case SDL_QUIT:

                return false;

            case SDL_WINDOWEVENT:

                switch( event.window.event )
                {
                    case SDL_WINDOWEVENT_ENTER:

                        fW = event.window.windowID - 2;
                        break;

                    case SDL_WINDOWEVENT_LEAVE:

                        mouseL() = mouseR() = false;
                        fW = fS = -1;
                        break;
                }

                break;

            case SDL_KEYDOWN:

                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: return false;

                    case SDLK_UP:    keys.up    = true; break;
                    case SDLK_DOWN:  keys.down  = true; break;
                    case SDLK_LEFT:  keys.left  = true; break;
                    case SDLK_RIGHT: keys.right = true; break;

                    case SDLK_q: keys.q = true; break;
                    case SDLK_w: keys.w = true; break;
                    case SDLK_e: keys.e = true; break;
                    case SDLK_a: keys.a = true; break;
                    case SDLK_s: keys.s = true; break;
                    case SDLK_d: keys.d = true; break;
                    case SDLK_z: keys.z = true; break;
                    case SDLK_x: keys.x = true; break;
                    case SDLK_c: keys.c = true; break;

                    case SDLK_i: keys.i = true; break;
                    case SDLK_o: keys.o = true; break;
                    case SDLK_j: keys.j = true; break;
                    case SDLK_k: keys.k = true; break;
                    case SDLK_l: keys.l = true; break;
                    case SDLK_b: keys.b = true; break;
                    case SDLK_n: keys.n = true; break;
                    case SDLK_m: keys.m = true; break;

                    case SDLK_r: keys.r = true; break;
                    case SDLK_t: keys.t = true; break;
                    case SDLK_y: keys.y = true; break;
                    case SDLK_u: keys.u = true; break;
                    case SDLK_f: keys.f = true; break;
                    case SDLK_g: keys.g = true; break;
                    case SDLK_h: keys.h = true; break;
                    case SDLK_v: keys.v = true; break;

                    case SDLK_LCTRL:  keys.lctrl  = true; break;
                    case SDLK_RCTRL:  keys.rctrl  = true; break;
                    case SDLK_LALT:   keys.lalt   = true; break;
                    case SDLK_RALT:   keys.ralt   = true; break;
                    case SDLK_LSHIFT: keys.lshift = true; break;
                    case SDLK_RSHIFT: keys.rshift = true; break;
                    case SDLK_TAB:    keys.tab    = true; break;

                    case SDLK_KP_0: keys.kp0 = true; break;
                    case SDLK_KP_1: keys.kp1 = true; break;
                    case SDLK_KP_2: keys.kp2 = true; break;
                    case SDLK_KP_3: keys.kp3 = true; break;
                    case SDLK_KP_4: keys.kp4 = true; break;
                    case SDLK_KP_5: keys.kp5 = true; break;
                    case SDLK_KP_6: keys.kp6 = true; break;
                    case SDLK_KP_7: keys.kp7 = true; break;
                    case SDLK_KP_8: keys.kp8 = true; break;
                    case SDLK_KP_9: keys.kp9 = true; break;

                    case SDLK_RETURN:

                        keys.enter = true;

                        break;

                    case SDLK_SPACE:

                        keys.space = true;

                        if( hasFocus() )
                        {
                            if( fScreen().type == PLOT_2D )
                            {
                                fSores() = fSres();
                            }
                        }

                        break;

                    case SDLK_p:

                        keys.p = true;

                        if( hasFocus() )
                        {
                            if( fScreen().type == WORLD_3D ||
                                fScreen().type ==  PLOT_3D )
                            {
                                viewer(fS).getPos().t().appD(viewer(fS).getLook().t())
                                          .print("POS/LOOK SCREEN " + std::to_string(fS) );
                            }
                        }

                        break;
                }

                break;

            case SDL_KEYUP:

                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:    keys.up    = false; break;
                    case SDLK_DOWN:  keys.down  = false; break;
                    case SDLK_LEFT:  keys.left  = false; break;
                    case SDLK_RIGHT: keys.right = false; break;

                    case SDLK_q: keys.q = false; break;
                    case SDLK_w: keys.w = false; break;
                    case SDLK_e: keys.e = false; break;
                    case SDLK_a: keys.a = false; break;
                    case SDLK_s: keys.s = false; break;
                    case SDLK_d: keys.d = false; break;
                    case SDLK_z: keys.z = false; break;
                    case SDLK_x: keys.x = false; break;
                    case SDLK_c: keys.c = false; break;

                    case SDLK_i: keys.i = false; break;
                    case SDLK_o: keys.o = false; break;
                    case SDLK_p: keys.p = false; break;
                    case SDLK_j: keys.j = false; break;
                    case SDLK_k: keys.k = false; break;
                    case SDLK_l: keys.l = false; break;
                    case SDLK_b: keys.b = false; break;
                    case SDLK_n: keys.n = false; break;
                    case SDLK_m: keys.m = false; break;

                    case SDLK_r: keys.r = false; break;
                    case SDLK_t: keys.t = false; break;
                    case SDLK_y: keys.y = false; break;
                    case SDLK_u: keys.u = false; break;
                    case SDLK_f: keys.f = false; break;
                    case SDLK_g: keys.g = false; break;
                    case SDLK_h: keys.h = false; break;
                    case SDLK_v: keys.v = false; break;

                    case SDLK_LCTRL:  keys.lctrl  = false; break;
                    case SDLK_RCTRL:  keys.rctrl  = false; break;
                    case SDLK_LALT:   keys.lalt   = false; break;
                    case SDLK_RALT:   keys.ralt   = false; break;
                    case SDLK_LSHIFT: keys.lshift = false; break;
                    case SDLK_RSHIFT: keys.rshift = false; break;
                    case SDLK_TAB:    keys.tab    = false; break;

                    case SDLK_RETURN: keys.enter = false; break;
                    case SDLK_SPACE:  keys.space = false; break;

                    case SDLK_KP_0: keys.kp0 = false; break;
                    case SDLK_KP_1: keys.kp1 = false; break;
                    case SDLK_KP_2: keys.kp2 = false; break;
                    case SDLK_KP_3: keys.kp3 = false; break;
                    case SDLK_KP_4: keys.kp4 = false; break;
                    case SDLK_KP_5: keys.kp5 = false; break;
                    case SDLK_KP_6: keys.kp6 = false; break;
                    case SDLK_KP_7: keys.kp7 = false; break;
                    case SDLK_KP_8: keys.kp8 = false; break;
                    case SDLK_KP_9: keys.kp9 = false; break;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:

                if( hasFocus() )
                {
                    if( event.button.button == SDL_BUTTON_LEFT )
                    {
                        mouseL() = true;
                        mouseLp() << event.motion.x , event.motion.y;
                    }

                    if( event.button.button == SDL_BUTTON_RIGHT )
                    {
                        mouseR() = true;
                        mouseRp() << event.motion.x , event.motion.y;

                        if( fScreen().type == IMAGE_2D ||
                            fScreen().type ==  PLOT_2D )
                        {
                            fScreen().changed = true;
                            dcoord = coord;
                        }
                    }

                    if( event.button.button == SDL_BUTTON_MIDDLE )
                    {
                        mouseM()= true;
                    }
                }

                break;

            case SDL_MOUSEBUTTONUP:

                if( hasFocus() )
                {
                    if( event.button.button == SDL_BUTTON_LEFT )
                    {
                        mouseL() = false;
                    }

                    if( event.button.button == SDL_BUTTON_RIGHT )
                    {
                        mouseR() = false;

                        if( fScreen().type == IMAGE_2D ||
                            fScreen().type ==  PLOT_2D )
                        {
                            fSres().lurd( std::min( dcoord.x , coord.x ) , std::min( dcoord.y , coord.y ) ,
                                          std::max( dcoord.x , coord.x ) , std::max( dcoord.y , coord.y ) );
                        }

                        if( fScreen().type == IMAGE_2D )
                        {
                            trimImageBoundary();
                        }
                    }

                    if( event.button.button == SDL_BUTTON_MIDDLE )
                    {
                        mouseM()= false;

                        if( fScreen().type == IMAGE_2D ||
                            fScreen().type ==  PLOT_2D )
                        {
                            fScreen().changed = false;
                            fSres() = fSores();
                        }

                        if( fScreen().type == PLOT_3D )
                        {
                            if( !fScreen().changed ) fScreen().view++;
                            fScreen().view = fScreen().view % 4;
                            fScreen().changed = false;

                            switch( fScreen().view )
                            {
                            case 0: fViewer().reset().setPos(1.8,1.8,1.8)
                                                     .setLook(0.0,0.0,-0.2); break;
                            case 1: fViewer().reset().setPos(0.5,2.7,0.5)
                                                     .setLook(0.5,0.0,+0.5); break;
                            case 2: fViewer().reset().setPos(2.7,0.5,0.5)
                                                     .setLook(0.0,0.5,+0.5); break;
                            case 3: fViewer().reset().setPos(0.5,0.5,2.7)
                                                     .setLook(0.5,0.5,+0.0); break;
                            }
                        }

                        if( fScreen().type == WORLD_3D )
                        {
                            fViewer() = fOViewer();
                        }
                    }
                }

                break;

            case SDL_MOUSEMOTION:

                if( fW >= 0 )
                {
                    if( !mouseL() && !mouseM()&& !mouseR() && !keys.p )
                    {
                        fS = -1;
                        for( unsigned j = 0 ; j < nfScreens() ; j++ )
                        {
                            if( fWindow().screens[j].borders.inside(
                                          event.motion.x , event.motion.y ) )
                                fS = j;
                        }
                    }

                    if( fScreen().type == IMAGE_2D )
                    {
                        coord = coordImage2D( event.motion.x , event.motion.y );
                        if( keys.p ) { disp( coord ); }

                        if( mouseL() && !selecting )
                        {
                            mouseLd() << event.motion.x , event.motion.y;
                            mouseLd() -= mouseLp();

                            float mlt = keys.rshift ? 0.02 : 0.0025 ;
                            fSres().points() += mlt * Pt2f( + fSres().w() * mouseLd(0) ,
                                                            + fSres().h() * mouseLd(1) );
                            trimImageBoundary();

                            mouseLp() << event.motion.x , event.motion.y;
                        }
                    }
                    else
                    if( fScreen().type == PLOT_2D )
                    {
                        coord = coordPlot2D( event.motion.x , event.motion.y );
                        if( keys.p ) { disp( coord ); }

                        if( mouseL() )
                        {
                            fScreen().changed = true;

                            mouseLd() << event.motion.x , event.motion.y;
                            mouseLd() -= mouseLp();

                            float mlt = keys.rshift ? 0.02 : 0.0025 ;
                            fSres().points() += mlt * Pt2f( + fSres().w() * mouseLd(0) ,
                                                            - fSres().h() * mouseLd(1) );

                            mouseLp() << event.motion.x , event.motion.y;
                        }
                    }
                    else
                    if( fScreen().type == WORLD_3D ||
                        fScreen().type ==  PLOT_3D )
                    {
                        if( mouseL() )
                        {
                            float mlt = keys.rctrl ? ( keys.rshift ? 120.0 : 12.0 ) : 1.0 ;

                            mouseLd() << event.motion.x , event.motion.y;
                            mouseLd() -= mouseLp();

                            fScreen().viewer->moveZ( -0.02 * mlt * mouseLd(1) );
                            fScreen().viewer->moveY( -0.02 * mlt * mouseLd(0) );

                            mouseLp() << event.motion.x , event.motion.y;
                            fScreen().changed = true;
                        }

                        if( mouseR() )
                        {
                            float mlt = keys.rshift ? 2.0 : 1.0 ;

                            mouseRd() << event.motion.x , event.motion.y;
                            mouseRd() -= mouseRp();

                            fScreen().viewer->rotateZ( -0.1 * mlt * mouseRd(0) );
                            fScreen().viewer->rotateY( +0.1 * mlt * mouseRd(1) );
                            fScreen().viewer->align();

                            mouseRp() << event.motion.x , event.motion.y;
                            fScreen().changed = true;
                        }
                    }
                }

                break;

            case SDL_MOUSEWHEEL:

                if( hasFocus() )
                {
                    if( fScreen().type == IMAGE_2D ||
                        fScreen().type ==  PLOT_2D )
                    {
                        fScreen().changed = true;

                        float mlt = keys.rctrl ? 1.5 : 1.05 ;
                        if( event.motion.x > 0 ) mlt = 1.0 / mlt;

                        fSres().points() = ( fSres().points() - coord ) * mlt + coord;
                    }

                    if( fScreen().type == IMAGE_2D )
                    {
                        trimImageBoundary();
                    }

                    if( fScreen().type == WORLD_3D ||
                        fScreen().type ==  PLOT_3D )
                    {
                        fScreen().changed = true;

                        float mlt = keys.rctrl ? ( keys.rshift ? 120.0 : 12.0 ) : 1.0 ;
                        fScreen().viewer->moveX( 0.1 * mlt * event.motion.x );
                    }
                }

                break;
        }
    }

    return true;
}

Pt2f
CPPlot::coordPlot2D( const float& x , const float& y )
{
    float xx = ( x - fSbrd().l() ) / fSbrd().w();
    float yy = ( fSbrd().h() - y + fSbrd().u() ) / fSbrd().h();

    return Pt2f( fSres().l() + fSres().w() * ( 1.3 * xx - 0.2 ) ,
                 fSres().u() + fSres().h() * ( 1.2 * yy - 0.1 ) );
}

Pt2f
CPPlot::coordImage2D( const float& x , const float& y )
{
    float xx = ( x - fSbrd().l() ) / fSbrd().w();
    float yy = ( y - fSbrd().u() ) / fSbrd().h();

    return Pt2f( fSres().l() + fSres().w() * xx,
                 fSres().u() + fSres().h() * yy );
}

void
CPPlot::trimImageBoundary()
{
    if( fSres().w() > fSores().w() || fSres().h() > fSores().h() )
    {
        fSres() = fSores();
    }
    else
    {
        if( fSres().l() < 0 ) fSres().points() -= Pt2f( fSres().l() , 0.0 );
        if( fSres().u() < 0 ) fSres().points() -= Pt2f( 0.0 , fSres().u() );

        float resr = fSres().r() - fSores().r();
        float resd = fSres().d() - fSores().d();

        if( resr > 0 ) fSres().points() -= Pt2f( resr , 0.0 );
        if( resd > 0 ) fSres().points() -= Pt2f( 0.0 , resd );
    }
}

const bool
CPPlot::selectLU( Borders2d& brd )
{
    if( mouseL() )
    {
        if( !brd.started() )
            brd.lu( mousePos() ) , selecting = true;
        brd.rd( mousePos() );
        return false;
    }

    selecting = false;
    return brd.started() ? true : false;
}

const bool
CPPlot::selectXY( Borders2d& brd )
{
    if( mouseL() )
    {
        if( !brd.started() )
            brd.lu( mousePos() ).rd( mousePos() ) , selecting = true;
        Pt2f ctr = brd.xy() , dif = mousePos() - ctr;
        brd.lu( ctr - dif ).rd( ctr + dif );
        return false;
    }

    selecting = false;
    return brd.started() ? true : false;
}

const bool
CPPlot::control( Posef& pose , const float& v ,
                               const float& w )
{
    bool changed = false;

    if( keys.up    ) { pose.moveX( +v ); changed = true; }
    if( keys.down  ) { pose.moveX( -v ); changed = true; }
    if( keys.left  ) { pose.moveY( +v ); changed = true; }
    if( keys.right ) { pose.moveY( -v ); changed = true; }
    if( keys.x     ) { pose.moveZ( +v ); changed = true; }
    if( keys.z     ) { pose.moveZ( -v ); changed = true; }

    if( keys.a ) { pose.rotateZ( +w ); changed = true; }
    if( keys.d ) { pose.rotateZ( -w ); changed = true; }
    if( keys.s ) { pose.rotateY( +w ); changed = true; }
    if( keys.w ) { pose.rotateY( -w ); changed = true; }
    if( keys.e ) { pose.rotateX( +w ); changed = true; }
    if( keys.q ) { pose.rotateX( -w ); changed = true; }

    return changed;
}

}

