#ifndef GP_DRAW_REGRESSION_LSS_H
#define GP_DRAW_REGRESSION_LSS_H

#include "../draw_base.h"

namespace cvpp
{

class DrawRegressionLSS : public DrawBase
{

protected:

    unsigned m;
    unsigned *buf_nlml , *buf_errs ;

public:

    DrawRegressionLSS( InfoGP* gp ) : DrawBase( gp )
    {
    }

    // Local Loop
    const void loopLocal( const SeqPts2d& lmls , const SeqPts2d& errs )
    {
        m = lmls.size();

        lim_nlml = LIMITSd( 2 ); buf_nlml = new unsigned[ m ];
        for( unsigned i = 0 ; i < m ; i++ ) lim_nlml.Lim( lmls[i].limRows() );

        if( gp->has_Yev() )
        {
            lim_errs = LIMITSd( 2 ); buf_errs = new unsigned[ m ];
            for( unsigned i = 0 ; i < m ; i++ ) lim_errs.Lim( errs[i].limRows() );
        }

        prepScreens( true );

        for( unsigned i = 0 ; i < m ; i++ )
            buf_nlml[i] = draw.addBuffer2D( lmls[i] );

        if( gp->has_Yev() )
        {
            for( unsigned i = 0 ; i < m ; i++ )
                buf_errs[i] = draw.addBuffer2D( errs[i] );
        }

        prepBuffers();
        improveBuffers();

        while( draw.input() )
            drawScreens();
    }

    // Prepare Buffers 2D
    const void
    prepBuffersInput2D()
    {
        buffers.resize(9);

        buffers[0] = draw.addBuffer2D( gp->Xtr() , gp->Ytr() );
        buffers[1] = draw.addBufferRGBlbl( gp->Ltr() );

        if( gp->has_Yev() ) buffers[2] = draw.addBuffer2D( gp->Xev() , gp->Yev() );

        buffers[3] = draw.addBuffer2Dd( gp->n_ev() );
        buffers[4] = draw.addBuffer2Dd( gp->n_ev() );

        buffers[5] = draw.addBuffer2Dd( gp->n_ev() );
        buffers[6] = draw.addBuffer2Dd( gp->n_ev() );

        Matd Yz( gp->n_ind() ); Yz.setVal( draw.screen(0).resolution.u() );
        buffers[7] = draw.addBuffer2D( gp->Ztr() , Yz );

        Mati idx( gp->n_ind() ); idx.setIncrease();
        buffers[8] = draw.addBufferRGBlbl( idx );
    }

    // Prepare Buffers 3D
    const void
    prepBuffersInput3D()
    {
        buffers.resize(9);

        buffers[0] = draw.addBuffer3D( gp->Xtr() , gp->Ytr() );
        buffers[1] = draw.addBufferRGBlbl( gp->Ltr() );

        buffers[2] = draw.addBufferIDXgrid( gp->n_ev() );

        buffers[3] = draw.addBuffer3Dd( gp->n_ev() );
        buffers[4] = draw.addBuffer3Dd( gp->n_ev() );

        buffers[5] = draw.addBuffer3Df( gp->n_ev() );
        buffers[6] = draw.addBuffer3Df( gp->n_ev() );

        Matd Yz( gp->n_ind() ); Yz.setVal( draw.screen(0).resolution.b() );
        buffers[7] = draw.addBuffer3D( gp->Ztr() , Yz );

        Mati idx( gp->n_ind() ); idx.setIncrease();
        buffers[8] = draw.addBufferRGBlbl( idx );
    }

    // Improve Buffers 2D
    const void
    improveBuffersInput2D()
    {
        draw.updBuffer2D( buffers[3] , gp->Xev() , gp->mf );
        draw.updBuffer2D( buffers[4] , gp->Xev() , gp->vf );

        draw.updBuffer2D( buffers[5] , gp->Xev() , gp->lvf() );
        draw.updBuffer2D( buffers[6] , gp->Xev() , gp->uvf() );
    }

    // Improve Buffers 3D
    const void
    improveBuffersInput3D()
    {
        draw.updBuffer3D( buffers[3] , gp->Xev() , gp->mf );
        draw.updBuffer3D( buffers[4] , gp->Xev() , gp->vf );

        draw.updBuffer3D( buffers[5] , gp->mf.c(0).toRGBjet() );
        draw.updBuffer3D( buffers[6] , gp->vf.c(0).toRGBjet() );
    }

    // Draw Screens 2D
    const void
    drawScreensInput2D()
    {
        draw[0].clear().axes();

        draw.ps(3).pts2D( buffers[0] , buffers[1] );
        draw.ps(8).pts2D( buffers[7] , buffers[8] );

        if( gp->has_Yev() ) draw.lwc(3,BLA).line2D( buffers[2] );

        draw.lwc(3,RED).line2D( buffers[3] );
        draw.lwc(3,BLU).line2D( buffers[5] );
        draw.lwc(3,BLU).line2D( buffers[6] );

        draw[2].clear().axes();
        draw.lwc(3,BLU).line2D( buffers[4] );
    }

    // Draw Screens 3D
    const void
    drawScreensInput3D()
    {
        draw[0].clear().axes();

        draw.ps(3).pts3D( buffers[0] , buffers[1] );
        draw.ps(8).pts3D( buffers[7] , buffers[8] );

        draw.wgrid3D( buffers[3] , buffers[2] , buffers[5] );

        draw[2].clear().axes();
        draw.wgrid3D( buffers[4] , buffers[2] , buffers[6] );
    }

    // Draw LML
    const void
    drawLML( const unsigned& idx )
    {
        draw[idx].clear().axes();
        for( unsigned i = 0 ; i < m ; i++ )
            draw.lwc(3,i).line2D( buf_nlml[i] );
    }

    // Draw ERR
    const void
    drawERR( const unsigned& idx )
    {
        drawERRbase(idx);

        draw.axes();
        for( unsigned i = 0 ; i < m ; i++ )
            draw.lwc(3,i).line2D( buf_errs[i] );
    }

};

}

#endif
