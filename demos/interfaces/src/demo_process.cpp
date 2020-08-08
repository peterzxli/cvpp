
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/interfaces/cppture.h>
#include <cvpp/interfaces/cpprint.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // VARIABLES

    Dims idim( 360 ,  640 ); // Input Dimension
    Dims odim( 720 , 1280 ); // Output Dimension
    int fps = 20;            // Frames per Second

    // START CAPTURE INTERFACE

    CPPture input( "../data/bullfinch.mp4" );

    // START PRINT INTERFACE

    CPPrint output( "../data/output.avi" , fps , odim );

    // START PLOT INTERFACE

    CPPlot draw( "Window" , 1 , 2 );
    draw[0].set2Dimage();
    draw[1].set2Dimage();

    // START TEXTURE BUFFERS

    unsigned tex1 = draw.addTexture3U( idim );
    unsigned tex2 = draw.addTexture3U( odim );

    Img3c raw , img;
    while( draw.input() && input.read( raw ) )
    {
        // PROCESS IMAGE

        img = raw.resize( odim ).LABscale();

        // WRITE IMAGE TO VIDEO

        output.write( img );

        // DRAW IMAGES TO SCREEN

        draw[0].clear().useTexture( tex1 , raw );
        draw[1].clear().useTexture( tex2 , img );

        // UPDATE WINDOW

        draw.updateWindow(30);
    }

    return 0;
}
