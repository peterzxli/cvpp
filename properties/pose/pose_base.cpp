#include "../pose.h"

namespace cvpp
{

TPL_T // New Constructor
Pose<T>::Pose()
{
    trans.reset(4,4).setIdentity();
    pos >> trans.b(0,3,3,1);
    rot >> trans.b(0,0,3,3);

    orient.setIdentity();
    look.reset(3); up.reset(3);

    update();
}

TPL_T // Copy Constructor
Pose<T>::Pose( const Pose& pose )
{
    setPose( pose );
    update();
}

TPL_T // Destructor
Pose<T>::~Pose()
{
}

// Reset
TPL_T Pose<T>&
Pose<T>::reset()
{
    pos.setVal( 0 );
    orient.setIdentity();
    return update();
}

// Update
TPL_T Pose<T>&
Pose<T>::update()
{
    Quat<T> quat = orient;
    T scale = quat.norm();

    quat.coeffs() /= scale;
    rot.eig() = quat.toRotationMatrix() * scale;

    look.eig() = pos.eig() + orient._transformVector( Eig3<T>::UnitX() );
    up.eig() = orient._transformVector( Eig3<T>::UnitZ() );

    return *this;
}

// Update
TPL_T Pose<T>&
Pose<T>::align()
{
    rotateX( - atan2( 2.0 * ( qw() * qx() + qy() * qz() ) ,
                1.0 - 2.0 * ( qx() * qx() + qy() * qy() ) ) * 180 / PI );

    return *this;
}

// Print
TPL_T void
Pose<T>::print() const
{
    std::cout << px() << " " << py() << " " << pz() << " : "
              << qw() << " " << qx() << " " << qy() << " " << qz() << std::endl;
}

}
