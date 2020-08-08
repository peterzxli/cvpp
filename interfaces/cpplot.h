#ifndef CPPLOT_H
#define CPPLOT_H

#define GL_GLEXT_PROTOTYPES

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#ifdef CUDA_FOUND

#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#endif

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/macros.h>

#include <cvpp/objects/object.h>
#include <cvpp/objects/object_world.h>

#include <cvpp/structs/struct_buffer.h>
#include <cvpp/structs/struct_texture.h>
#include <cvpp/structs/struct_keyboard.h>
#include <cvpp/structs/struct_data_type.h>

#include <cvpp/structs/struct_screen.h>
#include <cvpp/structs/struct_window.h>
#include <cvpp/structs/struct_borders3.h>

#include <cvpp/containers/image.h>
#include <cvpp/algorithms/kdtree/kdtree.h>

#include <cvpp/auxiliar/definitions/definitions_cpplot.h>

namespace cvpp
{

class CPPlot
{

protected:

    int fW,fS,cW,cS;
    int idxBuffer,idxTexture;

    void *fontT,*fontM,*fontS;
    GLUquadric *quad;

    Seq<Window> windows;
    SDL_Event event;

    Seq<Buffer> buffers;
    Seq<Texture> textures;

    Pt2f coord,dcoord;
    bool selecting;

    #ifdef CUDA_FOUND
    cudaGraphicsResource* resources[1];
    #endif

public:

    Keyboard keys;

public:

    CPPlot();
    ~CPPlot();

    CPPlot( const String& , const Borders2f& = ULHW( 0 , 0 , 600 , 800 ) ,
            const int& = 1 , const int& = 1 );

    CPPlot( const String& str , const int& r , const int& c = 1 )
        : CPPlot( str , ULHW( 0 , 0 , 600 * r , 800 * c ) , r , c ) {}

    // INPUT

    const bool input();

    Pt2f coordPlot2D( const float& , const float& );
    Pt2f coordImage2D( const float& , const float& );

    void trimImageBoundary();

    const bool control( Posef& , const float& = 0.1 , const float& = 2.0 );
    const bool control( Object& obj , const float& v = 0.1 , const float& w = 2.0 ) { return control( obj.pose , v , w ); }
    const bool control( Pointer<Posef>& ptr , const float& v = 0.1 , const float& w = 2.0 ) { return control( *ptr , v , w ); }

    const bool hasFocus() const { return fW >= 0 && fS >= 0; }

    bool& mouseL() { return fWindow().mouseL; }
    bool& mouseR() { return fWindow().mouseR; }
    bool& mouseM() { return fWindow().mouseM; }

    Eig2f& mouseLd() { return fWindow().mouseLd; }
    Eig2f& mouseRd() { return fWindow().mouseRd; }

    Eig2f& mouseLp() { return fWindow().mouseLp; }
    Eig2f& mouseRp() { return fWindow().mouseRp; }

    float& mouseLd( const int& n ) { return fWindow().mouseLd(n); }
    float& mouseRd( const int& n ) { return fWindow().mouseRd(n); }

    float& mouseLp( const int& n ) { return fWindow().mouseLp(n); }
    float& mouseRp( const int& n ) { return fWindow().mouseRp(n); }

//    Pt2f mousePos() const { return Pt2f( coord.y , coord.x ); }
    const Pt2f& mousePos() const { return coord; }

    const bool selectLU( Borders2d& );
    const bool selectXY( Borders2d& );

    // DRAW

    void vertex( const Pt2i& pt ) const { glVertex2i( pt.x , pt.y ); }
    void vertex( const Pt2f& pt ) const { glVertex2f( pt.x , pt.y ); }
    void vertex( const Pt2d& pt ) const { glVertex2d( pt.x , pt.y ); }
    void vertex( const float& x ,const float& y ) const { glVertex2f( x , y ); }

    void vertex( const Pt3i& pt ) const { glVertex3i( pt.x , pt.y , pt.z ); }
    void vertex( const Pt3f& pt ) const { glVertex3f( pt.x , pt.y , pt.z ); }
    void vertex( const Pt3d& pt ) const { glVertex3d( pt.x , pt.y , pt.z ); }
    void vertex( const float& x ,const float& y , const float& z ) const { glVertex3f( x , y , z ); }

    void vertex( const Matrix<int>&    mat ) const { glVertex3i( mat(0) , mat(1) , mat(2) ); }
    void vertex( const Matrix<float>&  mat ) const { glVertex3f( mat(0) , mat(1) , mat(2) ); }
    void vertex( const Matrix<double>& mat ) const { glVertex3d( mat(0) , mat(1) , mat(2) ); }

    void vertex2D( const float& x , const float& y ) { vertex( cSres().l() + x * cSres().w() ,
                                                                     cSres().u() + y * cSres().h() ); }

    CPPlot& ps( const int& s ) { glPointSize( s ); return *this; }
    CPPlot& pointSize( const int& s ) { glPointSize( s ); return *this; }

    CPPlot& lw( const int& w ) { glLineWidth( w ); return *this; }
    CPPlot& lineWidth( const int& w ) { glLineWidth( w ); return *this; }

    CPPlot& color( const Scalar& rgb , const double& alpha = 1.0 )
    { glColor4d( rgb[0] , rgb[1] , rgb[2] , alpha ); return *this; }

