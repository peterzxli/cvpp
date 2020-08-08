
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/interfaces/cppture.h>

#include <cvpp/algorithms/features/feature_tracker.h>

using namespace cvpp;

int main(void)
{
    // START CAPTURE INTERFACE

    CPPture capture( 0 );

    // START PLOT INTERFACE

    CPPlot draw("Window");
    draw[0].set2Dimage().setResolution( 480 , 640 );

    // START TRACKER INTERFACE

    Img3c raw;
    FeatureTracker tracker;

    // INITIATE

    capture.read( raw );
    tracker.startGOOD( raw.grayscale() );

    // CREATE TEXTURE

    unsigned tex = draw.addTexture1U( raw );

    // TRACKING LOOP

    while( draw.input() && capture.read( raw ) )
    {
        draw[0].clear().useTexture( tex , raw );    // Draw texture

        tracker.loopGOOD( raw.grayscale() );        // Loop tracking

        draw.psc(5,RED).pts2D( tracker.cFeats() );                      // Draw current features
        draw.lwc(2,BLU).cct2D( tracker.cFeats() , tracker.pFeats() );   // Draw feature motion

        draw.updateWindow();    // Update window
    }

    return 0;
}
