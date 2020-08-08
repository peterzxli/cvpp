#ifndef GP_DRAW_REGRESSION_SS_H
#define GP_DRAW_REGRESSION_SS_H

#include "../draw_base.h"

namespace cvpp
{

class DrawRegressionSS : public DrawBase
{

protected:

public:

    // Constructor
    DrawRegressionSS( InfoGP* gp ) : DrawBase( gp )
    {
    }

    // Prepare Buffers 2D
    const void
    prepBuffersInput2D()
    {
        buffers.resize(9);

        buffers[0] = draw.addBuffer2D( gp->Xtr() , gp->Ytr() );
        if( gp->has_Yev() ) buffers[1] = draw.addBuffer2D( gp->Xev() , gp->Yev() );

        buffers[2] = draw.addBuffer2Dd( gp->n_ev() );
        buffers[3] = draw.addBuffer2Dd( gp->n_ev() );
        buffers[4] = draw.addBuffer2Dd( gp->n_ev() );
        buffers[5] = draw.addBuffer2Dd( gp->n_ev() );

        if( gp->has_Ztr() )
        {
            Yz.reset( gp->n_ind() ).setVal( draw.screen(0).resolution.u() );
            buffers[6] = draw.addBuffer2D( gp->Ztr() , Yz );
        }

        if( gp->has_bt() )
            buffers[7] = draw.addBuffer2Dd( gp->n_btc() );
    }

    // Prepare Buffers 3D
    const void
    prepBuffersInput3D()
    {
        buffers.resize(9);

        buffers[0] = draw.addBuffer3D( gp->Xtr() , gp->Ytr() );
        buffers[1] = draw.addBufferIDXgrid( gp->Xev() );

        buffers[2] = draw.addBuffer3Dd( gp->n_ev() );
        buffers[3] = draw.addBuffer3Df( gp->n_ev() );

        buffers[4] = draw.addBuffer3Dd( gp->n_ev() );
        buffers[5] = draw.addBuffer3Df( gp->n_ev() );

        if( gp->has_Ztr() )
        {
            Yz.reset( gp->n_ind() ).setVal( draw.screen(0).resolution.b() );
            buffers[6] = draw.addBuffer3D( gp->Ztr() , Yz );
        }

        if( gp->has_bt() )
        {
            buffers[7] = draw.addBuffer3Dd( gp->n_btc() );
        }

        if( gp->options.draw_3D_view == TOPVIEW )
             buffers[8] = draw.addBufferRGBjet( gp->Ytr() );
        else buffers[8] = -1;
    }

    // Update Buffers 2D
    const void
    updateBuffersInput2D()
    {
        if( gp->has_bt() )
            draw.updBuffer2D( buffers[7] , gp->Xbt() , gp->Ybt() );
    }

    // Update Buffers 3D
    const void
    updateBuffersInput3D()
    {
        if( gp->has_bt() )
            draw.updBuffer3D( buffers[7] , gp->Xbt() , gp->Ybt() );
    }

    // Improve Screens 2D
    const void
    improveBuffersInput2D()
    {
        draw.updBuffer2D( buffers[2] , gp->Xev() , gp->mf );
        draw.updBuffer2D( buffers[3] , gp->Xev() , gp->vf );

        draw.updBuffer2D( buffers[4] , gp->Xev() , gp->lvf() );
        draw.updBuffer2D( buffers[5] , gp->Xev() , gp->uvf() );

        if( gp->has_Ztr() )
            draw.updBuffer2D( buffers[6] , gp->Ztr() , Yz );
    }

    // Improve Screens 3D
    const void
    improveBuffersInput3D()
    {
        draw.updBuffer3D( buffers[2] , gp->Xev() , gp->mf );
        draw.updBuffer3D( buffers[3] , gp->mf.c(0).toRGBjet() );

        draw.updBuffer3D( buffers[4] , gp->Xev() , gp->vf );
        draw.updBuffer3D( buffers[5] , gp->vf.c(0).toRGBjet() );

        if( gp->has_Ztr() )
            draw.updBuffer3D( buffers[6] , gp->Ztr() , Yz );
    }

    // Draw Screens 2D
    const void
    drawScreensInput2D()
    {
        draw[0].clear().axes();

        draw.psc(3,BLA).pts2D( buffers[0] );
        if( gp->has_Yev() ) draw.lwc(3,BLA).line2D( buffers[1] );
        if( gp->has_Ztr() ) draw.psc(8,MAG).pts2D( buffers[6] );
        if( gp->has_bt()  ) draw.psc(4,GRE).pts2D( buffers[7] );

        draw.lwc(3,RED).line2D( buffers[2] );
        draw.lwc(3,BLU).line2D( buffers[4] );
        draw.lwc(3,BLU).line2D( buffers[5] );

        draw[2].clear().axes( buffers[3] );
        draw.lwc(3,BLU).line2D( buffers[3] );
    }

    // Draw Screens 3D
    const void
    drawScreensInput3D()
    {
        draw[0].clear().axes();

        draw.grid3D( buffers[2] , buffers[1] , buffers[3] , gp->options.draw_wire );
        draw.psc(4,BLA).pts3D( buffers[0] , buffers[8] );
        if( gp->has_Ztr() ) draw.psc(6,MAG).pts3D( buffers[6] );
        if( gp->has_bt()  ) draw.psc(4,GRE).pts3D( buffers[7] );

        draw[2].clear().axes( buffers[4] );
        draw.grid3D( buffers[4] , buffers[1] , buffers[5] , gp->options.draw_wire );
    }

};

}

#endif
