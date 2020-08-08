
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/features/feature_extractor.h>
#include <cvpp/algorithms/features/feature_descriptor.h>
#include <cvpp/algorithms/features/feature_matcher.h>

using namespace cvpp;

int main(void)
{
    // LOAD IMAGES

    Img3c img1( "../data/box.png" , 1 );
    Img3c img2( "../data/box.png" , 2 );

    // EXTRACT FEATURES

    FeatureExtractor<cvSURF> extractor;
    KPts kpts1 = extractor.compute( img1 );
    KPts kpts2 = extractor.compute( img2 );

    // DESCRIBE FEATURES

    FeatureDescriptor<cvSIFT> descriptor;
    CVf desc1 = descriptor.compute( img1 , kpts1 );
    CVf desc2 = descriptor.compute( img2 , kpts2 );

    // MATCH FEATURES

    FeatureMatcher<cvFLANN> matcher;
    MPts mtc = matcher.compute( desc1 , desc2 );

    // PARSE FEATURES

    Pts2f pts1 , pts2;
    matcher.parse( kpts1 , kpts2 , mtc , pts1 , pts2 );

    // CREATE PLOT INTERFACE

    CPPlot draw( "Window", 1 , 2 );
    draw[0].set2Dimage().setResolution( img1 );
    draw[1].set2Dimage().setResolution( img2 );

    // CREATE BUFFERS

    unsigned tex_img1 = draw.addTexture( img1 );
    unsigned buf_pts1 = draw.addBuffer2D( kpts1 );
    unsigned buf_mtc1 = draw.addBuffer2D( pts1 );

    unsigned tex_img2 = draw.addTexture( img2 );
    unsigned buf_pts2 = draw.addBuffer2D( kpts2 );
    unsigned buf_mtc2 = draw.addBuffer2D( pts2 );

    // DRAW

    while( draw.input() )
    {
        draw[0].clear().useTexture( tex_img1 ); // Left Image
        draw.psc(6,BLU).pts2D( buf_pts1 );      // All features
        draw.psc(4,RED).pts2D( buf_mtc1 );      // Matched features

        draw[1].clear().useTexture( tex_img2 ); // Right Image
        draw.psc(6,BLU).pts2D( buf_pts2 );      // All features
        draw.psc(4,RED).pts2D( buf_mtc2 );      // Matched features

        draw.allScreens();                              // Both Images
        draw.lwc(4,GRE).cct2D( 0 , pts1 , 1 , pts2 );   // Match lines

        draw.updateWindow(30);
    }

    return 0;
}