    CPPlot& clr( const Scalar& rgb , const double& alpha = 1.0 )
    { glColor4d( rgb[0] , rgb[1] , rgb[2] , alpha ); return *this; }

    CPPlot& color( const int& i , const double& alpha = 1.0 ) { return color( RGBint(i) , alpha ); }
    CPPlot& clr(   const int& i , const double& alpha = 1.0 ) { return clr(   RGBint(i) , alpha ); }

    CPPlot& psc( const int& s , const Scalar& rgb , const double& alpha = 1.0 )
    { glPointSize(s); glColor4d(rgb[0],rgb[1],rgb[2],alpha); return *this; }

    CPPlot& lwc( const int& w , const Scalar& rgb , const double& alpha = 1.0 )
    { glLineWidth(w); glColor4d(rgb[0],rgb[1],rgb[2],alpha); return *this; }

    CPPlot& psc( const int& s , const int& i , const double& alpha = 1.0 ) { return psc( s , RGBint(i) , alpha ); }
    CPPlot& lwc( const int& s , const int& i , const double& alpha = 1.0 ) { return lwc( s , RGBint(i) , alpha ); }

    CPPlot& object( const Object& obj ) { if( obj.started() ) obj.draw( *this ); return *this; }
    CPPlot& object( const Object* obj ) { return object( *obj ); }

    TPL_T CPPlot& object( const Seq<T>&  objs ) { forLOOPi( objs.size() ) object( objs[i] ); return *this;  }
    TPL_T CPPlot& object( const Seq<T*>& objs ) { forLOOPi( objs.size() ) object( objs[i] ); return *this;  }

    CPPlot& object( const World& wld )
    { for( unsigned i = 0 ; i < wld.qtyObjects() ; i++ ) object( wld[i] ); return *this; }

    CPPlot& object( const Object& obj , const World& world )
    { if( obj.started() ) obj.draw( *this , world ); return *this; }

    void prepareText();

    void text( const double& , const double& , String , const int& = LEFT ) const;
    void text( const double& , const double& , const double& , String , const int& = LEFT ) const;

    void text2D( const double& , const double& , String , const int& = LEFT ) const;
    void textFlat( const double& , const double& , String , const int& = LEFT ) const;

    void storeColor( Img3c& ) const;
    Img3c storeColor3C() const { Img3c img; storeColor( img ); return img; }

    void storeColor( Img1c& ) const;
    Img1c storeColor1C() const { Img1c img; storeColor( img ); return img; }

    void storeColor( Matf& ) const;
    Matf storeColor() const { Matf mat; storeColor( mat ); return mat; }

    void storeDepth( Matf& ) const;
    Img1f storeDepth() const { Matf img; storeDepth( img ); return img; }

    void save( const String& str ) const { cv::imwrite( str , storeColor3C().cv() ); }

    // DRAW 1D

    TPL_T CPPlot& ellipse1D( const T& , const T& , const T& y );
    TPL_T CPPlot& ellipse1D( const Matrix<T>& , const Matrix<T>& , const Matrix<T>& y );

    // DRAW 2D

    TPL_T CPPlot& pt2D( const Pt2<T>& );
    TPL_T CPPlot& pt2D( const Pt3<T>& );
    TPL_T CPPlot& pt2D( const T& x , const T& y )
    { return pt2D( Pt2<T>( x , y ) ); }

    TPL_T CPPlot& line2D( const Pt2<T>& , const Pt2<T>& );
    TPL_T CPPlot& line2D( const T& x1 , const T& y1 ,
                          const T& x2 , const T& y2 ) { return pt2D( Pt2<T>( x1 , y1 ) ,
                                                                     Pt2<T>( x2 , y2 ) ); }

    TPL_T CPPlot& quad2D( const Pt2<T>& , const Pt2<T>& );
    TPL_TU CPPlot& quad2D( const Pt2<T>& pt , const U& h , const U& w )
    { return quad2D( pt , Pt2<T>( pt.x + h , pt.y + w ) ); }
    TPL_TCU CPPlot& quad2D( const Pt2<T>& pt , const Image<U,C>& img )
    { return quad2D( pt , Pt2<T>( pt.x + img.c() , pt.y + img.r() ) ); }
    TPL_TCU CPPlot& quad2D( const Pts2<T>& pts , const Image<U,C>& img )
    { forLOOPi( pts.n() ) quad2D( pts[i] , Pt2<T>( pts[i].x + img.c() , pts[i].y + img.r() ) ); return *this; }

    TPL_T CPPlot& pts2D( const Matrix<T>& );
    TPL_T CPPlot& pts2Dc( const Matrix<T>& , const Matrix<float>& );

    TPL_T CPPlot& pts2D( const Pts2<T>& pts , const Pts3<float>& clr ) { return pts2Dc( pts.mat() , clr.mat() ); }
    TPL_T CPPlot& pts2D( const Pts2<T>& pts , const Matrix<float>& clr ) { return pts2Dc( pts.mat() , clr ); }

    TPL_T CPPlot& pts2D( const Pts2<T>& pts ) { return pts2D( pts.mat() ); }
    TPL_T CPPlot& pts2D( const Vec<T>& pts1 , const Vec<T>& pts2 ) { return pts2D( pts1.mat().appR( pts2.mat() ) ); }

