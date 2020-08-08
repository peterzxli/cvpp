#include "../pose.h"

namespace cvpp
{

// Load
TPL_T Pose<T>&
Pose<T>::load( const String &str )
{
    IFile file( str.c_str() );
    if( file.is_open() )
    {
        file >> pos(0) >> pos(1) >> pos(2)
             >> orient.w() >> orient.x() >> orient.y() >> orient.z();
        file.close();
    }
    return update();
}

// Save
TPL_T void
Pose<T>::save( const String &str ) const
{
    OFile file( str.c_str() );
    if( file.is_open() )
    {
        file << std::fixed << std::setprecision(10)
             << pos(0) << "  " << pos(1) << "  " << pos(2) << "\n"
             << orient.w() << "  " << orient.x() << "  " << orient.y() << "  " << orient.z() << "\n" ;
        file.close();
    }
}

// Set Pos
TPL_T Pose<T>&
Pose<T>::setPos( const T& x , const T& y , const T& z )
{
    pos.eig() << x , y , z;
    return update();
}

// Set Pos
TPL_T Pose<T>&
Pose<T>::setPos( const Matrix<T>& mat )
{
    pos = mat;
    return update();
}

// Set Pos
TPL_T Pose<T>&
Pose<T>::setPos( const Pt3<T>& pt )
{
    pos.eig() << pt.x , pt.y , pt.z ;
    return update();
}

// Set Pose
TPL_T Pose<T>&
Pose<T>::setPose( const Pose<T>& pose )
{
    pos = pose.getPos();
    orient = pose.getOrient();
    return update();
}

// Set Pose
TPL_T Pose<T>&
Pose<T>::setPose( const T& px , const T& py , const T& pz ,
                  const T& qw , const T& qx , const T& qy , const T& qz )
{
    setPos( px , py , pz );
    setOrient( qw , qx , qy , qz );
    return update();
}

// Set Pose
TPL_T Pose<T>&
Pose<T>::setPose( const T& px , const T& py , const T& pz ,
                  const T& ar , const T& ap , const T& aw )
{
    setPos( px , py , pz );
    setOrient( ar , ap , aw );
    return update();
}

// Set Pose
TPL_T Pose<T>&
Pose<T>::setPose( const Matrix<T>& mat )
{
    if( ( mat.r() == 4 && mat.c() == 4 ) ||
        ( mat.r() == 3 && mat.c() == 4 ) )
    {
        setPos( mat.b(0,3,3,1).clone() );
        setOrient( mat.b(0,0,3,3).clone() );
    }

    if( mat.r() == 6 && mat.c() == 1 ||
        mat.r() == 1 && mat.c() == 6 )
    {
        setPos( mat(0) , mat(1) , mat(2) );
        setOrient( mat(3) , mat(4) , mat(5) );
    }

    return update();
}

TPL_T Pose<T>&
Pose<T>::setPose( const Pose<T>& pose1 , const Pose<T>& pose2 , const T& t )
{
    setPos( pose1.getPos() + t * ( pose2.getPos() - pose1.getPos() ) );
    setOrient( pose1.getOrient().slerp( t , pose2.getOrient() ) );
    return update();
}


// Set Look
TPL_T Pose<T>&
Pose<T>::setLook( const T& x , const T& y , const T& z )
{
    Matrix<T> vec(3);
    vec.eig() << x , y , z;

    Matrix<T> tmp1 = look - pos;
    Matrix<T> tmp2 = vec  - pos;

    Quat<T> rot;
    rot.setFromTwoVectors( tmp1.raw() , tmp2.raw() );
    orient *= rot;

    return align();
}

// Set Look
TPL_T Pose<T>&
Pose<T>::setLook( const Matrix<T>& mat )
{
    return setLook( mat(0) , mat(1) , mat(2) );
}

// Set Look
TPL_T Pose<T>&
Pose<T>::setLook( const Pt3<T>& pt )
{
    return setLook( pt.x , pt.y , pt.z );
}

// Set Orient
TPL_T Pose<T>&
Pose<T>::setOrient( const Quat<T>& orient )
{
    this->orient = orient;
    return update();
}

// Set Orient
TPL_T Pose<T>&
Pose<T>::setOrient( const T& w , const T& x , const T& y , const T& z )
{
    orient = Quat<T>( w , x , y , z );
    return update();
}

// Set Orient
TPL_T Pose<T>&
Pose<T>::setOrient( const T& r , const T& p , const T& w )
{
    orient = Quat<T>( Eigen::AngleAxis<T>( w , Eig3<T>::UnitZ() ) *
                      Eigen::AngleAxis<T>( p , Eig3<T>::UnitY() ) *
                      Eigen::AngleAxis<T>( r , Eig3<T>::UnitX() ) );

    return update();
}

// Set Orient
TPL_T Pose<T>&
Pose<T>::setOrient( const Matrix<T>& rot )
{
    orient = Quat<T>( Eig33<T>( rot.raw() ) );
    return update();
}

// Set Orient
TPL_T Pose<T>&
Pose<T>::setOrient( const CV& rot )
{
    Matrix<T> mat( rot , COPY );
    return setOrient( mat );
}

}
