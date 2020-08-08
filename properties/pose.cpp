
#include "./pose/pose_base.cpp"
#include "./pose/pose_change.cpp"
#include "./pose/pose_operator.cpp"
#include "./pose/pose_set.cpp"

namespace cvpp
{
    template class Pose<float>;
    template class Pose<double>;
}
