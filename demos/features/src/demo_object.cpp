
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/interfaces/cppture.h>
#include <cvpp/algorithms/features/tracker_object.h>

using namespace cvpp;

int main()
{
    // START CAPTURE INTERFACE

    CPPture cap( 0 );

    // START PLOT INTERFACE

    CPPlot draw("Window",ULHW(0,0,480,640));
    draw[0].set2Dimage();

    // CREATE TEXTURE

    Img3c raw; cap.read( raw );
    unsigned tex = draw.addTexture( raw );
    Borders2d brd;

    // SELECTION LOOP

    bool selected = false;
    while( !selected && draw.input() && cap.read( raw ) )
    {
        draw[0].clear().useTexture( tex , raw );
        selected = draw.selectLU( brd );
        draw.lwc(3,BLU).brd2D( brd );

        draw.updateWindow();
    }

    // START TRACKER

    ObjectTracker<cvTracker> tracker( "KCF" );
    tracker.start( raw , brd );

    // TRACKING LOOP

    while( draw.input() && cap.read( raw ) )
    {
        tracker.update( raw );

        draw[0].clear().useTexture( tex , raw );
        draw.lwc(3,RED).brd2D( tracker.brd() );

        draw.updateWindow();
    }

    return 0;
}




