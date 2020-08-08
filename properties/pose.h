#ifndef POSE_H
#define POSE_H

#include <cvpp/containers/vector.h>

namespace cvpp
{

TPL_T
class Pose
{

protected:

    Matrix<T> pos,look,up,rot,trans;
    Quat<T> orient;

public:

    Pose();
    Pose( const Pose& );

    ~Pose();

    Pose<T>& reset();
    Pose<T>& update();
    Pose<T>& align();

    void print() const;

    // GET

    const T& x() const { return pos(0); }
    const T& y() const { return pos(1); }
    const T& z() const { return pos(2); }

    const T& px() const { return pos(0); }
    const T& py() const { return pos(1); }
    const T& pz() const { return pos(2); }

    const T& pi( const int& i ) const
    { if( i == 0 ) return px() ; if( i == 1 ) return py(); if ( i == 2 ) return pz(); }

    const T& lx() const { return look(0); }
    const T& ly() const { return look(1); }
    const T& lz() const { return look(2); }

    const T& ux() const { return up(0); }
    const T& uy() const { return up(1); }
    const T& uz() const { return up(2); }

    const T qw() const { return orient.w(); }
    const T qx() const { return orient.x(); }
    const T qy() const { return orient.y(); }
    const T qz() const { return orient.z(); }

    const T qi( const int& i ) const
    { if( i == 0 ) return qx() ; if( i == 1 ) return qy(); if ( i == 2 ) return qz(); }

    const T r() const { return atan2( 2.0 * ( qw() * qx() + qy() * qz() ) ,
                                      1.0 - 2.0 * ( qx() * qx() + qy() * qy() ) ); }

    const T p() const { return asin( 2.0 * ( qw() * qy() - qz() * qx() ) ); }

    const T w() const { return atan2( 2.0 * ( qw() * qz() + qx() * qy() ) ,
                                      1.0 - 2.0 * ( qy() * qy() + qz() * qz() ) ); }

    const Matrix<T>& t()  const { return pos;   }
    const Matrix<T>& R()  const { return rot;   }
    const Matrix<T>& Rt() const { return trans; }

    const Matrix<T>& getPos()  const { return pos;  }
    const Matrix<T>& getLook() const { return look; }
    const Matrix<T>& getUp()   const { return up;   }

    const Quat<T>& getOrient() const { return orient; }

    Pt3<T> getPosPt() const { return Pt3<T>( x() , y() , z() );  }

    // SET

    Pose<T>& load( const String& );
    void save( const String& ) const;

    Pose<T>& setPos( const Pt3<T>& );
    Pose<T>& setPos( const Matrix<T>& );
    Pose<T>& setPos( const T& , const T& , const T& );

    Pose<T>& setLook( const Pt3<T>& );
    Pose<T>& setLook( const Matrix<T>& );
    Pose<T>& setLook( const T& , const T& , const T& );

    Pose<T>& setOrient( const Quat<T>& );
    Pose<T>& setOrient( const T& , const T& , const T& , const T& );

    Pose<T>& setOrient( const CV& );
    Pose<T>& setOrient( const Matrix<T>& );
    Pose<T>& setOrient( const T& , const T& , const T& );

    Pose<T>& setPose( const Pose<T>& );
    Pose<T>& setPose( const Pointer< Pose<T> >& pose ) { return setPose( *pose ); }

    Pose<T>& setPose( const Matrix<T>& );
    Pose<T>& setPose( const T& , const T& , const T& ,
                      const T& , const T& , const T& );
    Pose<T>& setPose( const T& , const T& , const T& ,
                      const T& , const T& , const T& , const T& );
    Pose<T>& setPose( const Pose<T>& , const Pose<T>& , const T& );

    Pose<T>& setPose( const String& str )
    { Matrix<T> tmp( str ); return setPose( tmp ); }

    // CHANGE

    Pose<T>& moveX( const T& );
    Pose<T>& moveY( const T& );
    Pose<T>& moveZ( const T& );

    Pose<T>& moveXY( const T& , const T& );

    Pose<T>& moveXYZ( const T& , const T& , const T& );
    Pose<T>& moveXYZ( const Pt3f& pt ) { return moveXYZ( pt.x , pt.y , pt.z ); }

    Pose<T>& rotateX( const T& );
    Pose<T>& rotateY( const T& );
    Pose<T>& rotateZ( const T& );

    Pose<T>& rotateXYZ( const T& r , const T& p , const T& w )
    { return rotateX( r ).rotateY( p ).rotateZ( w ); }

    Pose<T>& rotatePos( const Matrix<T>& );

    Pose<T>& scale( const T& );

    void o2w( const Matrix<T>& , Matrix<T>& ) const;
    void w2o( const Matrix<T>& , Matrix<T>& ) const;

    void o2w( const Pts3<T>& obj , Pts3<T>& wld ) const { o2w( obj.mat() , wld.mat() ); }
    void w2o( const Pts3<T>& wld , Pts3<T>& obj ) const { w2o( wld.mat() , obj.mat() ); }

    Matrix<T> o2w( const Matrix<T>& src ) const { Matrix<T> dst( src.r() , 3 ); o2w( src , dst ); return dst; }
    Matrix<T> w2o( const Matrix<T>& src ) const { Matrix<T> dst( src.r() , 3 ); w2o( src , dst ); return dst; }

    Pts3<T> o2w( const Pts3<T>& src ) const { Pts3<T> dst( src.n() ); o2w( src , dst ); return dst; }
    Pts3<T> w2o( const Pts3<T>& src ) const { Pts3<T> dst( src.n() ); w2o( src , dst ); return dst; }

    // OPERATOR

    Pose<T>& operator+=( const Pose<T>& );
    Pose<T>& operator-=( const Pose<T>& );

    Pose<T>& operator+=( const Pointer< Pose<T> >& pose ) { return operator+=( *pose ); }
    Pose<T>& operator-=( const Pointer< Pose<T> >& pose ) { return operator-=( *pose ); }

    Pose<T> operator+( const Pose<T>& );
    Pose<T> operator-( const Pose<T>& );

    Pose<T> operator+( const Pointer< Pose<T> >& pose ) { return operator+( *pose ); }
    Pose<T> operator-( const Pointer< Pose<T> >& pose ) { return operator-( *pose ); }

};

using Posef = Pose<float>;
using Posed = Pose<double>;

using SeqPosef = Seq<Posef>;
using SeqPosed = Seq<Posed>;

}

#endif