    TPL_T CPPlot& pts2D( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
    { if( mat1.c() + mat2.c() == 2 ) return pts2D( mat1.appR( mat2 ) ); else return pts2D( mat1 , mat2); }

    TPL_T CPPlot& line2D( const Matrix<T>& );
    TPL_T CPPlot& line2D( const Pts2<T>& pts ) { return line2D( pts.mat() ); }
    TPL_T CPPlot& line2D( const Matrix<T>& mat1 ,
                          const Matrix<T>& mat2 ) { return line2D( mat1.appR(mat2) ); }
    TPL_T CPPlot& line2D( const Vector<T,T,1>& vec1 ,
                          const Vector<T,T,1>& vec2 ) { return line2D( vec1.mat() , vec2.mat() ); }

    TPL_T CPPlot& loop2D( const Matrix<T>& );
    TPL_T CPPlot& loop2D( const Pts2<T>& pts ) { return loop2D( pts.mat() ); }
    TPL_T CPPlot& loop2D( const Borders2<T>& brd ) { return loop2D( brd.points() ); }
    TPL_T CPPlot& loop2D( const Matrix<T>& mat1 ,
                          const Matrix<T>& mat2 ) { return loop2D( mat1.appR(mat2) ); }
    TPL_T CPPlot& loop2D( const Vector<T,T,1>& vec1 ,
                          const Vector<T,T,1>& vec2 ) { return loop2D( vec1.mat() , vec2.mat() ); }

    TPL_T CPPlot& brd2D( const Borders2<T>& brd )
    { return brd.started() ? loop2D( brd.points() ).line2D( brd[0] , brd[2] ).line2D( brd[1] , brd[3] ) : *this; }

    TPL_T CPPlot& cct2D( const Pts2<T>& , const Pts2<T>& );
    TPL_T CPPlot& cct2D( const int& , const Pts2<T>& ,
                         const int& , const Pts2<T>& );

    TPL_T CPPlot& rect2D( const Rect2<T>& );
    TPL_T CPPlot& rect2D( const Seq<Rect2<T>>& seq ) { forLOOPi( seq.size() ) rect2D( seq[i] ); return *this; }

    CPPlot& ellipse2D( const Matrix<float>& , const Matrix<float>& );
    CPPlot& ellipse2D( const Matrix<double>& , const Matrix<double>& );

    TPL_T CPPlot& ellipse2D( const Matrix<T>& , const Seq<Matrix<T>>& );
    TPL_T CPPlot& ellipse2D( const Seq<Matrix<T>>& , const Seq<Matrix<T>>& );

    CPPlot& epip2D( const CV& );

    // DRAW 3D

    TPL_T CPPlot& pt3D( const Pt2<T>& );
    TPL_T CPPlot& pt3D( const Pt3<T>& );
    TPL_T CPPlot& pt3D( const T& x , const T& y , const T& z )
    { return pt3D( Pt3<T>( x , y , z ) ); }

    TPL_T CPPlot& line3D( const Pt3<T>& , const Pt3<T>& );
    TPL_T CPPlot& line3D( const T& x1 , const T& y1 , const T& z1 ,
                          const T& x2 , const T& y2 , const T& z2 ) { return line3D( Pt3<T>( x1 , y1 , z1 ) ,
                                                                                     Pt3<T>( x2 , y2 , z2 ) ) ; }

    TPL_T CPPlot& pts3D( const Matrix<T>& );
    TPL_T CPPlot& pts3D( const Pts3<T>& pts ) { return pts3D( pts.mat() ); }
    TPL_T CPPlot& pts3D( const Matrix<T>& mat1 ,
                         const Matrix<T>& mat2 ) { return pts3D( mat1.appR(mat2) ); }

    TPL_T CPPlot& line3D( const Matrix<T>& );
    TPL_T CPPlot& line3D( const Pts3<T>& pts ) { return line3D( pts.mat() ); }
    TPL_T CPPlot& line3D( const Matrix<T>& mat1 ,
                          const Matrix<T>& mat2 ) { return line3D( mat1.appR(mat2) ); }
    TPL_T CPPlot& line3D( const Vector<T,T,1>& vec1 ,
                          const Vector<T,T,1>& vec2 ) { return line3D( vec1.mat() , vec2.mat() ); }

    TPL_T CPPlot& loop3D( const Matrix<T>& );
    TPL_T CPPlot& loop3D( const Pts3<T>& pts ) { return loop3D( pts.mat() ); }
    TPL_T CPPlot& loop3D( const Borders3<T>& brd ) { return loop3D( brd.points() ); }
    TPL_T CPPlot& loop3D( const Matrix<T>& mat1 ,
                          const Matrix<T>& mat2 ) { return loop3D( mat1.appR(mat2) ); }
    TPL_T CPPlot& loop3D( const Vector<T,T,1>& vec1 ,
                          const Vector<T,T,1>& vec2 ) { return loop3D( vec1.mat() , vec2.mat() ); }

    TPL_T CPPlot& cct3D( const Pt3<T>& , const Pts3<T>& );
    TPL_T CPPlot& cct3D( const Pts3<T>& pts ) { Pt3<T> org( 0 , 0 , 0 ); return cct3D( org , pts ); }

    TPL_T CPPlot& cct3D( const Pts3<T>& , const Pts3<T>& );
    TPL_T CPPlot& cct3D( const Borders3<T>& brd ) { return cct3D( brd.points() ); }

    CPPlot& ellipse3D( const Matrix<float>& , const Matrix<float>& );
    CPPlot& ellipse3D( const Matrix<double>& , const Matrix<double>& );

    TPL_T CPPlot& ellipse3D( const Seq<Matrix<T>>& , const Seq<Matrix<T>>& );

    // PLOT

    CPPlot& axes() { return axesBase().preparePlot(); }
    CPPlot& axes( const int& idx ) { return setAxes( idx ).axes(); }

    TPL_T CPPlot& axes( const Matrix<T>& mat , const float& px = 0.0 , const float& py = 0.0 , const float& pz = 0.0 ) { return setAxes( mat , px , py , pz ).axes(); }
    TPL_T CPPlot& axes( const Matrix<T>& mat1 , const Matrix<T>& mat2 , const float& px = 0.0 , const float& py = 0.0 , const float& pz = 0.0 ) { return setAxes( mat1 , mat2 , px , py , pz ).axes(); }

    TPL_T CPPlot& axes( const Pts2<T>& pts , const float& px = 0.0 , const float& py = 0.0 , const float& pz = 0.0 ) { return axes( pts.mat() , px , py , pz ); }
    TPL_T CPPlot& axes( const Pts3<T>& pts , const float& px = 0.0 , const float& py = 0.0 , const float& pz = 0.0 ) { return axes( pts.mat() , px , py , pz ); }

    CPPlot& axes( const float& pxi , const float& pxf , const float& pyi = 0.0 , const float& pyf = 0.0 , const float& pzi = 0.0 , const float& pzf = 0.0 )
    { return setAxes( pxi , pxf , pyi , pyf , pzi , pzf ).axes(); }

    CPPlot& axesBase();

    CPPlot& preparePlot();
//    CPPlot& preparePlot( const int& );

//    TPL_T CPPlot& preparePlot( const Matrix<T>& );
//    TPL_T CPPlot& preparePlot( const Pts2<T>& pts ) { return preparePlot( pts.mat() ); }
//    TPL_T CPPlot& preparePlot( const Pts3<T>& pts ) { return preparePlot( pts.mat() ); }

//    CPPlot& preparePlot( const float& , const float& ,
//                         const float& , const float& ,
//                         const float& , const float& );

    CPPlot& freeAxes();

    TPL_T CPPlot& setAxes( const Matrix<T>& , const float& = 0.0 , const float& = 0.0 , const float& = 0.0 );
    TPL_T CPPlot& setAxes( const Matrix<T>& , const Matrix<T>& , const float& = 0.0 , const float& = 0.0 , const float& = 0.0 );

    TPL_T CPPlot& setAxes( const Pts2<T>& pts , const float& px = 0.0 , const float& py = 0.0 , const float& pz = 0.0 ) { return setAxes( pts.mat() , px , py , pz ); }
    TPL_T CPPlot& setAxes( const Pts3<T>& pts , const float& px = 0.0 , const float& py = 0.0 , const float& pz = 0.0 ) { return setAxes( pts.mat() , px , py , pz ); }

    CPPlot& setAxes( const float&       , const float&       ,
                     const float& = 0.0 , const float& = 0.0 ,
                     const float& = 0.0 , const float& = 0.0 );

    CPPlot& setAxes( const int& idx );

    TPL_T CPPlot& setAxisX( const T& , const T& );
    TPL_T CPPlot& setAxisY( const T& , const T& );
    TPL_T CPPlot& setAxisZ( const T& , const T& );

    TPL_T CPPlot& setAxisX( const Matrix<T>& mat , const T& pad ) { return setAxisX( mat.min() - pad , mat.max() + pad ); }
    TPL_T CPPlot& setAxisY( const Matrix<T>& mat , const T& pad ) { return setAxisY( mat.min() - pad , mat.max() + pad ); }
    TPL_T CPPlot& setAxisZ( const Matrix<T>& mat , const T& pad ) { return setAxisZ( mat.min() - pad , mat.max() + pad ); }

    CPPlot& setTickX( const int& n ) { cScreen().nTickX = n; }
    CPPlot& setTickY( const int& n ) { cScreen().nTickY = n; }
    CPPlot& setTickZ( const int& n ) { cScreen().nTickZ = n; }

    CPPlot& setTicks( const int& nx , const int& ny , const int& nz )
    { cScreen().nTickX = nx; cScreen().nTickY = ny; cScreen().nTickZ = nz; }

    // CUDA

    float* cudaPointer( const int& );

    // BUFFER

    const bool hasBuffer() const { return idxBuffer >= 0; }

    Buffer& cBuffer() { return buffers[idxBuffer]; }
    Buffer& buffer( const int& idx ) { return buffers[idx]; }

    CPPlot& bindBuffer( const int& );
    CPPlot& unbindBuffer();

    // BUFFER_ADD

    const int addBuffer();

    TPL_T const int addBuffer( const Matrix<T>& mat )
    { return mat.c() == 2 ? addBuffer2D( mat ) : addBuffer3D( mat ); }

    TPL_T const int addBuffer( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
    { return mat1.c() + mat2.c() == 2 ? addBuffer2D( mat1 , mat2 ) : addBuffer3D( mat1 , mat2 ); }

    TPL_T const int addBuffer2D( const int& );
    TPL_T const int addBuffer3D( const int& );

    const int addBuffer2Di( const int& idx ) { return addBuffer2D<int>(    idx ); }
    const int addBuffer2Df( const int& idx ) { return addBuffer2D<float>(  idx ); }
    const int addBuffer2Dd( const int& idx ) { return addBuffer2D<double>( idx ); }

    const int addBuffer3Di( const int& idx ) { return addBuffer3D<int>(    idx ); }
    const int addBuffer3Df( const int& idx ) { return addBuffer3D<float>(  idx ); }
    const int addBuffer3Dd( const int& idx ) { return addBuffer3D<double>( idx ); }

    TPL_T const int addBuffer2D( const Matrix<T>& );
    TPL_T const int addBuffer2D( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
    { return addBuffer2D( mat1.appR(mat2) ); }

    TPL_T const int addBuffer3D( const Matrix<T>& );
    TPL_T const int addBuffer3D( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
    { return addBuffer3D( mat1.appR(mat2) ); }

    TPL_T const int addBuffer2D( const Pts2<T> pts ) { return addBuffer2D( pts.mat() ); }
    TPL_T const int addBuffer3D( const Pts3<T> pts ) { return addBuffer3D( pts.mat() ); }

    const int addBuffer2D( const KPts& kpts ) { Pts2f pts = kpts; return addBuffer2D( pts ); }

    const int addBufferIDXgrid( const int& , const int& );
    const int addBufferIDXgrid( const int& n ) { return addBufferIDXgrid( sqrt(n) , sqrt(n) ); }
    const int addBufferIDXgrid( const Dims& dims ) { return addBufferIDXgrid( dims.r , dims.c ); }
    TPL_T const int addBufferIDXgrid( const Matrix<T>& mat ) { return addBufferIDXgrid( mat.gridDims() ); }

    const int addBufferIDXtrid( const int& , const int& );
    const int addBufferIDXtrid( const int& n ) { return addBufferIDXtrid( sqrt(n) , sqrt(n) ); }
    const int addBufferIDXtrid( const Dims& dims ) { return addBufferIDXtrid( dims.r , dims.c ); }
    TPL_T const int addBufferIDXtrid( const Matrix<T>& mat ) { return addBufferIDXtrid( mat.gridDims() ); }

    TPL_T const int addBufferRGBjet( const Matrix<T>& mat , const T& min , const T& max ) { return addBuffer3D( mat.toRGBjet( min , max ) ); }
    TPL_DTM const int addBufferRGBjet( const Vector<D,T,M>& vec , const T& min , const T& max ) { return addBufferRGBjet( vec.mat() , min , max ); }

    TPL_T const int addBufferRGBjet( const Matrix<T>& mat ) { return addBufferRGBjet( mat , mat.min() , mat.max() ); }
    TPL_DTM const int addBufferRGBjet( const Vector<D,T,M>& vec ) { return addBufferRGBjet( vec.mat() ); }

    TPL_T const int addBufferGRAYjet( const Matrix<T>& mat , const T& min , const T& max ) { return addBuffer3D( mat.toGRAYjet( min , max ) ); }
    TPL_DTM const int addBufferGRAYjet( const Vector<D,T,M>& vec , const T& min , const T& max ) { return addBufferGRAYjet( vec.mat() , min , max ); }

    TPL_T const int addBufferGRAYjet( const Matrix<T>& mat ) { return addBufferGRAYjet( mat , mat.min() , mat.max() ); }
    TPL_DTM const int addBufferGRAYjet( const Vector<D,T,M>& vec ) { return addBufferGRAYjet( vec.mat() ); }

    TPL_T const int addBufferRGBbnd( const Matrix<T>& mat , const T& val = 0.5 , const T& pad = 0.05 ) { return addBuffer3D( mat.toRGBbnd( val , pad ) ); }
    TPL_DTM const int addBufferRGBbnd( const Vector<D,T,M>& vec , const T& val = 0.5 , const T& pad = 0.05 ) { return addBufferRGBbnd( vec.mat() , val , pad ); }

    TPL_T const int addBufferRGBlbl( const Matrix<T>& mat ) { return addBuffer3D( mat.toRGBlbl() ); }
    TPL_DTM const int addBufferRGBlbl( const Vector<D,T,M>& vec ) { return addBufferRGBlbl( vec.mat() ); }

    TPL_T const int addBufferRGBknn( const Matrix<T>& , const Matrix<T>& , const Matrix<T>& );

    // BUFFER_SET

    TPL_T CPPlot& setBuffer2D( const int& , const int& );
    TPL_T CPPlot& setBuffer2D( const int& );

    TPL_T CPPlot& setBuffer3D( const int& , const int& );
    TPL_T CPPlot& setBuffer3D( const int& );

    TPL_T CPPlot& setBuffer2D( const int& , const Matrix<T>& );
    TPL_T CPPlot& setBuffer2D( const Matrix<T>& );

    TPL_T CPPlot& setBuffer3D( const int& , const Matrix<T>& );
    TPL_T CPPlot& setBuffer3D( const Matrix<T>& );

    CPPlot& setBufferIDXgrid( const int& , const int& );
    CPPlot& setBufferIDXgrid( const int& , const int& , const int& );

    CPPlot& setBufferIDXtrid( const int& , const int& );
    CPPlot& setBufferIDXtrid( const int& , const int& , const int& );

    TPL_T CPPlot& setBufferRGBknn( const int& , const Matrix<T>& , const Matrix<T>& , const Matrix<T>& );
    TPL_T CPPlot& setBufferRGBknn( const Matrix<T>& , const Matrix<T>& , const Matrix<T>& );

    // BUFFER_UPDATE

    TPL_T CPPlot& updBuffer2D( const int& , const Matrix<T>& , const int& = 0 );
    TPL_T CPPlot& updBuffer2D( const Matrix<T>& , const int& = 0 );

    TPL_T CPPlot& updBuffer2D( const int& idx , const Pts2<T>& pts , const int& off = 0 ) { return updBuffer2D( idx , pts.mat() , off ); }
    TPL_T CPPlot& updBuffer2D( const Pts2<T>& pts , const int& off = 0 ) { return updBuffer2D( pts.mat() , off ); }

    TPL_T CPPlot& updBuffer2D( const int& idx , const Matrix<T>& mat1 , const Matrix<T>& mat2 , const int& off = 0 )
    { return updBuffer2D( idx , mat1.appR(mat2) , off ); }

    TPL_T CPPlot& updBuffer3D( const int& , const Matrix<T>& , const int& = 0 );
    TPL_T CPPlot& updBuffer3D( const Matrix<T>& , const int& = 0 );

    TPL_T CPPlot& updBuffer3D( const int& idx , const Pts3<T>& pts , const int& off = 0 ) { return updBuffer3D( idx , pts.mat() , off ); }
    TPL_T CPPlot& updBuffer3D( const Pts3<T>& pts , const int& off = 0 ) { return updBuffer3D( pts.mat() , off ); }

    TPL_T CPPlot& updBuffer3D( const int& idx , const Matrix<T>& mat1 , const Matrix<T>& mat2 , const int& off = 0 )
    { return updBuffer3D( idx , mat1.appR(mat2) , off ); }

    TPL_T CPPlot& updBufferRGBjet( const int& idx , const Matrix<T>& mat , const T& min , const T& max , const int& off = 0 )
    { return updBuffer3D( idx , mat.toRGBjet( min , max ) , off ); }

    TPL_DTM CPPlot& updBufferRGBjet( const int& idx , const Vector<D,T,M>& vec , const T& min , const T& max , const int& off = 0 )
    { return updBufferRGBjet( idx , vec.mat() , min , max , off ); }

    TPL_T CPPlot& updBufferRGBjet( const int& idx , const Matrix<T>& mat , const int& off = 0 )
    { return updBufferRGBjet( idx , mat , mat.min() , mat.max() , off ); }

    TPL_DTM CPPlot& updBufferRGBjet( const int& idx , const Vector<D,T,M>& vec , const int& off = 0 )
    { return updBufferRGBjet( idx , vec.mat() , off ); }

    TPL_T CPPlot& updBufferRGBlbl( const int& idx , const Matrix<T>& mat , const int& off = 0 )
    { return updBuffer3D( idx , mat.toRGBlbl() , off ); }

    // BUFFER_DRAW

    CPPlot& pts2D( const int& , const int& = -1 );
    CPPlot& pts3D( const int& , const int& = -1 );

    CPPlot& pts( const int& idx , const int& clr = -1 ) { return buffer(idx).d == 2 ? pts2D( idx , clr ) : pts3D( idx , clr ); }

    CPPlot& line2D( const int& , const int& = -1 );
    CPPlot& line3D( const int& , const int& = -1 );

    CPPlot& line( const int& idx , const int& clr = -1 ) { return buffer(idx).d == 2 ? line2D( idx , clr ) : line3D( idx , clr ); }

    CPPlot& loop2D( const int& , const int& = -1 );
    CPPlot& loop3D( const int& , const int& = -1 );

    CPPlot& triang3D( const int& , const int& = -1 );

    CPPlot& grid2D( const int& , const int& , const int& = -1 );
    CPPlot& grid3D( const int& , const int& , const int& = -1 );

    CPPlot& trid2D( const int& , const int& , const int& = -1 );
    CPPlot& trid3D( const int& , const int& , const int& = -1 );

    CPPlot& gwire2D( const int& , const int& , const int& = -1 );
    CPPlot& gwire3D( const int& , const int& , const int& = -1 );

    CPPlot& twire2D( const int& , const int& , const int& = -1 );
    CPPlot& twire3D( const int& , const int& , const int& = -1 );

    CPPlot& wgrid2D( const int& xyz , const int& idx , const int& clr = -1 )
    { return grid2D( xyz , idx , clr ).lwc(2,BLA).gwire2D( xyz , idx ); }

    CPPlot& wgrid3D( const int& xyz , const int& idx , const int& clr = -1 )
    { return grid3D( xyz , idx , clr ).lwc(2,BLA).gwire3D( xyz , idx ); }

    CPPlot& grid2D( const int& xyz , const int& idx , const int& clr , const bool& wire )
    { if( wire ) return wgrid2D( xyz , idx , clr ) ; else return grid2D( xyz , idx , clr ); }

    CPPlot& grid3D( const int& xyz , const int& idx , const int& clr , const bool& wire )
    { if( wire ) return wgrid3D( xyz , idx , clr ) ; else return grid3D( xyz , idx , clr ); }

    CPPlot& wtrid2D( const int& xyz , const int& idx , const int& clr = -1 )
    { return trid2D( xyz , idx , clr ).lwc(2,BLA).twire2D( xyz , idx ); }

    CPPlot& wtrid3D( const int& xyz , const int& idx , const int& clr = -1 )
    { return trid3D( xyz , idx , clr ).lwc(2,BLA).twire3D( xyz , idx ); }

    CPPlot& trid2D( const int& xyz , const int& idx , const int& clr , const bool& wire )
    { if( wire ) return wtrid2D( xyz , idx , clr ) ; else return trid2D( xyz , idx , clr ); }

    CPPlot& trid3D( const int& xyz , const int& idx , const int& clr , const bool& wire )
    { if( wire ) return wtrid3D( xyz , idx , clr ) ; else return trid3D( xyz , idx , clr ); }

    CPPlot& surf2D( const int& , const int& = -1 );
    CPPlot& surf3D( const int& , const int& = -1 );

    CPPlot& swire3D( const int& , const int& = -1 );

    CPPlot& wsurf3D( const int& xyz , const int& clr = -1 )
    { return surf3D( xyz , clr ).lwc(2,BLA).swire3D( xyz ); }

    CPPlot& shape( const int& , const int& , const int& ,
                   const int& , const int& , const int& );

    // TEXTURE

    const bool hasTexture() const { return this->idxTexture >= 0; }

    Texture& cTexture() { return textures[idxTexture]; }
    Texture& texture( const int& idx ) { return textures[idx]; }

    CPPlot& bindTexture( const int& );
    CPPlot& unbindTexture();

    const int addTexture();
    const int addTexture1U( const int& , const int& );
    const int addTexture3U( const int& , const int& );

    TPL_TC const int addTexture1U( const Image<T,C>& img ) { return addTexture1U( img.r() , img.c() ); }
    TPL_TC const int addTexture3U( const Image<T,C>& img ) { return addTexture3U( img.r() , img.c() ); }

    const int addTexture1U( const Dims& dims ) { return addTexture1U( dims.r , dims.c ); }
    const int addTexture3U( const Dims& dims ) { return addTexture3U( dims.r , dims.c ); }

    const int addTexture( const CV& cv ) { unsigned idx = addTexture(); setTexture( idx , cv ); return idx; }
    TPL_TC const int addTexture( const Image<T,C>& img ) { return addTexture( img.cv() ); }

    TPL_TC const Sequ addTexture( const Seq<Image<T,C>>& img )
    { Sequ tmp( img.size() ); forLOOPi( tmp.size() ) tmp[i] = addTexture( img[i] ); return tmp; }

    CPPlot& setTexture( const CV& );
    CPPlot& updTexture( const CV& );

    TPL_TC CPPlot& setTexture( const Image<T,C>& img ) { return setTexture( img.cv() ); }
    TPL_TC CPPlot& updTexture( const Image<T,C>& img ) { return updTexture( img.cv() ); }

    CPPlot& setTexture( const int& , const CV& );
    CPPlot& updTexture( const int& , const CV& );

    TPL_TC CPPlot& setTexture( const int& idx , const Image<T,C>& img ) { return setTexture( idx , img.cv() ); }
    TPL_TC CPPlot& updTexture( const int& idx , const Image<T,C>& img ) { return updTexture( idx , img.cv() ); }

    CPPlot& useTexture();
    CPPlot& useTexture( const int& tex )
    { return bindTexture( tex ).useTexture(); }

    CPPlot& useTexture( const Borders2f& , const float& = 0.0 );
    CPPlot& useTexture( const int& tex , const Borders2f& brd , const float& repeat = 0.0 )
    { return bindTexture( tex ).useTexture( brd , repeat ); }

    CPPlot& useTexture( const Borders3f& , const float& = 0.0 );
    CPPlot& useTexture( const int& tex , const Borders3f& brd , const float& repeat = 0.0 )
    { return bindTexture( tex ).useTexture( brd , repeat ); }

    CPPlot& useTexture( const int& , const CV& );
    TPL_TC CPPlot& useTexture( const int& tex , const Image<T,C>& img )
    { return useTexture( tex , img.cv() ); }

    // WINDOW

    const int nWindows()  const { return windows.size(); }
    const int ncScreens() const { return cWindow().screens.size(); }
    const int nfScreens() const { return cWindow().screens.size(); }

    Window& cWindow() { return windows[cW]; }
    const Window& cWindow() const { return windows[cW]; }

    Screen& cScreen() { return windows[cW].screens[cS]; }
    const Screen& cScreen() const { return windows[cW].screens[cS]; }

    Window& fWindow() { return windows[fW]; }
    const Window& fWindow() const { return windows[fW]; }

    Screen& fScreen() { return windows[fW].screens[fS]; }
    const Screen& fScreen() const { return windows[fW].screens[fS]; }

    Window& window( const int& i ) { return windows[i]; }
    const Window& window( const int& i ) const { return windows[i]; }

    Screen& screen( const int& j ) { return windows[cW].screens[j]; }
    const Screen& screen( const int& j ) const { return windows[cW].screens[j]; }

    Screen& screen( const int& i , const int& j ) { return windows[i].screens[j]; }
    const Screen& screen( const int& i , const int& j ) const { return windows[i].screens[j]; }

    Posef& viewer( const int& i ) { return *screen(i).viewer; }
    const Posef& viewer( const int& i ) const { return *screen(i).viewer; }

    Borders2f& res( const int& i ) { return screen(i).resolution; }
    const Borders2f& res( const int& i ) const { return screen(i).resolution; }

    Borders2f& brd( const int& i ) { return screen(i).borders; }
    const Borders2f& brd( const int& i ) const { return screen(i).borders; }

    Borders2f& cWbrd() { return cWindow().borders; }
    const Borders2f& cWbrd() const { return cWindow().borders; }

    Borders2f& fWbrd() { return fWindow().borders; }
    const Borders2f& fWbrd() const { return fWindow().borders; }

    Borders2f& cSbrd() { return cScreen().borders; }
    const Borders2f& cSbrd() const { return cScreen().borders; }

    Borders2f& fSbrd() { return fScreen().borders; }
    const Borders2f& fSbrd() const { return fScreen().borders; }

    Borders2f& cSres() { return cScreen().resolution; }
    const Borders2f& cSres() const { return cScreen().resolution; }

    Borders2f& fSres() { return fScreen().resolution; }
    const Borders2f& fSres() const { return fScreen().resolution; }

    Borders2f& cSores() { return cScreen().resoriginal; }
    const Borders2f& cSores() const { return cScreen().resoriginal; }

    Borders2f& fSores() { return fScreen().resoriginal; }
    const Borders2f& fSores() const { return fScreen().resoriginal; }

    Posef& cViewer() { return *cScreen().viewer; }
    const Posef& cViewer() const { return *cScreen().viewer; }

    Posef& fViewer() { return *fScreen().viewer; }
    const Posef& fViewer() const { return *fScreen().viewer; }

    Posef& cOViewer() { return cScreen().view_original; }
    const Posef& cOViewer() const { return cScreen().view_original; }

    Posef& fOViewer() { return fScreen().view_original; }
    const Posef& fOViewer() const { return fScreen().view_original; }

    Scalar& cBack() { return cScreen().background; }
    const Scalar& cBack() const { return cScreen().background; }

    CPPlot& setTitle( const String& title ) { cScreen().title = title; return *this; }
    CPPlot& setBorders( const Borders2f& brd ) { cScreen().borders = brd; return *this; }
    CPPlot& setBackground( const Scalar& back ) { cScreen().background = back; return *this; }

    CPPlot& setResolution( const float& h , const float& w )
    { cScreen().resolution.luwh( 0.0 , 0.0 , w , h ); cSores() = cSres(); return *this; }

    TPL_TC CPPlot& setResolution( const Image<T,C>& img ) { return setResolution( img.r() , img.c() ); }

    CPPlot& setViewer( const float& xi , const float& yi , const float& zi ,
                       const float& xf , const float& yf , const float& zf )
    { viewer(cS).setPos( xi , yi , zi ).setLook( xf , yf , zf ); cOViewer() = cViewer(); return *this; }

    CPPlot& setViewer( const float& xi , const float& yi , const float& zi )
    { return setViewer( xi , yi , zi , 0.0 , 0.0 , 0.0 ); }

    CPPlot& setViewer( Pointer< Posef >& pose )
    { screen(cS).viewer = pose; cOViewer() = cViewer(); return *this; }

    CPPlot& calibrate( const Matf& , const float& = 600 , const float& = 800 ,
                       const float& = 1e-3 , const float& = 1e4 );

    CPPlot& clear() { glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); return *this; }

    CPPlot& updateWindow() { SDL_GL_SwapWindow( cWindow().SDLpointer ); return *this; }
    CPPlot& updateWindow( const int& t ) { updateWindow(); halt( t ); return *this; }
    CPPlot& updateWindow( const int& t1 , const int& t2 ) { return updateWindow( std::max( 0 , t1 - t2 ) ); }

    CPPlot& rotate( const Posef& pose ) { glMultMatrixf( pose.Rt().t().eig_data() ); return *this; }
    CPPlot& rotate( const Pointer<Posef>& pose ) { return rotate( *pose ); }

    CPPlot& rotateX( const float& ang ) { glRotatef( ang , 1.0 , 0.0 , 0.0 );  return *this; }
    CPPlot& rotateY( const float& ang ) { glRotatef( ang , 0.0 , 1.0 , 0.0 );  return *this; }
    CPPlot& rotateZ( const float& ang ) { glRotatef( ang , 0.0 , 0.0 , 1.0 );  return *this; }

    CPPlot& pushMatrix() { glPushMatrix(); return *this; }
    CPPlot& popMatrix() { glPopMatrix(); return *this; }

    const int addWindow( const String& , const Borders2f& , const int& = 1 , const int& = 1 );
    const int addScreen( const Borders2f& , const Scalar& = WHITE );

    CPPlot& useWindow( const int& );
    CPPlot& useScreen( const int& );
    CPPlot& useScreen( const int& , const int& );

    CPPlot& operator()( const int& w , const int& s ) { return useScreen(w,s); }
    CPPlot& operator()( const int& w ) { return useWindow(w); }
    CPPlot& operator[]( const int& s ) { return useScreen(s); }

    CPPlot& set2Dimage();
    CPPlot& set3Dworld();
    CPPlot& set2Dplot();
    CPPlot& set3Dplot();

    CPPlot& flatten();
    CPPlot& allScreens();

    CPPlot& enableScissor( const float& , const float& ,
                           const float& , const float& );
    CPPlot& disableScissor();

};

}

#endif
