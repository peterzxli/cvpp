#include "../pose.h"

namespace cvpp
{

// Move X
TPL_T Pose<T>&
Pose<T>::moveX( const T& x )
{
    pos.eig() += orient._transformVector( x * Eig3<T>::UnitX() );
    return update();
}

// Move Y
TPL_T Pose<T>&
Pose<T>::moveY( const T& y )
{
    pos.eig() += orient._transformVector( y * Eig3<T>::UnitY() );
    return update();
}

// Move Z
TPL_T Pose<T>&
Pose<T>::moveZ( const T& z )
{
    pos.eig() += orient._transformVector( z * Eig3<T>::UnitZ() );
    return update();
}

// Move XY
TPL_T Pose<T>&
Pose<T>::moveXY( const T& x , const T& y )
{
    pos.eig() += orient._transformVector( x * Eig3<T>::UnitX() );
    pos.eig() += orient._transformVector( y * Eig3<T>::UnitY() );
    return update();
}

// Move XYZ
TPL_T Pose<T>&
Pose<T>::moveXYZ( const T& x , const T& y , const T& z )
{
    pos.eig() += orient._transformVector( x * Eig3<T>::UnitX() );
    pos.eig() += orient._transformVector( y * Eig3<T>::UnitY() );
    pos.eig() += orient._transformVector( z * Eig3<T>::UnitZ() );
    return update();
}

// Scale
TPL_T Pose<T>&
Pose<T>::scale( const T& scl )
{
    pos *= scl;
    return update();
}

// Rotate X
TPL_T Pose<T>&
Pose<T>::rotateX( const T& deg )
{
    T rad = deg * PI / 360;
    T c = cos(rad) , s = sin(rad);

    orient *= Quat<T>( c , s , 0 , 0 );
    orient.normalize();

    return update();
}

// Rotate Y
TPL_T Pose<T>&
Pose<T>::rotateY( const T& deg )
{
    T rad = deg * PI / 360;
    T c = cos(rad) , s = sin(rad);

    orient *= Quat<T>( c , 0 , s , 0 );
    orient.normalize();

    return update();
}

// Rotate Z
TPL_T Pose<T>&
Pose<T>::rotateZ( const T& deg )
{
    T rad = deg * PI / 360;
    T c = cos(rad) , s = sin(rad);

    orient *= Quat<T>( c , 0 , 0 , s );
    orient.normalize();

    return update();
}

// Rotate Pos
TPL_T Pose<T>&
Pose<T>::rotatePos( const Matrix<T>& R )
{
    pos = ( pos.t() * R ).t();
    return update();
}

// Object to World
TPL_T void
Pose<T>::o2w( const Matrix<T>& obj , Matrix<T>& wld ) const
{
    wld = obj * R().transpose() + t().transpose();
}

// World to Object
TPL_T void
Pose<T>::w2o( const Matrix<T>& wld , Matrix<T>& obj ) const
{
    obj = ( wld - t().transpose() ) * R();
}

}
