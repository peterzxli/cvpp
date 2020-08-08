#ifndef GP_DRAW_CLASSIFICATION_SS_H
#define GP_DRAW_CLASSIFICATION_SS_H

#include "../draw_base.h"

namespace cvpp
{

class DrawClassificationSS : public DrawBase
{

protected:

public:

    // Constructor
    DrawClassificationSS( InfoGP* gp ) : DrawBase( gp )
    {
    }

    // Prepare Buffers 2D
    const void
    prepBuffersInput2D()
    {
    }

    // Prepare Buffers 3D
    const void
    prepBuffersInput3D()
    {
        buffers.resize(6);

        buffers[0] = draw.addBuffer2D( gp->Xtr() );
        buffers[1] = draw.addBufferRGBlbl( gp->Ytr().replace( -1 , 0 ) );

        buffers[2] = draw.addBufferIDXgrid( gp->Xev() );
        buffers[3] = draw.addBuffer2Dd( gp->n_ev() );

        buffers[4] = draw.addBuffer3Df( gp->n_ev() );
        buffers[5] = draw.addBuffer3Df( gp->n_ev() );
    }

    // Update Buffers 2D
    const void
    updateBuffersInput2D()
    {
    }

    // Update Buffers 3D
    const void
    updateBuffersInput3D()
    {
    }

    // Improve Screens 2D
    const void
    improveBuffersInput2D()
    {
    }

    // Improve Screens 3D
    const void
    improveBuffersInput3D()
    {
        draw.updBuffer2D( buffers[3] , gp->Xev() );
        draw.updBuffer3D( buffers[4] , gp->lp.exp().toRGBbnd() );
        draw.updBuffer3D( buffers[5] , gp->vf.toRGBjet() );
    }

    // Draw Screens 2D
    const void
    drawScreensInput2D()
    {
    }

    // Draw Screens 3D
    const void
    drawScreensInput3D()
    {
        draw[0].clear().axes();

        draw.grid2D( buffers[3] , buffers[2] , buffers[4] );
        draw.ps(5).pts2D( buffers[0] , buffers[1] );

        draw[2].clear().axes( gp->Xev() );

        draw.grid2D( buffers[3] , buffers[2] , buffers[5] );
        draw.psc(5,BLA).pts2D( buffers[0] );
    }

};

}

#endif
