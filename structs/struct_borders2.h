#ifndef BORDERS2_H
#define BORDERS2_H

#include <cvpp/containers/vector.h>
#include <cvpp/auxiliar/definitions/definitions_opencv.h>

namespace cvpp
{

TPL_T
class Borders2
{

protected:

    Pts2<T> pts;
    Eig2<T> hgt;

public:

    Borders2()
    {
        pts.resize( 4 );
        empty();
    }

    Borders2( const Borders2<T>& brd ) : Borders2()
    {
        *this = brd;
    }

    TPL_U
    Borders2<T>( const Rect2<U>& rect ) : Borders2()
    {
        *this = rect;
    }

    Borders2<T>& operator=( const Borders2<T>& brd )
    {
        this->pts = brd.pts;
        return *this;
    }

    Borders2<T>& operator>>( const Borders2<T>& brd )
    {
        this->pts >> brd.pts;
        return *this;
    }

    Borders2<T>& operator=( const Pts2<T>& pts )
    {
        this->pts = pts;
        return *this;
    }

    Borders2<T>& operator>>( const Pts2<T>& pts )
    {
        this->pts >> pts;
        return *this;
    }

    TPL_U
    Borders2<T>& operator=( const Rect2<U>& rect )
    {
        luwh( rect.x , rect.y , rect.width , rect.height );
        return *this;
    }

    void print() const { pts.print(); }
    void info() const { pts.info(); }

    const bool started() const { return l() > 0 && r() > 0; }
    void empty() { pts.mat().setVal( 0 ); }

    Rect2<T> rect() const { return Rect2<T>( l() , u() , w() , h() ); }

    Pt2<T>& operator[]( const int& idx ) { return pts[idx]; }
    const Pt2<T>& operator[]( const int& idx ) const { return pts[idx]; }

    Pt2<T>& at( const int& idx ) { return pts[idx]; }
    const Pt2<T>& at( const int& idx ) const { return pts[idx]; }

    Pts2<T>& points() { return pts; }
    const Pts2<T>& points() const { return pts; }

    const T& l() const { return pts[0].x; }
    const T& u() const { return pts[0].y; }
    const T& r() const { return pts[2].x; }
    const T& d() const { return pts[2].y; }

    const T& b() const { return hgt(0); }
    const T& t() const { return hgt(1); }
    const T  e() const { return t() - b(); }

    const T w() const { return ( pts[2].x - pts[0].x ); }
    const T h() const { return ( pts[2].y - pts[0].y ); }
    const T x() const { return ( pts[2].x + pts[0].x ) / 2.0; }
    const T y() const { return ( pts[2].y + pts[0].y ) / 2.0; }

    Pt2<T> xy() const { return Pt2f( x() , y() ); }

    Pt2<T>& lu() { return pts[0]; }
    const Pt2<T>& lu() const { return pts[0]; }

    Pt2<T>& ld() { return pts[1]; }
    const Pt2<T>& ld() const { return pts[1]; }

    Pt2<T>& rd() { return pts[2]; }
    const Pt2<T>& rd() const { return pts[2]; }

    Pt2<T>& ru() { return pts[3]; }
    const Pt2<T>& ru() const { return pts[3]; }

    const bool inside( const T& x , const T& y ) const
    {
        return x >= pts[0].x && x <= pts[2].x &&
               y >= pts[0].y && y <= pts[2].y ;
    }

    const bool inside( const Pt2<T>& pt ) const
    {
        return inside( pt.x , pt.y );
    }

    Borders2<T>& l( const T& l )
    {
        lu() = Pt2<T>( l , u() );
        ld() = Pt2<T>( l , d() );
        return *this;
    }

    Borders2<T>& u( const T& u )
    {
        lu() = Pt2<T>( l() , u );
        ru() = Pt2<T>( r() , u );
        return *this;
    }

    Borders2<T>& r( const T& r )
    {
        ru() = Pt2<T>( r , u() );
        rd() = Pt2<T>( r , d() );
        return *this;
    }

    Borders2<T>& d( const T& d )
    {
        ld() = Pt2<T>( l() , d );
        rd() = Pt2<T>( r() , d );
        return *this;
    }

    Borders2<T>& xywh( const T& x , const T& y ,
                       const T& w , const T& h )
    {
        T w2 = w / 2.0 , h2 = h / 2.0 ;
        lu() = Pt2<T>( x-w2 , y-h2 ) ; ld() = Pt2<T>( x-w2 , y+h2 );
        rd() = Pt2<T>( x+w2 , y+h2 ) ; ru() = Pt2<T>( x+w2 , y-h2 );
        return *this;
    }

    Borders2<T>& luwh( const T& l , const T& u ,
                       const T& w , const T& h )
    {
        lu() = Pt2<T>(  l  ,  u  ) ; ld() = Pt2<T>(  l  , u+h );
        rd() = Pt2<T>( l+w , u+h ) ; ru() = Pt2<T>( l+w ,  u  );
        return *this;
    }

    Borders2<T>& lurd( const T& l , const T& u ,
                       const T& r , const T& d )
    {
        lu() = Pt2<T>( l , u ) ; ld() = Pt2<T>( l , d ) ;
        rd() = Pt2<T>( r , d ) ; ru() = Pt2<T>( r , u ) ;
        return *this;
    }

    Borders2<T>& lu( const Pt2<T>& pt ) { return lu( pt.x , pt.y ); }
    Borders2<T>& lu( const T& l , const T& u )
    {
        lu() = Pt2<T>( l , u ) ; ld() = Pt2<T>( l , d() ) ; ru() = Pt2<T>( r() , u ) ;
        return *this;
    }

    Borders2<T>& rd( const Pt2<T>& pt ) { return rd( pt.x , pt.y ); }
    Borders2<T>& rd( const T& r , const T& d )
    {
        rd() = Pt2<T>( r , d ) ; ru() = Pt2<T>( r , u() ) ; ld() = Pt2<T>( l() , d ) ;
        return *this;
    }

    Borders2<T>& lr( const T& l , const T& r )
    {
        lu() = Pt2<T>( l , u() ) ; ld() = Pt2<T>( l , d() ) ;
        rd() = Pt2<T>( r , d() ) ; ru() = Pt2<T>( r , u() ) ;
        return *this;
    }

    Borders2<T>& ud( const T& u , const T& d )
    {
        lu() = Pt2<T>( l() , u ) ; ld() = Pt2<T>( l() , d ) ;
        rd() = Pt2<T>( r() , d ) ; ru() = Pt2<T>( r() , u ) ;
        return *this;
    }

    Borders2<T>& bt( const T& b , const T& t )
    {
        hgt << b , t;
        return *this;
    }

};

using Borders2i = Borders2<int>;
using Borders2f = Borders2<float>;
using Borders2d = Borders2<double>;

}

#endif
