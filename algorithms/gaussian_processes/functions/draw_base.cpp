#include "./draw_base.h"

namespace cvpp
{

DrawBase::DrawBase()
{
    title = "GAUSSIAN PROCESS TRAINING";

    mean[0] = "Mean Estimates";
    var[0]  = "Variance Estimates";

    nlml = "Negative Log-Marginal Likelihood";

    rmse = "Root Mean Square Error";
    nlpd = "Negative Log-Probability Distribution";
}

DrawBase::DrawBase( InfoGP* gp ) : DrawBase()
{
    this->gp = gp;
}

// Set Screen Format
const void
DrawBase::setFormat()
{
    if( gp->has_Xev() )
    {
        if( gp->options.draw_type == INPUT )
        {
            if( gp->d_in() < 3 )
                 format = FULL;
            else
            if( gp->has_Yev() )
                 format = HALF;
            else format = SINGLE;
        }
        else format = FULL;
    }
    else format = SINGLE;
}

// Prepare Screens
const void
DrawBase::prepScreens( const bool& done )
{
    this->done = done;
    setFormat();

    switch( format )
    {
    case FULL:

        nr = 2 , nc = 1 + gp->d_gp();

        draw.addWindow( title , ULHW( 0 , 0 ,
                        nr * gp->options.screen_height ,
                        nc * gp->options.screen_width  ) , nr , nc );

        double minx,maxx,miny,maxy,minz,maxz,hgt;

        switch( gp->options.draw_type )
        {
        case INPUT:

            switch( gp->d_in() )
            {
            case 1:

                minx = gp->Xtr().c(0).min() ; maxx = gp->Xtr().c(0).max() ;
                miny = gp->Ytr().c(0).min() ; maxy = gp->Ytr().c(0).max() ;

                minx = std::min( minx , gp->Xev().c(0).min() ); maxx = std::max( maxx , gp->Xev().c(0).max() );
                if( gp->has_Yev() )
                    miny = std::min( miny , gp->Yev().c(0).min() ) , maxy = std::max( maxy , gp->Yev().c(0).max() );
                hgt = ( maxy - miny ) / 10.0 ;

                for( unsigned i = 0 ; i < nc ; i++ )
                {
                    draw[i].set2Dplot(); if( i == 0 ) draw.setAxes( minx , maxx , miny - hgt , maxy + hgt );
                    draw[i+nc].set2Dplot(); if( done ) draw.setAxes( gp->Xev() , gp->vf.c(0) );
                }

                break;

            case 2:

                minx = gp->Xtr().c(0).min() ; maxx = gp->Xtr().c(0).max() ;
                miny = gp->Xtr().c(1).min() ; maxy = gp->Xtr().c(1).max() ;
                minz = gp->Ytr().c(0).min() ; maxz = gp->Ytr().c(0).max() ;

                minx = std::min( minx , gp->Xev().c(0).min() ); maxx = std::max( maxx , gp->Xev().c(0).max() );
                miny = std::min( miny , gp->Xev().c(1).min() ); maxy = std::max( maxy , gp->Xev().c(1).max() );
                if( gp->has_Yev() )
                    minz = std::min( minz , gp->Yev().c(0).min() ) , maxz = std::max( maxz , gp->Yev().c(0).max() );

                for( unsigned i = 0 ; i < nc ; i++ )
                {
                    switch( gp->options.draw_3D_view )
                    {
                    case ISOMETRIC:

                        draw[i].set3Dplot(); if( i == 0 ) draw.setAxes( minx , maxx , miny , maxy , minz , maxz );
                        draw[i+nc].set3Dplot(); if( done ) draw.setAxes( gp->Xev() , gp->vf.c(0) );

                        break;

                    case TOPVIEW:

                        draw[i].set2Dplot(); if( i == 0 ) draw.setAxes( minx , maxx , miny , maxy );
                        draw[i+nc].set2Dplot(); if( done ) draw.setAxes( gp->Xev() );

                        break;
                    }

                }

                break;
            }

            break;

        case OUTPUT:

            for( unsigned i = 0 ; i < nc ; i++ )
            {
                draw[i].set2Dplot();
                draw[i+nc].set2Dplot();
            }

            if( gp->has_Yev() )
            {
                minx = 0 ; maxx = gp->n_ev() ;
                miny = gp->Yev().min() ; maxy = gp->Yev().max() ; hgt = ( maxy - miny ) / 10.0 ;

                draw[0].setAxes( minx , maxx , miny - hgt , maxy + hgt );
            }

            break;
        }

        for( unsigned i = 0 ; i < nc - 1 ; i++ )
        {
            draw[i].setTitle(mean[i]);
            draw[nc+i].setTitle(var[i]);
        }

        prepLML(nc-1); prepERR(nr*nc-1);

        break;

    case HALF:

        nr = 1 , nc = 2;

        draw.addWindow( title , ULHW( 0 , 0 ,
                        nr * gp->options.screen_height ,
                        nc * gp->options.screen_width  ) , nr , nc );

        prepLML(0); prepERR(1);

        break;

    case SINGLE:

        nr = 1 , nc = 1;

        draw.addWindow( title , ULHW( 0 , 0 ,
                        nr * gp->options.screen_height ,
                        nc * gp->options.screen_width  ) , nr , nc );

        prepLML(0);

        break;
    }
}

// Prepare LML
const void
DrawBase::prepLML( const unsigned& idx )
{
    draw[idx].set2Dplot().setTitle(nlml);
    if( done ) draw[idx].setAxes( lim_nlml , 0.0 , 0.1 );
}

// Prepare ERR
const void
DrawBase::prepERR( const unsigned& idx )
{
    switch( gp->options.error_metric )
    {
    case RMSE: draw[idx].set2Dplot().setTitle(rmse); break;
    case NLPD: draw[idx].set2Dplot().setTitle(nlpd); break;
    }
    if( done ) draw[idx].setAxes( lim_errs , 0.0 , 0.1 );
}

// Draw Text
const void
DrawBase::drawTXT( const unsigned& idx )
{
    draw[idx].flatten().clr(BLA);
    SStream ss; ss << "ITER : ";

    switch( gp->options.optimizer )
    {
    case NL_LBFGS: case NL_COBYLA: case NUMERIC: case GRADIENT:
        ss << gp->data.cnt_eval ; break;
    case MIN_NUMERIC: case MIN_GRADIENT:
        ss << gp->data.cnt_eval << "/" << gp->data.cnt_loop ; break;
    case STOCHASTIC:
        ss << gp->data.cnt_loop << "/" << gp->data.cnt_eval ; break;
    }

    double len = ss.str().length();

    if( draw.cScreen().type == PLOT_2D )
        draw.text( draw.cSbrd().w() * ( 1.03 - 0.02 * len ) ,
                   draw.cSbrd().h() * 0.05 , ss.str() );
    else
        if( draw.cScreen().type == PLOT_3D )
            draw.text( draw.cSbrd().w() * ( 0.95 - 0.02 * len ) ,
                       draw.cSbrd().h() * 0.06 , ss.str() );

    switch( gp->data.training )
    {
    case TRAINING: ss.str("TRAINING ..."); break;
    case   ENDING: ss.str(" ENDING ... "); break;
    case    ENDED: ss.str("   DONE!    "); break;
    }

    if( draw.cScreen().type == PLOT_2D )
        draw.text( draw.cSbrd().w() * 0.05 ,
                   draw.cSbrd().h() * 0.045 , ss.str() );
    else
        if( draw.cScreen().type == PLOT_3D )
            draw.text( draw.cSbrd().w() * 0.10 ,
                       draw.cSbrd().h() * 0.06 , ss.str() );
}

// Draw LML base
const void
DrawBase::drawLMLbase( const unsigned& idx )
{
    draw[idx].clear().clr(BLA);

    SStream ss;
    if( gp->data.lmls.n() == 0 )
        ss << "NLML : --- ";
    else ss << "NLML : " << std::fixed << std::setprecision(3) << gp->data.lmls[-1].y;

    double len = ss.str().length();
    if( !done) draw.setAxes( gp->data.lmls , 0.0 , 0.1 );
    draw.text2D( 1.00 - 0.02 * len , 0.06 , ss.str() );
}

// Draw LML
const void
DrawBase::drawLML( const unsigned& idx )
{
    drawLMLbase(idx);
    draw.axes().lwc(3,BLA).line2D( gp->data.lmls );
}

// Draw ERR base
const void
DrawBase::drawERRbase( const unsigned& idx )
{
    draw[idx].clear().clr(BLA);

    SStream ss;
    if( gp->data.errs.n() == 0 )
    {
        switch( gp->options.error_metric )
        {
        case NLPD: ss << "NLPD : --- "; break;
        case RMSE: ss << "RMSE : --- "; break;
        }
    }
    else
    {
        switch( gp->options.error_metric )
        {
        case NLPD: ss << "NLPD : " << std::fixed << std::setprecision(3) << gp->data.errs[-1].y; break;
        case RMSE: ss << "RMSE : " << std::fixed << std::setprecision(3) << gp->data.errs[-1].y; break;
        }
    }

    double len = ss.str().length();
    if( !done) draw.setAxes( gp->data.errs , 0.0 , 0.1 );
    draw.text2D( 1.00 - 0.02 * len , 0.06 , ss.str() );
}

// Draw ERR
const void
DrawBase::drawERR( const unsigned& idx )
{
    drawERRbase(idx);
    draw.axes().lwc(3,BLA).line2D( gp->data.errs );
}

// Prepare Buffers - Output
const void
DrawBase::prepBuffersOutput()
{
    buffers.resize(5);

    Xy.reset( gp->n_ev() ).setIncrease();
    if( gp->has_Yev() ) buffers[0] = draw.addBuffer2D( Xy , gp->Yev() );

    buffers[1] = draw.addBuffer2Dd( gp->n_ev() );
    buffers[2] = draw.addBuffer2Dd( gp->n_ev() );
    buffers[3] = draw.addBuffer2Dd( gp->n_ev() );
    buffers[4] = draw.addBuffer2Dd( gp->n_ev() );
}

// Update Screens - Output
const void
DrawBase::updateBuffersOutput()
{
}

// Improve Screens - Output
const void
DrawBase::improveBuffersOutput()
{
    draw.updBuffer2D( buffers[1] , Xy , gp->mf );
    draw.updBuffer2D( buffers[2] , Xy , gp->vf );

    draw.updBuffer2D( buffers[3] , Xy , gp->lvf() );
    draw.updBuffer2D( buffers[4] , Xy , gp->uvf() );
}

// Base Draw Screens - Output
const void
DrawBase::drawScreensOutput()
{
    draw[0].clear();

    if( gp->has_Yev() )
         draw.axes().lwc(3,BLA).line2D( buffers[0] );
    else draw.setAxes( buffers[1] ).axes();

    draw.lwc(3,RED).line2D( buffers[1] );

    draw.lwc(3,BLU).line2D( buffers[3] );
    draw.lwc(3,BLU).line2D( buffers[4] );

    draw[2].clear().setAxes( buffers[2] ).axes();
    draw.lwc(3,BLU).line2D( buffers[2] );
}

// Draw Screens Extras
const void
DrawBase::drawScreensExtras()
{
    switch( format )
    {
    case FULL:

        drawLML(nc-1);
        if( gp->has_Yev() ) drawERR(nr*nc-1);
        break;

    case HALF:

        drawLML(0);
        if( gp->has_Yev() ) drawERR(nr*nc-1);
        break;

    case SINGLE:

        drawLML(0);
        break;
    }

    if( !done ) drawTXT(0);

    draw.updateWindow();
}

// Prepare Buffers
const void
DrawBase::prepBuffers()
{
    if( format == FULL )
    {
        switch( gp->options.draw_type )
        {
        case INPUT:

            switch( gp->d_in() )
            {
            case 1: prepBuffersInput2D(); break;
            case 2: prepBuffersInput3D(); break;
            }
            break;

        case OUTPUT:

            prepBuffersOutput();
            break;
        }
    }
}

// Update Screens
const void
DrawBase::updateBuffers()
{
    if( format == FULL )
    {
        switch( gp->options.draw_type )
        {
        case INPUT:

            switch( gp->d_in() )
            {
            case 1: updateBuffersInput2D(); break;
            case 2: updateBuffersInput3D(); break;
            }
            break;

        case OUTPUT:

            updateBuffersOutput();
            break;
        }
    }
}

// Improve Screens
const void
DrawBase::improveBuffers()
{
    if( format == FULL )
    {
        switch( gp->options.draw_type )
        {
        case INPUT:

            switch( gp->Xev().c() )
            {
            case 1: improveBuffersInput2D(); break;
            case 2: improveBuffersInput3D(); break;
            }
            break;

        case OUTPUT:

            improveBuffersOutput();
            break;
        }
    }
}

// Draw Screens
const void
DrawBase::drawScreens()
{
    if( format == FULL )
    {
        switch( gp->options.draw_type )
        {
        case INPUT:

            switch( gp->d_in() )
            {
            case 1: drawScreensInput2D(); break;
            case 2: drawScreensInput3D(); break;
            }
            break;

        case OUTPUT:

            drawScreensOutput();
            break;
        }
    }
    drawScreensExtras();
}

}
