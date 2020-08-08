
#include <cvpp/containers/matrix.h>
#include <cvpp/containers/vector.h>

using namespace cvpp;

int main()
{
    Matd mat( 10 );
    mat.setIncrease().print();

    Vecd vec( 10 );
    vec.setIncrease().print();

//    Pts2d pts( 30 );

    return 0;
}
