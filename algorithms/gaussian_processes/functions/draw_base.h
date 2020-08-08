#ifndef GP_DRAW_BASE_H
#define GP_DRAW_BASE_H

#include <cvpp/auxiliar/definitions.h>

#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/gaussian_processes/models/base/gp_base_info.h>

namespace cvpp
{

class DrawBase
{

protected:

    bool done;
    Matd Yz,Xy,lim_nlml,lim_errs;
    unsigned format,nr,nc;

    InfoGP* gp;

    CPPlot draw;
    Veci buffers;

    String title,nlml,rmse,nlpd;
    String mean[10],var[10];

public:

    DrawBase();
    DrawBase( InfoGP* );

    const bool input() { return draw.input(); }

    const void setFormat();
    const void prepScreens( const bool& = false );

    virtual const void prepBuffers();
    virtual const void updateBuffers();
    virtual const void improveBuffers();
    virtual const void drawScreens();

    virtual const void prepLML( const unsigned& );
    virtual const void prepERR( const unsigned& );

    virtual const void loopLocal( const SeqPts2d& , const SeqPts2d& ) {}

    virtual const void drawLMLbase( const unsigned& );
    virtual const void drawERRbase( const unsigned& );

    virtual const void drawTXT( const unsigned& );
    virtual const void drawLML( const unsigned& );
    virtual const void drawERR( const unsigned& );

    virtual const void prepBuffersInput2D() {}
    virtual const void prepBuffersInput3D() {}
    virtual const void prepBuffersOutput();

    virtual const void updateBuffersInput2D() {}
    virtual const void updateBuffersInput3D() {}
    virtual const void updateBuffersOutput();

    virtual const void improveBuffersInput2D() {}
    virtual const void improveBuffersInput3D() {}
    virtual const void improveBuffersOutput();

    virtual const void drawScreensInput2D() {}
    virtual const void drawScreensInput3D() {}
    virtual const void drawScreensOutput();

    const void drawScreensExtras();

};

}

#endif
