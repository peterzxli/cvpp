#ifndef GP_DRAW_REGRESSION_MS_H
#define GP_DRAW_REGRESSION_MS_H

#include "../draw_base.h"

namespace cvpp
{

class DrawRegressionMS : public DrawBase
{

protected:

public:

    // Constructor
    DrawRegressionMS( InfoGP* gp ) : DrawBase( gp )
    {
        mean[1] = "Noise Mean Estimates";
        var[1]  = "Noise Variance Estimates";
    }

    // Prepare Buffers 2D
    const void
    prepBuffersInput2D()
    {
        buffers.resize(2);

        buffers[0] = draw.addBuffer2D( gp->Xtr() , gp->Ytr() );
        if( gp->has_Yev() ) buffers[1] = draw.addBuffer2D( gp->Xev() , gp->Yev() );

        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
        }
    }

    // Prepare Buffers 3D
    const void
    prepBuffersInput3D()
    {
        buffers.resize(3);

        buffers[0] = draw.addBuffer3D( gp->Xtr() , gp->Ytr() );
        buffers[1] = draw.addBufferIDXgrid( gp->Xev() );

        if( gp->options.draw_3D_view == TOPVIEW )
             buffers[2] = draw.addBufferRGBjet( gp->Ytr() );
        else buffers[2] = -1;

        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            buffers.push( draw.addBuffer3Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer3Df( gp->n_ev() ) );
            buffers.push( draw.addBuffer3Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer3Df( gp->n_ev() ) );
        }
    }

    // Prepare Buffers Output
    const void
    prepBuffersOutput()
    {
        buffers.resize(1);

        Xy.reset( gp->n_ev() ).setIncrease();
        if( gp->has_Yev() ) buffers[0] = draw.addBuffer2D( Xy , gp->Yev() );

        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
            buffers.push( draw.addBuffer2Dd( gp->n_ev() ) );
        }
    }

    // Improve Buffers 2D
    const void
    improveBuffersInput2D()
    {
        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            draw.updBuffer2D( buffers[2+4*i] , gp->Xev() , gp->mf.c(i).clone() );
            draw.updBuffer2D( buffers[3+4*i] , gp->Xev() , gp->vf.c(i).clone() );

            draw.updBuffer2D( buffers[4+4*i] , gp->Xev() , gp->lvf().c(i).clone() );
            draw.updBuffer2D( buffers[5+4*i] , gp->Xev() , gp->uvf().c(i).clone() );

        }
    }

    // Improve Buffers 3D
    const void
    improveBuffersInput3D()
    {
        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            draw.updBuffer3D( buffers[3+4*i] , gp->Xev() , gp->mf.c(i).clone() );
            draw.updBuffer3D( buffers[4+4*i] , gp->mf.c(i).toRGBjet() );

            draw.updBuffer3D( buffers[5+4*i] , gp->Xev() , gp->vf.c(i).clone() );
            draw.updBuffer3D( buffers[6+4*i] , gp->vf.c(i).toRGBjet() );
        }

    }

    // Improve Buffers Output
    const void
    improveBuffersOutput()
    {
        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            draw.updBuffer2D( buffers[1+4*i] , Xy , gp->mf.c(i).clone() );
            draw.updBuffer2D( buffers[2+4*i] , Xy , gp->vf.c(i).clone() );

            draw.updBuffer2D( buffers[3+4*i] , Xy , gp->lvf().c(i).clone() );
            draw.updBuffer2D( buffers[4+4*i] , Xy , gp->uvf().c(i).clone() );
        }
    }

    // Draw Screens 2D
    const void
    drawScreensInput2D()
    {
        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            if( i == 0 )
            {
                 draw[i].clear().axes();
                 draw.psc(3,BLA).pts2D( buffers[0] );
                 if( gp->has_Yev() ) draw.lwc(3,BLA).line2D( buffers[1] );
            }
            else draw[i].clear().axes( buffers[2+4*i] );

            draw.lwc(3,RED).line2D( buffers[2+4*i] );
            draw.lwc(3,BLU).line2D( buffers[4+4*i] );
            draw.lwc(3,BLU).line2D( buffers[5+4*i] );

            draw[i+gp->d_gp()+1].clear().axes( buffers[3+4*i] );
            draw.lwc(3,BLU).line2D( buffers[3+4*i] );
        }
    }

    // Draw Screens 3D
    const void
    drawScreensInput3D()
    {
        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            if( i == 0 )
                  draw[i].clear().axes();
            else  draw[i].clear().axes( buffers[3+4*i] );

            draw.grid3D( buffers[3+4*i] , buffers[1] , buffers[4+4*i] , gp->options.draw_wire );
            if( i == 0 ) draw.psc(3,BLA).pts3D( buffers[0] , buffers[2] );

            draw[i+gp->d_gp()+1].clear().axes( buffers[5+4*i] );
            draw.grid3D( buffers[5+4*i] , buffers[1] , buffers[6+4*i] , gp->options.draw_wire );
        }
    }

    // Draw Screens Output
    const void
    drawScreensOutput()
    {
        for( unsigned i = 0 ; i < gp->d_gp() ; i++ )
        {
            if( i == 0 )
            {
                 draw[i].clear();
                 if( gp->has_Yev() ) draw.axes().lwc(3,BLA).line2D( buffers[0] );
                 else draw.axes( buffers[1] );
            }
            else draw[i].clear().axes( buffers[1+4*i] );

            draw.lwc(3,RED).line2D( buffers[1+4*i] );
            draw.lwc(3,BLU).line2D( buffers[3+4*i] );
            draw.lwc(3,BLU).line2D( buffers[4+4*i] );

            draw[i+gp->d_gp()+1].clear().axes( buffers[2+4*i] );
            draw.lwc(3,BLU).line2D( buffers[2+4*i] );
        }
    }

};

}

#endif
