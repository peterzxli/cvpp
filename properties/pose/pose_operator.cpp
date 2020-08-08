#include "../pose.h"

namespace cvpp
{

TPL_T Pose<T>&
Pose<T>::operator+=( const Pose<T>& pose )
{
    pos += pose.pos;
    orient = pose.orient * orient;
    return update();
}

TPL_T Pose<T>&
Pose<T>::operator-=( const Pose<T>& pose )
{
    pos -= pose.pos;
    orient = pose.orient.inverse() * orient;
    return update();
}

TPL_T Pose<T>
Pose<T>::operator+( const Pose<T>& pose )
{
    Pose tmp( *this ); tmp += pose;
    return tmp;
}

TPL_T Pose<T>
Pose<T>::operator-( const Pose<T>& pose )
{
    Pose tmp( *this ); tmp -= pose;
    return tmp;
}

}
