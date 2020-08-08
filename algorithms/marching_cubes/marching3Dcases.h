
#include "./marching3D.h"

namespace cvpp
{

double s3x,s3y,s3z;
double p1,p2,p3,p4,p5,p6,p7,p8;

inline Pt3d A() { return Pt3d(  0  ,  0  , s3z*std::fabs(p1/(p1-p2)) ); }
inline Pt3d B() { return Pt3d(  0  , s3y*std::fabs(p2/(p2-p3)) , s3z ); }
inline Pt3d C() { return Pt3d(  0  , s3y , s3z*std::fabs(p4/(p4-p3)) ); }
inline Pt3d D() { return Pt3d(  0  , s3y*std::fabs(p1/(p1-p4))  , 0  ); }
inline Pt3d E() { return Pt3d( s3x ,  0  , s3z*std::fabs(p5/(p5-p6)) ); }
inline Pt3d F() { return Pt3d( s3x , s3y*std::fabs(p6/(p6-p7)) , s3z ); }
inline Pt3d G() { return Pt3d( s3x , s3y , s3z*std::fabs(p8/(p8-p7)) ); }
inline Pt3d H() { return Pt3d( s3x , s3y*std::fabs(p5/(p5-p8)) ,  0  ); }
inline Pt3d I() { return Pt3d( s3x*std::fabs(p1/(p1-p5)) ,  0  ,  0  ); }
inline Pt3d J() { return Pt3d( s3x*std::fabs(p2/(p2-p6)) ,  0  , s3z ); }
inline Pt3d K() { return Pt3d( s3x*std::fabs(p3/(p3-p7)) , s3y , s3z ); }
inline Pt3d L() { return Pt3d( s3x*std::fabs(p4/(p4-p8)) , s3y ,  0  ); }

TPL_T inline void
marching3Dcases( const unsigned& binary , const Pt3<T>& org , Pts3<T>& pts )
{
    switch( binary )
    {

    // 1A VERTICES

    case 1   : // 1
        pts.push( org + A() ).push( org + D() ).push( org + I() ); break;
    case 2   : // 2
        pts.push( org + A() ).push( org + J() ).push( org + B() ); break;
    case 4   : // 4
        pts.push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 8   : // 8
        pts.push( org + C() ).push( org + D() ).push( org + L() ); break;
    case 16  : // 16
        pts.push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 32  : // 32
        pts.push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 64  : // 64
        pts.push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 128 : // 128
        pts.push( org + L() ).push( org + G() ).push( org + H() ); break;

    // 7A VERTICES

    case 254 : // 2 + 4 + 8 + 16 + 32 + 64 + 128
        pts.push( org + A() ).push( org + D() ).push( org + I() ); break;
    case 253 : // 1 + 4 + 8 + 16 + 32 + 64 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() ); break;
    case 251 : // 1 + 2 + 8 + 16 + 32 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 247 : // 1 + 2 + 4 + 16 + 32 + 64 + 128
        pts.push( org + C() ).push( org + D() ).push( org + L() ); break;
    case 239 : // 1 + 2 + 4 + 8 + 32 + 64 + 128
        pts.push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 223 : // 1 + 2 + 4 + 8 + 16 + 64 + 128
        pts.push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 191 : // 1 + 2 + 4 + 8 + 16 + 32 + 128
        pts.push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 127 : // 1 + 2 + 4 + 8 + 16 + 32 + 64
        pts.push( org + L() ).push( org + G() ).push( org + H() ); break;

    // 2A VERTICES

    case 3   : // 1 + 2
        pts.push( org + I() ).push( org + J() ).push( org + B() )
           .push( org + B() ).push( org + D() ).push( org + I() ); break;
    case 12  : // 4 + 8
        pts.push( org + B() ).push( org + K() ).push( org + L() )
           .push( org + L() ).push( org + D() ).push( org + B() ); break;
    case 192 : // 64 + 128
        pts.push( org + K() ).push( org + F() ).push( org + H() )
           .push( org + H() ).push( org + L() ).push( org + K() ); break;
    case 48  : // 16 + 32
        pts.push( org + F() ).push( org + J() ).push( org + I() )
           .push( org + I() ).push( org + H() ).push( org + F() ); break;
    case 6   : // 2 + 4
        pts.push( org + A() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + C() ).push( org + A() ); break;
    case 9   : // 1 + 8
        pts.push( org + A() ).push( org + C() ).push( org + L() )
           .push( org + L() ).push( org + I() ).push( org + A() ); break;
    case 144 : // 16 + 128
        pts.push( org + E() ).push( org + I() ).push( org + L() )
           .push( org + L() ).push( org + G() ).push( org + E() ); break;
    case 96  : // 32 + 64
        pts.push( org + K() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + G() ).push( org + K() ); break;
    case 34  : // 2 + 32
        pts.push( org + B() ).push( org + A() ).push( org + E() )
           .push( org + E() ).push( org + F() ).push( org + B() ); break;
    case 68  : // 4 + 64
        pts.push( org + B() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + B() ); break;
    case 136 : // 8 + 128
        pts.push( org + C() ).push( org + G() ).push( org + H() )
           .push( org + H() ).push( org + D() ).push( org + C() ); break;
    case 17  : // 1 + 16
        pts.push( org + A() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + E() ).push( org + A() ); break;

    // 6A VERTICES

    case 252 : // 4 + 8 + 16 + 32 + 64 + 128
        pts.push( org + I() ).push( org + J() ).push( org + B() )
           .push( org + B() ).push( org + D() ).push( org + I() ); break;
    case 243 : // 1 + 2 + 16 + 32 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + L() )
           .push( org + L() ).push( org + D() ).push( org + B() ); break;
    case 63  : // 1 + 2 + 4 + 8 + 16 + 32
        pts.push( org + K() ).push( org + F() ).push( org + H() )
           .push( org + H() ).push( org + L() ).push( org + K() ); break;
    case 207 : // 1 + 2 + 4 + 8 + 64 + 128
        pts.push( org + F() ).push( org + J() ).push( org + I() )
           .push( org + I() ).push( org + H() ).push( org + F() ); break;
    case 249 : // 1 + 8 + 16 + 32 + 64 + 128
        pts.push( org + A() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + C() ).push( org + A() ); break;
    case 246 : // 2 + 4 + 16 + 32 + 64 + 128
        pts.push( org + A() ).push( org + C() ).push( org + L() )
           .push( org + L() ).push( org + I() ).push( org + A() ); break;
    case 111 : // 1 + 2 + 4 + 8 + 32 + 64
        pts.push( org + E() ).push( org + I() ).push( org + L() )
           .push( org + L() ).push( org + G() ).push( org + E() ); break;
    case 159 : // 1 + 2 + 4 + 8 + 16 + 128
        pts.push( org + K() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + G() ).push( org + K() ); break;
    case 221 : // 1 + 4 + 8 + 16 + 64 + 128
        pts.push( org + B() ).push( org + A() ).push( org + E() )
           .push( org + E() ).push( org + F() ).push( org + B() ); break;
    case 187: // 1 + 2 + 8 + 16 + 32 + 128
        pts.push( org + B() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + B() ); break;
    case 119 : // 1 + 2 + 4 + 16 + 32 + 64
        pts.push( org + C() ).push( org + G() ).push( org + H() )
           .push( org + H() ).push( org + D() ).push( org + C() ); break;
    case 238 : // 2 + 4 + 8 + 32 + 64 + 128
        pts.push( org + A() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + E() ).push( org + A() ); break;

    // 2B VERTICES

    case 5   : // 1 + 4
        pts.push( org + B() ).push( org + A() ).push( org + I() )
           .push( org + I() ).push( org + K() ).push( org + B() )
           .push( org + C() ).push( org + D() ).push( org + I() )
           .push( org + I() ).push( org + K() ).push( org + C() ); break;
    case 10  : // 2 + 8
        pts.push( org + A() ).push( org + D() ).push( org + L() )
           .push( org + L() ).push( org + J() ).push( org + A() )
           .push( org + B() ).push( org + C() ).push( org + L() )
           .push( org + L() ).push( org + J() ).push( org + B() ); break;
    case 80  : // 16 + 64
        pts.push( org + F() ).push( org + E() ).push( org + I() )
           .push( org + I() ).push( org + K() ).push( org + F() )
           .push( org + G() ).push( org + H() ).push( org + I() )
           .push( org + I() ).push( org + K() ).push( org + G() ); break;
    case 160 : // 32 + 128
        pts.push( org + G() ).push( org + F() ).push( org + J() )
           .push( org + J() ).push( org + L() ).push( org + G() )
           .push( org + H() ).push( org + E() ).push( org + J() )
           .push( org + J() ).push( org + L() ).push( org + H() ); break;
    case 33  : // 1 + 32
        pts.push( org + I() ).push( org + E() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + I() )
           .push( org + A() ).push( org + J() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + A() ); break;
    case 18  : // 2 + 16
        pts.push( org + A() ).push( org + I() ).push( org + H() )
           .push( org + H() ).push( org + B() ).push( org + A() )
           .push( org + J() ).push( org + E() ).push( org + H() )
           .push( org + H() ).push( org + B() ).push( org + J() ); break;
    case 72  : // 8 + 64
        pts.push( org + L() ).push( org + G() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + L() )
           .push( org + C() ).push( org + K() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + C() ); break;
    case 132 : // 4 + 128
        pts.push( org + C() ).push( org + L() ).push( org + H() )
           .push( org + H() ).push( org + B() ).push( org + C() )
           .push( org + K() ).push( org + G() ).push( org + H() )
           .push( org + H() ).push( org + B() ).push( org + K() ); break;
    case 66  : // 2 + 64
        pts.push( org + B() ).push( org + K() ).push( org + G() )
           .push( org + G() ).push( org + A() ).push( org + B() )
           .push( org + J() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + A() ).push( org + J() ); break;
    case 36  : // 4 + 32
        pts.push( org + J() ).push( org + B() ).push( org + C() )
           .push( org + C() ).push( org + E() ).push( org + J() )
           .push( org + F() ).push( org + K() ).push( org + C() )
           .push( org + C() ).push( org + E() ).push( org + F() ); break;
    case 129 : // 1 + 128
        pts.push( org + D() ).push( org + L() ).push( org + G() )
           .push( org + G() ).push( org + A() ).push( org + D() )
           .push( org + I() ).push( org + H() ).push( org + G() )
           .push( org + G() ).push( org + A() ).push( org + I() ); break;
    case 24  : // 8 + 16
        pts.push( org + I() ).push( org + D() ).push( org + C() )
           .push( org + C() ).push( org + E() ).push( org + I() )
           .push( org + H() ).push( org + L() ).push( org + C() )
           .push( org + C() ).push( org + E() ).push( org + H() ); break;

    // 6B VERTICES

    case 250 : // 2 + 8 + 16 + 32 + 64 + 128
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 245 : // 1 + 4 + 16 + 32 + 64 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + C() ).push( org + D() ).push( org + L() ); break;
    case 175 : // 1 + 2 + 4 + 8 + 32 + 128
        pts.push( org + H() ).push( org + I() ).push( org + E() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 95  : // 1 + 2 + 4 + 8 + 16 + 64
        pts.push( org + E() ).push( org + F() ).push( org + J() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 222 : // 2 + 4 + 8 + 16 + 64 + 128
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 237 : // 1 + 4 + 8 + 32 + 64 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 183 : // 1 + 2 + 4 + 16 + 32 + 128
        pts.push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 123 : // 1 + 2 + 8 + 16 + 32 + 64
        pts.push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 189 : // 1 + 4 + 8 + 16 + 32 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 219 : // 1 + 2 + 8 + 16 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 126 : // 2 + 4 + 8 + 16 + 32 + 64
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 231 : // 1 + 2 + 4 + 32 + 64 + 128
        pts.push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;

    // 2C VERTICES

    case 65  : // 1 + 64
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 130 : // 2 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 20  : // 4 + 16
        pts.push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 40  : // 8 + 32
        pts.push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;

    // 6C VERTICES

    case 190 : // 2 + 4 + 8 + 16 + 32 + 128
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 125 : // 1 + 4 + 8 + 16 + 32 + 64
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 235 : // 1 + 2 + 8 + 32 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 215 : // 1 + 2 + 4 + 16 + 64 + 128
        pts.push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;

    // 3A VERTICES

    case 70  : // 2 + 4 + 64
        pts.push( org + A() ).push( org + C() ).push( org + G() )
           .push( org + A() ).push( org + J() ).push( org + G() )
           .push( org + J() ).push( org + F() ).push( org + G() ); break;
    case 100 : // 4 + 32 + 64
        pts.push( org + C() ).push( org + G() ).push( org + E() )
           .push( org + C() ).push( org + B() ).push( org + E() )
           .push( org + B() ).push( org + J() ).push( org + E() ); break;
    case 98  : // 2 + 32 + 64
        pts.push( org + G() ).push( org + E() ).push( org + A() )
           .push( org + G() ).push( org + K() ).push( org + A() )
           .push( org + K() ).push( org + B() ).push( org + A() ); break;
    case 38  : // 2 + 4 + 32
        pts.push( org + E() ).push( org + A() ).push( org + C() )
           .push( org + E() ).push( org + F() ).push( org + C() )
           .push( org + F() ).push( org + K() ).push( org + C() ); break;
    case 137 : // 1 + 8 + 128
        pts.push( org + A() ).push( org + C() ).push( org + G() )
           .push( org + A() ).push( org + I() ).push( org + G() )
           .push( org + I() ).push( org + H() ).push( org + G() ); break;
    case 152 : // 8 + 16 + 128
        pts.push( org + C() ).push( org + G() ).push( org + E() )
           .push( org + C() ).push( org + D() ).push( org + E() )
           .push( org + D() ).push( org + I() ).push( org + E() ); break;
    case 145 : // 1 + 16 + 128
        pts.push( org + G() ).push( org + E() ).push( org + A() )
           .push( org + G() ).push( org + L() ).push( org + A() )
           .push( org + L() ).push( org + D() ).push( org + A() ); break;
    case 25  : // 1 + 8 + 16
        pts.push( org + E() ).push( org + A() ).push( org + C() )
           .push( org + E() ).push( org + H() ).push( org + C() )
           .push( org + H() ).push( org + L() ).push( org + C() ); break;
    case 35  : // 1 + 2 + 32
        pts.push( org + D() ).push( org + B() ).push( org + F() )
           .push( org + D() ).push( org + I() ).push( org + F() )
           .push( org + I() ).push( org + E() ).push( org + F() ); break;
    case 19  : // 1 + 2 + 16
        pts.push( org + H() ).push( org + D() ).push( org + B() )
           .push( org + H() ).push( org + E() ).push( org + B() )
           .push( org + E() ).push( org + J() ).push( org + B() ); break;
    case 49  : // 1 + 16 + 32
        pts.push( org + F() ).push( org + H() ).push( org + D() )
           .push( org + F() ).push( org + J() ).push( org + D() )
           .push( org + J() ).push( org + A() ).push( org + D() ); break;
    case 50  : // 2 + 16 + 32
        pts.push( org + B() ).push( org + F() ).push( org + H() )
           .push( org + B() ).push( org + A() ).push( org + H() )
           .push( org + A() ).push( org + I() ).push( org + H() ); break;
    case 76  : // 4 + 8 + 64
        pts.push( org + D() ).push( org + B() ).push( org + F() )
           .push( org + D() ).push( org + L() ).push( org + F() )
           .push( org + L() ).push( org + G() ).push( org + F() ); break;
    case 140 : // 4 + 8 + 128
        pts.push( org + H() ).push( org + D() ).push( org + B() )
           .push( org + H() ).push( org + G() ).push( org + B() )
           .push( org + G() ).push( org + K() ).push( org + B() ); break;
    case 200 : // 8 + 64 + 128
        pts.push( org + F() ).push( org + H() ).push( org + D() )
           .push( org + F() ).push( org + K() ).push( org + D() )
           .push( org + K() ).push( org + C() ).push( org + D() ); break;
    case 196 : // 4 + 64 + 128
        pts.push( org + B() ).push( org + F() ).push( org + H() )
           .push( org + B() ).push( org + C() ).push( org + H() )
           .push( org + C() ).push( org + L() ).push( org + H() ); break;
    case 7   : // 1 + 2 + 4
        pts.push( org + K() ).push( org + J() ).push( org + I() )
           .push( org + K() ).push( org + C() ).push( org + I() )
           .push( org + C() ).push( org + D() ).push( org + I() ); break;
    case 14  : // 2 + 4 + 8
        pts.push( org + L() ).push( org + K() ).push( org + J() )
           .push( org + L() ).push( org + D() ).push( org + J() )
           .push( org + D() ).push( org + A() ).push( org + J() ); break;
    case 13  : // 1 + 4 + 8
        pts.push( org + I() ).push( org + L() ).push( org + K() )
           .push( org + I() ).push( org + A() ).push( org + K() )
           .push( org + A() ).push( org + B() ).push( org + K() ); break;
    case 11  : // 1 + 2 + 8
        pts.push( org + J() ).push( org + I() ).push( org + L() )
           .push( org + J() ).push( org + B() ).push( org + L() )
           .push( org + B() ).push( org + C() ).push( org + L() ); break;
    case 112 : // 16 + 32 + 64
        pts.push( org + K() ).push( org + J() ).push( org + I() )
           .push( org + K() ).push( org + G() ).push( org + I() )
           .push( org + G() ).push( org + H() ).push( org + I() ); break;
    case 224 : // 32 + 64 + 128
        pts.push( org + L() ).push( org + K() ).push( org + J() )
           .push( org + L() ).push( org + H() ).push( org + J() )
           .push( org + H() ).push( org + E() ).push( org + J() ); break;
    case 208 : // 16 + 64 + 128
        pts.push( org + I() ).push( org + L() ).push( org + K() )
           .push( org + I() ).push( org + E() ).push( org + K() )
           .push( org + E() ).push( org + F() ).push( org + K() ); break;
    case 176 : // 16 + 32 + 128
        pts.push( org + J() ).push( org + I() ).push( org + L() )
           .push( org + J() ).push( org + F() ).push( org + L() )
           .push( org + F() ).push( org + G() ).push( org + L() ); break;

    // 5A VERTICES

    case 155 : // 1 + 2 + 8 + 16 + 128
        pts.push( org + C() ).push( org + G() ).push( org + B() )
           .push( org + G() ).push( org + J() ).push( org + B() )
           .push( org + G() ).push( org + J() ).push( org + E() ); break;
    case 157 : // 1 + 4 + 8 + 16 + 128
        pts.push( org + G() ).push( org + E() ).push( org + K() )
           .push( org + E() ).push( org + B() ).push( org + K() )
           .push( org + E() ).push( org + B() ).push( org + A() ); break;
    case 217 : // 1 + 8 + 16 + 64 + 128
        pts.push( org + E() ).push( org + A() ).push( org + F() )
           .push( org + A() ).push( org + K() ).push( org + F() )
           .push( org + A() ).push( org + K() ).push( org + C() ); break;
    case 185 : // 1 + 8 + 16 + 32 + 128
        pts.push( org + A() ).push( org + C() ).push( org + J() )
           .push( org + C() ).push( org + F() ).push( org + J() )
           .push( org + C() ).push( org + F() ).push( org + G() ); break;
    case 103 : // 1 + 2 + 4 + 32 + 64
        pts.push( org + C() ).push( org + G() ).push( org + D() )
           .push( org + G() ).push( org + I() ).push( org + D() )
           .push( org + G() ).push( org + I() ).push( org + E() ); break;
    case 110 : // 2 + 4 + 8 + 32 + 64
        pts.push( org + G() ).push( org + E() ).push( org + L() )
           .push( org + E() ).push( org + D() ).push( org + L() )
           .push( org + E() ).push( org + D() ).push( org + A() ); break;
    case 230 : // 2 + 4 + 32 + 64 + 128
        pts.push( org + E() ).push( org + A() ).push( org + H() )
           .push( org + A() ).push( org + L() ).push( org + H() )
           .push( org + A() ).push( org + L() ).push( org + C() ); break;
    case 118 : // 2 + 4 + 16 + 32 + 64
        pts.push( org + A() ).push( org + C() ).push( org + I() )
           .push( org + C() ).push( org + H() ).push( org + I() )
           .push( org + C() ).push( org + H() ).push( org + G() ); break;
    case 55  : // 1 + 2 + 4 + 16 + 32
        pts.push( org + D() ).push( org + H() ).push( org + C() )
           .push( org + H() ).push( org + K() ).push( org + C() )
           .push( org + H() ).push( org + K() ).push( org + F() ); break;
    case 59  : // 1 + 2 + 8 + 16 + 32
        pts.push( org + H() ).push( org + F() ).push( org + L() )
           .push( org + F() ).push( org + C() ).push( org + L() )
           .push( org + F() ).push( org + C() ).push( org + B() ); break;
    case 179 : // 1 + 2 + 16 + 32 + 128
        pts.push( org + F() ).push( org + B() ).push( org + G() )
           .push( org + B() ).push( org + L() ).push( org + G() )
           .push( org + B() ).push( org + L() ).push( org + D() ); break;
    case 115 : // 1 + 2 + 16 + 32 + 64
        pts.push( org + B() ).push( org + D() ).push( org + K() )
           .push( org + D() ).push( org + G() ).push( org + K() )
           .push( org + D() ).push( org + G() ).push( org + H() ); break;
    case 206 : // 2 + 4 + 8 + 64 + 128
        pts.push( org + D() ).push( org + H() ).push( org + A() )
           .push( org + H() ).push( org + J() ).push( org + A() )
           .push( org + H() ).push( org + J() ).push( org + F() ); break;
    case 205 : // 1 + 4 + 8 + 64 + 128
        pts.push( org + H() ).push( org + F() ).push( org + I() )
           .push( org + F() ).push( org + A() ).push( org + I() )
           .push( org + F() ).push( org + A() ).push( org + B() ); break;
    case 220 : // 4 + 8 + 16 + 64 + 128
        pts.push( org + F() ).push( org + B() ).push( org + E() )
           .push( org + B() ).push( org + I() ).push( org + E() )
           .push( org + B() ).push( org + I() ).push( org + D() ); break;
    case 236 : // 4 + 8 + 32 + 64 + 128
        pts.push( org + B() ).push( org + D() ).push( org + J() )
           .push( org + D() ).push( org + E() ).push( org + J() )
           .push( org + D() ).push( org + E() ).push( org + H() ); break;
    case 241 : // 1 + 16 + 32 + 64 + 128
        pts.push( org + L() ).push( org + K() ).push( org + D() )
           .push( org + K() ).push( org + A() ).push( org + D() )
           .push( org + K() ).push( org + A() ).push( org + J() ); break;
    case 242 : // 2 + 16 + 32 + 64 + 128
        pts.push( org + I() ).push( org + L() ).push( org + A() )
           .push( org + L() ).push( org + B() ).push( org + A() )
           .push( org + L() ).push( org + B() ).push( org + K() ); break;
    case 244 : // 4 + 16 + 32 + 64 + 128
        pts.push( org + J() ).push( org + I() ).push( org + B() )
           .push( org + I() ).push( org + C() ).push( org + B() )
           .push( org + I() ).push( org + C() ).push( org + L() ); break;
    case 248 : // 8 + 16 + 32 + 64 + 128
        pts.push( org + K() ).push( org + J() ).push( org + C() )
           .push( org + J() ).push( org + D() ).push( org + C() )
           .push( org + J() ).push( org + D() ).push( org + I() ); break;
    case 31  : // 1 + 2 + 4 + 8 + 16
        pts.push( org + L() ).push( org + K() ).push( org + H() )
           .push( org + K() ).push( org + E() ).push( org + H() )
           .push( org + K() ).push( org + E() ).push( org + J() ); break;
    case 47  : // 1 + 2 + 4 + 8 + 32
        pts.push( org + I() ).push( org + L() ).push( org + E() )
           .push( org + L() ).push( org + F() ).push( org + E() )
           .push( org + L() ).push( org + F() ).push( org + K() ); break;
    case 79  : // 1 + 2 + 4 + 8 + 64
        pts.push( org + J() ).push( org + I() ).push( org + F() )
           .push( org + I() ).push( org + G() ).push( org + F() )
           .push( org + I() ).push( org + G() ).push( org + L() ); break;
    case 143 : // 1 + 2 + 4 + 8 + 128
        pts.push( org + K() ).push( org + J() ).push( org + G() )
           .push( org + J() ).push( org + H() ).push( org + G() )
           .push( org + J() ).push( org + H() ).push( org + I() ); break;

    // 3B VERTICES

    case 194 : // 2 + 64 + 128
        pts.push( org + J() ).push( org + F() ).push( org + H() )
           .push( org + J() ).push( org + A() ).push( org + H() )
           .push( org + A() ).push( org + H() ).push( org + L() )
           .push( org + A() ).push( org + B() ).push( org + L() )
           .push( org + B() ).push( org + K() ).push( org + L() ); break;
    case 52  : // 4 + 16 + 32
        pts.push( org + B() ).push( org + J() ).push( org + I() )
           .push( org + B() ).push( org + C() ).push( org + I() )
           .push( org + C() ).push( org + I() ).push( org + H() )
           .push( org + C() ).push( org + K() ).push( org + H() )
           .push( org + K() ).push( org + F() ).push( org + H() ); break;
    case 67  : // 1 + 2 + 64
        pts.push( org + K() ).push( org + B() ).push( org + D() )
           .push( org + K() ).push( org + G() ).push( org + D() )
           .push( org + G() ).push( org + D() ).push( org + I() )
           .push( org + G() ).push( org + F() ).push( org + I() )
           .push( org + F() ).push( org + J() ).push( org + I() ); break;
    case 44  : // 4 + 8 + 32
        pts.push( org + F() ).push( org + K() ).push( org + L() )
           .push( org + F() ).push( org + E() ).push( org + L() )
           .push( org + E() ).push( org + L() ).push( org + D() )
           .push( org + E() ).push( org + J() ).push( org + D() )
           .push( org + J() ).push( org + B() ).push( org + D() ); break;
    case 193 : // 1 + 64 + 128
        pts.push( org + I() ).push( org + H() ).push( org + F() )
           .push( org + I() ).push( org + A() ).push( org + F() )
           .push( org + A() ).push( org + F() ).push( org + K() )
           .push( org + A() ).push( org + D() ).push( org + K() )
           .push( org + D() ).push( org + L() ).push( org + K() ); break;
    case 56  : // 8 + 16 + 32
        pts.push( org + D() ).push( org + I() ).push( org + J() )
           .push( org + D() ).push( org + C() ).push( org + J() )
           .push( org + C() ).push( org + J() ).push( org + F() )
           .push( org + C() ).push( org + L() ).push( org + F() )
           .push( org + L() ).push( org + H() ).push( org + F() ); break;
    case 131 : // 1 + 2 + 128
        pts.push( org + L() ).push( org + D() ).push( org + B() )
           .push( org + L() ).push( org + G() ).push( org + B() )
           .push( org + G() ).push( org + B() ).push( org + J() )
           .push( org + G() ).push( org + H() ).push( org + J() )
           .push( org + H() ).push( org + I() ).push( org + J() ); break;
    case 28  : // 4 + 8 + 16
        pts.push( org + H() ).push( org + L() ).push( org + K() )
           .push( org + H() ).push( org + E() ).push( org + K() )
           .push( org + E() ).push( org + K() ).push( org + B() )
           .push( org + E() ).push( org + I() ).push( org + B() )
           .push( org + I() ).push( org + D() ).push( org + B() ); break;
    case 41  : // 1 + 8 + 32
        pts.push( org + E() ).push( org + I() ).push( org + L() )
           .push( org + E() ).push( org + F() ).push( org + L() )
           .push( org + F() ).push( org + L() ).push( org + C() )
           .push( org + F() ).push( org + J() ).push( org + C() )
           .push( org + J() ).push( org + A() ).push( org + C() ); break;
    case 146 : // 2 + 16 + 128
        pts.push( org + J() ).push( org + E() ).push( org + G() )
           .push( org + J() ).push( org + B() ).push( org + G() )
           .push( org + B() ).push( org + G() ).push( org + L() )
           .push( org + B() ).push( org + A() ).push( org + L() )
           .push( org + A() ).push( org + I() ).push( org + L() ); break;
    case 97  : // 1 + 32 + 64
        pts.push( org + A() ).push( org + J() ).push( org + K() )
           .push( org + A() ).push( org + D() ).push( org + K() )
           .push( org + D() ).push( org + K() ).push( org + G() )
           .push( org + D() ).push( org + I() ).push( org + G() )
           .push( org + I() ).push( org + E() ).push( org + G() ); break;
    case 22  : // 2 + 4 + 16
        pts.push( org + I() ).push( org + A() ).push( org + C() )
           .push( org + I() ).push( org + H() ).push( org + C() )
           .push( org + H() ).push( org + C() ).push( org + K() )
           .push( org + H() ).push( org + E() ).push( org + K() )
           .push( org + E() ).push( org + J() ).push( org + K() ); break;
    case 73  : // 1 + 8 + 64
        pts.push( org + G() ).push( org + L() ).push( org + I() )
           .push( org + G() ).push( org + F() ).push( org + I() )
           .push( org + F() ).push( org + I() ).push( org + A() )
           .push( org + F() ).push( org + K() ).push( org + A() )
           .push( org + K() ).push( org + C() ).push( org + A() ); break;
    case 148 : // 4 + 16 + 128
        pts.push( org + K() ).push( org + G() ).push( org + E() )
           .push( org + K() ).push( org + B() ).push( org + E() )
           .push( org + B() ).push( org + E() ).push( org + I() )
           .push( org + B() ).push( org + C() ).push( org + I() )
           .push( org + C() ).push( org + L() ).push( org + I() ); break;
    case 104 : // 8 + 32 + 64
        pts.push( org + C() ).push( org + K() ).push( org + J() )
           .push( org + C() ).push( org + D() ).push( org + J() )
           .push( org + D() ).push( org + J() ).push( org + E() )
           .push( org + D() ).push( org + L() ).push( org + E() )
           .push( org + L() ).push( org + G() ).push( org + E() ); break;
    case 134 : // 2 + 4 + 128
        pts.push( org + L() ).push( org + C() ).push( org + A() )
           .push( org + L() ).push( org + H() ).push( org + A() )
           .push( org + H() ).push( org + A() ).push( org + J() )
           .push( org + H() ).push( org + G() ).push( org + J() )
           .push( org + G() ).push( org + K() ).push( org + J() ); break;
    case 21  : // 1 + 4 + 16
        pts.push( org + C() ).push( org + D() ).push( org + H() )
           .push( org + C() ).push( org + K() ).push( org + H() )
           .push( org + K() ).push( org + H() ).push( org + E() )
           .push( org + K() ).push( org + B() ).push( org + E() )
           .push( org + B() ).push( org + A() ).push( org + E() ); break;
    case 42  : // 2 + 8 + 32
        pts.push( org + D() ).push( org + A() ).push( org + E() )
           .push( org + D() ).push( org + L() ).push( org + E() )
           .push( org + L() ).push( org + E() ).push( org + F() )
           .push( org + L() ).push( org + C() ).push( org + F() )
           .push( org + C() ).push( org + B() ).push( org + F() ); break;
    case 69  : // 1 + 4 + 64
        pts.push( org + A() ).push( org + B() ).push( org + F() )
           .push( org + A() ).push( org + I() ).push( org + F() )
           .push( org + I() ).push( org + F() ).push( org + G() )
           .push( org + I() ).push( org + D() ).push( org + G() )
           .push( org + D() ).push( org + C() ).push( org + G() ); break;
    case 138 : // 2 + 8 + 128
        pts.push( org + B() ).push( org + C() ).push( org + G() )
           .push( org + B() ).push( org + J() ).push( org + G() )
           .push( org + J() ).push( org + G() ).push( org + H() )
           .push( org + J() ).push( org + A() ).push( org + H() )
           .push( org + A() ).push( org + D() ).push( org + H() ); break;
    case 81  : // 1 + 16 + 64
        pts.push( org + G() ).push( org + H() ).push( org + D() )
           .push( org + G() ).push( org + K() ).push( org + D() )
           .push( org + K() ).push( org + D() ).push( org + A() )
           .push( org + K() ).push( org + F() ).push( org + A() )
           .push( org + F() ).push( org + E() ).push( org + A() ); break;
    case 162 : // 2 + 32 + 128
        pts.push( org + H() ).push( org + E() ).push( org + A() )
           .push( org + H() ).push( org + L() ).push( org + A() )
           .push( org + L() ).push( org + A() ).push( org + B() )
           .push( org + L() ).push( org + G() ).push( org + B() )
           .push( org + G() ).push( org + F() ).push( org + B() ); break;
    case 84  : // 4 + 16 + 64
        pts.push( org + E() ).push( org + F() ).push( org + B() )
           .push( org + E() ).push( org + I() ).push( org + B() )
           .push( org + I() ).push( org + B() ).push( org + C() )
           .push( org + I() ).push( org + H() ).push( org + C() )
           .push( org + H() ).push( org + G() ).push( org + C() ); break;
    case 168 : // 8 + 32 + 128
        pts.push( org + F() ).push( org + G() ).push( org + C() )
           .push( org + F() ).push( org + J() ).push( org + C() )
           .push( org + J() ).push( org + C() ).push( org + D() )
           .push( org + J() ).push( org + E() ).push( org + D() )
           .push( org + E() ).push( org + H() ).push( org + D() ); break;

    // 5B VERTICES

    case 62  : // 2 + 4 + 8 + 16 + 32
        pts.push( org + K() ).push( org + F() ).push( org + H() )
           .push( org + H() ).push( org + L() ).push( org + K() )
           .push( org + A() ).push( org + D() ).push( org + I() ); break;
    case 188 : // 4 + 8 + 16 + 32 + 128
        pts.push( org + I() ).push( org + J() ).push( org + B() )
           .push( org + B() ).push( org + D() ).push( org + I() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 124 : // 4 + 8 + 16 + 32 + 64
        pts.push( org + I() ).push( org + J() ).push( org + B() )
           .push( org + B() ).push( org + D() ).push( org + I() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 61  : // 1 + 4 + 8 + 16 + 32
        pts.push( org + K() ).push( org + F() ).push( org + H() )
           .push( org + H() ).push( org + L() ).push( org + K() )
           .push( org + A() ).push( org + J() ).push( org + B() ); break;
    case 214 : // 2 + 4 + 16 + 64 + 128
        pts.push( org + A() ).push( org + C() ).push( org + L() )
           .push( org + L() ).push( org + I() ).push( org + A() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 151 : // 1 + 2 + 4 + 16 + 128
        pts.push( org + K() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + G() ).push( org + K() )
           .push( org + C() ).push( org + D() ).push( org + L() ); break;
    case 182 : // 2 + 4 + 16 + 32 + 128
        pts.push( org + A() ).push( org + C() ).push( org + L() )
           .push( org + L() ).push( org + I() ).push( org + A() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 158 : // 2 + 4 + 8 + 16 + 128
        pts.push( org + K() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + G() ).push( org + K() )
           .push( org + A() ).push( org + D() ).push( org + I() ); break;
    case 234 : // 2 + 8 + 32 + 64 + 128
        pts.push( org + A() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + E() ).push( org + A() )
           .push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 171 : // 1 + 2 + 8 + 32 + 128
        pts.push( org + B() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + B() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 174 : // 2 + 4 + 8 + 32 + 128
        pts.push( org + A() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + E() ).push( org + A() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 186 : // 2 + 8 + 16 + 32 + 128
        pts.push( org + B() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + B() )
           .push( org + A() ).push( org + D() ).push( org + I() ); break;
    case 233 : // 1 + 8 + 32 + 64 + 128
        pts.push( org + A() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + C() ).push( org + A() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 107 : // 1 + 2 + 8 + 32 + 64
        pts.push( org + E() ).push( org + I() ).push( org + L() )
           .push( org + L() ).push( org + G() ).push( org + E() )
           .push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 121 : // 1 + 8 + 16 + 32 + 64
        pts.push( org + A() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + C() ).push( org + A() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 109 : // 1 + 4 + 8 + 32 + 64
        pts.push( org + E() ).push( org + I() ).push( org + L() )
           .push( org + L() ).push( org + G() ).push( org + E() )
           .push( org + A() ).push( org + J() ).push( org + B() ); break;
    case 213 : // 1 + 4 + 16 + 64 + 128
        pts.push( org + B() ).push( org + A() ).push( org + E() )
           .push( org + E() ).push( org + F() ).push( org + B() )
           .push( org + C() ).push( org + D() ).push( org + L() ); break;
    case 87  : // 1 + 2 + 4 + 16 + 64
        pts.push( org + C() ).push( org + G() ).push( org + H() )
           .push( org + H() ).push( org + D() ).push( org + C() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 93  : // 1 + 4 + 8 + 16 + 64
        pts.push( org + B() ).push( org + A() ).push( org + E() )
           .push( org + E() ).push( org + F() ).push( org + B() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 117 : // 1 + 4 + 16 + 32 + 64
        pts.push( org + C() ).push( org + G() ).push( org + H() )
           .push( org + H() ).push( org + D() ).push( org + C() )
           .push( org + A() ).push( org + J() ).push( org + B() ); break;
    case 227 : // 1 + 2 + 32 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + L() )
           .push( org + L() ).push( org + D() ).push( org + B() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 203 : // 1 + 2 + 8 + 64 + 128
        pts.push( org + F() ).push( org + J() ).push( org + I() )
           .push( org + I() ).push( org + H() ).push( org + F() )
           .push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 211 : // 1 + 2 + 16 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + L() )
           .push( org + L() ).push( org + D() ).push( org + B() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 199 : // 1 + 2 + 4 + 64 + 128
        pts.push( org + F() ).push( org + J() ).push( org + I() )
           .push( org + I() ).push( org + H() ).push( org + F() )
           .push( org + C() ).push( org + D() ).push( org + L() ); break;

    // 3C VERTICES

    case 26  : // 2 + 8 + 16
        pts.push( org + B() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + H() ).push( org + B() )
           .push( org + B() ).push( org + H() ).push( org + C() )
           .push( org + C() ).push( org + L() ).push( org + H() )
           .push( org + A() ).push( org + D() ).push( org + I() ); break;
    case 37  : // 1 + 4 + 32
        pts.push( org + F() ).push( org + K() ).push( org + C() )
           .push( org + C() ).push( org + D() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + E() )
           .push( org + E() ).push( org + I() ).push( org + D() )
           .push( org + A() ).push( org + J() ).push( org + B() ); break;
    case 74  : // 2 + 8 + 64
        pts.push( org + J() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + L() ).push( org + J() )
           .push( org + J() ).push( org + L() ).push( org + A() )
           .push( org + A() ).push( org + D() ).push( org + L() )
           .push( org + B() ).push( org + K() ).push( org + C() ); break;
    case 82  : // 2 + 16 + 64
        pts.push( org + K() ).push( org + B() ).push( org + A() )
           .push( org + A() ).push( org + I() ).push( org + K() )
           .push( org + K() ).push( org + I() ).push( org + G() )
           .push( org + G() ).push( org + H() ).push( org + I() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 88  : // 8 + 16 + 64
        pts.push( org + F() ).push( org + K() ).push( org + C() )
           .push( org + C() ).push( org + D() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + E() )
           .push( org + E() ).push( org + I() ).push( org + D() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 133 : // 1 + 4 + 128
        pts.push( org + K() ).push( org + B() ).push( org + A() )
           .push( org + A() ).push( org + I() ).push( org + K() )
           .push( org + K() ).push( org + I() ).push( org + G() )
           .push( org + G() ).push( org + H() ).push( org + I() )
           .push( org + C() ).push( org + D() ).push( org + L() ); break;
    case 161 : // 1 + 32 + 128
        pts.push( org + J() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + L() ).push( org + J() )
           .push( org + J() ).push( org + L() ).push( org + A() )
           .push( org + A() ).push( org + D() ).push( org + L() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;
    case 164 : // 4 + 32 + 128
        pts.push( org + B() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + H() ).push( org + B() )
           .push( org + B() ).push( org + H() ).push( org + C() )
           .push( org + C() ).push( org + L() ).push( org + H() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;

    // 5C VERTICES

    case 91  : // 1 + 2 + 8 + 16 + 64
        pts.push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + E() ).push( org + F() ).push( org + J() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 94  : // 2 + 4 + 8 + 16 + 64
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + E() ).push( org + F() ).push( org + J() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 122 : // 2 + 8 + 16 + 32 + 64
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 167 : // 1 + 2 + 4 + 32 + 128
        pts.push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + H() ).push( org + I() ).push( org + E() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 173 : // 1 + 4 + 8 + 32 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + H() ).push( org + I() ).push( org + E() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 181 : // 1 + 4 + 16 + 32 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + F() ).push( org + G() ).push( org + K() ); break;
    case 218 : // 2 + 8 + 16 + 64 + 128
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + E() ).push( org + F() ).push( org + J() ); break;
    case 229 : // 1 + 4 + 32 + 64 + 128
        pts.push( org + A() ).push( org + J() ).push( org + B() )
           .push( org + C() ).push( org + D() ).push( org + L() )
           .push( org + H() ).push( org + I() ).push( org + E() ); break;

    // 4A VERTICES

    case 15  : // 1 + 2 + 4 + 8
        pts.push( org + I() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + L() ).push( org + I() ); break;
    case 240 : // 16 + 32 + 64 + 128
        pts.push( org + I() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + L() ).push( org + I() ); break;
    case 51  : // 1 + 2 + 16 + 32
        pts.push( org + B() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + F() ).push( org + B() ); break;
    case 204 : // 4 + 8 + 64 + 128
        pts.push( org + B() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + F() ).push( org + B() ); break;
    case 102 : // 2 + 4 + 32 + 64
        pts.push( org + A() ).push( org + E() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + A() ); break;
    case 153 : // 1 + 8 + 16 + 128
        pts.push( org + A() ).push( org + E() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + A() ); break;

    // 4B VERTICES

    case 27  : // 1 + 2 + 8 + 16
        pts.push( org + B() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + H() ).push( org + B() )
           .push( org + B() ).push( org + H() ).push( org + C() )
           .push( org + C() ).push( org + L() ).push( org + H() ); break;
    case 228 : // 4 + 32 + 64 + 128
        pts.push( org + B() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + H() ).push( org + B() )
           .push( org + B() ).push( org + H() ).push( org + C() )
           .push( org + C() ).push( org + L() ).push( org + H() ); break;
    case 141 : // 1 + 4 + 8 + 128
        pts.push( org + K() ).push( org + B() ).push( org + A() )
           .push( org + A() ).push( org + I() ).push( org + K() )
           .push( org + K() ).push( org + I() ).push( org + G() )
           .push( org + G() ).push( org + H() ).push( org + I() ); break;
    case 114 : // 2 + 16 + 32 + 64
        pts.push( org + K() ).push( org + B() ).push( org + A() )
           .push( org + A() ).push( org + I() ).push( org + K() )
           .push( org + K() ).push( org + I() ).push( org + G() )
           .push( org + G() ).push( org + H() ).push( org + I() ); break;
    case 216 : // 8 + 16 + 64 + 128
        pts.push( org + F() ).push( org + K() ).push( org + C() )
           .push( org + C() ).push( org + D() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + E() )
           .push( org + E() ).push( org + I() ).push( org + D() ); break;
    case 39  : // 1 + 2 + 4 + 32
        pts.push( org + F() ).push( org + K() ).push( org + C() )
           .push( org + C() ).push( org + D() ).push( org + F() )
           .push( org + F() ).push( org + D() ).push( org + E() )
           .push( org + E() ).push( org + I() ).push( org + D() ); break;
    case 177 : // 1 + 16 + 32 + 128
        pts.push( org + J() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + L() ).push( org + J() )
           .push( org + J() ).push( org + L() ).push( org + A() )
           .push( org + A() ).push( org + D() ).push( org + L() ); break;
    case 78  : // 2 + 4 + 8 + 64
        pts.push( org + J() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + L() ).push( org + J() )
           .push( org + J() ).push( org + L() ).push( org + A() )
           .push( org + A() ).push( org + D() ).push( org + L() ); break;

    // 4C VERTICES

    case 195 : // 1 + 2 + 64 + 128
        pts.push( org + B() ).push( org + K() ).push( org + L() )
           .push( org + L() ).push( org + D() ).push( org + B() )
           .push( org + J() ).push( org + I() ).push( org + H() )
           .push( org + H() ).push( org + F() ).push( org + J() ); break;
    case 60  : // 4 + 8 + 16 + 32
        pts.push( org + I() ).push( org + J() ).push( org + B() )
           .push( org + B() ).push( org + D() ).push( org + I() )
           .push( org + K() ).push( org + F() ).push( org + H() )
           .push( org + H() ).push( org + L() ).push( org + K() ); break;
    case 105 : // 1 + 8 + 32 + 64
        pts.push( org + A() ).push( org + J() ).push( org + K() )
           .push( org + K() ).push( org + C() ).push( org + A() )
           .push( org + I() ).push( org + E() ).push( org + G() )
           .push( org + G() ).push( org + L() ).push( org + I() ); break;
    case 150 : // 2 + 4 + 16 + 128
        pts.push( org + A() ).push( org + C() ).push( org + L() )
           .push( org + L() ).push( org + I() ).push( org + A() )
           .push( org + K() ).push( org + J() ).push( org + E() )
           .push( org + E() ).push( org + G() ).push( org + K() ); break;
    case 85  : // 1 + 4 + 16 + 64
        pts.push( org + B() ).push( org + A() ).push( org + E() )
           .push( org + E() ).push( org + F() ).push( org + B() )
           .push( org + C() ).push( org + G() ).push( org + H() )
           .push( org + H() ).push( org + D() ).push( org + C() ); break;
    case 170 : // 2 + 8 + 32 + 128
        pts.push( org + A() ).push( org + D() ).push( org + H() )
           .push( org + H() ).push( org + E() ).push( org + A() )
           .push( org + B() ).push( org + F() ).push( org + G() )
           .push( org + G() ).push( org + C() ).push( org + B() ); break;

    // 4D VERTICES

    case 212 : // 4 + 16 + 64 + 128
        pts.push( org + E() ).push( org + B() ).push( org + F() )
           .push( org + E() ).push( org + B() ).push( org + I() )
           .push( org + I() ).push( org + B() ).push( org + C() )
           .push( org + I() ).push( org + L() ).push( org + C() ); break;
    case 142 : // 2 + 4 + 8 + 128
        pts.push( org + G() ).push( org + J() ).push( org + K() )
           .push( org + G() ).push( org + J() ).push( org + H() )
           .push( org + H() ).push( org + J() ).push( org + A() )
           .push( org + H() ).push( org + D() ).push( org + A() ); break;
    case 43  : // 1 + 2 + 8 + 32
        pts.push( org + C() ).push( org + F() ).push( org + B() )
           .push( org + C() ).push( org + F() ).push( org + L() )
           .push( org + L() ).push( org + F() ).push( org + E() )
           .push( org + L() ).push( org + I() ).push( org + E() ); break;
    case 113 : // 1 + 16 + 32 + 64
        pts.push( org + A() ).push( org + K() ).push( org + J() )
           .push( org + A() ).push( org + K() ).push( org + D() )
           .push( org + D() ).push( org + K() ).push( org + G() )
           .push( org + D() ).push( org + H() ).push( org + G() ); break;
    case 178 : // 2 + 16 + 32 + 128
        pts.push( org + G() ).push( org + B() ).push( org + F() )
           .push( org + G() ).push( org + B() ).push( org + L() )
           .push( org + L() ).push( org + B() ).push( org + A() )
           .push( org + L() ).push( org + I() ).push( org + A() ); break;
    case 232 : // 8 + 32 + 64 + 128
        pts.push( org + C() ).push( org + J() ).push( org + K() )
           .push( org + C() ).push( org + J() ).push( org + D() )
           .push( org + D() ).push( org + J() ).push( org + E() )
           .push( org + D() ).push( org + H() ).push( org + E() ); break;
    case 77  : // 1 + 4 + 8 + 64
        pts.push( org + A() ).push( org + F() ).push( org + B() )
           .push( org + A() ).push( org + F() ).push( org + I() )
           .push( org + I() ).push( org + F() ).push( org + G() )
           .push( org + I() ).push( org + L() ).push( org + G() ); break;
    case 23  : // 1 + 2 + 4 + 16
        pts.push( org + E() ).push( org + K() ).push( org + J() )
           .push( org + E() ).push( org + K() ).push( org + H() )
           .push( org + H() ).push( org + K() ).push( org + C() )
           .push( org + H() ).push( org + D() ).push( org + C() ); break;
    case 46  : // 2 + 4 + 8 + 32
        pts.push( org + F() ).push( org + L() ).push( org + K() )
           .push( org + F() ).push( org + L() ).push( org + E() )
           .push( org + E() ).push( org + L() ).push( org + D() )
           .push( org + E() ).push( org + A() ).push( org + D() ); break;
    case 99  : // 1 + 2 + 32 + 64
        pts.push( org + K() ).push( org + D() ).push( org + B() )
           .push( org + K() ).push( org + D() ).push( org + G() )
           .push( org + G() ).push( org + D() ).push( org + I() )
           .push( org + G() ).push( org + E() ).push( org + I() ); break;
    case 116 : // 4 + 16 + 32 + 64
        pts.push( org + B() ).push( org + I() ).push( org + J() )
           .push( org + B() ).push( org + I() ).push( org + C() )
           .push( org + C() ).push( org + I() ).push( org + H() )
           .push( org + C() ).push( org + G() ).push( org + H() ); break;
    case 198 : // 2 + 4 + 64 + 128
        pts.push( org + J() ).push( org + H() ).push( org + F() )
           .push( org + J() ).push( org + H() ).push( org + A() )
           .push( org + A() ).push( org + H() ).push( org + L() )
           .push( org + A() ).push( org + C() ).push( org + L() ); break;
    case 201 : // 1 + 8 + 64 + 128
        pts.push( org + I() ).push( org + F() ).push( org + H() )
           .push( org + I() ).push( org + F() ).push( org + A() )
           .push( org + A() ).push( org + F() ).push( org + K() )
           .push( org + A() ).push( org + C() ).push( org + K() ); break;
    case 29  : // 1 + 4 + 8 + 16
        pts.push( org + H() ).push( org + K() ).push( org + L() )
           .push( org + H() ).push( org + K() ).push( org + E() )
           .push( org + E() ).push( org + K() ).push( org + B() )
           .push( org + E() ).push( org + A() ).push( org + B() ); break;
    case 147 : // 1 + 2 + 16 + 128
        pts.push( org + L() ).push( org + B() ).push( org + D() )
           .push( org + L() ).push( org + B() ).push( org + G() )
           .push( org + G() ).push( org + B() ).push( org + J() )
           .push( org + G() ).push( org + E() ).push( org + J() ); break;
    case 184 : // 8 + 16 + 32 + 128
        pts.push( org + D() ).push( org + J() ).push( org + I() )
           .push( org + D() ).push( org + J() ).push( org + C() )
           .push( org + C() ).push( org + J() ).push( org + F() )
           .push( org + C() ).push( org + G() ).push( org + F() ); break;
    case 209 : // 1 + 16 + 64 + 128
        pts.push( org + D() ).push( org + K() ).push( org + L() )
           .push( org + D() ).push( org + K() ).push( org + A() )
           .push( org + A() ).push( org + K() ).push( org + F() )
           .push( org + A() ).push( org + E() ).push( org + F() ); break;
    case 57  : // 1 + 8 + 16 + 32
        pts.push( org + L() ).push( org + F() ).push( org + H() )
           .push( org + L() ).push( org + F() ).push( org + C() )
           .push( org + C() ).push( org + F() ).push( org + J() )
           .push( org + C() ).push( org + A() ).push( org + J() ); break;
    case 139 : // 1 + 2 + 8 + 128
        pts.push( org + H() ).push( org + J() ).push( org + I() )
           .push( org + H() ).push( org + J() ).push( org + G() )
           .push( org + G() ).push( org + J() ).push( org + B() )
           .push( org + G() ).push( org + C() ).push( org + B() ); break;
    case 156 : // 4 + 8 + 16 + 128
        pts.push( org + I() ).push( org + B() ).push( org + D() )
           .push( org + I() ).push( org + B() ).push( org + E() )
           .push( org + E() ).push( org + B() ).push( org + K() )
           .push( org + E() ).push( org + G() ).push( org + K() ); break;
    case 226 : // 2 + 32 + 64 + 128
        pts.push( org + B() ).push( org + L() ).push( org + K() )
           .push( org + B() ).push( org + L() ).push( org + A() )
           .push( org + A() ).push( org + L() ).push( org + H() )
           .push( org + A() ).push( org + E() ).push( org + H() ); break;
    case 54  : // 2 + 4 + 16 + 32
        pts.push( org + K() ).push( org + H() ).push( org + F() )
           .push( org + K() ).push( org + H() ).push( org + C() )
           .push( org + C() ).push( org + H() ).push( org + I() )
           .push( org + C() ).push( org + A() ).push( org + I() ); break;
    case 71  : // 1 + 2 + 4 + 64
        pts.push( org + F() ).push( org + I() ).push( org + J() )
           .push( org + F() ).push( org + I() ).push( org + G() )
           .push( org + G() ).push( org + I() ).push( org + D() )
           .push( org + G() ).push( org + C() ).push( org + D() ); break;
    case 108 : // 4 + 8 + 32 + 64
        pts.push( org + J() ).push( org + D() ).push( org + B() )
           .push( org + J() ).push( org + D() ).push( org + E() )
           .push( org + E() ).push( org + D() ).push( org + L() )
           .push( org + E() ).push( org + G() ).push( org + L() ); break;

//                4E VERTICES

    case 149 : // 1 + 4 + 16 + 128
        pts.push( org + E() ).push( org + G() ).push( org + K() )
           .push( org + E() ).push( org + A() ).push( org + B() )
           .push( org + E() ).push( org + B() ).push( org + K() )
           .push( org + D() ).push( org + C() ).push( org + L() ); break;
    case 89  : // 1 + 8 + 16 + 64
        pts.push( org + A() ).push( org + E() ).push( org + F() )
           .push( org + A() ).push( org + C() ).push( org + K() )
           .push( org + A() ).push( org + K() ).push( org + F() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    case 169 : // 1 + 8 + 32 + 128
        pts.push( org + C() ).push( org + A() ).push( org + J() )
           .push( org + C() ).push( org + G() ).push( org + F() )
           .push( org + C() ).push( org + F() ).push( org + J() )
           .push( org + H() ).push( org + E() ).push( org + I() ); break;
    case 154 : // 2 + 8 + 16 + 128
        pts.push( org + G() ).push( org + C() ).push( org + B() )
           .push( org + G() ).push( org + E() ).push( org + J() )
           .push( org + G() ).push( org + J() ).push( org + B() )
           .push( org + I() ).push( org + A() ).push( org + D() ); break;
    case 106 : // 2 + 8 + 32 + 64
        pts.push( org + E() ).push( org + G() ).push( org + L() )
           .push( org + E() ).push( org + A() ).push( org + D() )
           .push( org + E() ).push( org + D() ).push( org + L() )
           .push( org + B() ).push( org + C() ).push( org + K() ); break;
    case 166 : // 2 + 4 + 32 + 128
        pts.push( org + A() ).push( org + E() ).push( org + H() )
           .push( org + A() ).push( org + C() ).push( org + L() )
           .push( org + A() ).push( org + L() ).push( org + H() )
           .push( org + K() ).push( org + G() ).push( org + F() ); break;
    case 86  : // 2 + 4 + 16 + 64
        pts.push( org + C() ).push( org + A() ).push( org + I() )
           .push( org + C() ).push( org + G() ).push( org + H() )
           .push( org + C() ).push( org + H() ).push( org + I() )
           .push( org + F() ).push( org + E() ).push( org + J() ); break;
    case 101 : // 1 + 4 + 32 + 64
        pts.push( org + G() ).push( org + C() ).push( org + D() )
           .push( org + G() ).push( org + E() ).push( org + I() )
           .push( org + G() ).push( org + I() ).push( org + D() )
           .push( org + J() ).push( org + A() ).push( org + B() ); break;
    case 53  : // 1 + 4 + 16 + 32
        pts.push( org + H() ).push( org + F() ).push( org + K() )
           .push( org + H() ).push( org + D() ).push( org + C() )
           .push( org + H() ).push( org + C() ).push( org + K() )
           .push( org + A() ).push( org + B() ).push( org + J() ); break;
    case 58  : // 2 + 8 + 16 + 32
        pts.push( org + F() ).push( org + B() ).push( org + C() )
           .push( org + F() ).push( org + H() ).push( org + L() )
           .push( org + F() ).push( org + L() ).push( org + C() )
           .push( org + I() ).push( org + D() ).push( org + A() ); break;
    case 163 : // 1 + 2 + 32 + 128
        pts.push( org + B() ).push( org + D() ).push( org + L() )
           .push( org + B() ).push( org + F() ).push( org + G() )
           .push( org + B() ).push( org + G() ).push( org + L() )
           .push( org + E() ).push( org + H() ).push( org + I() ); break;
    case 83  : // 1 + 2 + 16 + 64
        pts.push( org + D() ).push( org + H() ).push( org + G() )
           .push( org + D() ).push( org + B() ).push( org + K() )
           .push( org + D() ).push( org + K() ).push( org + G() )
           .push( org + J() ).push( org + F() ).push( org + E() ); break;
    case 202 : // 2 + 8 + 64 + 128
        pts.push( org + H() ).push( org + F() ).push( org + J() )
           .push( org + H() ).push( org + D() ).push( org + A() )
           .push( org + H() ).push( org + A() ).push( org + J() )
           .push( org + C() ).push( org + B() ).push( org + K() ); break;
    case 197 : // 1 + 4 + 64 + 128
        pts.push( org + F() ).push( org + B() ).push( org + A() )
           .push( org + F() ).push( org + H() ).push( org + I() )
           .push( org + F() ).push( org + I() ).push( org + A() )
           .push( org + L() ).push( org + D() ).push( org + C() ); break;
    case 92  : // 4 + 8 + 16 + 64
        pts.push( org + B() ).push( org + D() ).push( org + I() )
           .push( org + B() ).push( org + F() ).push( org + E() )
           .push( org + B() ).push( org + E() ).push( org + I() )
           .push( org + G() ).push( org + H() ).push( org + L() ); break;
    case 172 : // 4 + 8 + 32 + 128
        pts.push( org + D() ).push( org + H() ).push( org + E() )
           .push( org + D() ).push( org + B() ).push( org + J() )
           .push( org + D() ).push( org + J() ).push( org + E() )
           .push( org + K() ).push( org + F() ).push( org + G() ); break;
    case 45  : // 1 + 4 + 8 + 32
        pts.push( org + L() ).push( org + I() ).push( org + E() )
           .push( org + L() ).push( org + K() ).push( org + F() )
           .push( org + L() ).push( org + F() ).push( org + E() )
           .push( org + B() ).push( org + J() ).push( org + A() ); break;
    case 75  : // 1 + 2 + 8 + 64
        pts.push( org + I() ).push( org + J() ).push( org + F() )
           .push( org + I() ).push( org + L() ).push( org + G() )
           .push( org + I() ).push( org + G() ).push( org + F() )
           .push( org + C() ).push( org + K() ).push( org + B() ); break;
    case 135 : // 1 + 2 + 4 + 128
        pts.push( org + J() ).push( org + K() ).push( org + G() )
           .push( org + J() ).push( org + I() ).push( org + H() )
           .push( org + J() ).push( org + H() ).push( org + G() )
           .push( org + D() ).push( org + L() ).push( org + C() ); break;
    case 30  : // 2 + 4 + 8 + 16
        pts.push( org + K() ).push( org + L() ).push( org + H() )
           .push( org + K() ).push( org + J() ).push( org + E() )
           .push( org + K() ).push( org + E() ).push( org + H() )
           .push( org + A() ).push( org + I() ).push( org + D() ); break;
    case 210 : // 2 + 16 + 64 + 128
        pts.push( org + L() ).push( org + I() ).push( org + A() )
           .push( org + L() ).push( org + K() ).push( org + B() )
           .push( org + L() ).push( org + B() ).push( org + A() )
           .push( org + F() ).push( org + J() ).push( org + E() ); break;
    case 180 : // 4 + 16 + 32 + 128
        pts.push( org + I() ).push( org + J() ).push( org + B() )
           .push( org + I() ).push( org + L() ).push( org + C() )
           .push( org + I() ).push( org + C() ).push( org + B() )
           .push( org + G() ).push( org + K() ).push( org + F() ); break;
    case 120 : // 8 + 16 + 32 + 64
        pts.push( org + J() ).push( org + K() ).push( org + C() )
           .push( org + J() ).push( org + I() ).push( org + D() )
           .push( org + J() ).push( org + D() ).push( org + C() )
           .push( org + H() ).push( org + L() ).push( org + G() ); break;
    case 225 : // 1 + 32 + 64 + 128
        pts.push( org + K() ).push( org + L() ).push( org + D() )
           .push( org + K() ).push( org + J() ).push( org + A() )
           .push( org + K() ).push( org + A() ).push( org + D() )
           .push( org + E() ).push( org + I() ).push( org + H() ); break;

    // 4F VERTICES

    case 165 : // 1 + 4 + 32 + 128
        pts.push( org + A() ).push( org + B() ).push( org + J() )
           .push( org + C() ).push( org + L() ).push( org + D() )
           .push( org + I() ).push( org + H() ).push( org + E() )
           .push( org + K() ).push( org + F() ).push( org + G() ); break;
    case 90  : // 2 + 8 + 16 + 64
        pts.push( org + A() ).push( org + D() ).push( org + I() )
           .push( org + B() ).push( org + K() ).push( org + C() )
           .push( org + E() ).push( org + F() ).push( org + J() )
           .push( org + L() ).push( org + G() ).push( org + H() ); break;
    }
}

}
