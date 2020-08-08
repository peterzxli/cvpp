#ifndef BORDERS3_H
#define BORDERS3_H

#include <cvpp/containers/vector.h>

namespace cvpp
{

TPL_T
class Borders3
{

protected:

    Pts3<T> pts;

public:

    Borders3()
    {
        pts.reset( 4 );
    }

    Borders3( const Borders3<T>& brd ) : Borders3()
    {
        *this = brd;
    }

    Borders3& operator=( const Borders3& brd )
    {
        this->pts = brd.pts;
        return *this;
    }

    Borders3& operator>>( const Borders3& brd )
    {
        this->pts >> brd.pts;
        return *this;
    }

    Borders3& operator=( const Pts3<T>& pts )
    {
        this->pts = pts;
        return *this;
    }

    Borders3& operator>>( const Pts3<T>& pts )
    {
        this->pts >> pts;
        return *this;
    }

    void print() const { pts.print(); }
    void info() const { pts.info(); }

    Pt3<T>& operator[]( const int& idx ) { return pts[idx]; }
    const Pt3<T>& operator[]( const int& idx ) const { return pts[idx]; }

    Pt3<T>& at( const int& idx ) { return pts[idx]; }
    const Pt3<T>& at( const int& idx ) const { return pts[idx]; }

    Pts3<T>& points() { return pts; }
    const Pts3<T>& points() const { return pts; }

    Matrix<T>& mat() { return pts.mat(); }
    const Matrix<T>& mat() const { return pts.mat(); }

    Pt3<T>& lu() { return pts[0]; }
    const Pt3<T>& lu() const { return pts[0]; }

    Pt3<T>& ld() { return pts[1]; }
    const Pt3<T>& ld() const { return pts[1]; }

    Pt3<T>& rd() { return pts[2]; }
    const Pt3<T>& rd() const { return pts[2]; }

    Pt3<T>& ru() { return pts[3]; }
    const Pt3<T>& ru() const { return pts[3]; }

};

using Borders3i = Borders3<int>;
using Borders3f = Borders3<float>;
using Borders3d = Borders3<double>;

}

#endif
