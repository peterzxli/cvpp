
#include <cvpp/interfaces/cpplot.h>

using namespace cvpp;

Matf color( const  Matd& Y )
{
    Matf C( Y.r() , 3 );

    #pragma omp parallel for
    forLOOPi( Y.r() )
    {
        if( Y(i) == 0 )
             C.row(i) << 0.0 , 1.0 , 0.0 ;
        else C.row(i) << 1.0 , 0.0 , 0.0 ;
    }

    return C;
}

int main( int argc , char* argv[] )
{
    String name = argv[1];

    int cnt;
    if( argc == 3 )
    {
         cnt = std::atoi( argv[2] );
    }
    else
    {
        Mati idx( name + "_cnt" );
        cnt = idx;
    }

    Matd X , XX( 0 , 3 ) , YY( 0 , 3 );
    if( cnt == -1 )
    {
        cnt++;
        XX.save( name + std::to_string( cnt ) + "_X" );
        YY.save( name + std::to_string( cnt ) + "_Y" );
    }
    else
    {
        XX.load( name + std::to_string( cnt ) + "_X" );
        YY.load( name + std::to_string( cnt ) + "_Y" );
    }

    Matd lim(2,3);
    if( cnt == 0 ) lim.setVal(0);
    else lim = XX.limRows();

    int cur = cnt;

    double px , py , pz , lx1 , lx2 , ly1 , ly2 , lz1 , lz2 , ax , az ;
    px = py = pz = 0.0 ; lx1 = lx2 = lz1 = lz2 = 0.5 ; ly1 = ly2 = 0.1 ; ax = az = 0.0 ;
    int dn = 200 , n = dn ;

    CPPlot draw("Window");
    draw[0].set3Dworld().setViewer( -10.0 , 10.0 , 10.0 );

    double dlin = 1.0 , dsize = 0.5 , dang = 15;
    bool change = true , occ = true;

    unsigned pts,clr;
    if( XX.r() > 0 )
    {
        pts = draw.addBuffer3D( XX );
        clr = draw.addBuffer3D( color( YY ) );
//        clr = draw.addBufferRGBjet( XX.c(2).clone() );
    }

    while( draw.input() )
    {
        dlin = draw.keys.lshift ? 0.1 : 1.0 ;

        if( draw.keys.up     ) { change = true; draw.keys.s ? ly1 += dsize : draw.keys.a ? ly2 -= dsize : py -= dlin ; }
        if( draw.keys.down   ) { change = true; draw.keys.s ? ly1 -= dsize : draw.keys.a ? ly2 += dsize : py += dlin ; }
        if( draw.keys.left   ) { change = true; draw.keys.s ? lx1 -= dsize : draw.keys.a ? lx2 += dsize : px += dlin ; }
        if( draw.keys.right  ) { change = true; draw.keys.s ? lx1 += dsize : draw.keys.a ? lx2 -= dsize : px -= dlin ; }
        if( draw.keys.rshift ) { change = true; draw.keys.s ? lz1 -= dsize : draw.keys.a ? lz2 += dsize : pz += dlin ; }
        if( draw.keys.rctrl  ) { change = true; draw.keys.s ? lz1 += dsize : draw.keys.a ? lz2 -= dsize : pz -= dlin ; }

        if( draw.keys.x ) { change = true; az += dang ; }
        if( draw.keys.z ) { change = true; az -= dang ; }
        if( draw.keys.c ) { change = true; ax += dang ; }
        if( draw.keys.v ) { change = true; ax -= dang ; }

        if( draw.keys.q )
        {
            if( cur > 0 )
            {
                cur--;
                XX.load( name + std::to_string( cur ) + "_X" );
                YY.load( name + std::to_string( cur ) + "_Y" );

                if( XX.r() > 0 ) pts = draw.addBuffer3D( XX );
                if( YY.r() > 0 ) clr = draw.addBuffer3D( color(YY) );
//                if( YY.r() > 0 ) clr = draw.addBufferRGBjet( XX.c(2).clone() );
            }
            if( cur == 0 ) lim.setVal(0); else lim = XX.limRows();
            halt(100);
        }

        if( draw.keys.w )
        {
            if( cur < cnt )
            {
                cur++;
                XX.load( name + std::to_string( cur ) + "_X" );
                YY.load( name + std::to_string( cur ) + "_Y" );

                pts = draw.addBuffer3D( XX );
                clr = draw.addBuffer3D( color(YY) );
//                clr = draw.addBufferRGBjet( XX.c(2).clone() );
            }
            if( cur == 0 ) lim.setVal(0); else lim = XX.limRows();
            halt(100);
        }

        if( draw.keys.d )
        {
            Mati idx,ins = MatXXi( XX.r() ).setIncrease();
            Matd XXX = XX.clone();

            idx = XXX.c(0).eqbiggerIDX( px - lx1 );
            ins.SampleRows( idx ); XXX.SampleRows( idx );
            idx = XXX.c(0).eqsmallerIDX( px + lx2 );
            ins.SampleRows( idx ); XXX.SampleRows( idx );
            idx = XXX.c(1).eqbiggerIDX( py - ly1 );
            ins.SampleRows( idx ); XXX.SampleRows( idx );
            idx = XXX.c(1).eqsmallerIDX( py + ly2 );
            ins.SampleRows( idx ); XXX.SampleRows( idx );
            idx = XXX.c(2).eqbiggerIDX( pz - lz1 );
            ins.SampleRows( idx ); XXX.SampleRows( idx );
            idx = XXX.c(2).eqsmallerIDX( pz + lz2 );
            ins.SampleRows( idx ); XXX.SampleRows( idx );

            if( !ins.empty() )
            {
                ins = ins.uniqueRows().SortRows();
                Mati out( XX.r() );

                int cnt = 0 , j = 0;
                forLOOPi( XX.r() )
                {
                    if( i != ins(j) )
                         out(cnt++) = i;
                    else j++;
                }
                out.KeepU( cnt );

                XX.SampleRows( out );
                YY.SampleRows( out );

                cur++; cnt = cur;
                XX.save( name + std::to_string( cur ) + "_X" );
                YY.save( name + std::to_string( cur ) + "_Y" );
                lim = XX.limRows();

                XX.save( name + "_X" );
                YY.save( name + "_Y" );

                Mati tmp(1); tmp = cnt;
                tmp.save( name + "_cnt" );

                if( XX.r() > 0 ) pts = draw.addBuffer3D( XX );
                if( YY.r() > 0 ) clr = draw.addBuffer3D( color(YY) );
//                if( YY.r() > 0 ) clr = draw.addBufferRGBjet( XX.c(2).clone() );
            }

            halt(100);
        }

        if( draw.keys.tab )
        {
            occ = !occ;
            halt(100);
        }

        if( change )
        {
            n = dn;
            if( abs( lx2 + lx1 ) >= 0.5 ) n *= ( lx2 + lx1 );
            if( abs( ly2 + ly1 ) >= 0.5 ) n *= ( ly2 + ly1 );
            if( abs( lz2 + lz1 ) >= 0.5 ) n *= ( lz2 + lz1 );

            X = MatWall3d( px - lx1 , px + lx2 ,
                           py - ly1 , py + ly2 ,
                           pz - lz1 , pz + lz2 , n );
            X.SpinZ( az ).SpinX( ax );

            change = false; halt(100);
        }

        if( draw.keys.enter )
        {
            if( XX.empty() ) XX = X;
            else XX |= X;

            cur++; cnt = cur;
            XX.save( name + std::to_string( cur ) + "_X" );
            lim = XX.limRows();

            YY |= MatXXd( X.r() ).setVal( occ ? 1 : 0 );
            YY.save( name + std::to_string( cur ) + "_Y" );

            XX.save( name + "_X" );
            YY.save( name + "_Y" );

            Mati idx(1); idx = cnt;
            idx.save( name + "_cnt" );

            pts = draw.addBuffer3D( XX );
            clr = draw.addBuffer3D( color(YY) );
//            clr = draw.addBufferRGBjet( XX.c(2).clone() );

            halt(100);
        }

        draw[0].clear();

        draw.psc(1,WHI).pts3D( X );
        if( XX.r() > 0 ) draw.psc(1,RED).pts3D( pts , clr );

        draw.flatten();
        draw.clr(YEL);

        draw.text2D( 0.02 , 0.95 , std::to_string( cur ) + " / " +
                                   std::to_string( cnt ) );

        draw.text2D( 0.02 , 0.90 , std::to_string( n ) + " : " +
                                   std::to_string( XX.r() ) );

        draw.text2D( 0.02 , 0.20 , "Pos. X : " + std::to_string( px ) + " : " +
                                                 std::to_string( lx1+lx2 ) );
        draw.text2D( 0.02 , 0.15 , "Pos. Y : " + std::to_string( py ) + " : " +
                                                 std::to_string( ly1+ly2 ) );
        draw.text2D( 0.02 , 0.10 , "Pos. Z : " + std::to_string( pz ) + " : " +
                                                 std::to_string( lz1+lz2 ) );
        draw.text2D( 0.02 , 0.05 , "Ang. XZ : " + std::to_string( ax ) + " : " +
                                                  std::to_string( az ) );

        draw.text2D( 0.60 , 0.15 , "Lim. X : " + std::to_string( std::floor( lim(0,0) ) ) + " : " +
                                                 std::to_string( std::ceil( lim(1,0) ) ) );
        draw.text2D( 0.60 , 0.10 , "Lim. Y : " + std::to_string( std::floor( lim(0,1) ) ) + " : " +
                                                 std::to_string( std::ceil( lim(1,1) ) ) );
        draw.text2D( 0.60 , 0.05 , "Lim. Z : " + std::to_string( std::floor( lim(0,2) ) ) + " : " +
                                                 std::to_string( std::ceil( lim(1,2) ) ) );

        draw.clr( occ ? RED : GRE );
        draw.text2D( 0.85 , 0.95 , occ ? "OCCUPIED" : "  FREE  " );

        draw.updateWindow(30);

    }

    return 0;
}
